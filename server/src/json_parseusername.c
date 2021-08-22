#include "server.h"


int json_parseusername (cJSON *user_json) {
    const cJSON *name = NULL;
    int status = 0;
    
    name = cJSON_GetObjectItemCaseSensitive(user_json, "name");
    if (cJSON_IsString(name) && (name->valuestring != NULL))
    {
        printf("Checking user \"%s\"\n", name->valuestring);
    }

        cJSON *us = cJSON_GetObjectItemCaseSensitive(user_json, "username");

        char *username = (char*) malloc(sizeof(char)* strlen(us->valuestring));
        // printf("%lu\n", strlen(msg->valuestring));
        // printf("В ПАРСИНГЕ\n");
        strcpy(username, us->valuestring);

        printf("USSSSSS %s\n", username);
        free(username);

     return status;
}
