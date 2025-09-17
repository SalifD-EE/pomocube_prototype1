<a id="readme-top"></a>

<div align="center">
  <h1 align="center">Project Pomocube - Prototype 1</h1>

  <p align="center">
    A simple, no BS pomodoro timer &middot; <a href="https://github.com/othneildrew/Best-README-Template">View Demo</a>
    <br />
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#introduction">Introduction</a></li>
        <li><a href="#what-the-hell-is-a-pomodoro">What the Hell is a Pomodoro?</a></li>
      </ul>
    </li>
    <li>
      <a href="#parts-selection">Parts Selection</a>
      <ul>
        <li><a href="#bill-of-materials">Bill of Materials</a></li>
        <li><a href="#microcontroller">Microcontroller</a></li>
        <li><a href="#display">Display</a></li>
        <li><a href="#rotary-encoder">Rotary Encoder</a></li>
        <li><a href="#passive-buzzer">Passive Buzzer</a></li>
        <li><a href="#wiring-diagram">Wiring Diagram</a></li>
      </ul>
    </li>
    <li>
      <a href="#the-process">The Process</a>
      <ul>
        <li><a href="#getting-the-encoder-working">Getting the Encoder Working</a></li>
        <li><a href="#displaying-a-timer">Displaying a Timer</a></li>
        <li><a href="#creating-a-fsm">Creating a Finite State Machine (FSM)</a></li>
        <li><a href="#implementing-a-pause-feature">Implementing a Pause Feature</a></li>
        <li><a href="#creating-a-main-menu">Creating a Main Menu</a></li>
        <li><a href="#implementing-a-buzzer">Implementing a Buzzer</a></li>
        <li><a href="#tying-it-all-together">Tying it All Together</a></li>
      </ul>
    </li>
    <li><a href="#final-result">Final Result</a></li>
    <li><a href="#conclusion">Conclusion</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
<a id="about-the-project"></a>
## About The Project

<a id="introduction"></a>
### Introduction

As an electrical engineering student, I'm well-aware that just getting the degree isn't nearly enough to set yourself apart when looking for a job or an internship, <em>especially</em> not in this job market.
A common strategy to counter that is to work on personal projects in your free time, but I'm also an engineer, so I may as well use that as a chance to fix a problem in my life. Enter the Pomocube.

<a id="what-the-hell-is-a-pomodoro"></a>
### What the Hell is a Pomodoro?

Named after the tomato-shaped kitchen timer, the pomodoro technique is a way to stay focused for long periods of time. You work for 25 minutes, then take a 5 minute break, and repeat the process 3 more times, with a longer break at the end.
By taking small, regular breaks, you allow your attention-span to recharge, keeping you more productive overall. Plus, you always have a small reward to look forward too. Everyone is obviously different, but I have personally had
great success with this technique both to study and work.

Of course, there are a lot of pomodoro apps out there, and I've used my share over the years (my favorite is [Flow](https://www.flow.app/)).
With that said, you may wonder why I'm taking on this project. Here are a couple of reasons:

* I need a personal project, and this strikes a perfect balance between simplicity, relevance, and usefulness.
* Desktop pomodoro apps often take up valuable screen real-estate, and sometimes don't sync between platforms.
* Phone apps consume precious battery, require a stand and force you to keep your phone near you.
* Regardless of the device used, you're downloading <em>yet another app</em>, and I'm SICK of apps.

That's when I started thinking about creating a cute little physical timer that's stylish, delightful to use and can be carried anywhere.
I want the device to be simple and single-purpose, a short reprieve from today's hyper-connected slabs of glass and metal.
Here's a quick little render of what I picture the final version looking like:
(photo)

Engineering and learning both take time, so I chose to work in iterations rather than try to reach this final result right away. This first prototype aims to 
implement some basic functionality. Later revisions will use different parts and feature extended functionality.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- PARTS SELECTION -->
<a id="parts-selection"></a>
## Parts Selection

Continuing the theme of simplicity, this project requires very few parts to get working.

<a id="bill-of-materials"></a>
### Bill of Materials

| Description | Part Number | Quantity | Unit Cost (CAD) |
|---|---|---|---|
| ELEGOO Arduino Uno R3 w/ ATmega328P | EL-CB-001 | 1 | $24.99 |
| GeeekPi 0.96" Monochrome OLED | - | 1 | $4.80 |
| Cylewet KY-40 Rotary Encoder | CLT1062 | 1 | $2.80 |
| Passive Buzzer | - | 1 | $0.88 |
| Total | - | - | $33.47 |

<a id="microcontroller"></a>
### Microcontroller - ATmega328P (With Arduino Uno R3)

Yes, I'm using an Arduino, but hear me out. The truth is that I didn't know any better when I started tinkering with embedded development.
By the time I learned that this MCU is very old and the Arduino platform simplifies away a lot of things, I had already bought some equipment,
so I figured I might as well make a quick and dirty prototype with what I have to get my feet wet and have something to show at my school's career fair, 
which is in 2 weeks as I'm writing these lines. The intention was never to make the final version with this MCU or with the Arduino IDE. 
I plan to use the much more powerful STM32-F446RE instead. For this first iteration however, this will do.

<a id="display"></a>
### Display - 0.96" SSD1306 Monochrome OLED

This display is cheap, has plenty of support and documentation, and looks very sharp. My UI contains a lot blank space, which pairs well
with the deep blacks OLEDs are known for. This project is simple enough to not require high-speed communication, so I²C's 2-cable setup 
helps cut down on the cable clutter as well.

<a id="rotary-encoder"></a>
### Rotary Encoder - KY-40

This rotary encoder is the only form of input for this device. It's satisfying to rotate around and fairly intuitive.
The added bonus of the KY-40 is that it's soldered to a PCB which already includes the resistors you need to filter out
the noise from the SW, CLK and DT signals. That does make it a little harder to secure on a breadboard, but I can deal with that.

<a id="passive-buzzer"></a>
### Passive Buzzer

It's the one that came with my Arduino starter kit. It gets the job done.

<a id="wiring-diagram"></a>
### Wiring Diagram

<img width="50%" height="50%" alt="{C89FDA2B-B4BD-4FD9-9956-544990561FB0}" src="https://github.com/user-attachments/assets/bffef6d4-cfb3-4b5c-992a-340779c5e63c" />


<!-- THE PROCESS -->
<a id="the-process"></a>
## The Process

### Getting the Encoder Working
After deciding which parts I would use, it was time to get to work. I started by spending my summer getting acquainted with the basics with the help of
Paul McWorther’s excellent Arduino tutorials on YouTube. After that, I started by testing out the rotary encoder. It's straightforward enough to make it 
work with the Uno R3. The only slight snag I hit is that my encoder had its DT and CLK sensors inverted compared to the tutorial’s, 
which caused it to read the directions in an inverted way (CW was detected as CCW and vice versa). This is a good thing because it forced me to understand
how the device actually works. The solution was simply to invert the logic in the code from DT ≠ CLK to DT == CLK.

<img width="371" height="441" alt="image" src="https://github.com/user-attachments/assets/f5e2d0a1-2fed-4f4c-a66a-c00109776211" />

<a id="displaying-a-timer"></a>
### Displaying a Timer
With the encoder working, my next task was to get that OLED screen to work. First, I had to choose between using a library, following a tutorial, or writing the logic myself. 
I opted for the first and third options because doing things on your own builds one’s engineering mindset and helps keep bloat down. I didn't want this project to
take forever though, so I opted to use the Adafruit GFX library to handle drawing the actual pixels, with the actual timer logic made by me.

I used Arduino’s millis() function as a base, which counts how much time in milliseconds has elapsed since boot-up. My logic is mostly centered around
recording the value of millis() when the timer starts, defining how long I want the timer to run, and making various conversions and simple math to figure out what to display.

```
elapsedTime = millis() - timerStartTime;
```


A slight challenge was to display leading zeroes when there’s less than 10 seconds in a given segment. I wound up deciding on simple logic. 
Just add a zero first if the number of seconds or minutes to display is below 10. Easy peasy.

```
if (minDisplay < 10) display.print("0"); //Leading zero
display.print(minDisplay);
```


The next challenge was to handle the end of a segment. At first, I thought I just needed to check if the remaining time was higher than zero.
But doing that resulted in the timer somehow jumping to a much higher time. Why? I printed the remaining time on the Serial Monitor to figure out what the hell was going on (the Uno doesn't support debugging, alas).

```
195
150
105
61
16
4294967268
4294967223
4294967179
4294967135
```

Then I understood. A closer look reveals that the ATmega 328P’s internal timer has a tick rate of roughly 45 ms at 16 MHz, so if the remaining time was smaller than that tick, we’d go into the negatives, except there <em>are</em> no negatives, 
because time is handled with unsigned longs, so instead we overflow back to the highest value possible for that variable type, which is about 4.29 billion. That’s why we go from 16 to these ridiculously huge numbers. 
The solution was to only update the timer if the remaining time was more than one tick away from zero, otherwise, the segment is over, and the timer stops. You do lose some precision because of this limitation, 
but 50 milliseconds isn’t crucial for what is nothing more than a little study timer.

```
if (timerDuration - elapsedTime > TICK_RATE) {
    elapsedTime = millis() - timerStartTime;
  } else {
    elapsedTime = timerDuration;
    //End of segment logic goes here...
}
```
This resulted in the functional, albeit rudimentary timer you can see here:
<br/>
<br/>
<img width="40%" height="40%" alt="image" src="https://github.com/user-attachments/assets/7118cc0d-da98-4ad4-a9d0-6b2646958485" />


<a id="creating-a-fsm"></a>
### Creating a Finite State Machine (FSM)

Next, I started implementing a finite state machine to manage the timer’s possible states. The first iteration was as simple as possible with 3 states: WORK, S_BREAK AND L_BREAK. 
Implementing them with a switch statement was easy enough, especially after taking the time to draw my FSM on a whiteboard.
<br/>
<br/>
<img width="60%" height="60%" alt="image" src="https://github.com/user-attachments/assets/56cd5906-b2a3-4cff-8959-c05edb07cf6d" />


<a id="implementing-a-pause-feature"></a>
### Implementing a Pause Feature

This was one of the more challenging parts of this project. It took me a few hours to figure it out, plus I needed a nudge from an LLM. I made sure not to let it give me a solution though. 
Normally, I use LLMs and examples liberally, but the point here is really to learn and sharpen my skills to really understand what I’m doing. I won’t get there unless I do it myself. 
The solution for pausing turned out to actually be rather simple.

The elapsed time is usually calculated using the difference between the current running time and the running time when the timer was started, but when you pause, millis() doesn’t stop ticking. 
At a low level like this, we’re reading more or less from the oscillator (likely with a bunch of stuff simplified by the Arduino platform), which cannot be stopped. 
If you pause for 30 seconds, millis() now has 30 seconds more than what you’re expecting. So all you need to do is take those 30 seconds away from millis(), and you’re back to the exact state you were in before pausing.

Even while implementing this, I ran into some issues. The time added back made no sense. After some rudimentary debugging, I quickly realized that I need to keep a tally of not just one pause, but all the pauses until 
a new segment starts and the start time is reset to 0. The total pause time needs to be reset to 0 at that point, too. And now, pausing works as it should. When it did, a rush of excitement and satisfaction coursed through my body 
and I whispered “motherf**ker” to myself. Here’s the updated FSM diagram:

<img width="60%" height="60%" alt="image" src="https://github.com/user-attachments/assets/ad76c537-368e-4018-bc0d-352e7a130adc" />


<a id="creating-a-main-menu"></a>
### Creating a Main Menu

With the project really starting to take shape, I added the main menu that lets you configure your durations and start the timer. That involved a lot of challenges.

First, I had to come up with a system to manage the menu’s states. I took liberal inspiration from this [All About Circuits tutorial](https://www.allaboutcircuits.com/projects/how-to-use-a-rotary-encoder-in-a-mcu-based-project/). 
It was no mere copy-paste though. The underlying logic is the same, but I heavily modified the code to fit my needs. Two variables drive the menu: one for which item is selected and another for whether you’re adjusting it or not. 

The second challenge was to draw the menu. I once again used AAC’s tutorial as a base. It took me little more than simple if-else statements to determine whether each item was highlighted or not. 
Some basic math involving text bounds also allowed me to dynamically center elements on the screen. Displaying the time was a little trickier. My previous displayTime() function was a poor fit for this, 
since it both formatted the milliseconds to an MM:SS format and displayed the time in large characters. This is when I understood that the function had 2 roles, which is not usually good practice, 
so I split it into 2 functions. displayTime() does what it says on the tin and simply displays whatever is in my time buffer with the right size and color, 
while formatTime() converts an unsigned long into an actual MM:SS format, then places it into a buffer just large enough to contain it.

The third challenge was fixing my rotary encoder inputs, which worked fine on their own, but either got misread or not read at all when paired with a display. This is because up until now, all of my code was 100% sequential in the loop.
That introduced a lot of delays. So I had to learn interrupts, but it honestly wasn’t too hard. All you have to do is plug the value you want to read into one of the Arduino’s interrupt pins and tell it which function to run when a change is detected. 
And voila, it’s much more responsive now, albeit with some oversensitivity issues with CW rotations that will need to be fixed later.

And finally, I had to put it all together. I used this occasion to 
clean up my code by adding comments, simplifying some sections, creating some helper functions and whatnot.

<img width="40%" height="40%" alt="image" src="https://github.com/user-attachments/assets/5b1f8f1c-4e12-4e51-996d-64a9ba550ef2" />


<a id="implementing-a-buzzer"></a>
### Implementing a Buzzer

The last major feature to implement was a passive buzzer. Getting that to work was surprisingly hard. The obvious option would have been to simply use Arduino’s delay() function, but that puts the entire program to a halt, which doesn’t work 
because the display needs to keep refreshing in the background. The classic millis() approach doesn’t work either, because playing a melody made of different notes and pauses would be impossible. Each new loop would forget the last note played 
and wouldn’t know which one to play next. The only way to stop that from happening is to create a sequencer, which is what I did. To that end, I created a struct called “Note”, which contains the frequency, duration and most importantly, 
how long to wait until the next note. Putting Notes into an array allows one to build any melody they wish by simply specifying which notes to play manually. A global variable named currentNote decides how far along we are in the sequence 
and is incremented by one each time a note is played. Its value is -1 if nothing is playing at the moment.

The second part of the challenge with this sequencer was to figure out how to start and end a sequence. I decided to use simple logic for the latter. If you’re waiting 0 ms until the next note, it’s assumed that it is because there is no next note. This works a little like the null terminator for strings in C. Finally, I had to figure out how to decide whether or not I wanted to start a sequence or do nothing. My first idea was to assume you wanted to start a sequence if you called the function while currentNote was -1. But with that logic, if you call the function on each loop to check if you’re playing something, then you would be playing something on repeat. I felt really confused for a bit, so I took a shower, made some coffee, and left that problem alone.

Upon returning to my desk, I had a new idea: split the very first tone and all the others into 2 functions called playBeepSequence() and updateBeepSequence() respectively. The former kicks off a sequence and is only called a single time, while the latter is called on every loop and checks if a sequence is being played. If that’s the case, then it increments currentNote by 1 and plays it, but only if the previous note’s wait time has elapsed. When the last note is reached, currentNote is set back to -1, awaiting playBeepSequence()’s next call.  For now, I only have 2 very basic sequences that sound like a dollar store timer, but later down the line, making more expressive tunes is definitely in the cards.

Then I had to do some fiddling to make things actually good. I ran into an issue where the buzzer would play horrible high-pitch sound, even though it was supposed to be done playing sounds. Turns out I had just forgotten to set the final note’s wait time to 0. Oops. Another problem was the volume. The tones were absurdly loud. They absolutely decimated my eardrums. There’s this concept called resonant frequency. I’m not too informed on it, but from what I understand, there’s a sweet-spot frequency where a passive buzzer is at absolute loudest. I learned the hard way that for mine, that frequency is 2000 Hz. Now, I could have added a potentiometer or a resistor to tone it down, but I’d rather keep volume controls for a future iteration, along with a rumble feature in case there are people around. So I just adjusted the frequency to 1000 Hz.

<a id="tying-it-all-together"></a>
### Tying it all together

With this, all of the main functionality for this timer was COMPLETE… But there were still a couple of QOL tweaks to make. I’d deferred almost every UI and UX feature until the end, so now is the time to tackle that. T
he first thing that needed to go was that dreadful default font for the time display. I replaced it with Sans, one of the fonts offered by the Adafruit GFX library. It’s inspired by the perennial Helvetica and it looks great. 
It instantly transformed the feel of the product from hacker doo-dad to a real product used by real people. I mean, witness the difference yourself.

<img width="30%" height="30%" alt="image" src="https://github.com/user-attachments/assets/0061f9a2-940f-4262-81c7-f1ffc63ab661" />
<img width="31%" height="31%" alt="image" src="https://github.com/user-attachments/assets/bf916b53-88bc-4455-bb2b-b92bdbedf712" />
<br/>


After this, I had a couple more bothersome flies to swat down for added polish:

* There was no obvious, visible feedback to let the user know the timer was paused. Yes, the text at the top says “Pause”, but it’s too small! I made the display blink when the timer is paused, which makes it significantly easier to tell at a glance that the timer is suspended.
* When you started a timer at, say, 5 minutes, you would see “05:00” for a fraction of a second, then it would immediately decrease to “04:59”. I know why this happens and it makes sense, but it’s jarring. This was resolved by sneakily adding exactly 999 ms to every single duration.
  This way, there’s a built in “grace period” where you can actually see how much time you put in.
* There was a slight debouncing issue with the rotary encoder, specifically when rotating clockwise. I fixed this by requiring at least 2 ms of delay between inputs. Any more and too many inputs were skipped. Any less and the problem simply wasn’t fixed.
  This still doesn't feel as good as I'd like, but it'll have to do for this iteration.

<a id="final-result"></a>
## Final Result

After ordering a Nano V3, ~~stealing~~ borrowing my sister's battery bank and doing some quick cable management to make the whole thing portable, this is the final result:

<br/>
<img width="40%" height="40%"  alt="image" src="https://github.com/user-attachments/assets/7088efaf-009c-4144-b957-8d6407224d5e" />
<br/>
Here, I connected the OLED screen to a couple of Dupont wires and propped it up on a phone stand for easier viewing.

<br/><br/>
<img width="40%" height="40%" alt="image" src="https://github.com/user-attachments/assets/74e80ea5-289a-4cb4-9774-4bf50e5c639b" />
<br/>
This is a portable version made with a Nano V3 and a battery pack.
<br/><br/>

<!-- CONCLUSION -->
<a id="conclusion"></a>
## Conclusion

I'm proud of what I've accomplished so far and I've learned a lot from the process. Looking back, here's what I'd do differently with what I know now:
<ul>
  <li>Be more diligent when researching parts. Had I spent more time pondering what exactly I wanted to do with each component, I could have saved some cash on things I didn't end up using or will need to replace later down the line, especially for the display.</li>
  <li>Use version control from the start. You're currently reading this on GitHub, so I obviously did that in the end, but didn't at first because I thought this project was too small to require it. I was wrong.</li>
</ul>

And yet, as you take lessons from the past, you must also look to the future. This is only the beginning, and I really plan to design an actual product from A to Z.
Here's the roadmap I have in mind to get there:

- [x] Create an Arduino-based prototype
- [ ] Create an STM32 prototype
- [ ] Design and produce a PCB
- [ ] Design and 3D print a case
- [ ] Make the final build

In the meantime, I'm using this prototype while studying and making notes of features to add and tweaks to make in the next iteration.
This was seriously really fun to make, and I have not felt this motivated by a personal project in years. If you made it this far in my 
write-up, you have the patience of a saint, because holy crap was it long. Thank you for reading, and I hope you got something out of it.

<!-- CONTACT -->
<a id="contact"></a>
## Contact

Wanna get in touch? Work with me? Have me work <em>for</em> you? You can find me here:

Email - salif8514@gmail.com<br/>
LinkedIn - https://www.linkedin.com/in/salif-d-b567011ba/

<!-- ACKNOWLEDGMENTS -->
<a id="acknowledgments"></a>
## Acknowledgments

* [Paul McWorther's excellent series on Arduino](https://www.youtube.com/playlist?list=PLGs0VKk2DiYw-L-RibttcvK-WBZm8WLEP)
* [That one All About Circuits tutorial](https://www.allaboutcircuits.com/projects/how-to-use-a-rotary-encoder-in-a-mcu-based-project/)
* [This guy explaining interrupts in a way that makes sense](https://www.circuitbasics.com/how-to-use-hardware-interrupts-and-timer-interrupts-on-the-arduino/)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

