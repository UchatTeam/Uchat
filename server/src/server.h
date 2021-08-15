#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sqlite3.h>
#include <cJSON.h>

#define MAX_CLIENTS 128
#define BUFFER_SZ 2048
#define ARRLEN(s) (sizeof(s) / sizeof(*s))
#define USER_NONE 0
#define PASSWORD_ERR 1
#define LOGIN_OK 2



int sockfds[MAX_CLIENTS];

typedef struct user {
    sqlite3 *db;
    int rc_db;
    int fd;
    int status_user;
    char *type;
    char *login;
    char *password;
    char *email;
}              t_user;

typedef struct server {
    sqlite3 *db;
}              t_server;

typedef struct s_list {
    void *data;
    struct s_list *next;
}              t_list; 


int Socket (int domain, int type, int protocol);
void Bind(int sockfd, struct sockaddr *addr, socklen_t addrlen);
void Listen (int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
void Connect(int sockfd, struct sockaddr *addr, socklen_t addrlen);
void Inet_pton (int af, const char *src, void *dst);
cJSON *json_parcer (const char *user);
int json_parcetype (cJSON *user_json, t_user *str_user);
int json_parcereg (cJSON *user_json, t_user *str_user);
int json_parcelog (cJSON *user_json, t_user*user_str);
// t_list *mx_create_node (void *data);
// void mx_push_back (t_list **list, void *data);
// int mx_create_db();
void mx_create_tb (sqlite3 **db, int *rc);
void mx_create_tb ();
int mx_insert ();
int mx_select();
int mx_search();

#endif
