#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "server.h"
#include <string.h>
#include <pthread.h>
#include <fcntl.h>

void * handle_server(void* fdser) {
    int fd = *(int*)fdser;
    ssize_t sread;
    char buffs[256];

    while(1) {
        memset(buffs, 0, sizeof(buffs));
		sread = read (fd, buffs, 256);

		// read возвращает количество считанных байт и поместит в nread
		if (sread == -1) {
			perror("read failed");
			exit(EXIT_FAILURE);
		}
		if (sread == 0) {
			printf("END OF FILE occured\n");
			close(fd);
			return NULL;
		}
		// напечатаем в консоли то, что мы получили:
		write(STDOUT_FILENO, buffs, sread);
		// передадим на клиента ответ (он будет таким же, что мы и получили):
		// write(fd, buffs, sread);
	}
	// printf("%s", create_user()); 
	return NULL;
}

int main (int argc, char **argv) {
    // создаём сокет
    pthread_t spth;

    printf("%d\n", argc);
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    // порт должет совпадать с сервером
    addr.sin_port = htons(atoi(argv[1]));
    // задать адресс
    // Inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    Connect(fd, (struct sockaddr *) &addr, sizeof addr);

    ssize_t nread;
    char buff[256];
    
    pthread_create(&spth, NULL, handle_server, &fd);

    // int counter = 0;
    // char *buffer;

    // char *new1 = json_registr();
    // FILE *file = fopen ("new.txt", "w");
    // fprintf (file,"%s", new1); 
    // fclose(file);

    // int file1 = open ("new.txt", O_RDONLY);
    //      while (read(file1, &buffer, 1))
    //             counter++;
    // close(file1);
    // printf("reading file: %d\n", counter);

    //  printf("%lu\n", strlen(json_registr()));
    // write(STDOUT_FILENO, json_registr(), 256);

    while(1) {
        // memset(buff, 0, sizeof(buff));
        // nread = read(STDOUT_FILENO, buff, 256);

        // if (nread == -1) {
	    // 	perror("bind failed");
	    // 	exit(EXIT_FAILURE);
	    // }
        // if (nread == 0) {
	    // 	printf("END OF FILE occured\n");
	    // }
    char *res;

// Вместо GTK
    char type[20];
    memset(type, '\0', 20);
    size_t logread = read(STDIN_FILENO, type, sizeof type);
// 
    // printf("%s",type);
    // printf("STRCMP:%d", strcmp(type, "registration"));

    if(strcmp(type, "registration\n") == 0) {
        res = json_registr();
    }
    else if (strcmp(type, "login\n") == 0) {
        res = json_login();
    }

        // char lbuff1[4];
        char lbuff[4];

        sprintf (lbuff, "%lu", strlen(res));
        send (fd, lbuff,4,0);
        send (fd, res, strlen(res), 0);

        // sprintf (lbuff1, "%lu", strlen(res1));
        // send (fd, lbuff1,4,0);
        // send (fd, res1, strlen(res1), 0);
    }
    // printf("HUITA: %s", buff);
    //напечатаем в консоли то, что мы получили:
	//  write(STDOUT_FILENO, buff, nread);
    sleep(5);
    close (fd);
    return 0;
}
