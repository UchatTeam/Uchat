#include <cJSON.h>
#include "server.h"
#include <string.h>
// #include <../json/cJSON.c>

char *json_message(void) {

    char *string = NULL;
    cJSON *name = NULL;

    cJSON *user = cJSON_CreateObject();
        if (user == NULL)
        {
            exit(2);
        }

    char buff[20];
    memset(buff, '\0', 20);
    size_t logread = read(STDIN_FILENO, buff, sizeof buff);

    name = cJSON_CreateString(buff);
        if (name == NULL)
        {
        exit(2);
        }

    cJSON_AddItemToObject(user, "type", name);
    string = cJSON_Print(user);

    char buff2[20];
    memset(buff2, '\0', 20);
    
    size_t passread = read (STDIN_FILENO, buff2, sizeof buff2);
    name = cJSON_CreateString(buff2);
        if (name == NULL)
        {
        exit(2);
        }

    cJSON_AddItemToObject(user, "message", name);
    string = cJSON_Print(user);
    return string;
}

