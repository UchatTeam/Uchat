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


#define MAX_CLIENTS 128
#define BUFFER_SZ 2048
#define ARRLEN(s) (sizeof(s) / sizeof(*s))
#define USER_NONE 0
#define PASSWORD_ERR 1
#define LOGIN_OK 2

int sockfds[MAX_CLIENTS];

typedef struct user {
// fd для пайпа в который я буду писать
    int port;
    int sock_desk;
    int fd;
    int status_user;
    char *type;
    char *login;
    char *password;
    char *email;
}              t_user;

typedef struct s_list {
    void *data;
    struct s_list *next;
} t_list;


int Socket (int domain, int type, int protocol);
void Bind(int sockfd, struct sockaddr *addr, socklen_t addrlen);
void Listen (int sockfd, int backlog);
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
void Connect(int sockfd, struct sockaddr *addr, socklen_t addrlen);
void Inet_pton (int af, const char *src, void *dst);
char *create_user(void);
char *json_registr(void);
char *json_message(void);
char *json_login(t_user *user);
int mx_isspace(char c);
int client (t_user *user_str);

#endif
