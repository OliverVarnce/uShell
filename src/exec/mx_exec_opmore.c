#include "ush.h"

static bool printerr(int fd) {
    if (fd == -1) {
        mx_printerr("ush: ");
        mx_printerr(strerror(errno));
        mx_printerr("\n");
        return true;
    }
    return false;
}

static int pipe_w(t_tnode *root, int *fds, int opstat, t_ush *ush) {
    int fdsBuff[2];
    int status = 0;
    int fd = open(((t_token*)(root->right->data))->value[0], MX_FLAGS_WE);

    if (printerr(fd))
        return -1;
    fdsBuff[0] = fds[0];
    fdsBuff[1] = fd;
    status = mx_execute_tree(root->left, fdsBuff, opstat
                             | OP_MORE, ush);
    close(fds[1]);
    fd = open(((t_token*)(root->right->data))->value[0],
              O_RDWR , S_IWRITE | S_IREAD);
    fds[1] = fd;
    status = mx_execute_tree(root->left, fdsBuff, opstat
                             | OP_MORE | LEFT_VISITED, ush);
    close(fd);
    return status;
}

static int pipe_r(t_tnode *root, int *fds, int opstat, t_ush *ush) {
    int fdsBuff[2];
    int status = 0;
    int fd = 0;

    fd = open(((t_token*)(root->right->data))->value[0], MX_FLAGS_W);
    if (printerr(fd))
        return 1;
    fdsBuff[0] = fds[0];
    fdsBuff[1] = fd;
    status = mx_execute_tree(root->left, fdsBuff,
                             opstat | OP_MORE, ush);
    return status;
}

int mx_exec_opmore(t_tnode *root, int *fds, int opstat, t_ush *ush) {
    int fdsBuff[2];
    int status = 0;
    int fd = 0;

    if ((opstat & 3) == 0) {
        fd = open(((t_token*)(root->right->data))->value[0], MX_FLAGS_WE);
        if (printerr(fd))
            return -1;
        fdsBuff[0] = 0;
        fdsBuff[1] = fd;
        status = mx_execute_tree(root->left, fdsBuff,
                                 opstat | OP_MORE, ush);
    }
    if (opstat & OP_PIPE_W)
        status = pipe_w(root, fds, opstat, ush);
    if (opstat & OP_PIPE_R)
        status = pipe_r(root, fds, opstat, ush);
    return status;
}
