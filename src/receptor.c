//David Sequera
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#include "conexion.h" 

//main functions
int queriesManager(int qc,query []);
int readQueries(int ap, query []);

//subfunctions


int main (int argc, char **argv)
{
//CONTROL
    if(argc != 3){//./e pipe db
        printf ("Bad request: Check Documentation\n");
        exit(1);
    }

  int tp,ap, pid,bytes; //THEPIPE = tp A PIPE = ap
  query queries[MAXQUERIES];//BUFFER


//OPEN PIPE
  mode_t fifo_mode = S_IRUSR | S_IWUSR;
  
  unlink("ThePipe");
  if (mkfifo ("ThePipe", fifo_mode) == -1) {
     perror("[mkfifo]");
     exit(1);
  }
  
  tp = open ("ThePipe", O_RDONLY);
  printf ("Pipe Opening\n");

//READ QUERIES
    // query counter
    int qc= readQueries(tp,queries);
  //queryManager
    queriesManager(qc, queries);

    /* toca usar un hilo  */
//RESPOND QUERIES
    queries[0].status = 200;
    for (size_t i = 0; i < qc; i++)
    {
      ap = open(queries[i].pipe, O_WRONLY);
      if (ap == -1) {
        perror("A Pipe");
        printf(" Se volvera a intentar despues\n");
	      sleep(5);        
      }
      printf ("Open Apipe\n");
      write (ap, &queries[i], sizeof(query));
    }
    

}


int queriesManager(int qc,query *qv){
  int i = 0;
  int founded = 0;
  book b;
  copy c;
  int size = 100;
  char* sample;
  FILE *fi, *fo;
  fi = fopen("dbin", "r");//recuerda cambiar el argv
  fo = fopen("dbout", "w");
  sample = (char *) malloc (size);
  while (!feof(fi))  {
    getline(&sample,&size,fi);
    printf("%s",sample);
    // fscanf(fi,"%[^,]s,%d,%d\n", b.name,&b.ISBN,&b.copies);
    // printf("%s,%d,%d\n", b.name,b.ISBN,b.copies);
    // for (size_t v = 0; v < qc; v++)
    // {
    //   printf("Comparing\n");
    //   if(strcmp(b.name,(qv+v)->book) == 0   && b.ISBN == (qv+v)->ISBN){//comparar 2 strings
    //     founded = 1;
    //     printf("Founded\n");
    //   }
    // }
    // for (size_t j = 0; j < b.copies; j++)
    // {
    //   fscanf(fi, "%d,%c,%d-%d-%d\n",&c.index,&c.state,&(c.date.day),&(c.date.month),&(c.date.year));
    //   if(founded){
    //     printf("LO LOGRAMOS");
    //   }
    // }    
    i++;
  }
  printf("\n");
  fclose(fi);
  fclose(fo);
}


int readQueries(int tp, query *qv){
    int qc= 0, bytes;
    while (qc != 1)  {//!feof(tp)
        bytes = read (tp, &qv[qc], sizeof(query));
        printf("Type: %c\tName: %s\tISBN: %d\tStatus: %d\tPipeName: %s\n",  qv[qc].type,qv[qc].book,qv[qc].ISBN,qv[qc].status,qv[qc].pipe);
        qc++;
        if (bytes == -1) {
            perror("[Reading Queries]");
            exit(1);
        }
    }
    return qc;
}


