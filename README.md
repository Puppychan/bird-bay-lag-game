# Instruction
- Open terminal or console in the root
- Run `make cleanall-run`
- If this run is not your first run, and you did not modify anything in program -> just run `make test` to save time


# For developers
- Store all files being relevant to images, and videos inside `data` folder
- When adding files, make sure optimize both `data.h` and `data.c` files
## Optimized Run
- If you add any header files into `data` folder to store images, videos
    => Run `make cleanall-run`
- If you do not change any header files in `data` folder
    => Run `make test`