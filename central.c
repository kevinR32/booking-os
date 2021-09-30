//David Sequera
#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>

#include "book.h" 


int main (int argc, char **argv)
{
  int fd, pid, n, bytes;
  book em;

  mode_t fifo_mode = S_IRUSR | S_IWUSR;
  
  unlink(argv[1]);
  if (mkfifo (argv[1], fifo_mode) == -1) {
     perror("mkfifo");
     exit(1);
  }

  
  fd = open (argv[1], O_RDONLY);
  printf ("Abrio el pipe\n");
  bytes = read (fd, &n, sizeof(int));
    if (bytes == -1) {
      perror("proceso lector:");
      exit(1);
    }
  for (size_t i = 0; i < n; i++)
  {
    
    bytes = read (fd, &em, sizeof(book));
    if (bytes == -1) {
      perror("proceso lector:");
      exit(1);
    }
    printf ("Empleado\n\tNombre:%s\n\tEdad:%d\n\tSalario:%f\n",em.nombre,em.edad,em.salario);
  }

}