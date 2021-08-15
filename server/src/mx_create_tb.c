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

void mx_create_tb (sqlite3 **db, int *rc) {
   char *zErrMsg = 0;
   char *sql;

   /* Open database */
   // rc = sqlite3_open_v2("uchat.db", &db, SQLITE_OPEN_FULLMUTEX, NULL);
    *rc = sqlite3_open("uchat.db", db);
   printf("RCCC: %d", *rc);
   
   if( *rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(*db));
      // return(0);
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

   *rc = sqlite3_exec(*db, sql, callback, 0, &zErrMsg);
   
   printf("pointer_create: %p\n", (void*) db);
   if( *rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } else {
      fprintf(stdout, "Table created successfully\n");
   }
   // user_str->rc_db = rc;
   // user_str->db = db;
   
   // printf("pointer_cr2: %p\n", (void*) user_str->db);
   // sqlite3_close(db);
   // return 0;
}



