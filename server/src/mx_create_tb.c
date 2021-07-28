#include "server.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
   int i;
   printf ("%s", (char*) NotUsed);
   for(i = 0; i<argc; i++) {
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int mx_create_tb () {
    sqlite3 *db;
    char *zErrMsg = 0;
   int rc;
   char *sql;

   /* Open database */
   rc = sqlite3_open("uchat.db", &db);

   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      return(0);
   } 
    else {
      fprintf(stdout, "_Opened database successfully\n");
      fflush(stdout);
   }
    
    /* Create SQL statement */
   sql = "CREATE TABLE users ("  \
      "id INTEGER PRIMARY KEY  AUTOINCREMENT   NOT NULL," \
      "login           TEXT    NOT NULL," \
      "password        TEXT     NOT NULL," \
      "email           CHAR(50));";

   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
   // sqlite3_close(db);
   return 0;
}



