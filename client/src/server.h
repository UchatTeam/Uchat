#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <pthread.h>
#include <stdbool.h>
#include <sqlite3.h>
#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <cJSON.h>


#define MAX_CLIENTS 128
#define BUFFER_SZ 2048
#define PASSWORD_ERR 1
#define USER_NONE 0
#define LOGIN_OK 2
#define ARRLEN(s) (sizeof(s) / sizeof(*s))

int sockfds[MAX_CLIENTS];

typedef struct user {
// fd для пайпа в который я буду писать
    sqlite3 *db;
    int      port;
    int      rc_db;
    int      sock_desk;
    int      fd;
    int      status_user;
    char    *type;
    char    *login;
    char    *password;
    char    *email;
}              t_user;

typedef struct server {
    sqlite3 *db;
}              t_server;

typedef struct s_list {
    void *data;
    struct s_list *next;
}               t_list;


typedef struct s_reg_win {
    GtkEntry *log_entry;
    GtkEntry *pass_entry;
    GtkLabel *err_log_label;
    GtkLabel *err_pas_label;
    GtkStack *stk;
    GtkEntry *reg_log;
    GtkEntry *reg_pass1;
    GtkEntry *reg_pass2;
    GtkEntry *reg_email;
    GtkLabel *reg_log_label;
    GtkLabel *reg_pas_label1;
    GtkLabel *reg_pas_label2;
    GtkLabel *reg_email_label;
}               t_reg_win;

typedef struct s_chat_win {
    GtkStackSwitcher        *switcher;

    GtkListBox         *contacts_list;
    GtkListBox            *chats_list;
    GtkListBox           *search_list;

    GtkStack            *search_stack;
    GtkStack               *all_stack;
    GtkFixed          *my_profile_box;
    GtkFixed           *u_profile_box;
    GtkBox              *edit_vax_box;

    GtkFixed            *edit_profile;
    GtkLabel             *err_msg_lbl;

    GtkDialog                *err_pop;

    GtkBox                   *msg_box;
    GtkStack           *msg_entry_stk;
    GtkBox             *msg_entry_box;
    GtkBox             *vox_entry_box;

    GtkEntry               *msg_entry;
    GtkListBox            *msg_viewer;

    GtkSearchEntry     *csearch_entry;
    GtkSearchEntry     *fsearch_entry;
    GtkWidget              **fresults;
    GtkWidget     *file_choose_window;

    GtkLabel            *welcome_user;

    GtkLabel            *friend_login;
    GtkScrolledWindow  *scrl_chat_box;

    GtkStack     *add_remove_stk;
    GtkButton          *add_user;
    GtkButton       *remove_user;
    GtkImage    *edit_avatar_img;
    GtkImage *profile_avatar_img;
    GtkLabel      *profile_login;
}                t_chat_win;


// extern u_char *chat;
extern t_reg_win reg_win;



void Connect(int sockfd, struct sockaddr *addr, socklen_t addrlen);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
void Bind(int sockfd, struct sockaddr *addr, socklen_t addrlen);
int json_parcetype (cJSON *user_json, t_user *str_user);
int json_parcereg (cJSON *user_json, t_user *str_user);
int json_parcelog (cJSON *user_json, t_user*user_str);
void Inet_pton (int af, const char *src, void *dst);
int Socket (int domain, int type, int protocol);
void mx_create_tb (sqlite3 **db, int *rc);
void Listen (int sockfd, int backlog);
cJSON *json_parcer (const char *user);
char *json_login(t_user *user);
char *json_registr();
int client (t_user *user_str);
char *json_message(void);
int mx_isspace(char c);
void mx_create_tb ();
int mx_insert ();
int mx_select();
int mx_search();
cJSON *json_parcer (const char *user);
int json_parcetype (cJSON *user_json, t_user *str_user);
char *response_parse (cJSON *user_json);
int json_parsemsg (cJSON *user_json);
char *json_username(void);
// void mx_push_back (t_list **list, void *data);
// t_list *mx_create_node (void *data);
// int mx_create_db();


#endif
