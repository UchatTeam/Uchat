#include <cJSON.h>
#include "server.h"
#include <string.h>

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   
   // int p = strlen((char *)data);
   // printf("HUITA :%d\n\n", p);
   fprintf(stderr, "INFORM %s: ", (const char*)data);
   
   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   
   printf("\n");
   return 0;
}

int mx_search(t_user *user) {
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   char *sql = (char *) malloc(1000);
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("uchat.db", &db);
   
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } 
   else {
      fprintf(stderr, "Opened database successfully\n");
   }

   //  sprintf (sql, "INSERT INTO users (login, password, email) "   \
   //       "VALUES ('%s', '%s', '%s');", user->login, user->password, user->email);


   /* Create SQL statement */
   sprintf (sql, "SELECT * From users WHERE login = '%s'", user->login);

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   
   if( rc != SQLITE_OK ) {
      fprintf(stderr, "Huita  SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Operation done successfully-gooooooooooood\n");
   }
   sqlite3_close(db);
   return 0;
}
