#include "ush.h"

static bool cmds(char tmp) {
    if (tmp == '\r'|| tmp == '|' || tmp == '&')
        return 1;
    else
        return 0;
}

static char *direct(char *parsing) {
    int i = mx_strlen(parsing);

    if (cmds(parsing[0]) == 0) {
        while (i != 0 && parsing[--i] != '/');
        if (i == 0)
            return mx_strdup("./");
        else
            return mx_strndup(&parsing[1], i);
    }
    return mx_strdup("./");
}

static void add_comand(t_list **list_cmd, char *parsing, char ***paths,
                       char **directori) {
    static char *comand[] = {"history", "unset", "export", "./", "../", 0};
    char *tmp = 0;

    for (int i = 0; cmds(parsing[0]) != 0 && comand[i]; i++) {
        if (mx_strcmp2(comand[i],&parsing[1]) == 0) {
            tmp = mx_strdup(comand[i]);
            mx_push_front(list_cmd, tmp);
        }
    }
    mx_del_strarr(paths);
    mx_strdel(directori);
}

static void add_file_directory(t_list **list_cmd,
                               char *pars, char ***paths) {
    DIR *dir = 0;
    char *tmp = 0;
    struct dirent *entry;
    char *directori = direct(pars);
    int i = 1;

    if (mx_strcmp2("./", directori) == 0 && mx_strcmp2(&pars[1], "./") != 0)
        i = 1;
    else
        i = mx_strlen(directori) + 1;
    if ((cmds(pars[0]) == 0) && (dir = opendir(directori))) {
        while ((entry = readdir(dir)) != NULL) {
            if (entry->d_name[0] != '.'
                && mx_strcmp2(entry->d_name, &pars[i]) == 0) {
                tmp = mx_strdup(entry->d_name);
                mx_push_front(list_cmd, tmp);
            }
        }
        closedir(dir);
    }
    add_comand(list_cmd, pars, paths, &directori);
}

void mx_read_comand(char *parsing, t_list **list_cmd) {
    char *path = getenv("PATH");
    char **paths = mx_strsplit(path, ':');
    DIR *dir = 0;
    struct dirent *entry;

    if (cmds(parsing[0])) {
        for (int i = 0; paths && paths[i]; i++) {
            if ((dir = opendir(paths[i]))) {
                while ((entry = readdir(dir)) != NULL) {
                    if (entry->d_name[0] != '.'
                        && mx_strcmp2(entry->d_name, &parsing[1]) == 0) {
                        path = mx_strdup(entry->d_name);
                        mx_push_front(list_cmd, path);
                    }
                }
                closedir(dir);
            }
        }
    }
    add_file_directory(list_cmd, parsing, &paths);
}
