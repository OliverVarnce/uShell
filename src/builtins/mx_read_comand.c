#include "ush.h"

static bool str_line(char buf) {
    if (buf == '\r'|| buf == '|' || buf == '&')
        return 1;
    else
        return 0;
}

static char *direct_line(char *pars) {
    int i = mx_strlen(pars);

    if (str_line(pars[0]) == 0) {
        while (i != 0 && pars[--i] != '/');
        if (i == 0)
            return mx_strdup("./");
        else
            return mx_strndup(&pars[1], i);
    }
    return mx_strdup("./");
}

static void add_comand(t_list **list_comand, char *pars, char ***paths,
                       char **directori) {
    static char *comand[] = {"history", "unset", "export", "./", "../", 0};
    char *tmp = 0;

    for (int i = 0; str_line(pars[0]) != 0 && comand[i]; i++) {
        if (mx_strcmp2(comand[i],&pars[1]) == 0) {
            tmp = mx_strdup(comand[i]);
            mx_push_front(list_comand, tmp);
        }
    }
    mx_del_strarr(paths);
    mx_strdel(directori);
}

static void file_in_dir(t_list **list_comand,
                               char *pars, char ***paths) {
    DIR *dir = 0;
    char *tmp = 0;
    struct dirent *entry;
    char *directori = direct_line(pars);
    int i = 1;

    if (mx_strcmp2("./", directori) == 0 && mx_strcmp2(&pars[1], "./") != 0)
        i = 1;
    else
        i = mx_strlen(directori) + 1;
    if ((str_line(pars[0]) == 0) && (dir = opendir(directori))) {
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_name[0] != '.'
                && mx_strcmp2(entry->d_name, &pars[i]) == 0) {
                tmp = mx_strdup(entry->d_name);
                mx_push_front(list_comand, tmp);
            }
        }
        closedir(dir);
    }
    add_comand(list_comand, pars, paths, &directori);
}

void mx_read_comand(char *pars, t_list **list_comand) {
    char *path = getenv("PATH");
    char **paths = mx_strsplit(path, ':');
    DIR *dir = 0;
    struct dirent *entry;

    if (str_line(pars[0])) {
        for (int i = 0; paths && paths[i]; i++) {
            if ((dir = opendir(paths[i]))) {
                while ((entry = readdir(dir)) != NULL) {
                    if (entry->d_name[0] != '.'
                        && mx_strcmp2(entry->d_name, &pars[1]) == 0) {
                        path = mx_strdup(entry->d_name);
                        mx_push_front(list_comand, path);
                    }
                }
                closedir(dir);
            }
        }
    }
    file_in_dir(list_comand, pars, &paths);
}
