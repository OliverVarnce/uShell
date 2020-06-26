#include "ush.h"

char **mx_call_env(char **av, int i) {
    int counter = 0;
    char **av_to_proces = NULL;

    for (; av[i]; i++, counter++);
    av_to_proces = malloc(sizeof(char *) * (counter + 1));
    av_to_proces[counter] = NULL;
    for (i -= counter, counter = 0; av[i]; i++, counter++)
        av_to_proces[counter] = strdup(av[i]);
    return av_to_proces;
}
