#include "server.h"

int Socket (int domain, int type, int protocol) {
	    int res = socket(domain, type, protocol);
		if (res == -1) {
		perror("err");
		exit(EXIT_FAILURE);
		}
		return res;
}

// привязка сокета к адрессу
void Bind(int sockfd, struct sockaddr *addr, socklen_t addrlen) {
	int res = bind(sockfd, addr, addrlen);
		if (res == -1) {
			perror("bind failed");
			exit(EXIT_FAILURE);
		}
}

void Listen (int sockfd, int backlog) {
	int res = listen (sockfd, backlog);
	if (res == -1) {
		perror("listed failed");
		exit(EXIT_FAILURE);
	}
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
	int res = accept(sockfd, addr, addrlen);
		if (res == -1) {
		perror("accept failed");
		exit(EXIT_FAILURE);
	}
	return res;
}

void Connect(int sockfd, struct sockaddr *addr, socklen_t addrlen) {
    int res = connect (sockfd, addr, addrlen);
    if (res == -1) {
        perror("accept failed");
		exit(EXIT_FAILURE);
	}
}

void Inet_pton (int af, const char *src, void *dst) {
    int res = inet_pton(af, src, dst);
    if (res == 0) {
        printf ("inet_pton failed: src does not contain a character"
                "string representing a valid network address in the specified"
                "adress family\n");
        exit(EXIT_FAILURE);
    }
    if (res == -1) {
        printf ("inet_pton failed\n");
        exit(EXIT_FAILURE);
    }
}
