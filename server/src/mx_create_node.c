#include "server.h"

t_list *mx_create_node (t_login *log_str) {

    if(log_str == NULL)
        return 0;
    else {
        t_list *tmp = (t_list *)malloc(sizeof(t_list));
        tmp->log_str = log_str;
        tmp->next = NULL;
        return tmp;
    }
}
