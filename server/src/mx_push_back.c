#include "server.h"

t_list *mx_create_node (void *data);

void mx_push_back (t_list **list, void *data) {
    t_list *temp = *list;
    t_list *new = mx_create_node(data);

    if (*list == NULL) {
        *list = new;
        return;
    }
    else 
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new;
}
