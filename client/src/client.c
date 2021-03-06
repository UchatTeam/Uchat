#include "server.h"

// void set_button_clicked(GtkWidget *button, gpointer data);
// void set_button_clicked(GtkEntry *button, gpointer type);

GtkBuilder     *builder;
GtkButton      *Button_Log, *Button_Reg, *Button_Sub, *Button_Back1, *Button_Back2;
GtkWindow      *Login_Win, *Win_Reg, *Win_Load;
GtkEntry       *Log_Field, *Pass_Field;


const char *Login;

void clicked(GtkWidget* sender, GtkWindow* window)
{
    gtk_widget_hide(gtk_widget_get_toplevel(sender));
    gtk_widget_show_all(GTK_WIDGET(window));
}

void clicked_l(GtkWidget* sender, GtkWindow* window)
{
    t_user *user_str = (t_user *)malloc(sizeof(t_user));
    gtk_widget_hide(gtk_widget_get_toplevel(sender));
    gtk_widget_show_all(GTK_WIDGET(window));
    char *res = json_login(user_str);
}

void clicked_R(GtkWidget* sender, GtkWindow* window)
{
    gtk_widget_hide(gtk_widget_get_toplevel(sender));
    gtk_widget_show_all(GTK_WIDGET(window));
    char *res = json_registr();
}

void button_clicked(GtkEntry *LoginField, gpointer data, GtkWidget *widget)
{
    Login = gtk_entry_get_text(Log_Field);
    //const gchar *pass = gtk_entry_get_text(Pass_Field);
    g_print("%s", Login);
    //g_print("clicked %s\n", pass);
}


void * handle_server(void *user_str_void) {
	t_user *user_str = user_str_void;
    int fd = user_str->sock_desk;

    ssize_t sread;
    char buffs[256];
    char *res;

    char username[20];
    ssize_t userread;

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
                // return 0;

        cJSON *user_json = json_parcer((const char*)buffs);

		json_parcetype(user_json, user_str);
        
        printf("ТИП %s\n", user_str->type);

        //  int cmp = strcmp(user_str->type, "message");
        //  printf ("CMP: %d\n", cmp);


        if (strcmp(user_str->type, "login_response") == 0) {
            // printf("РЕЗУЛЬТАТ:\n");


            char *result;
                result = response_parse (user_json);
                printf("РЕЗУЛЬТАТ:%s\n", result);

            if (strcmp(result, "there is no user with such login") == 0) {
                write(STDOUT_FILENO, result, strlen(result));
                write(STDOUT_FILENO, "\n", 1);
                printf("FROM THREAD\n");
                res = json_login(user_str);
                printf("111111111");
                char lbuff[4];
                sprintf (lbuff, "%lu", strlen(res));
                send (fd, lbuff,4,0);
                send (fd, res, strlen(res), 0);
            }

              // else if (strcmp(user_str->type, "message") == 0) {
        //      json_parsemsg (user_json);
        // }

            else {
                write(STDOUT_FILENO, result, strlen(result));
                write(STDOUT_FILENO, "\n", 1);
                // while (1) { 
                    char *username = json_username();
                    //  memset(username, 0, sizeof(username));
		            //  userread = read (STDOUT_FILENO, username, 20);
                    printf("User Name: %s\n", username);
                    char namelen[4];
                    sprintf (namelen, "%lu", strlen(username));
                    send (fd, namelen,4,0);
                    send (fd, username, strlen(username), 0);

                    char *message = json_message();
                    char lmsg[4];
                    sprintf (lmsg, "%lu", strlen(message));
                    send (fd, lmsg,4,0);
                    send (fd, message, strlen(message), 0);
                // }
                // user_str->status_user = 2;
            }
        }

        else if (strcmp(user_str->type, "message") == 0) {
            json_parsemsg (user_json);
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

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/TrueWin.glade", NULL);
    // builder = gtk_builder_new_from_file("glade/LoginWin.glade");

    Login_Win = GTK_WINDOW(gtk_builder_get_object(builder, "Log_Win"));
    Win_Reg = GTK_WINDOW(gtk_builder_get_object(builder, "Reg_Win"));
    Win_Load = GTK_WINDOW(gtk_builder_get_object(builder, "Load_Win"));

    Button_Log = GTK_BUTTON(gtk_builder_get_object(builder, "LoginButton"));
    g_signal_connect(Button_Log, "clicked", G_CALLBACK(clicked), Win_Load);
    g_signal_connect(Button_Log, "clicked", G_CALLBACK(button_clicked), Log_Field);

    Button_Reg = GTK_BUTTON(gtk_builder_get_object(builder, "RegistButt"));
    g_signal_connect(Button_Reg, "clicked", G_CALLBACK(clicked), Win_Reg);
    Button_Sub = GTK_BUTTON(gtk_builder_get_object(builder, "SubmitRegist"));
    g_signal_connect(Button_Sub, "clicked", G_CALLBACK(clicked), Win_Load);
    Button_Back1 = GTK_BUTTON(gtk_builder_get_object(builder, "Back1"));
    g_signal_connect(Button_Back1, "clicked", G_CALLBACK(clicked), Login_Win);
    Button_Back2 = GTK_BUTTON(gtk_builder_get_object(builder, "backToLog"));
    g_signal_connect(Button_Back2, "clicked", G_CALLBACK(clicked), Login_Win);
    
    
    Log_Field = GTK_ENTRY(gtk_builder_get_object(builder, "LoginField"));
    g_signal_connect(Log_Field, "connect", G_CALLBACK(button_clicked), Win_Load);
    //Pass_Field = GTK_ENTRY(gtk_builder_get_object(builder, "PassField"));

    gtk_widget_show_all(GTK_WIDGET(Login_Win));
/*     gtk_label_set_width_chars(GTK_LABEL(Login_Field), 12);
    gtk_label_set_width_chars(GTK_LABEL(Pass_Field), 12); */


    // set_button_clicked(GtkEntry *button, gpointer type){
    // gtk_entry_set_text(GTK_ENTRY((GtkWidget*) Login_Field), "GtkEntry");
    // gtk_entry_set_text(GTK_ENTRY((GtkWidget*) Pass_Field), "GtkEntry");
    // }



    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    gtk_main();




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
     char lbuff[4];

    if(strcmp(type, "registration\n") == 0) {
        res = json_registr();
        sprintf (lbuff, "%lu", strlen(res));
        send (fd, lbuff,4,0);
        send (fd, res, strlen(res), 0);
        printf("Registration done successfully\n");
        char *res1 = json_login(user_str);
        sprintf (lbuff, "%lu", strlen(res1));
        send (fd, lbuff,4,0);
        send (fd, res1, strlen(res1), 0);
    }
    else if (strcmp(type, "login\n") == 0) {
        printf("FROM MAIN");
        res = json_login(user_str);
        sprintf (lbuff, "%lu", strlen(res));
        send (fd, lbuff,4,0);
        send (fd, res, strlen(res), 0);
    }
        // char lbuff1[4];
        // char lbuff[4];

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
