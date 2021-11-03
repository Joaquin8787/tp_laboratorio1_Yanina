#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Employee.h"
#include "joaquin.h"

int altaEmpleado(){

}
Employee* employee_new(){
	Employee* nuevoEmpleado = NULL;
	nuevoEmpleado = (Employee*)malloc(sizeof(Employee));
	if(nuevoEmpleado != NULL){
		employee_setId(nuevoEmpleado, 0);
		employee_setNombre(nuevoEmpleado," ");
		employee_setHorasTrabajadas(nuevoEmpleado,0);
		employee_setSueldo(nuevoEmpleado,0);
	}

	return nuevoEmpleado;
}

Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr, char* sueldoStr){
	Employee* nuevoEmpleado = NULL;
	if(idStr != NULL && nombreStr != NULL && horasTrabajadasStr != NULL && sueldoStr != NULL){

		nuevoEmpleado = employee_new();

		if(nuevoEmpleado != NULL){
			if(employee_setId(nuevoEmpleado, atoi(idStr))==1||
			employee_setNombre(nuevoEmpleado,nombreStr)==1||
			employee_setHorasTrabajadas(nuevoEmpleado,atoi(horasTrabajadasStr))==1||
			employee_setSueldo(nuevoEmpleado,atoi(sueldoStr))==1){

				printf("NO SE PUDO CARGAR EL EMPLEADO PORQUE FALLO ALGUN SETTER\n"); //DEBUG
				free(nuevoEmpleado);
				nuevoEmpleado = NULL;

			}

		}
	}
	return nuevoEmpleado;
}
Employee* employee_newParametrosCorrespondientes(int* id,char* nombre,int* horasTrabajadas, int* sueldo){
	Employee* nuevoEmpleado = NULL;
		if(id != NULL && nombre != NULL && horasTrabajadas != NULL && sueldo != NULL){

			nuevoEmpleado = employee_new();

			if(nuevoEmpleado != NULL){
				if(employee_setId(nuevoEmpleado, id)==1||
				employee_setNombre(nuevoEmpleado,nombre)==1||
				employee_setHorasTrabajadas(nuevoEmpleado,horasTrabajadas)==1||
				employee_setSueldo(nuevoEmpleado,sueldo)==1){

					printf("NO SE PUDO CARGAR EL EMPLEADO PORQUE FALLO ALGUN SETTER\n"); //DEBUG
					free(nuevoEmpleado);
					nuevoEmpleado = NULL;
				}
			}
		}
		return nuevoEmpleado;

}

//SETTERS Y GETTERS
int employee_setId(Employee* this, int id)
{
    int retorno=1;
    if(this!=NULL && id>0)
    {
        this->id=id;
        retorno=0;
    }
    return retorno;
}

int employee_getId(Employee* this, int* id)
{
    int retorno=1;
    if(this!=NULL)
    {
        *id = this->id;
        retorno=0;
    }
    return retorno;
}

int employee_setNombre(Employee* this,char* nombre)
{
    int retorno=1;
    if(this!=NULL && nombre!=NULL && strlen(nombre)>1 && strlen(nombre)<30)
    {
        strcpy(this->nombre,nombre);

        retorno=0;
    }
    return retorno;
}
int employee_getNombre(Employee* this,char* nombre)
{
    int retorno=1;
    if(this!=NULL && nombre!=NULL)
    {
        strcpy(nombre,this->nombre);
        retorno=0;
    }
    return retorno;
}

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas)
{
    int retorno=1;
    if(this!=NULL && horasTrabajadas>=0)
    {
        this->horasTrabajadas=horasTrabajadas;
        retorno=0;
    }
    return retorno;
}
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas)
{
    int retorno=1;
    if(this!=NULL && horasTrabajadas!=NULL)
    {
        *horasTrabajadas=this->horasTrabajadas;
        retorno=0;
    }
    return retorno;
}

int employee_setSueldo(Employee* this,int sueldo)
{
    int retorno=1;
    if(this!=NULL && sueldo>0)
    {
        this->sueldo=sueldo;
        retorno=0;
    }
    return retorno;
}
int employee_getSueldo(Employee* this,int* sueldo)
{
    int retorno=1;
    if(this!=NULL && sueldo!=NULL)
    {
        *sueldo=this->sueldo;
        retorno=0;
    }
    return retorno;
}
