#include "ush.h"

t_ush* mx_get_info(t_ush *ush) {
    static t_ush* info_ = 0;

    if (ush == 0)
        return info_;
    else
        info_ = ush;
    return info_;
}
