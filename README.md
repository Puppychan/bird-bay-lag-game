# Instruction
## Running on QUEMU
- Open terminal or console in the root
- Run `make cleanall-run` - please wait for a few minutes
- If this run is not your first run, and you did not modify anything in program -> just run `make test` to save time
## Running on RPI4
- In `gpio.h`: change line `#define RBP3 //for emulation with QEMU` to `#define RBP4`
- 



# For developers
- Store all files being relevant to images, and videos inside `data` folder
- When adding files, make sure optimize both `data.h` and `data.c` files
## Optimized Run
- If you add any header files into `data` folder to store images, videos
    => Run `make cleanall-run`
- If you do not change any header files in `data` folder
    => Run `make test`

Please dont:
- Zoom the TeraTerm before or during the running
- Disconnect TeraTerm and then connect again -> Nothing will display

- If want to run program again: 
  - Close teraterm and reopen again
  - Setuo again

- Runnign:
  - Game:
    - w: move arrow up
    - s: move arrow down


- Bugs:
  - Laggy when playing game on rpi4
  - Laggy when on larger screen -> so should test on your laptop only ( depend on the screen size )