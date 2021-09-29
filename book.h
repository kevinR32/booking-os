/* archivo empleados.h */
/* Adaptado por C. Figueira, mayo 2013
 */

#define MAXEMP 100000
#define MAXLIN 80
#define MAXNOMBRE 20

typedef struct reg {
  char nombre[MAXNOMBRE];
  int edad;
  float salario;
} book;

