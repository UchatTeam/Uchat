#include "server.h"

cJSON *json_parcer (const char *user) {

    cJSON *user_json = cJSON_Parse(user);

    if (user_json == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        exit(2);
    }
    return user_json;
}
