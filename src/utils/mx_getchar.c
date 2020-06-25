#include "ush.h"

static void mx_set_Terminal_Settings() {
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

static void mx_disable_Terminal(struct termios oldTerm) {
    tcsetattr(STDIN_FILENO, 0, &oldTerm);
}

unsigned int mx_getchar() {
    unsigned int ch = 0;
    struct termios oldTerm;

    tcgetattr(STDIN_FILENO, &oldTerm);
    mx_set_Terminal_Settings();
    if (read(0, &ch, 4) == 0)
        return 0;
        
    mx_disable_Terminal(oldTerm);
    return ch;
}
