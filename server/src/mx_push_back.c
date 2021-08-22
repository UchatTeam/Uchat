#include "server.h"

void mx_push_back (t_list **list, t_login *log_str) {
    t_list *temp = *list;
    t_list *new = mx_create_node(log_str);

    if (*list == NULL) {
        *list = new;
        return;
    }
    else 
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new;
}
