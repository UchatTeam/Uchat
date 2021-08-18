#include "server.h"

int json_parcelog (cJSON *user_json, t_user *user_str) {
    const cJSON *name = NULL;
    int status = 0;

    name = cJSON_GetObjectItemCaseSensitive(user_json, "name");
    if (cJSON_IsString(name) && (name->valuestring != NULL))
    {
        printf("Checking user \"%s\"\n", name->valuestring);
    }

        cJSON *login = cJSON_GetObjectItemCaseSensitive(user_json, "login");
        cJSON *password = cJSON_GetObjectItemCaseSensitive(user_json, "password");

        user_str->login = (char*) malloc(sizeof(char)* strlen(login->valuestring));
        strcpy(user_str->login, login->valuestring);

        // printf("%s\n", user_str->login);

        user_str->password = (char*) malloc(sizeof(char)* strlen(password->valuestring));
        strcpy(user_str->password, password->valuestring);
        // printf("%s\n", user_str->password);

//         if (!cJSON_IsString(login) || !cJSON_IsString(email))
//         {
//             status = 0;
//             goto end;
//         }

// end:
//     cJSON_Delete(user_json);
     return status;
}
