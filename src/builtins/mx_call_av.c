#include "ush.h"

char **mx_call_av(char **av, int i) {
    int count = 0;
    char **av_pr = NULL;

    for (; av[i]; i++, count++);
    av_pr = malloc(sizeof(char *) * (count + 1));
    av_pr[count] = NULL;
    for (i -= count, count = 0; av[i]; i++, count++)
        av_pr[count] = strdup(av[i]);
    return av_pr;
}
