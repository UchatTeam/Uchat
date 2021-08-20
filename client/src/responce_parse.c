#include "server.h"

char *response_parse (cJSON *user_json) {
    const cJSON *name = NULL;
    int status = 0;
    
    name = cJSON_GetObjectItemCaseSensitive(user_json, "name");
    if (cJSON_IsString(name) && (name->valuestring != NULL))
    {
        printf("Checking user \"%s\"\n", name->valuestring);
    }

        cJSON *rsp = cJSON_GetObjectItemCaseSensitive(user_json, "login_response");

        char *response = (char*) malloc(sizeof(char)* strlen(rsp->valuestring));
        // printf("%lu\n", strlen(msg->valuestring));
        // printf("В ПАРСИНГЕ\n");
        strcpy(response, rsp->valuestring);

        // printf("%s\n", response);

     return response;
}
