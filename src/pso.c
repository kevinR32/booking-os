//David Sequera
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <time.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#include "conexion.h" 

query createQuery(char type,  char book[MAXNAME],  int ISBN,int status, char* pipename );


int main (int argc, char **argv)
{
//CONTROL

  int tp,ap, pid, n, bytes;
  mode_t fifo_mode = S_IRUSR | S_IWUSR;
    // if(argc != 3){//./e pipe db
    //     printf ("Bad request: Check Documentation\n");
    //     exit(1);
    // }

//MENU
// informacion quemada
//CREATE QUERY
    query q = createQuery('S',"Love Child",6829,100,"PipePrueba"), response;
    printf("Type: %c\tName: %s\tISBN: %d\tStatus: %d\tPipeName: %s\n",  q.type,q.book,q.ISBN,q.status,q.pipe);

//SENT QUERY
    tp = open("ThePipe", O_WRONLY);
     if (tp == -1) {
        perror("ThePipe");
        printf(" Se volvera a intentar despues\n");
	      sleep(5);        
      }
    printf ("Open ThePipe\n");
    write (tp, &q, sizeof(query));

//WAIT RESPONSE

    unlink(q.pipe);
    if (mkfifo (q.pipe, fifo_mode) == -1) {
        perror("mkfifo");
        exit(1);
    }
    ap = open (q.pipe, O_RDONLY);
    printf ("Open a Pipe\n");

    bytes = read (ap, &response, sizeof(query));
    if (bytes == -1) {
      perror("proceso lector:");
      exit(1);
    }
    if(response.status == 200){
        printf("Success\n");
        exit(0);
    }else{
      exit(1);
    }
    exit(0);
}


query createQuery(char type,  char book[MAXNAME],  int ISBN,int status, char* pipename ){
  query q;
  q.type = type;
  strcpy(q.book,book);
  q.ISBN = ISBN;
  strcpy(q.pipe,pipename);
  q.status = status;
  return q;
}


