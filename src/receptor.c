//David Sequera
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "book.h"

void EnviarPipe(book *miemp, int cuantos,char pipe[]) {
  book em;
  int i, creado, fd;
  fd = open(pipe, O_WRONLY);
     if (fd == -1) {
         perror("pipe");
         printf(" Se volvera a intentar despues\n");
	 sleep(5);        
  }
  // este código lo tienen que hacer Uds. Deben abrir el pipe y enviar los datos. 
  write (fd, &cuantos, sizeof(int));
  for (size_t i = 0; i < cuantos; i++)
  {
    write (fd, &miemp[i] , sizeof(book));
  }
	sleep(5);        

  close(fd);


}

/* asignar
   inserta un nuevo empleado en la lista en la posicion pos
   e inicializa su edad, tiempo de trabajo y nombre
*/
void asignar(book *emp, char *nombre, int edad, float salary, int pos)
{
     
  char *p;
  emp[pos].edad = edad;
  emp[pos].salario = salary;
  strcpy(emp[pos].nombre, nombre);
 
}

/* imprimir
   imprime los primeros cuantos empleados del arreglo
*/
void  imprimir(book *emp, int cuantos)
{
  int i;

    printf("Empleados:\n");

  for(i=0; i < cuantos; i++)
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
    /* printf("valid: %s\n", line); */
    /* printf("%d, %d, %s\n", edad, tiempo, nom); */
    asignar(miemp, nom, edad, salario, i++);
  }
  
  imprimir(miemp, i);
  // Enviar por el pipe

  
  EnviarPipe(miemp,i,argv[2]);
  

     
  fclose(fp); 
}
