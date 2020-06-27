#include "ush.h"

static void left_right(char *chars, t_ush *ush) {
    unsigned char check;

    if (chars[2] == 67) { // RIGHT
        mx_clean_terminal(MX_USH, ush->input->inplen, ush->input->endpoint,
                ush->input->comands[ush->input->id]);
        check = (unsigned char)ush->input->comands[ush->input->id][ush->input->inplen - ush->input->endpoint];
        for (; check >> 6 == 2;) {
            ush->input->endpoint--;
            check = (unsigned char)ush->input->comands[ush->input->id][ush->input->inplen - ush->input->endpoint];
        }
        (ush->input->endpoint)--;
    }
    else { // LEFT
        mx_clean_terminal(MX_USH, ush->input->inplen, ush->input->endpoint,
                ush->input->comands[ush->input->id]);
        check = (unsigned char)ush->input->comands[ush->input->id][ush->input->inplen - ush->input->endpoint - 2];
        for (; check >> 6 == 2; ) {
            (ush->input->endpoint)++;
            check = (unsigned char)ush->input->comands[ush->input->id][ush->input->inplen - ush->input->endpoint - 2];
        }
        (ush->input->endpoint)++;
    }
}

static void up_down(char *chars, t_ush *ush){
    if (chars[2] == 65) { // UP
        if (ush->input->id != ush->input->maxcmd) {
            mx_clean_terminal(MX_USH, ush->input->inplen,
                    ush->input->endpoint, ush->input->comands[ush->input->id]);
            (ush->input->id)++;
            ush->input->endpoint = 0;
            ush->input->inplen = mx_strlen(ush->input->comands[ush->input->id]) + 1;
        }
        else 
            chars[2] = 10;
    }
    else if (chars[2] == 66) { //DOWN
        if (ush->input->id != 0) {
            mx_clean_terminal(MX_USH, ush->input->inplen,
                    ush->input->endpoint, ush->input->comands[ush->input->id]);
            (ush->input->id)--;
            ush->input->endpoint = 0;
            ush->input->inplen = mx_strlen(ush->input->comands[ush->input->id]) + 1;
        }
        else 
            chars[2] = 10;
    }
}

static void home_end(char *chars, t_ush *ush) {
    if (chars[2] == 70) { // position 0
        if (ush->input->endpoint != 0) {
            mx_clean_terminal(MX_USH, ush->input->inplen, ush->input->endpoint,
                    ush->input->comands[ush->input->id]);
            ush->input->endpoint = 0;
        }
        else 
            chars[2] = 10;
    }
    else if (chars[2] == 72) { // position end
        if (ush->input->endpoint != ush->input->inplen - 1) {
            mx_clean_terminal(MX_USH, ush->input->inplen, ush->input->endpoint,
                    ush->input->comands[ush->input->id]);
            ush->input->endpoint = ush->input->inplen - 1;
        }
        else 
            chars[2] = 10;
    }
    else 
        mx_printstr("/n/nEROOR!! DUBLE_COMAND\n\n");
}

static void page_u_Page_d(char *chars, t_ush *ush) {
    if (chars[2] == 53) { // PageUP
        if (ush->input->id != ush->input->maxcmd) {
            mx_clean_terminal(MX_USH, ush->input->inplen,
                    ush->input->endpoint, ush->input->comands[ush->input->id]);
            ush->input->endpoint = 0;
            ush->input->inplen = mx_strlen(ush->input->comands[ush->input->maxcmd]) + 1;
            ush->input->id = ush->input->maxcmd;
        }
        else
            chars[2] = 10;
    }
    else if (chars[2] == 54) { //PageDown
        if (ush->input->id != 0) {
            mx_clean_terminal(MX_USH, ush->input->inplen,
                    ush->input->endpoint, ush->input->comands[ush->input->id]);
            ush->input->inplen = mx_strlen(ush->input->comands[0]) + 1;
            ush->input->endpoint = 0;
            ush->input->id = 0;
        }
        else
            chars[2] = 10;
    }
}

void mx_is_ascii(char *chars, t_ush *ush) {
    if (chars[3] == 0 && (chars[2] == 65 || chars[2] == 66)) {
        up_down(chars, ush);
    }
    else if (chars[3] == 0 && (chars[2] == 70 || chars[2] == 72)) {
        home_end(chars, ush);
    }
    else if (chars[3] == 0 && chars[2] == 68 &&
    ush->input->inplen - 1 > ush->input->endpoint) {
        left_right(chars, ush);
    }
    else if (chars[3] == 0 && chars[2] == 67 && 0 < ush->input->endpoint) {
        left_right(chars, ush);
    }
    else if (chars[3] == 126 && (chars[2] == 53 || chars[2] == 54)) {
        page_u_Page_d(chars, ush);
    }
    else if (chars[3] == 126 && chars[2] == 51 && ush->input->endpoint != 0) {
        mx_key_delite(ush);
    }
    else
        chars[2] = 10;
}
