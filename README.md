# Bird Bay Lag Game Project
Group Project - Group 13 OS - Game 
EEET2490_G13_GroupProject
# Instruction
## Prerequisites
- You have installed latest version of [Docker Desktop](https://docs.docker.com/get-docker/)
- You have installed [Git Client](https://git-scm.com/downloads) - if you want to clone the project using git in terminal.
- You have IDE or text edit files. (I use Visual Studio Code in this case).
## Clone project
-  Clone the project `git clone https://github.com/Puppychan/bird-bay-lag-game`
-  
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
- Afterwards, copy `kernel8.img` in the root folder and follow these steps [here](https://rmit.instructure.com/courses/121602/files/34052795?wrap=1).
- After following and complete these steps, please wait for a few minutes to let the **Welcome Message** appearing on the TeraTerm, because TeraTerm is slow in recognizing unicode displaying character.
- To run the OS system, the TeraTerm now is the console/ terminal when the user runs on QUEMU.
- Refer to [The Team OS System](#the-team-os-system) to see how to use the team OS system and play game application inside the system.

## Please DON'T

- Zoom the TeraTerm before or during the running
- Disconnect TeraTerm and then connect again -> Nothing will display
  => If you want to run the program on RPi4 again, make sure follow [these steps](#running-on-rpi4) instead of disconnecting then connecting the TeraTerm again.

## Others

- Things available in this OS system (because the team concentrates on displaying images, using font, and developing game this time):
  - Delete
  - Simple Autocompletion (only suggest with simple features) by pressing `tab`
  - Enter to generate command
## Not Be Able To Run
**_NOTE_**: There is no difference in running Windows, or Mac OS systems, because the Makefile handles different OS system cases. By testing on both the team members' MAC and Windows, you also do not need to create **_object_** folder by yourself. However, if you still cannot run by following these below steps [here](#instruction):

- Firstly, creating **_object_** folder in the root.
- If you still cannot run, run `make cleanall-run` in the terminal/ console in the root.
- If you still cannot run, please contact us [here](#contact-us).

# For developers

- Store all files being relevant to images, and videos inside `data` folder
- When adding files, make sure modify both `data.h` and `data.c` files to use the medias.

# Extract Video

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
