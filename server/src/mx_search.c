#include <cJSON.h>
#include "server.h"
#include <string.h>

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   t_user *user_str = (t_user *) data;
   // int p = strlen((char *)data);
   // printf("HUITA :%d\n\n", p);
//   fprintf(stderr, "%s\n", (const char*)data);
   
//   printf("argc: %d", argc);
   
//   printf("%s = %s\n", azColName[0], argv[0] ? argv[0] : "NULL");
   for(i = 0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   //  send(user_str->fd, "successful login", 30, 0);
   user_str->status_user = 2;
   // printf("ЮЗЕР есть!!!!\n");
   return 0;
}

int mx_search(t_user *user_str) {

   sqlite3 *db = user_str->db;
   char *zErrMsg = 0;
   int rc;
   char *sql = (char *) malloc(1000);
   user_str->status_user = 0;

   /* Open database */
   rc = user_str->rc_db;

   /* Create SQL statement */
   sprintf (sql, "SELECT * From users WHERE login = '%s'", user_str->login);

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)user_str, &zErrMsg);
   
   if( rc != SQLITE_OK ) {
      // printf("YYYYY");
      // fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } 
   else {
      fprintf(stdout, "Operation done successfully\n");
   }

   if(user_str->status_user == LOGIN_OK) {
      send(user_str->fd, "successful login", 16, 0);
      // printf("LOL\n");
   } 
   else { 
      send(user_str->fd, "there is no user with such login", 32, 0);
      // printf("KEK\n");
   } 

   sqlite3_close(db);
   return 0;
}

// сделать открытие базы в серваке в самом начале, вынести, передать указатель в хедер
// onexit
