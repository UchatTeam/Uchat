#include <cJSON.h>
#include "server.h"
#include <string.h>

int json_parcelog (cJSON *user_json) {
    const cJSON *name = NULL;
    int status = 0;
    
    name = cJSON_GetObjectItemCaseSensitive(user_json, "name");
    if (cJSON_IsString(name) && (name->valuestring != NULL))
    {
        printf("Checking user \"%s\"\n", name->valuestring);
    }

        cJSON *login = cJSON_GetObjectItemCaseSensitive(user_json, "login");
        cJSON *password = cJSON_GetObjectItemCaseSensitive(user_json, "password");

        char *loginc = (char*) malloc(sizeof(char)* strlen(login->valuestring));
        strcpy(loginc, login->valuestring);

        printf("%s\n", loginc);

        char *passwordc = (char*) malloc(sizeof(char)* strlen(password->valuestring));
        strcpy(passwordc, password->valuestring);
        printf("%s\n", passwordc);

//         if (!cJSON_IsString(login) || !cJSON_IsString(email))
//         {
//             status = 0;
//             goto end;
//         }

// end:
//     cJSON_Delete(user_json);
     return status;
}
