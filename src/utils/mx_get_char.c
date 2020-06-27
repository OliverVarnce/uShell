#include "ush.h"

static void set_Terminal_Settings() {
    struct termios newTerm;

    tcgetattr(STDIN_FILENO, &newTerm);
    newTerm.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP
                         | INLCR | IGNCR | ICRNL | IXON);
    newTerm.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    newTerm.c_cflag &= ~(CSIZE | PARENB);
    newTerm.c_cflag |= CS8;
    newTerm.c_iflag &= IGNCR;
    tcsetattr(STDIN_FILENO, 0, &newTerm);
}

static void disable_Terminal(struct termios oldTerm) {
    tcsetattr(STDIN_FILENO, 0, &oldTerm);
}

unsigned int mx_get_char() {
    unsigned int ch = 0;
    struct termios oldTerm;

    tcgetattr(STDIN_FILENO, &oldTerm);
    set_Terminal_Settings();
    if (read(0, &ch, 4) == 0) {
        return 0;
    }
    disable_Terminal(oldTerm);
    return ch;
}
