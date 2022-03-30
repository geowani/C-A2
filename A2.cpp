#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
const char *nombre_archivo= "registro.dat";

struct Estudiante{
	int codigo, *p_cod;
	char nombre[50], *p_nom[50];
	char apellido[50], *p_ape[50];
	char direccion[150], *p_dir[150];
	int telefono, *p_tel;
};

void agregar();
void abrir();
void buscar();
void modificar();
void eliminar();

int main(){
	char op;
	char op2;
	do{
		system("cls");
		fflush(stdin);
		int op=0;
	cout<<"---------Menu principal----------"<<endl<<endl;
	cout<<endl;
	cout<<"1. Agregar registros"<<endl;
	cout<<"2. Ver registros"<<endl;
	cout<<"3. Buscar registros"<<endl;
	cout<<"4. Modificar registros"<<endl;
	cout<<"5. Eliminar registros"<<endl;
	cout<<"6. Salir"<<endl;
	cout<<endl;
	cout<<"Respuesta: ";
	cin>>op;
	if((op>6) || (op<=0)){
		cout<<"eleccion invalida intenta de nuevo";
	}
	switch(op){
		case 1:
			agregar();
			break;
		case 2:
			 abrir();
			break;
		case 3:
			 buscar();
			break;
		case 4:
			 modificar();
			break;
		case 5:
			 eliminar();
			break;
		case 6:
	
			break;
		}
	cout<<"Deseas regresar al menu principal (s/n)";
	cin>>op2;
	}while((op2=='s')||(op2=='S'));
	return 0;
	system("cls");
}

void agregar(){
	char continuar;
	FILE* archivo = fopen("registro.data", "ab");
	
	Estudiante estudiante;
	string nombre,apellido,direccion;
	do{
		system("cls");
		cout<<"--------------Nuevo Registro--------------"<<endl;
		cout<<endl;
		fflush(stdin);
		cout<<"Ingresa el codigo:";
		cin>>estudiante.codigo;
		cin.ignore();
		cout<<"Ingresa el nombre:";
		getline(cin,nombre);
		strcpy(estudiante.nombre,nombre.c_str());
		cout<<"Ingresa el apellido:";
		getline(cin,apellido);
		strcpy(estudiante.apellido,apellido.c_str());
		cout<<"Ingresa la direccion:";
		getline(cin,direccion);
		strcpy(estudiante.direccion,direccion.c_str());
		cout<<"Ingresa el telefono:";
		cin>>estudiante.telefono;
		cin.ignore();
		fwrite(&estudiante,sizeof(Estudiante),1,archivo);
		cout<<endl;
		cout<<"Quieres ingresar otro estudiante (s/n)";
		cin>>continuar;
	}while((continuar=='s')||(continuar=='S'));
	system("cls");
	fclose(archivo);
}

void abrir(){
	system("cls");
	FILE* archivo= fopen("registro.data","rb");
	Estudiante estudiante;
	cout<<"--------------Registros Ingresados--------------"<<endl<<endl;
	if(!archivo){
		archivo=fopen("registro.data","w+b");
	}
	else{
		
		int registro=0;
		fread (&estudiante,sizeof(Estudiante),1,archivo);
		cout<<"___________________________________________________________"<<endl;
		cout<<"id"<<"|"<<"Codigo"<<"|"<<"Nombre"<<"|"<<"Apellido"<<"|"<<"Direccion"<<"|"<<"Telefono"<<""<<endl;
		do{
			cout<<"______________________________________________________________"<<endl;
			cout<<endl;
			cout<<registro<<"|"<<estudiante.codigo<<"|"<<estudiante.nombre<<"|"<<estudiante.apellido<<"|"<<estudiante.direccion<<"|"<<estudiante.telefono<<endl;
			fread(&estudiante,sizeof(Estudiante),1,archivo);
			registro +=1;
		}while(feof(archivo)==0);
		cout<<endl;
		fclose(archivo);
	}
	fclose(archivo);
}

void buscar(){
	FILE* archivo= fopen("registro.data","rb");
	
	int pos=0;
	system ("cls");
	cout<<"--------------Busqueda De Registros--------------"<<endl;
	cout<<endl;
	cout<<"Ingrese el ID del registro que desea ver: "<<endl;
	cin>>pos;
	cout<<"-----------NO de ID: "<<pos<<"----------"<<endl;
	fseek(archivo,pos* sizeof(Estudiante), SEEK_SET);
	Estudiante estudiante;
	fread(&estudiante, sizeof(Estudiante),1,archivo);
	cout<<"Codigo: "<<estudiante.codigo<<endl;
	cout<<"Nombre: "<<estudiante.nombre<<endl;
	cout<<"Apellido: "<<estudiante.apellido<<endl;
	cout<<"Direccion: "<<estudiante.direccion<<endl;
	cout<<"Telefono:"<<estudiante.telefono<<endl;
	cout<<endl;
	fclose(archivo);
	
}

void modificar(){
	FILE* archivo= fopen("registro.data","r+b");
	int id;
	system("cls");
	cout<<"--------------Modificar Registros--------------"<<endl;
	cout<<endl;
	string nombre,apellido,direccion;
	Estudiante estudiante;
	cout<<"Ingresa el ID que quieres cambiar:";
	cin>>id;
	fseek(archivo,id* sizeof(Estudiante),SEEK_SET);
	cout<<"Ingrese el codigo:";
	cin>>estudiante.codigo;
	cin.ignore();
	cout<<"Ingrese el nombre:";
	getline(cin,nombre);
	strcpy(estudiante.nombre,nombre.c_str());
	cout<<"Ingrese el apellido:";
	getline(cin,apellido);
	strcpy(estudiante.apellido,apellido.c_str());
	cout<<"Ingresa la direccion:";
	getline(cin,direccion);
	strcpy(estudiante.direccion,direccion.c_str());
	cout<<"Ingrese el telefono:";
	cin>>estudiante.telefono;
	fwrite(&estudiante,sizeof(Estudiante),1,archivo);
	fclose(archivo);
}

void eliminar(){
		FILE *archivo;
	archivo=fopen("registro.data","rb");
	system("cls");
	cout<<"--------------Eliminar Registros--------------"<<endl;
	cout<<endl;
	if(archivo==NULL)
		exit(1);
	cout<<"Ingresa el codigo a eliminar:";
	int cod;
	cin>>cod;
	Estudiante estudiante;
	FILE* nuevo;
	nuevo=fopen("aux.tmp","ab");
	if(archivo==NULL)
		exit(1);
	int existe=0;
	fread(&estudiante,sizeof(Estudiante),1,archivo);
	while(!feof(archivo)){
		if(cod==estudiante.codigo){
			cout<<"Registro seleccionado:"<<"|"<<estudiante.codigo<<"|"<<estudiante.nombre<<"|"<<estudiante.apellido<<"|"<<estudiante.direccion<<"|"<<estudiante.telefono<<endl;
			cout<<endl;
			cout<<"Registro eliminado!"<<endl;
			cout<<endl;
			existe=1;
		}
		else{
			fwrite(&estudiante,sizeof(Estudiante),1,nuevo);
		}
		fread(&estudiante,sizeof(Estudiante),1,archivo);
	}
	if(existe==0)
		cout<<"No existe alumno con este codigo";
	fclose(archivo);
	fclose(nuevo);
	
	remove("registro.data");
	rename("aux.tmp","reg.data");
}
