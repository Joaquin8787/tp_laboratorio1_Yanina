#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include "parser.h"
#include "joaquin.h"


/** \brief busca a un empleado mediante su id y retorna su posicion en la lista LinkedList
 *
 * \param idABuscar int* id a buscar
 * \param pArrayListEmployee LinkedList* lista a donde buscar el empleado
 * \return int retorna el indice si pudo encontrarlo y 0 si no lo logro
 *
 */
int buscarEmpleadoId(int* idABuscar, LinkedList* pArrayListEmployee){
	int retorno = 0;
	int id;//id del empleado
	Employee* empleado;

	if(idABuscar != NULL && pArrayListEmployee != NULL){
		for(int i=0;i<ll_len(pArrayListEmployee);i++){
			empleado = (Employee*) ll_get(pArrayListEmployee, i); //tomo un empleado
			employee_getId(empleado,&id); //tomo su id
			if(*idABuscar == id){ //comparo el id que me dieron al que recibi del empleado
			retorno = i; //retorno el indice donde esta ese empelado
			break;
			}
		}
	}
	return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */


int controller_loadFromText(char* path , LinkedList* pArrayListEmployee)
{
    int retorno = 0;
	FILE* auxP;
	if(path != NULL && pArrayListEmployee != NULL){
	auxP = fopen(path,"r");//LO LEO
	if(auxP != NULL){

		parser_EmployeeFromText(auxP ,pArrayListEmployee);
		retorno = 1;
	}
	else{

		printf("No se pudo leer el archivo");
	}
	fclose(auxP);
	}

    return retorno;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee)
{
	 int retorno = 0;
	FILE* auxP;
	if(path != NULL && pArrayListEmployee != NULL){
		auxP = fopen(path,"rb");//LO LEO EN MODO BINARIO
		if(auxP != NULL){
		parser_EmployeeFromBinary(auxP ,pArrayListEmployee);
		retorno = 1;
		}
		else{
		printf("No se pudo leer el archivo\n");
		}

	}
	fclose(auxP);
	return retorno;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee,int* id)
{
	int retorno = 0;

	char nombre[128];
	int horasTrabajadas;
	int sueldo;

	Employee* nuevoEmpleado;

	if(pArrayListEmployee != NULL){
		if(joaquin_getString(nombre,"Ingrese el nombre del empleado","ERROR!!!\n",128,10)
		&&joaquin_getNumero(&horasTrabajadas,"Ingrese las horas trabajadas del empleado","ERROR!!!\n",1,325,10)
		&&joaquin_getNumero(&sueldo,"Ingrese el sueldo del empleado","ERROR!!!\n",1,10000000,10)){
			(*id)++;
			nuevoEmpleado = employee_newParametrosCorrespondientes(id,nombre,&horasTrabajadas,&sueldo);
		}
		if(nuevoEmpleado != NULL){
			ll_add(pArrayListEmployee, nuevoEmpleado);
			retorno = 1;
		}

	}
    return retorno;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = 0;
	int idABuscar;
	int tam;
	int posicion;
	char seguir = 's';

	char auxNombre[128];
	int auxHorasTrabajadas;
	int auxSueldo;
	Employee* empleadoParaModificar;

	if(pArrayListEmployee != NULL){
	tam	= ll_len(pArrayListEmployee); //TOMO EL LARGO DE LA LISTA
	//PIDO EL ID
	do{
		joaquin_getNumero(&idABuscar,"Ingrese el id del empleado que quiere modificar: \n","ERROR!!!\n",0,tam,10);
		posicion = buscarEmpleadoId(&idABuscar, pArrayListEmployee);
		while(posicion == 0){
			printf("ERROR. El id ingresado no existe\n");
			joaquin_getNumero(&idABuscar,"Ingrese el id del empleado que quiere modificar: \n","ERROR!!!\n",0,tam,10);
			posicion = buscarEmpleadoId(&idABuscar, pArrayListEmployee);
		}
			if(posicion != 0){
				//TOMO EL EMPLEADO DE LA LISTA PARA MODIFICARLO
				empleadoParaModificar = (Employee*) ll_get(pArrayListEmployee,posicion);
				printf("------------------------------------------------------------------------\n");
				printf("                       EMPLEADO A MODIFICAR                             \n");
				printf("------------------------------------------------------------------------\n");
				printf("ID              NOMBRE               HORAS TRABAJADAS             SUELDO\n");
				employee_showOneEmployee(empleadoParaModificar);
				printf("------------------------------------------------------------------------\n");

				if(empleadoParaModificar != NULL){
					switch(menuModificaciones()){
					case 1:
					printf("---- NOMBRE ----\n");
					if(joaquin_getString(auxNombre,"Ingrese el nombre del empleado","ERROR!!!\n",128,10)==1){
					employee_setNombre(empleadoParaModificar,auxNombre);
					printf("Se ha modificado el nombre con exito!!!\n");
					}
					break;
					case 2:
					printf("---- HORAS TRABAJADAS ----\n");
					if(joaquin_getNumero(&auxHorasTrabajadas,"Ingrese las horas trabajadas del empleado","ERROR!!!\n",1,325,10)==1){
					employee_setHorasTrabajadas(empleadoParaModificar,auxHorasTrabajadas);
					printf("Se han modificado las horas trabajadas con exito!!!\n");
					}
					break;
					case 3:
					printf("---- SUELDO ----\n");
					if(joaquin_getNumero(&auxSueldo,"Ingrese el sueldo del empleado","ERROR!!!\n",1,10000000,10)==1){
					employee_setSueldo(empleadoParaModificar,auxSueldo);
					printf("Se ha modificado el sueldo con exito!!!\n");
					}
					break;
					}
				}

			}
	joaquin_getCaracter(&seguir,"Quiere modificar otro empleado? (s/n): ","ERROR!!! \n",'n','s',5);
	}while(seguir == 's');

	}
    return retorno;
}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = 0;
	int idABuscar;
	int posicion;
	int tam;
	char seguir = 's';
	char confirmar;
	Employee* empleadoParaEliminar;

	if(pArrayListEmployee != NULL){
		tam	= ll_len(pArrayListEmployee);//TOMO EL LARGO DE LA LISTA
do{
	joaquin_getNumero(&idABuscar,"Ingrese el id del empleado que quiere eliminar: \n","ERROR!!!\n",0,tam,10);
			posicion = buscarEmpleadoId(&idABuscar, pArrayListEmployee);
			while(posicion == 0){
			printf("ERROR. El id ingresado no existe\n");
			joaquin_getNumero(&idABuscar,"Ingrese el id del empleado que quiere eliminar: \n","ERROR!!!\n",0,tam,10);
			posicion = buscarEmpleadoId(&idABuscar, pArrayListEmployee);
			}
			if(posicion != 0){
			//TOMO EL EMPLEADO DE LA LISTA PARA ELIMINARLO
			empleadoParaEliminar = (Employee*) ll_get(pArrayListEmployee,posicion);

			if(empleadoParaEliminar != NULL){
				printf("------------------------------------------------------------------------\n");
				printf("                       EMPLEADO A ELIMINAR                            \n");
				printf("------------------------------------------------------------------------\n");
				printf("ID              NOMBRE               HORAS TRABAJADAS             SUELDO\n");
				employee_showOneEmployee(empleadoParaEliminar);
				printf("------------------------------------------------------------------------\n");
				}
				joaquin_getCaracter(&confirmar,"Esta seguro que quiere eliminar este empleado? (s/n): ","ERROR!!! \n",'n','s',5);
				if(confirmar == 's'){
				employee_delete(empleadoParaEliminar);
				ll_remove(pArrayListEmployee,posicion);
				retorno = 1;
				printf("Se ha eliminado el empleado con exito!!!\n");
				}
			}
joaquin_getCaracter(&seguir,"Quiere eliminar otro empleado? (s/n): ","ERROR!!! \n",'n','s',5);
}while(seguir == 's');
}

    return retorno;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = 0;
	Employee* empleado;
	if(pArrayListEmployee != NULL){
		printf("------------------------------------------------------------------------\n");
		printf("                       LISTA DE EMPLEADOS                               \n");
		printf("------------------------------------------------------------------------\n");
		printf("ID              NOMBRE               HORAS TRABAJADAS             SUELDO\n");
		for(int i= 0; i<ll_len(pArrayListEmployee);i++){
		empleado = (Employee*)ll_get(pArrayListEmployee,i);
		employee_showOneEmployee(empleado);
	 }
		retorno = 1;
	}
    return retorno;
}

/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
	int retorno = 0;
	int order;
	if(pArrayListEmployee != NULL){
		switch(menuOrdenamiento())
				{
			case 1:
				  order = menuOrder();
				  printf("ORDENANDO...\n");
            	  if(!ll_sort(pArrayListEmployee,employee_compareById,order)){
            		  retorno = 1;
            		  printf("Lista ordenada!!!\n");
            	  }
            	  else{
            	  printf("Hubo algun problema al ordenar la lista\n");
            	  }
			break;
			case 2:
				  order = menuOrder();
				  printf("ORDENANDO...\n");
				  if(!ll_sort(pArrayListEmployee,employee_compareByNombre,order)){
					  retorno = 1;
					  printf("Lista ordenada!!!\n");
				   }
				  else{
				  printf("Hubo algun problema al ordenar la lista\n");
				  }
			break;
			case 3:
				  order = menuOrder();
				  printf("ORDENANDO...\n");
				  if(!ll_sort(pArrayListEmployee,employee_compareByHorasTrabajadas,order)){
				  retorno = 1;
				  printf("Lista ordenada!!!\n");
				  }
				  else{
				  printf("Hubo algun problema al ordenar la lista\n");
				  }
			break;
			case 4:
				  order = menuOrder();
				  printf("ORDENANDO...\n");
				  if(!ll_sort(pArrayListEmployee,employee_compareBySueldo,order)){
				    retorno = 1;
				    printf("Lista ordenada!!!\n");
				  }
				  else{
					  printf("Hubo algun problema al ordenar la lista\n");
				  }
			break;
			case 5:
			break;
		}

	}
    return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */

int controller_saveAsText(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = 0;

	int id;
	char nombre[128];
	int horasTrabajadas;
	int sueldo;

	Employee* auxEmpleado;
	FILE* auxP;

	if(pArrayListEmployee != NULL)
	{
		auxP = fopen(path,"w");//Lo abro para escritura
		if(auxP != NULL)
		{
			//Escritura fantasma
			fprintf(auxP,"id,nombre,horasTrabajadas,sueldo\n");

			for(int i = 0;i<ll_len(pArrayListEmployee);i++)
			{
				auxEmpleado = (Employee*) ll_get(pArrayListEmployee,i);
				if(auxEmpleado != NULL)
				{
					if(employee_getId(auxEmpleado,&id)&&
							employee_getNombre(auxEmpleado,nombre)&&
							employee_getHorasTrabajadas(auxEmpleado,&horasTrabajadas)&&
							employee_getSueldo(auxEmpleado,&sueldo))
					{
						fprintf(auxP,"%d,%s,%d,%d\n",id,nombre,horasTrabajadas,sueldo);
						retorno = 1;
					}
				}
			}
		}
		else
		{
			printf("No se pudo escribir en el archivo \n");
		}
		fclose(auxP);
	}

	return retorno;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee)
{
	int retorno = 0;
	FILE* auxP;
	Employee* auxEmpleado;

	if(pArrayListEmployee != NULL)
	{
		auxP = fopen(path,"wb"); //Lo abro para escritura
		if(auxP != NULL)
		{
			for(int i = 0;i<ll_len(pArrayListEmployee);i++)
			{
				auxEmpleado = (Employee*)ll_get(pArrayListEmployee,i);
				if(auxEmpleado != NULL)
				{
					if(fwrite(auxEmpleado,sizeof(Employee),1, auxP) != 1)
					{
						retorno = 0;
						break;
					}
					retorno = 1;
				}
			}
		}
		else
		{
			printf("No se pudo escribir en el archivo");
		}
		fclose(auxP);
	}

 return retorno;
}
