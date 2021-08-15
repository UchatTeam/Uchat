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

int mx_insert (t_user *user) {
   sqlite3 *db = user->db;
   char *zErrMsg = 0;
   int rc;
   char *sql = (char *) malloc(1000);
   // char sql[80];
 /* Open database */
   rc = user->rc_db;
   //  rc = sqlite3_open("uchat.db", &db);
   // printf("RCCC: %d", rc);
   
   // if( rc ) {
   //    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
   //    // return(0);
   // } 
   
   // else {
   //    fprintf(stdout, "_Opened database successfully\n");
   //    fflush(stdout);
   // }

   sprintf (sql, "INSERT INTO users (login, password, email) "   \
         "VALUES ('%s', '%s', '%s');", user->login, user->password, user->email);

      // printf("sql -> %s\n", sql);
   printf("Pointer_INsert %p\n", (void*) db);
   printf("Pointer_INsert2222 %p\n", (void*) user->db); 
//  /* Execute SQL statement */
   rc = sqlite3_exec (db, sql, callback, 0, &zErrMsg);

   printf("rc2222: %d\n", rc);
   // rc = 0;
   if ( rc != SQLITE_OK ) {
      fprintf(stderr, "Insert SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   } 
   else {
      fprintf(stdout, "Records created successfully\n");
   }
   return 0;
}

