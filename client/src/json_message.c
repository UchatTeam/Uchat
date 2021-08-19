#include "server.h"

char *json_message(void) {

   char *string = NULL;
    cJSON *name = NULL;
   
    cJSON *user = cJSON_CreateObject();
        if (user == NULL)
        {
            exit(2);
        }
    
    name = cJSON_CreateString("message");
    cJSON_AddItemToObject(user, "type", name);

    printf("введите сообщение\n");
    char buff[1000];

        size_t logread = read(STDIN_FILENO, buff, sizeof buff);

        name = cJSON_CreateString(buff);
            if (name == NULL)
            {
            exit(2);
            }

        cJSON_AddItemToObject(user, "message", name);
        string = cJSON_Print(user);
        // printf("FROM_JSON_login: %s", string);
        // break;

    return string;
}

