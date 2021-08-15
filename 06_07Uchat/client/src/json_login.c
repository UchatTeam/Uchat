#include <cJSON.h>
#include "server.h"
#include <string.h>
// #include <../json/cJSON.c>

static int my_strlen (char *str) {
    int i = 0;
    for(; str[i] != '\n'; i++) {}
    return i;
}

char *json_login(t_user *user_str) {
    
    char *string = NULL;
    cJSON *name = NULL;
   
    cJSON *user = cJSON_CreateObject();
        if (user == NULL)
        {
            exit(2);
        }

int flag = 0;

while (flag == 0) { 
    
    name = cJSON_CreateString("login");
    cJSON_AddItemToObject(user, "type", name);

    printf("логин для авторизации\n");
    char buff[20];
    char buff2[20];

    memset(buff, '\0', 20);
    memset(buff2, '\0', 20);
    // printf("Flag: %d\n", flag);

    size_t logread = read(STDIN_FILENO, buff, sizeof buff);

    // printf("%d\n", my_strlen(buff));

    if (my_strlen (buff) == 0) {
        flag = 1;
    }

    for (int i = 0; i < 20; i++) {
        // printf("i: %d\n", i);
        if (mx_isspace(buff[i]) == 1) {
            // printf("HUITA\n");
            // exit(2);
            flag = 1;
            break;
        }
    }

    // size_t validator = read (user_str->fd, buff2, 256);

    // printf("VALIDATOR: %s", buff2);

    if (flag == 1) {
        printf("логин неверный\nвведите повторно\n"); 
    }
  
    // printf("Flagn: %d\n", flag);

    if (flag == 0) {
        char bufftmp[20];
        int j = 0;

        for (int i = 0; i <= (int)strlen(buff); i++) {
            if(buff[i] != '\n') {
                bufftmp[j] = buff[i];
                j++;
            }
        }
        name = cJSON_CreateString(bufftmp);
            if (name == NULL)
            {
            exit(2);
            }

        cJSON_AddItemToObject(user, "login", name);
        string = cJSON_Print(user);
        // printf("FROM_JSON: %s", string);
        break;
    }   
    flag = 0;
}

int flag1 = 0;

while (flag1 == 0) {

    printf("пароль для авторизации\n");
    char buff2[20];
    memset(buff2, '\0', 20);
    
    size_t passread = read (STDIN_FILENO, buff2, sizeof buff2);

    if (my_strlen (buff2) == 0) {
            flag1 = 1;
    }

     for (int i = 0; i < 20; i++) {
        // printf("i: %d\n", i);
        if (mx_isspace(buff2[i]) == 1) {
            // printf("HUITA\n");
            // exit(2);
            flag1 = 1;
            break;
        }
    }

    if (flag1 == 1) {
        printf("пароль некорректный\nвведите повторно\n"); 
    }

    if (flag1 == 0) {
        char bufftmp2[20];
        int j = 0;

        for (int i = 0; i <= (int)strlen(buff2); i++) {
            if(buff2[i] != '\n') {
                bufftmp2[j] = buff2[i];
                j++;
            }
        }
        name = cJSON_CreateString(bufftmp2);
            if (name == NULL)
            {
            exit(2);
            }

        cJSON_AddItemToObject(user, "password", name);
        string = cJSON_Print(user);
        printf("FROM_JSON_password: %s", string);
        break;
    }
    flag1 = 0;
}
    return string;
}
