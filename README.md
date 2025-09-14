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
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

As an electrical engineering student, I'm well-aware that just getting the degree isn't nearly enough to set yourself apart when looking for a job or an internship, <em>especially</em> not in this job market.
A common strategy to counter that is to work on personal projects in your free time, but I'm also an engineer, so I may as well use that as a chance to fix a problem in my life. Enter the Pomocube.

### What the hell is a pomodoro?

Named after the tomato-shaped kitchen timer, the pomodoro technique is a way to stay focused for long periods of time. You work for 25 minutes, then take a 5 minute break, and repeat the process 3 more times, with a longer break at the end.
By taking small, regular breaks, you allow your attention-span to recharge, keeping you more productive overall. Plus, you always have a small reward to look forward too. Everyone is obviously different, but I have personally had
great success with this technique both to study and work.

Of course, there are a lot of pomodoro apps out there, and I've used my share over the years (my favorite is https://www.flow.app/).
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


## Parts Selection

Continuing the theme of simplicity, this project requires very few parts to get working.

### Bill of Materials

| Description | Part Number | Quantity | Unit Cost (CAD) |
|---|---|---|---|
| ELEGOO Arduino Uno R3 w/ ATmega328P | EL-CB-001 | 1 | $24.99 |
| GeeekPi 0.96" Monochrome OLED | - | 1 | $4.80 |
| Cylewet KY-40 Rotary Encoder | CLT1062 | 1 | $2.80 |
| Passive Buzzer | - | 1 | $0.88 |
| Total | - | - | $33.47 |

### Microcontroller - ATmega328P (With Arduino Uno R3)

Yes, I'm using an Arduino, but hear me out. The truth is that I didn't know any better when I started tinkering with embedded development.
By the time I learned that this MCU is very old and the Arduino platform simplifies away a lot of things, I had already bought some equipment,
so I figured I might as well make a quick and dirty prototype with what I have to get my feet wet and have something to show at my school's career fair, 
which is in 2 weeks as I'm writing these lines. The intention was never to make the final version with this MCU or with the Arduino IDE. 
I plan to use the much more powerful STM32-F446RE instead. For this first iteration however, this will do.

### Display - 0.96" SSD1306 Monochrome OLED

This display is cheap, has plenty of support and documentation, and looks very sharp. My UI contains a lot blank space, which pairs well
with the deep blacks OLEDs are known for. This project is simple enough to not require high-speed communication, so I²C's 2-cable setup 
helps cut down on the cable clutter as well.

### Rotary Encoder - KY-40

This rotary encoder is the only form of input for this device. It's satisfying to rotate around and fairly intuitive.
The added bonus of the KY-40 is that it's soldered to a PCB which already includes the resistors you need to filter out
the noise from the SW, CLK and DT signals. That does make it a little harder to secure on a breadboard, but I can deal with that.

### Passive Buzzer

It's the one that came with my Arduino starter kit. It gets the job done.


### Wiring diagram

<img width="497" height="578" alt="{C89FDA2B-B4BD-4FD9-9956-544990561FB0}" src="https://github.com/user-attachments/assets/bffef6d4-cfb3-4b5c-992a-340779c5e63c" />


<p align="right">(<a href="#readme-top">back to top</a>)</p>


<!-- GETTING STARTED -->
## The Process





<p align="right">(<a href="#readme-top">back to top</a>)</p>


<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Final Result

<!-- USAGE EXAMPLES -->
## Challenges




<!-- ROADMAP -->
## What Next?

- [x] Create Arduino-based prototype
- [ ] Create STM32 prototype
- [ ] Design and produce PCB
- [ ] Design and 3D print case
- [ ] Make final build

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->
## Contact

Your Name - [@your_twitter](https://twitter.com/your_username) - email@example.com

Project Link: [https://github.com/your_username/repo_name](https://github.com/your_username/repo_name)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Use this space to list resources you find helpful and would like to give credit to. I've included a few of my favorites to kick things off!

* [Choose an Open Source License](https://choosealicense.com)
* [GitHub Emoji Cheat Sheet](https://www.webpagefx.com/tools/emoji-cheat-sheet)
* [Malven's Flexbox Cheatsheet](https://flexbox.malven.co/)
* [Malven's Grid Cheatsheet](https://grid.malven.co/)
* [Img Shields](https://shields.io)
* [GitHub Pages](https://pages.github.com)
* [Font Awesome](https://fontawesome.com)
* [React Icons](https://react-icons.github.io/react-icons/search)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

