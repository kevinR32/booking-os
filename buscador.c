//David Sequera
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "book.h"

void sendPipe(book *miemp, int cuantos,char pipe[]) {
  book em;
  int i, creado, fd;
  fd = open(pipe, O_WRONLY);
     if (fd == -1) {
         perror("pipe");
         printf(" Se volvera a intentar despues\n");
	      sleep(5);        
      }
  // este código abre el pipe y enviar los datos. 
  write (fd, &cuantos, sizeof(int));
  for (size_t i = 0; i < cuantos; i++)
  {
    write (fd, &miemp[i] , sizeof(book));
  }
	sleep(5);        

  close(fd);


}

/* set
   inserta un nuevo empleado en la lista en la posicion pos
   e inicializa su edad, tiempo de trabajo y nombre
*/
void set(book *emp, char *nombre, int edad, float salary, int pos)
{
     
  char *p;
  emp[pos].edad = edad;
  emp[pos].salario = salary;
  strcpy(emp[pos].nombre, nombre);
 
}

/* printBook
   imprime los primeros cuantos empleados del arreglo
*/
void  printBook(book *emp, int cuantos)
{
  printf("Empleados:\n");
  for(int i=0; i < cuantos; i++)
    printf("%s %d %f\n",  emp[i].nombre, emp[i].edad, emp[i].salario);
}


int main(int argc, char *argv[]) 
{
  book miemp[MAXEMP];
  char line[MAXLIN], nom[MAXNOMBRE];
  FILE *fp;
  int i, edad=0;
  float salario;
  
  fp = fopen(argv[1], "r");
  i = 0;

  while (!feof(fp))  {
    fscanf(fp, "%s %d %f\n", nom,&edad, &salario);
    set(miemp, nom, edad, salario, i++);
  }
  
  printBook(miemp, i);
  // Enviar por el pipe
  sendPipe(miemp,i,argv[2]);
     
  fclose(fp); 
}
