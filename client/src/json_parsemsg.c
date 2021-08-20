#include "server.h"


int json_parsemsg (cJSON *user_json) {
    const cJSON *name = NULL;
    int status = 0;
    
    name = cJSON_GetObjectItemCaseSensitive(user_json, "name");
    if (cJSON_IsString(name) && (name->valuestring != NULL))
    {
        printf("Checking user \"%s\"\n", name->valuestring);
    }

        cJSON *msg = cJSON_GetObjectItemCaseSensitive(user_json, "message");

        char *message = (char*) malloc(sizeof(char)* strlen(msg->valuestring));
        // printf("%lu\n", strlen(msg->valuestring));
        // printf("В ПАРСИНГЕ\n");
        strcpy(message, msg->valuestring);

        printf("%s\n", message);
        // fflush(stdout);
        // free(message);

     return status;
}


