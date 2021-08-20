#include "server.h"

char *json_login_resp (char* response) {

   char *string = NULL;
    cJSON *name = NULL;
   
    cJSON *user = cJSON_CreateObject();
        if (user == NULL)
        {
            exit(2);
        }
    
    name = cJSON_CreateString("login_response");
    cJSON_AddItemToObject(user, "type", name);

    // size_t logread = read(STDIN_FILENO, buff, sizeof buff);

        name = cJSON_CreateString(response);
            if (name == NULL)
            {
            exit(2);
            }

        cJSON_AddItemToObject(user, "login_response", name);
        string = cJSON_Print(user);
        // printf("FROM_JSON_login: %s", string);
        // break;

    return string;
}
