#include <cJSON.h>
#include "server.h"
#include <string.h>

int json_parcereg (cJSON *user_json, t_user *str_user) {
    int status = 0;
    const cJSON *name = NULL;

    name = cJSON_GetObjectItemCaseSensitive(user_json, "name");
    if (cJSON_IsString(name) && (name->valuestring != NULL))
    {
        printf("Checking user \"%s\"\n", name->valuestring);
    }
        // cJSON *type = cJSON_GetObjectItemCaseSensitive(user_json, "type");
        cJSON *login = cJSON_GetObjectItemCaseSensitive(user_json, "login");
        cJSON *password = cJSON_GetObjectItemCaseSensitive(user_json, "password");
        cJSON *email = cJSON_GetObjectItemCaseSensitive(user_json, "Email");

        // printf("llll: %s\n", login->string);
        // printf("%s: %s\n", login->string, login->valuestring);
        // printf("%s: %s\n", password->string, password->valuestring);
        // printf("%s: %s\n", email->string, email->valuestring);
        // str_user->type = (char*) malloc(sizeof(char)* strlen(type->valuestring));
        // strcpy(str_user->type, type->valuestring);

        str_user->login = (char*) malloc(sizeof(char)* strlen(login->valuestring));
        strcpy(str_user->login, login->valuestring);

        str_user->password = (char*) malloc(sizeof(char)* strlen(password->valuestring));
        strcpy(str_user->password, password->valuestring);

        str_user->email = (char*) malloc(sizeof(char)* strlen(email->valuestring));
        strcpy(str_user->email, email->valuestring);

        if (!cJSON_IsString(login) || !cJSON_IsString(password) || !cJSON_IsString(email))
        {
            status = 0;
            goto end;
        }
        
    //     if ((width->valuedouble == 1920) && (height->valuedouble == 1080))
    //     {
    //         status = 1;
    //         goto end;
    //     }
    // }

end:
    cJSON_Delete(user_json);
     return status;
}
