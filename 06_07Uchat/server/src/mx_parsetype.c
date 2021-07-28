#include <cJSON.h>
#include "server.h"
#include <string.h>

int json_parcetype (cJSON *user_json, t_user *str_user) {
    int status = 0;
    const cJSON *name = NULL;
    
    name = cJSON_GetObjectItemCaseSensitive(user_json, "name");
    if (cJSON_IsString(name) && (name->valuestring != NULL))
    {
        printf("Checking user \"%s\"\n", name->valuestring);
    }
        cJSON *type = cJSON_GetObjectItemCaseSensitive(user_json, "type");
        
        str_user->type = (char*) malloc(sizeof(char)* strlen(type->valuestring));
        strcpy(str_user->type, type->valuestring);
        
        if (!cJSON_IsString(type))
        {
            status = 0;
            // goto end;
        }

// end:
// cJSON_Delete(user_json);
return status;
}
