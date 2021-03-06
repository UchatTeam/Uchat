#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sqlite3.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <cJSON.h>

#define MAX_CLIENTS 128
#define PASSWORD_ERR 1
#define BUFFER_SZ 2048
#define USER_NONE 0
#define LOGIN_OK 2
#define ARRLEN(s) (sizeof(s) / sizeof(*s))



int sockfds[MAX_CLIENTS];

typedef struct login {
    int fd;
    char *login;
}             t_login;


typedef struct s_list {
    t_login *log_str;
    struct s_list *next;
}              t_list;

t_list *logged_in_users;

typedef struct user {
    sqlite3 *db;
    int      rc_db;
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




void Connect(int sockfd, struct sockaddr *addr, socklen_t addrlen);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
void Bind(int sockfd, struct sockaddr *addr, socklen_t addrlen);
int json_parcetype (cJSON *user_json, t_user *str_user);
int json_parcereg (cJSON *user_json, t_user *str_user);
int json_parcelog (cJSON *user_json, t_user*user_str);
void Inet_pton (int af, const char *src, void *dst);
// void mx_push_back (t_list **list, void *data);
int Socket (int domain, int type, int protocol);
void mx_create_tb (sqlite3 **db, int *rc);
// t_list *mx_create_node (void *data);
void Listen (int sockfd, int backlog);
cJSON *json_parser (const char *user);
// int mx_create_db();
void mx_create_tb ();
int mx_insert ();
int mx_search(t_user *user_str, t_login *login);
int json_parsemsg (cJSON *user_json);
char *json_login_resp (char* response);
t_list *mx_create_node (t_login *log_str);
void mx_push_back (t_list **list, t_login *log_str);
int json_parseusername (cJSON *user_json);

#endif
