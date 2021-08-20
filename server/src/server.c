#include "server.h"


// static int mx_strcmp(const char*s1, const char*s2) {

//     while(*s1 != '\0' || *s2 != '\0') {
//         if (*s1 != *s2)
//         return *s1 - *s2;
//     s1++;
//     s2++;
//     }
//     return 0;
// }


void * handle_client(void *user_str_void) {
	t_user *user_str = user_str_void;
	// printf("jjjjjj %p\n", (void*) user_str->db);
	int fd = user_str->fd;
	ssize_t nread;
	char *bufftxt;
	ssize_t nreadtxt;
	char buff[4];
	int len = 0;

	// free (user_str->email);

	while(1) {

        memset(buff, 0, sizeof(buff));
		nread = read (fd, buff, 4);

				// printf("%ld\n", nread);
				// char *res = json_parcereg (buff);
				// read возвращает количество считанных байт и поместит в nread
		// if (nread == -1) {
		// 	perror("read failed");
		// 	exit(EXIT_FAILURE);
		// }
		// if (nread == 0) {
		// 	printf("END OF FILE occured\n");
		// 	for (int j = 0; j < MAX_CLIENTS; j++) {
		// 		if(fd == sockfds[j]) {
		// 			sockfds[j] = 0;
		// 			break;
		// 		}
		// 	}
		// 	close(fd);
		// 	return NULL;
		// }

		len = atoi(buff);
		printf("len: %d\n", len);

		bufftxt = (char *)malloc(sizeof(char)* len);
		nreadtxt = read (fd, bufftxt, len);

		if (nreadtxt == -1) {
			perror("read failed");
			exit(EXIT_FAILURE);
		}
		if (nreadtxt == 0) {
			printf("END OF FILE occured\n");
			for (int j = 0; j < MAX_CLIENTS; j++) {
				if(fd == sockfds[j]) {
					sockfds[j] = 0;
					break;
				}
		}

			close(fd);
			return NULL;
		}

// printf("\n------------------ DONE ------------------\n");
		// t_user uslist;
		printf("%s\n", bufftxt);
		// t_list *listnew = mx_create_node(user_str);
		cJSON *user_json = json_parser((const char*)bufftxt);

		json_parcetype(user_json, user_str);
		// printf("aaaaa");
		// printf("%s\n", user_str->type);
		//
		if (strcmp(user_str->type, "registration") == 0) {
			json_parcereg (user_json, user_str);
			mx_insert (user_str);
		}

		if (strcmp(user_str->type, "login") == 0) {
			json_parcelog (user_json, user_str);
			// while (user_str->status_user == LOGIN_OK)
			mx_search(user_str);
			
		}

		if (strcmp(user_str->type, "message") == 0) {
			printf("Передаваемое: %s\n", bufftxt);
			json_parsemsg (user_json);  
				for (int j = 0; j < MAX_CLIENTS; j++) {
					if (fd != sockfds[j] && fd != 0) {
						// printf("Huita");
						send(sockfds[j], bufftxt, 256, 0);
					}
				}
		}

		// mx_select();
		// t_list *tmp = listnew;

		// int i = 0;

		// while(tmp) {
		// 	printf ("%d\n", i);
		// 	printf("\n--- CUR node ---\n");
		// 	printf("login: %s\n", ((t_user*)(listnew->data))->login);
		// 	printf("password: %s\n", ((t_user*)(listnew->data))-> password);
		// 	printf("email: %s\n", ((t_user*)(listnew->data))->email);
		// 	printf("\n--- ---- ---\n");
		// 	tmp = tmp->next;
		// 	i++;
		// }
			// printf("status: %d\n", status);
		// напечатаем в консоли то, что мы получили:
		// printf("struct: %s\n", (t_user *)(listnew->data)->login);

		// printf("login: %s\n", ((t_user*)(listnew->data))->login);
		// printf("password: %s\n", ((t_user*)(listnew->data))-> password);
		// printf("email: %s\n", ((t_user*)(listnew->data))->email);

		// write(STDOUT_FILENO, bufftxt, nreadtxt);

		// передаём с сервака другим клиентам
		// for (int j = 0; j < MAX_CLIENTS; j++) {
		// 	if (fd != sockfds[j] && fd != 0) {
		// 		// printf("Huita");
		// 		send(sockfds[j], buff, 256, 0);
		// 	}
		// }
		// передадим на клиента ответ (он будет таким же, что мы и получили):
		// write(fd, buff, nread);
			free (bufftxt);
	}
	return NULL;
}

int main (int argc, char **argv) {
	// t_server *server_str = (t_server *) malloc(sizeof(t_server));
	sqlite3 *base = NULL;
    int rc = 0;
	// mx_create_db();
	mx_create_tb (&base, &rc);
	// create_tables(server_str);

	printf("argc: %d\n", argc);
	pthread_t thr_id;
	// int sockfds[MAX_CLIENTS];
	memset(sockfds, 0, sizeof(int) * MAX_CLIENTS);

	int servfd = socket(AF_INET, SOCK_STREAM, 0);
	// это структура используется для того, что бы задать адресс по протоколу IPv4
	struct sockaddr_in addr = {0};
	// задаём семейство адрессов:
	addr.sin_family = AF_INET;
	// задаём порт на котором сервер будем слушать (так как значение порта на хосте и в сети может иметь разный порядок байт, используется фукция изменения порядка байт от хоста к сети и наоборот)
	addr.sin_port = htons(atoi(argv[1]));
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	Bind (servfd, (struct sockaddr *) &addr, sizeof addr);
	Listen(servfd, MAX_CLIENTS);
	// Для начала приймем одного клиента(в addr записываем информацию о клиенте)
	socklen_t addrlen = sizeof addr;
	// accept создаёт новый сокет для каждого нового соединения и возвращает дискриптор
	// int fd = Accept(servfd, (struct sockaddr *) &addr, &addrlen);
	// Клиент принят, теперь надо прочитать сообщение
	// ssize_t nread;
	// char buff[256];
	// int fd;
	int sockfdindex;

	while(1) {
		t_user *user_str = (t_user *)malloc(sizeof(t_user));

		user_str->db = base;
		user_str->rc_db = rc;

		printf("ppppp %p\n", (void*) user_str->db);
		user_str->fd = Accept(servfd, (struct sockaddr *) &addr, &addrlen);
		// printf ("fd: %d\n", fd);
		for(sockfdindex = 0; sockfdindex < MAX_CLIENTS; sockfdindex++) {
			if(sockfds[sockfdindex] == 0) {
				sockfds[sockfdindex] = user_str->fd;
				pthread_create(&thr_id, NULL, handle_client, user_str);
				break;
			}
		}

		if(sockfdindex == MAX_CLIENTS) {
			// printf("hhhhh");
			send(user_str->fd, "sorry",5, 0);
			close(user_str->fd);
		}

		// printf("connected %d\n", fd);
        // memset(buff, 0, sizeof(buff));
		// nread = read (fd, buff, 256);
		// // read возвращает количество считанных байт и поместит в nread
		// if (nread == -1) {
		// 	perror("read failed");
		// 	exit(EXIT_FAILURE);
		// }
		// if (nread == 0) {
		// 	printf("END OF FILE occured\n");
		// }
		// // напечатаем в консоли то, что мы получили:
		// write(STDOUT_FILENO, buff, nread);
		// // передадим на клиента ответ (он будет таким же, что мы и получили):
		// write(fd, buff, nread);
	}
	// закрываем сокет работы с клиентом
	// close(listen);
	return 0;
}
