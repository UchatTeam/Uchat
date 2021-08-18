#include "server.h"


GtkBuilder     *builder;

void clicked(GtkWidget* sender, GtkWindow* window)
{
    gtk_widget_hide(gtk_widget_get_toplevel(sender));
    gtk_widget_show_all(GTK_WIDGET(window));
}

void * handle_server(void *user_str_void) {
	t_user *user_str = user_str_void;
    int fd = user_str->sock_desk;

    ssize_t sread;
    char buffs[256];
    char *res;

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
            // write(STDOUT_FILENO, buffs, sread);

        if (strcmp(buffs, "there is no user with such login") == 0) {
            write(STDOUT_FILENO, buffs, sread);
            write(STDOUT_FILENO, "\n", 1);
            printf("FROM THREAD\n");
            res = json_login(user_str);
            printf("111111111");
            char lbuff[4];
            sprintf (lbuff, "%lu", strlen(res));
            send (fd, lbuff,4,0);
            send (fd, res, strlen(res), 0);
        }
        else {
            write(STDOUT_FILENO, buffs, sread);
            // user_str->status_user = 2;
        }
        // передадим на клиента ответ (он будет таким же, что мы и получили):
		// write(fd, buffs, sread);
	}
	// printf("%s", create_user());
	return NULL;
}

int main (int argc, char **argv) {

    int status;
    int status_addr;

    GtkButton *Button_Log, *Button_Reg, *Button_Sub, *Button_Back1, *Button_Back2;
    GtkWindow *Login_Win, *Win_Reg, *Win_Load;

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/TrueWin.glade", NULL);
    // builder = gtk_builder_new_from_file("glade/LoginWin.glade");

    Login_Win = GTK_WINDOW(gtk_builder_get_object(builder, "Log_Win"));
    Win_Reg = GTK_WINDOW(gtk_builder_get_object(builder, "Reg_Win"));
    Win_Load = GTK_WINDOW(gtk_builder_get_object(builder, "Load_Win"));

    Button_Log = GTK_BUTTON(gtk_builder_get_object(builder, "LoginButton"));
    g_signal_connect(Button_Log, "clicked", G_CALLBACK(clicked), Win_Load);
    Button_Reg = GTK_BUTTON(gtk_builder_get_object(builder, "RegistButt"));
    g_signal_connect(Button_Reg, "clicked", G_CALLBACK(clicked), Win_Reg);
    Button_Sub = GTK_BUTTON(gtk_builder_get_object(builder, "SubmitRegist"));
    g_signal_connect(Button_Sub, "clicked", G_CALLBACK(clicked), Win_Load);
    Button_Back1 = GTK_BUTTON(gtk_builder_get_object(builder, "Back1"));
    g_signal_connect(Button_Back1, "clicked", G_CALLBACK(clicked), Login_Win);
    Button_Back2 = GTK_BUTTON(gtk_builder_get_object(builder, "backToLog"));
    g_signal_connect(Button_Back2, "clicked", G_CALLBACK(clicked), Login_Win);

    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    gtk_widget_show_all(GTK_WIDGET(Login_Win));
    gtk_main();

    // создаём сокет
    pthread_t spth;
    t_user *user_str = (t_user *)malloc(sizeof(t_user));
    // user_str->status_user = 0;

    printf("%d\n", argc);
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    user_str->sock_desk = fd;

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    // порт должет совпадать с сервером
    addr.sin_port = htons(atoi(argv[1]));
    // задать адресс
    // Inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    Connect(fd, (struct sockaddr *) &addr, sizeof addr);

    ssize_t nread;
    char buff[256];


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

    // while(1) {

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
    printf("READ_TYPE\n");
    size_t logread = read(STDIN_FILENO, type, sizeof type);
//
    // printf("%s",type);
    // printf("STRCMP:%d", strcmp(type, "registration"));

    if(strcmp(type, "registration\n") == 0) {
        res = json_registr();
        // printf("Registration done successfully\n");
    }
    else if (strcmp(type, "login\n") == 0) {
        printf("FROM MAIN");
        res = json_login(user_str);
    }
        // char lbuff1[4];
        char lbuff[4];

        sprintf (lbuff, "%lu", strlen(res));
        send (fd, lbuff,4,0);
        send (fd, res, strlen(res), 0);

    // printf("USER_STATUS: %d\n", user_str->status_user);
        // sprintf (lbuff1, "%lu", strlen(res1));
        // send (fd, lbuff1,4,0);
        // send (fd, res1, strlen(res1), 0);
    // }
    // printf("HUITA: %s", buff);
    //напечатаем в консоли то, что мы получили:
	//  write(STDOUT_FILENO, buff, nread);

    pthread_create(&spth, NULL, handle_server, user_str);

    status = pthread_join(spth, (void**)&status_addr);
    //     if (status != SUCCESS) {
    //     printf("main error: can't join thread, status = %d\n", status);
    //     exit(ERROR_JOIN_THREAD);
    // }

    sleep(5);
    close (fd);

    return 0;
}

void on_LogRegWin_destroy()
{
    gtk_main_quit();
}
