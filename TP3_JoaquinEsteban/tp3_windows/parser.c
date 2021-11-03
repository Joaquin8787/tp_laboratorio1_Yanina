#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromText(FILE* pFile , LinkedList* pArrayListEmployee)
{
	int retorno = 1;
	int cantidad;
	char buffer1[1024];
	char buffer2[1024];
	char buffer3[1024];
	char buffer4[1024];

	Employee* nuevoEmpleado;

	if(pFile != NULL &&  pArrayListEmployee != NULL){
		// Lectura fantasma
		    fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", buffer1, buffer2, buffer3, buffer4);
		    //DEBUG
		    printf("%s   %s    %s    %s\n\n", buffer1, buffer2, buffer3, buffer4);

		    while(!feof(pFile)) //RECORRO HASTA QUE LEA CADA LINEA DEL ARCHIVO
		        {
		            cantidad = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", buffer1, buffer2, buffer3, buffer4);
		            if( cantidad < 4){ //VERIFICO QUE HAYA PODIDO LEVANTAR CADA CAMPO
		                break;
		              }

		            nuevoEmpleado = employee_newParametros(buffer1, buffer2,buffer3,buffer4); //CONSTRUYO UN NUEVO EMPLEADO

		            ll_add(pArrayListEmployee, nuevoEmpleado); //AGREGO AL LINKEDLIST

		            retorno = 0;
		        }
	}
    return retorno;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_EmployeeFromBinary(FILE* pFile , LinkedList* pArrayListEmployee)
{

    return 1;
}
