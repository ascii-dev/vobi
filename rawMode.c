//
// Created by Samuel Afolaranmi on 21/03/2021.
//

#include <stdlib.h>
#include <termios.h>

#include "rawMode.h"

struct termios originalTermios;

void disableRawMode() {
    // Set original attributes back into terminal on exit
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &originalTermios);
}

void enableRawMode() {
    // Read current terminal attributes into struct
    tcgetattr(STDIN_FILENO, &originalTermios);
    atexit(disableRawMode);

    struct termios raw = originalTermios;
    raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    raw.c_oflag &= ~(OPOST);
    raw.c_cflag |= ~(CS8);
    /*
     * The c_lflag field is for “local flags”. The other flag fields are
     * c_iflag (input flags), c_oflag (output flags), and c_cflag (control flags).
     * ECHO is a bitflag, defined as 00000000000000000000000000001000 in binary.
     * We use the bitwise-NOT operator (~) on this value to get 11111111111111111111111111110111.
     * We then bitwise-AND this value with the flags field, which forces the fourth bit in
     * the flags field to become 0, and causes every other bit to retain its current value.
     * Flipping bits like this is common in C.
     */
    raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG); // (bitwise) turn flags off

    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;

    // Set modified attributes back into terminal
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
