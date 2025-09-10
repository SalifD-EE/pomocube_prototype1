#define TEST_MODE 0  //1 enables shorter default times for easy testing

//--------------------GFX SETUP--------------------
#include <Wire.h>  //Aaaaahhh, wire...
#include <Adafruit_GFX.h>
#include <Fonts/FreeSansBold18pt7b.h>  //Font used in displayTime()
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C

//--------------------PINS--------------------
#define CLK_PIN 2
#define DT_PIN 3
#define SW_PIN 4
#define BUZZER_PIN 8
#define CLK_DEBOUNCE_DELAY 2
#define SW_DEBOUNCE_DELAY 200

//--------------------BUZZER--------------------
#define BUZZER_BEEP_FREQ 1000
#define BUZZER_BEEP_DURATION 30

unsigned long buzzStartTime = 0;
unsigned long noteStartTime = 0;
int currentNote = -1;  // -1 = not playing

struct Note {
  int frequency;   // 0 for silence
  int duration;    // how long to play this note
  int pauseAfter;  // how long to wait before next note (0 = end sequence)
};

Note* currentSequence;

Note seesionEndSequence[] = {
  { BUZZER_BEEP_FREQ, 140, 200 },
  { BUZZER_BEEP_FREQ, 140, 750 },
  { BUZZER_BEEP_FREQ, 140, 200 },
  { BUZZER_BEEP_FREQ, 140, 750 },
  { 0, 0, 0 },
};

Note pomodoroCompleteSequence[] = {
  { BUZZER_BEEP_FREQ, 80, 115 },
  { BUZZER_BEEP_FREQ, 80, 115 },
  { BUZZER_BEEP_FREQ, 80, 115 },
  { BUZZER_BEEP_FREQ, 80, 600 },
  { BUZZER_BEEP_FREQ, 80, 115 },
  { BUZZER_BEEP_FREQ, 80, 115 },
  { BUZZER_BEEP_FREQ, 80, 115 },
  { BUZZER_BEEP_FREQ, 80, 570 },
  { 0, 0, 0 },
};


//--------------------TIME MANAGEMENT--------------------
#define MILLIS_IN_SEC 1000
#define MILLIS_IN_MIN 60000
#define TIME_INCREMENT 300000  //05:00
#define MAX_TIMER_VAL 3300000  //55:00
#define TICK_RATE 60           //Avoids overflows at the end of sessions


/*The additional 999 ms allows the total duration to actually be shown when a segment begins,
otherwise, timers start at 24:59 rather than 25:00.*/
#if TEST_MODE == 0
unsigned long workDuration = 1500000 + 999;   //25 minutes
unsigned long sBreakDuration = 300000 + 999;  //5 minutes
unsigned long lBreakDuration = 900000 + 999;  //15 minutes
#endif

//Super short durations for testing
#if TEST_MODE == 1
unsigned long workDuration = 5000 + 999;    //5 seconds
unsigned long sBreakDuration = 5000 + 999;  //5 seconds
unsigned long lBreakDuration = 5000 + 999;  //5 seconds
#endif

unsigned long timerStartTime = 0;
unsigned long pauseStartTime = 0;

unsigned long elapsedTime = 0;
unsigned long elapsedPauseTime = 0;

bool sessionStart = false;
int completedWorkSessions = 0;
int totalWorkSessions = 4;

unsigned long minDisplay = 0;
unsigned long secDisplay = 0;
char timeBuffer[6];  //Time is formatted as MM:SS\0, so it's always 6 bytes

//--------------------MENU MANAGEMENT--------------------
byte menuItem = 1;
bool selected = false;
volatile bool cw = false;
volatile bool ccw = false;

//--------------------ROTATION MANAGEMENT--------------------
volatile int currentStateCLK;
volatile int previousStateCLK;
volatile unsigned long lastEncoderTime = 0;

//--------------------BUTTON MANAGEMENT--------------------
int btnState;
unsigned long lastButtonPress = 0;

//--------------------FSM MANAGEMENT--------------------
enum State {
  WORK,
  S_BREAK,
  L_BREAK,
  PAUSE,
  MENU
};

State currentState = MENU;
State previousState = NULL;

//--------------------DISPLAY MANAGEMENT--------------------

//Manages the blinking timer while paused
#define BLINK_FREQ 600
bool displayIsBlank = false;
unsigned long lastBlink = 0;

//Used to center text
int16_t x1, y1;
uint16_t w, h;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//--------------------HELPER FUNCTIONS--------------------

/*---------------------------------------------------------------
NAME: formatTime
DESCRIPTION: Converts the supplied time into text that can be used with displayTime,
             then stores the resulting string in timeBuffer.
INPUT: time -> The time in ms to convert.
       timeBuffer -> The string where the converted time will be stored.
OUTPUT: None.
SPECS: None.
---------------------------------------------------------------*/
void formatTime(unsigned long time, char* timeBuffer) {
  // The modulo is to maintain base 60
  minDisplay = time / MILLIS_IN_MIN % 60;
  secDisplay = time / MILLIS_IN_SEC % 60;

  // Format the time and copy it into the buffer
  sprintf(timeBuffer, "%02ld:%02ld", minDisplay, secDisplay);
}

/*---------------------------------------------------------------
NAME: displayTime
DESCRIPTION: Displays the time currently stored in timeBuffer.
INPUT: None.
OUTPUT: None.
SPECS: None.
---------------------------------------------------------------*/
void displayTime() {
  int xOffset;  //Keeps things centered with the font used

  display.setFont(&FreeSansBold18pt7b);
  display.setTextColor(WHITE);
  display.getTextBounds(timeBuffer, 0, 0, &x1, &y1, &w, &h);

  /*Sans Bold isn't a monospace font, so in a few special cases,
    we need a different offset to stay centered*/
  if (timeBuffer[4] == '1') {
    xOffset = -4;
  } else if (timeBuffer[4] == '6') {
    xOffset = -1;
  } else {
    xOffset = -2;
  }

  display.setCursor((SCREEN_WIDTH / 2) - (w / 2) + xOffset, 48);
  display.print(timeBuffer);
  display.display();
}

/*---------------------------------------------------------------
NAME: updateEncoder
DESCRIPTION: ISR triggered when a rotation is detected.
             Updates the internal rotation states.
INPUT: None.
OUTPUT: None.
SPECS: None.
---------------------------------------------------------------*/
void updateEncoder() {
  //Read the state of clk
  currentStateCLK = digitalRead(CLK_PIN);

  if (millis() - lastEncoderTime > CLK_DEBOUNCE_DELAY) {
    if (currentStateCLK != previousStateCLK) {
      previousStateCLK = currentStateCLK;
      byte data = digitalRead(DT_PIN);

      if (data && currentStateCLK == LOW) {
        cw = true;
      } else if (!data && currentStateCLK == LOW) {
        ccw = true;
      }
    }
    lastEncoderTime = millis();
  }
}

/*---------------------------------------------------------------
NAME: manageRotation
DESCRIPTION: Takes action if a new command is received from the encoder.
INPUT: None.
OUTPUT: None.
SPECS: Works with the internal rotation state, NOT the inputs from the pins.
       See updateEncoder for that.
---------------------------------------------------------------*/
void manageRotation() {
  if (ccw && !selected) {
    ccw = false;
    menuItem--;

    if (menuItem == 0) { menuItem = 4; }

  } else if (ccw && selected) {
    ccw = false;

    switch (menuItem) {
      case 1:
        if (workDuration > 0) workDuration -= TIME_INCREMENT;
        break;
      case 2:
        if (sBreakDuration > 0) sBreakDuration -= TIME_INCREMENT;
        break;
      case 3:
        if (lBreakDuration > 0) lBreakDuration -= TIME_INCREMENT;
        break;
    }
  }

  if (cw && !selected) {
    cw = false;
    menuItem++;

    if (menuItem == 5) { menuItem = 1; }

  } else if (cw && selected) {
    cw = false;

    switch (menuItem) {
      case 1:
        if (workDuration < MAX_TIMER_VAL) workDuration += TIME_INCREMENT;
        break;
      case 2:
        if (sBreakDuration < MAX_TIMER_VAL) sBreakDuration += TIME_INCREMENT;
        break;
      case 3:
        if (lBreakDuration < MAX_TIMER_VAL) lBreakDuration += TIME_INCREMENT;
        break;
    }
  }
}

/*---------------------------------------------------------------
NAME: displayTopBar 
DESCRIPTION: Displays text at the top of the screen with a horizontal line.
INPUT: text -> The string to display.
OUTPUT: None.
SPECS: Automatically displays session stats unless in the menu.
---------------------------------------------------------------*/
void displayTopBar(char* text) {
  char fullText[100];

  display.setFont();  //Resets font to default
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);

  if (currentState != MENU) {
    sprintf(fullText, "%s - %d/%d", text, completedWorkSessions + 1, totalWorkSessions);
  } else {
    strcpy(fullText, text);
  }

  // Get bounds for the complete text
  display.getTextBounds(fullText, 0, 0, &x1, &y1, &w, &h);
  display.setCursor((SCREEN_WIDTH / 2) - (w / 2), 0);  // Centers text on x-axis
  display.print(fullText);

  display.drawFastHLine(0, 10, 128, WHITE);
}

/*---------------------------------------------------------------
NAME: displayMenu
DESCRIPTION: Displays the main menu.
INPUT: None.
OUTPUT: None.
SPECS: selected -> level 1, !selected -> level 2.
---------------------------------------------------------------*/
void displayMenu() {
  // Create Menu Pages
  display.clearDisplay();

  displayTopBar("Main menu");

  if (menuItem == 1 && !selected) {
    display.setTextColor(BLACK, WHITE);
  } else {
    display.setTextColor(WHITE, BLACK);
  }
  display.setCursor(0, 15);
  display.print("> Work: ");

  if (menuItem == 1 && selected) {
    display.setTextColor(BLACK, WHITE);
  } else {
    display.setTextColor(WHITE, BLACK);
  }
  display.setCursor(98, 15);

  formatTime(workDuration, timeBuffer);
  display.print(timeBuffer);

  if (menuItem == 2 && !selected) {
    display.setTextColor(BLACK, WHITE);
  } else {
    display.setTextColor(WHITE, BLACK);
  }
  display.setCursor(0, 25);
  display.print("> S.Break: ");

  if (menuItem == 2 && selected) {
    display.setTextColor(BLACK, WHITE);
  } else {
    display.setTextColor(WHITE, BLACK);
  }
  display.setCursor(98, 25);
  formatTime(sBreakDuration, timeBuffer);
  display.print(timeBuffer);


  if (menuItem == 3 && !selected) {
    display.setTextColor(BLACK, WHITE);
  } else {
    display.setTextColor(WHITE, BLACK);
  }
  display.setCursor(0, 35);
  display.print("> L.Break: ");

  if (menuItem == 3 && selected) {
    display.setTextColor(BLACK, WHITE);
  } else {
    display.setTextColor(WHITE, BLACK);
  }
  display.setCursor(98, 35);
  formatTime(lBreakDuration, timeBuffer);
  display.print(timeBuffer);


  if (menuItem == 4 && !selected) {
    display.setTextColor(BLACK, WHITE);
  } else {
    display.setTextColor(WHITE, BLACK);
  }
  display.getTextBounds(" Start ", 0, 0, &x1, &y1, &w, &h);
  display.setCursor(SCREEN_WIDTH / 2 - (w - x1) / 2, 50);
  display.print(" Start ");

  display.display();
}

/*---------------------------------------------------------------
NAME: startBeepSequence
DESCRIPTION: Plays the first note of the supplied sequence.
INPUT: Note* sequence -> Array containing the Notes to be played.
OUTPUT: None
SPECS: Only call this function once to start a sequence.
       updateBeepSequence then takes care of the rest automagically.
---------------------------------------------------------------*/
void startBeepSequence(Note* sequence) {
  currentSequence = sequence;
  currentNote = 0;
  noteStartTime = millis();
  tone(BUZZER_PIN, currentSequence[0].frequency, currentSequence[0].duration);
}

/*---------------------------------------------------------------
NAME: updateBeepSequence
DESCRIPTION: Checks if a sequence is currently playing and plays 
             the next Note if the previous Note's pause has elapsed.
             Once the last Note is reached, the sequence automatically ends.
INPUT: None
OUTPUT: None
SPECS: This function only works if startBeepSequence is called first.
---------------------------------------------------------------*/
void updateBeepSequence() {
  if (currentNote == -1) return;

  if (millis() - noteStartTime >= currentSequence[currentNote].pauseAfter) {

    if (currentSequence[currentNote].pauseAfter == 0) {
      // Sequence complete
      noTone(BUZZER_PIN);
      currentNote = -1;
      return;
    }

    // Move to next step
    currentNote++;
    noteStartTime = millis();

    // Start next note if it's not silence
    if (currentSequence[currentNote].frequency > 0) {
      tone(BUZZER_PIN, currentSequence[currentNote].frequency, currentSequence[currentNote].duration);
    }
  }
}

//--------------------MAIN PROGRAM--------------------
void setup() {
  Serial.begin(9600);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(CLK_PIN, INPUT_PULLUP);
  pinMode(DT_PIN, INPUT_PULLUP);
  pinMode(SW_PIN, INPUT_PULLUP);

  // Initialize the OLED object
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;  // Don't proceed, loop forever
  }
  display.clearDisplay();

  // Read the initial state of CLK_PIN
  // Assign to previousStateCLK variable
  previousStateCLK = digitalRead(CLK_PIN);

  //Use an interrupt to ensure rotation inputs are read every time
  attachInterrupt(digitalPinToInterrupt(CLK_PIN), updateEncoder, CHANGE);
}

void loop() {
  //--------------------ROTARY LOGIC--------------------

  // Read the button state
  btnState = digitalRead(SW_PIN);

  //If we detect LOW signal, button is pressed
  if (btnState == LOW) {
    //if 200ms have passed since last LOW pulse, it means that the
    //button has been pressed, released and pressed again
    if (millis() - lastButtonPress > SW_DEBOUNCE_DELAY) {

      tone(BUZZER_PIN, BUZZER_BEEP_FREQ, BUZZER_BEEP_DURATION);

      //Behavior in menu
      if (currentState == MENU && menuItem == 4) {
        selected = false;  //Not useful now, but it will be when I add cancellation
        sessionStart = true;
        currentState = WORK;
      } else if (currentState == MENU && menuItem != 4) {
        selected = !selected;
      } else {  //This line stops the timer from pausing instantly after starting a session

        //Behavior during session
        if (currentState != MENU && currentState != PAUSE) {

          // Serial.println("Paused");
          previousState = currentState;
          currentState = PAUSE;
          pauseStartTime = millis();

        } else if (currentState != MENU && currentState == PAUSE) {

          // Serial.println("Unpaused");
          elapsedPauseTime += millis() - pauseStartTime;  //Accumulate the time "lost" while paused.
          currentState = previousState;
          previousState = PAUSE;
        }
      }
    }

    // Remember last button press event
    lastButtonPress = millis();
  }

  //--------------------TIMER LOGIC--------------------

  //Reset timer data when starting a session
  if (sessionStart) {
    elapsedTime = 0;
    elapsedPauseTime = 0;
    timerStartTime = millis();
    sessionStart = false;
  }

  switch (currentState) {
    case MENU:
      manageRotation();
      displayMenu();
      break;

    case PAUSE:
      if (millis() - lastBlink >= BLINK_FREQ) {

        if (displayIsBlank) {
          display.clearDisplay();
          displayTopBar("Pause");
        } else {
          display.clearDisplay();
          displayTopBar("Pause");
          displayTime();
        }
        displayIsBlank = !displayIsBlank;
        lastBlink = millis();
      }
      display.display();
      break;

    case WORK:
      //Update the timer unless we're less than 1 tick away from 0
      if (workDuration - elapsedTime > TICK_RATE) {
        elapsedTime = millis() - timerStartTime - elapsedPauseTime;
      } else {
        if (completedWorkSessions < totalWorkSessions - 1) {
          startBeepSequence(seesionEndSequence);
          currentState = S_BREAK;
          sessionStart = true;
        } else {
          startBeepSequence(pomodoroCompleteSequence);
          currentState = L_BREAK;
          sessionStart = true;
          break;
        }
      }

      display.clearDisplay();
      displayTopBar("Focus");
      formatTime(workDuration - elapsedTime, timeBuffer);
      displayTime();
      break;

    case S_BREAK:
      if (sBreakDuration - elapsedTime > TICK_RATE) {
        elapsedTime = millis() - timerStartTime - elapsedPauseTime;
      } else {
        startBeepSequence(seesionEndSequence);
        ++completedWorkSessions;
        currentState = WORK;
        sessionStart = true;
        break;
      }

      display.clearDisplay();
      displayTopBar("S. Break");
      formatTime(sBreakDuration - elapsedTime, timeBuffer);
      displayTime();
      break;

    case L_BREAK:
      if (lBreakDuration - elapsedTime > TICK_RATE) {
        elapsedTime = millis() - timerStartTime - elapsedPauseTime;
      } else {
        startBeepSequence(seesionEndSequence);
        currentState = WORK;
        sessionStart = true;
        completedWorkSessions = 0;
        break;
      }

      display.clearDisplay();
      displayTopBar("L. Break");
      formatTime(lBreakDuration - elapsedTime, timeBuffer);
      displayTime();
      break;
  }

  updateBeepSequence();
}