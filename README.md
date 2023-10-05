# Bird Bay Lag Game Project

Group Project - Group 13 OS - Game
EEET2490_G13_GroupProject

# Table of Content

1. 📝 [Introduction](#introduction)
2. 📚 [Instruction](#instruction)
   - [Prerequisites](#prerequisites)
   - [Setup](#setup)
   - [Running on QUEMU](#running-on-quemu)
   - [Running on RPI4](#running-on-rpi4)
   - [Additional Notes](#additional-notes)
3. 💻 [For Developers](#for-developers)
4. 📨 [Contact Us](#contact-us)

# Introduction

- The project is a game application designed to operate on a custom-built OS system.
- The game is developed using the C programming language <img src="https://img.shields.io/badge/C-00599C?style=for-the-badge&logo=c&logoColor=white" alt="C icon" width="45" height="20">.
- It's inspired by the popular game [Flappy Bird](https://thanhnien.vn/chang-trai-viet-game-flappy-bird-gay-sot-toan-cau-18584583.htm), and we've named our rendition "<span style="color: khaki;">**_Bird Bay Lag_**</span>".
- The primary purpose behind this project is to gain insights into OS development and dive deep into game creation.
- This endeavor was carried out by a team of four members participating in the "Embedded System: OS and Interfacing" course.
- The entire game development process takes approximately a month.
- As the core focus was on the gaming aspects, we decided to utilize a pre-developed OS system from one of our team members.

## Game Introduction <img src="./assets/player/player.png" alt="" width="48">

- **Bird Bay Lag**<img src="./assets/player/player.png" alt="" width="28"> is a game that the player controls a bird to fly through obstacles.
- This game is ***single-player***, and the player can choose different bird skins, backgrounds, and difficulties.
- The game has three rounds, and each round has a different game setting for increasing difficulty.

### Game Mechanics

**Obstacles:**
In the game, if the bird collides with any obstacles or the screen boundaries, the game ends. There are two main types of obstacles:

1. **Tube or Pipe:**  
   <img src="./assets/obstacle/tube.png" alt="" width="50" height="150">

2. **Balloon:**  
Various balloons act as obstacles, some examples are shown below:

| <img src="./assets/obstacle/balloon-1.png" alt="" width="180" height="220"> | <img src="./assets/obstacle/balloon-2.png" alt="" width="180" height="220"> |
| :-------------------------------------------------------------------------: | :-------------------------------------------------------------------------: |
| <img src="./assets/obstacle/balloon-3.png" alt="" width="180" height="220"> | <img src="./assets/obstacle/balloon-4.png" alt="" width="180" height="220"> |


## Gameplay and Features

### <span style="font-size: 23px; border-radius: 50%; border: 1px solid #fff;">🎮</span> Controls:

- **Start Game:** `Enter` key.
- **Flap Bird:** `Space` key. If not pressed, the bird will fall due to gravity.

###  Scoring:

- Earn **1 point** every time the bird successfully passes an obstacle.
-

### Customizations:

- **Bird Skin:** Players can choose different appearances for their bird.
- **Background:** Players can select various backdrops for the gameplay.
- **Difficulty:** Choose between varying game difficulties. As the player progresses through the game's three rounds, they'll encounter different obstacles and increased challenges.

### Post-Game:

- After all three rounds, players are directed to a **Results Page** displaying their final score.
- Option to replay the game or view individual round scores.

### Instructions:

- A comprehensive **Help Menu** within the game offers guidance and clarifies game mechanics.

# Instruction

The instruction includes 3 main parts:

- Setting up the development environment:
  - [Prerequisites](#prerequisites)
  - [Clone project](#clone-project)
- Running the project:
  - [Running on QUEMU](#running-on-quemu)
  - [Running on RPI4](#running-on-rpi4)
- Some additional notes:
  - [Please DON'T](#please-dont)
  - [Others](#others)

## Prerequisites

- **Git**: [Git Client](https://git-scm.com/downloads) installed.
- **Editor**: Any IDE or text editor (Example: Visual Studio Code).

### General

#### Windows - [Detailed](./assets/readme/setup-development-environment-win.pdf)

- **GCC Toolchain**: [GCC tool chain](https://github.com/◊niXman/mingw-builds-binaries/releases) with **_x86_64 release-posix-seh-ucrt-rt_** latest version.
- **ARM GCC**:
  - 32-bit one: [GNU ARM Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) for 32-bit.
  - 64-bit one: [64 Bit GNU ARM Embedded Toolchain](https://developer.arm.com/downloads/-/gnu-a) for 64-bit.
- **Make**: [GNU Make](https://www.gnu.org/software/make/).

#### MacOS

- **Homebrew**: Installed from [Homebrew](https://brew.sh/).
- Open terminal and run these commands:
  - **Make**: `brew install make`.
  - **ARM GCC**:
    - 64-bit:
      ```
      brew tap ArmMbed/homebrew-formulae
      brew install arm-none-eabi-gcc
      ```
    - 32-bit:
      ```
      brew tap SergioBenitez/osxct
      brew install aarch64-none-elf
      ```

| Requirement                    | Windows                                                                                                                                        | MacOS                                                                        |
| ------------------------------ | ---------------------------------------------------------------------------------------------------------------------------------------------- | ---------------------------------------------------------------------------- |
| **Installation Tool**          | -                                                                                                                                              | [Homebrew](https://brew.sh/)                                                 |
| **GCC Toolchain**              | [GCC tool chain](https://github.com/◊niXman/mingw-builds-binaries/releases) with **_x86_64 release-posix-seh-ucrt-rt_** (Latest Version)       | -                                                                            |
| **ARM GCC Toolchain (32-bit)** | [GNU ARM Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads) | `bash brew tap SergioBenitez/osxct && brew install aarch64-none-elf `        |
| **ARM GCC Toolchain (64-bit)** | [64 Bit GNU ARM Embedded Toolchain](https://developer.arm.com/downloads/-/gnu-a)                                                               | `bash brew tap ArmMbed/homebrew-formulae && brew install arm-none-eabi-gcc ` |
| **Make Utility**               | [GNU Make](https://www.gnu.org/software/make/)                                                                                                 | `brew install make`                                                          |
| **Detailed Setup**             | [Setup Details](./assets/readme/setup-development-environment-win.pdf)                                                                         | -                                                                            |

### Detailed Setup

#### Computer intention to run on QUEMU

| Requirement            | Windows                                 | MacOS                |
| ---------------------- | --------------------------------------- | -------------------- |
| **QUEMU Installation** | [QUEMU](https://www.qemu.org/download/) | `brew install quemu` |

#### Computer intention to run on RPI4

- Please follow step by step instruction in this section [here](#running-on-rpi4)

## Clone project

- Open terminal and navigate to the folder you want to clone the project
- Clone the project with this command on the terminal:
  ```shell
    git clone https://github.com/Puppychan/bird-bay-lag-game
  ```

## Running on QUEMU

- Open terminal or console in the root
- Run `make cleanall-run` - please wait for a few minutes - the video frames make the compiling time a bit long.
- If this run is not your first run, and you did not modify anything in `data` folder, or you did not delete or modify an `object` folder -> just run `make test` to save your time
- When there is a black screen - QUEMU - OS system appearing:

### The Team OS System

- Type **help** in terminal to see the instruction.
  - Type `displayImage`: to view list of images, and type `w` or `s` to scroll the image vertically
  - Type `displayVideo`: to view a video generating using a list of frames written in hexadecimals, a reason why the compiling time is so long
  - Type `displayName`: to view list of all members' name with rainbow colors.
  - Type `\n` - new line - return keyboard to exist the current command.
  - Type `playGame`: to open a `Bird Bay Lag` game. In game:
    - To control the game, ensure you are still typing on the terminal/ console.
    - In **Menu**:
      - Type `s` to move down the selection and choose suitable option in Menu
      - Type `w` to move up the selection and choose suitable option in Menu
      - Type `\n` - enter or return keyboard - to confirm the selection
    - In **Help** menu:
      - This menu displays game instruction
      - To back to main menu, press `\n`
    - To **Exit Game**: choose exit option and press `\n`
    - To **Start Game**: choose start option and press `\n`:
    - Before starting game:
      - Choose _background_ or use current default background
      - Choose _bird skin_ or use current default bird skin
      - Choose _difficulty_ or use current default game difficulty - Less - easy mode
      - To choose, press `a` or `d` to move the option to the left or right to view options
      - After each section, press `\n` to go to next section
      - After choosing 3 section, start playing game
      - There are 3 **_rounds_**, to start playing _next round_, press `\n`
    - After _loosing_ or _winning_, there is a result page displaying final scores. Pressing any key to back to main Menu.

## Running on RPI4

- In `gpio.h`: change line `#define RBP3 //for emulation with QEMU` to `#define RBP4`
- Run `make cleanall-run` if you haven't run this project before, or if you modify anything in _data_ folder, or you delete or modify in _object_ folder. Or you only need to run `make test` if you modify code excepting `data` folder.
- Afterwards, copy `kernel8.img` in the root folder and follow these steps [here](./assets/readme/setup-rpi4.docx).
- After following and complete these steps, please wait for a few minutes to let the **Welcome Message** appearing on the TeraTerm, because TeraTerm is slow in recognizing unicode displaying character.
- To run the OS system, the TeraTerm now is the console/ terminal when the user runs on QUEMU.
- Refer to [The Team OS System](#the-team-os-system) to see how to use the team OS system and play game application inside the system.

## Please DON'T

### Computer having intention to run on RPI4

- Zoom the TeraTerm before or during the running
- Disconnect TeraTerm and then connect again -> Nothing will display
  => If you want to run the program on RPi4 again, make sure follow [these steps](#running-on-rpi4) instead of disconnecting then connecting the TeraTerm again.

## Others

- Things available in this OS system (because the team concentrates on displaying images, using font, and developing game this time):
  - Delete
  - Simple Autocompletion (only suggest with simple features) by pressing `tab`
  - Enter to generate command

### Not Be Able To Run

**_NOTE_**: There is no difference in running Windows, or Mac OS systems, because the Makefile handles different OS system cases. By testing on both the team members' MAC and Windows, you also do not need to create **_object_** folder by yourself. However, if you still cannot run by following these below steps [here](#instruction):

- Firstly, creating **_object_** folder in the root.
- If you still cannot run, run `make cleanall-run` in the terminal/ console in the root.
- If you still cannot run, please contact us [here](#contact-us).

# For developers

- Store all files being relevant to images, and videos inside `data` folder
- When adding files, make sure modify both `data.h` and `data.c` files to use the medias.

## Extract Video

If you want to extract video, please follow these steps:

- In MacOS terminal:
  - Ensure the Mac has Brew, then run `brew install ffmpeg`
  - Run `ffmpeg -i Flappy-24fps.mp4 -vf "fps=24" ./flappy-24/frame_flappy_%04d.png` on MAC OS
    - _Flappy-24fps.mp4_: name and the location of the extracting video - the video names `Flappy-24fps.mp4` and the location is current terminal's location
    - "_fps=24"_: Extracting video with 24 fps
    - _./flappy-24/frame*flappy*%04d.png_: the location where the frames will be stored, and the name it uses to store. Store in `flappy-24` folder, and names `frame_flappy_....png`.

# Contact Us

| Name                 | Student ID | Mail                       | GitHub Profile                                | Contribution (%) |
| -------------------- | ---------- | -------------------------- | --------------------------------------------- | ---------------- |
| Tran Mai Nhung       | s3879954   | nhungmaitran1412@gmail.com | [Puppychan](https://github.com/Puppychan)     | 25%              |
| Tran Nguyen Ha Khanh | s3877707   | s3877707@rmit.edu.vn       | [hakhanhne](https://github.com/hakhanhne)     | 25%              |
| Phan Nhat Minh       | s3904422   | s3904422@rmit.edu.vn       | [MinhPhan123](https://github.com/MinhPhan123) | 25%              |
| Nguyen Ngoc Minh     | s3907086   | s3907086@rmit.edu.vn       | [ngcmnh](https://github.com/ngcmnh)           | 25%              |
