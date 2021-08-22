#include "server.h"

char *json_username(void) {

   char *string = NULL;
    cJSON *name = NULL;
   
    cJSON *user = cJSON_CreateObject();
        if (user == NULL)
        {
            exit(2);
        }
    
    name = cJSON_CreateString("username");
    cJSON_AddItemToObject(user, "type", name);


    printf("введите login получателя\n");
    char buff[1000];

    size_t logread = read(STDIN_FILENO, buff, sizeof buff);

    if(strcmp("exit\n",buff) == 0 ) {
        exit(0);
    }

        name = cJSON_CreateString(buff);
            if (name == NULL)
            {
            exit(2);
            }

        cJSON_AddItemToObject(user, "username", name);
        string = cJSON_Print(user);
        // printf("FROM_JSON_login: %s", string);
        // break;

    return string;
}
