/*
 * Funciones.cpp
 *
 *  Created on: 18/12/2014
 *      Author: i32goora
 */
 
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <list>


#include "Agenda.h"
#include "Contacto.h"
#include "Funciones.h"

using namespace std;
using namespace consulta;


int menu() {

	int opcion;

	borraPantalla();

	cout << "\tMENU" << endl << endl;
	cout << "1. Insertar paciente" << endl;
	cout << "2. Consultar paciente" << endl;
	cout << "3. Listar pacientes" << endl;
	cout << "4. Copia de seguridad" << endl;
	cout << "5. Restaurar copia de seguridad" << endl;
	cout << "6. Salir" << endl << endl;
	cout << "Seleccione una opción: ";

	cin >> opcion;

	return opcion;
}



void mostrarContacto(Contacto c) {

	std::list<std::string> redessociales;	//Redes sociales del contacto.
	std::list<std::string> :: iterator itr;

	cout << "Apellidos y nombre....: " << c.getApellido() << ", " << c.getNombre() << "\n";
	cout << "DNI...................: " << c.getDni() << "\n";
	cout << "Telefono fijo.........: " << c.getTlfFijo() << "\n";
	cout << "Telefono movil........: " << c.getTlfMovil() << "\n";
	cout << "Direccion postal......: " << c.getDireccionpostal() << "\n";
	cout << "Email.................: " << c.getEmail() << "\n";
	cout << "Observaciones.........: " << c.getObservaciones() << "\n";
	cout << "Favorito..............: " << (c.isFavorito()==1?"Sí":"No") << "\n";
	cout << "Frecuencia............: " << c.getFrecuente() << "\n";
	cout << "Redes sociales........: ";

	//Imprimimos las distintas redes sociales del contacto.
	redessociales=c.getRedessociales();

	for (itr = redessociales.begin(); itr != redessociales.end() ; itr++){

		//Imprime la red social y la separa de la siguiente por una coma.
		cout << *(itr) << ',';

	}

	cout << endl;

}



void menuBuscarPaciente(Agenda &a) {

	string apellido;
	string dni;
	string modifica;
	string busqueda;
	list <Contacto> :: iterator it;
	list <Contacto> auxC;
	Contacto contAux;
	unsigned int tam;
	int salir=0;
	int controlador=0;

	do {

		borraPantalla();
		cout << "Consultar Paciente\n";
		cout << "------------------\n\n";

		cin.ignore();
		cout << "Seleccione el apellido...: "; //Introduce el apellido de la persona a buscar
		getline (cin, apellido);

		cout << endl;

		auxC=a.buscarPaciente(apellido); //Busca contactos con ese apellido y devuelve una lista
		tam=auxC.size();

		if (tam == 0){

			cout << "No se ha encontrado. ¿Quiere seguir buscando? (S/N)...: ";
			cin >> 	busqueda;

			if (busqueda=="N" || busqueda=="n"){
				salir=1;
			}
		}

	} while (tam == 0 && salir==0);

	if (salir==0){

		if (tam == 1){ //Si hay una sola persona

			contAux=auxC.front();

			//Muestra por pantalla los datos del contacto.
			mostrarContacto (contAux);

			//Llamando a la función buscarPaciente mandándole el DNI llama a la función
			//masFrecuentes(DNI) para actualizar el campo frecuente_
			a.buscarPaciente(apellido, contAux.getDni());

			cout << endl;

			cout << "Desea modificar el contacto? (S/N) "; // Indica si desea modicarlo
			cin >> modifica;

			if (modifica=="S" || modifica=="s"){
				ModificarBorrarPaciente( a, contAux );
			}

		} else { //Hay más de una persona con el mismo apellido

			for (it = auxC.begin() ; it != auxC.end() ; it++) {
					cout << (*it).getApellido() << ", " << (*it).getNombre()<< ", " << (*it).getDni();
					cout << endl;
			}

			cout << endl;

			cout << "Introduzca el DNI del paciente que quiere ver: ";//Introduce el DNI de la persona que busca
			getline(std::cin, dni);

			cout << endl;

			for (it = auxC.begin() ; (it != auxC.end() && controlador==0); it++) {
				if ( dni ==  (*it).getDni() ) {
					contAux=(*it);
					controlador=1;
				}
			}

			if (controlador==1){

				//Se encontró al contacto que se quiere modificar.

				//Muestra por pantalla los datos del contacto.
				mostrarContacto (contAux);

				//Llamando a la función buscarPaciente mandándole el DNI llama a la función
				//masFrecuentes(DNI) para actualizar el campo frecuente_
				a.buscarPaciente(apellido, contAux.getDni());

				cout << "Desea modificar el contacto? (S/N) "; // Indica si desea modicarlo
				cin >> modifica;

				if (modifica=="S" || modifica=="s"){
					ModificarBorrarPaciente( a, contAux );
				}
			}else{

				cout << "No se encontró al contacto con DNI ..: " << dni;

				pulsaIntro(1);

			}

		}

	}

}



void ModificarBorrarPaciente(Agenda &a, Contacto &c){

	int opcion;
	bool correcto=false;
	string DNI;

	do {

		cout << endl;

		cout << "1. Modificar" << endl;
		cout << "2. Borrar" << endl;
		cout << "Introduzca la opción...: ";
		cin >> opcion;

		cout << endl;

	} while (opcion != 1 && opcion != 2);

	if (opcion == 2) {

		//Borrar contacto
		correcto=a.borrarPaciente( c.getDni() );

		if (correcto == true){
			cout << "El contacto se borró correctamente." << endl;
		} else {
			cout << "El contacto no pudo ser borrado." << endl;
		}

		pulsaIntro();

	}else{

		DNI=c.getDni();	//DNI del contacto a modificar.

		//Modificar contacto
		pideDatosModificarPaciente( c );

		//Modificamos el contacto en la agenda.
		correcto=a.modificarPaciente(DNI, c);

		if (correcto == true){
			cout << "El contacto se modificó correctamente." << endl;
		} else {
			cout << "El contacto no se pudo modificar. Compruebe el DNI." << endl;
		}

		pulsaIntro();

	}

}



void pideDatosModificarPaciente(Contacto &c) {

	int opcion;
	string nombre;
	string apellido;
	string dni;
	string tlf_fijo;
	string tlf_movil;
	string direccionPostal;
	string email;
	string observaciones;
	string continuar;
	string acierto;

	do
	{
		do
		{
			borraPantalla();
			cout << "Modificar Paciente\n";
			cout << "------------------\n\n";

			cout << "\tOPCIONES" << endl;
			cout << "1. Nombre" << endl;
			cout << "2. Apellidos" << endl;
			cout << "3. DNI" << endl;
			cout << "4. Teléfono fijo" << endl;
			cout << "5. Teléfono móvil" << endl;
			cout << "6. Dirección postal" << endl;
			cout << "7. Email" << endl;
			cout << "8. Observaciones" << endl;
			cout << "9. Favorito" << endl;
			cout << "10. Redes sociales" << endl;
			cout << endl;
			cout << "Escriba la opción del campo a modificar ...: ";
			cin >> opcion;

		} while (opcion>10 || opcion<1);

		//Para quitar el /n
		getchar();

		cout << endl;

		switch (opcion){

			case 1:		//Modificar el nombre.

				cout << "Escriba el nuevo nombre...: ";
				getline (cin, nombre);

				c.setNombre(nombre);
				break;

			case 2:		//Modificar los apellidos.

				cout << "Escriba los nuevos apellidos...: ";
				getline (cin, apellido);

				c.setApellido(apellido);
				break;

			case 3:		//Modificar el DNI.

				do{

					cout << "Escriba el nuevo DNI...: ";
					getline (cin, dni);

					if(dni==""){
						cout << "El DNI no se puede introducir en blanco." << endl;
					}

				}while(dni=="");

				c.setDni(dni);
				break;

			case 4:		//Modificar el teléfono fijo.

				cout << "Escriba el nuevo teléfono fijo...: ";
				getline (cin, tlf_fijo);

				c.setTlfFijo(tlf_fijo);
				break;

			case 5:		//Modificar el teléfono móvil.

				cout << "Escriba el nuevo teléfono móvil...: ";
				getline (cin, tlf_movil);

				c.setTlfMovil(tlf_movil);
				break;

			case 6:		//Modificar la dirección postal.

				cout << "Escriba la nueva dirección postal...: ";
				getline (cin, direccionPostal);

				c.setDireccionpostal(direccionPostal);
				break;

			case 7:		//Modificar el email.

				cout << "Escriba el nuevo email...: ";
				getline (cin, email);

				c.setEmail(email);
				break;

			case 8:		//Modificar las observaciones.

				cout << "Escriba las nuevas observaciones...: ";
				getline(cin, observaciones);

				c.setObservaciones(observaciones);
				break;

			case 9:		//Modificar favorito.

				cout << "Seleccione como favorito (S/N)...: ";
				getline (cin, acierto);

				if (acierto=="S" || acierto=="s"){
					c.setFavorito(true);
				} else {
					c.setFavorito(false);
				}

				break;

			case 10:	//Modificar las redes sociales.

				{

					list<std::string> redesSocialesContacto;

					int opcion;
					string redSocial;

					do {
						cout << "1. Añadir Red social" << endl;
						cout << "2. Borrar Red social" << endl;
						cout << "Introduzca la opción ...: ";
						cin >> opcion;
					} while (opcion != 1 && opcion != 2);

					//Para quitar el /n
					getchar();

					cout << "Introduzca la red social ..: ";
					getline (cin, redSocial);

					redesSocialesContacto=c.getRedessociales();

					if(opcion==1){

						//Añadir Red social
						redesSocialesContacto.push_back(redSocial);

						c.setRedessociales(redesSocialesContacto);

						cout << "La Red social " << redSocial << " se insertó correctamente." << endl;

					}else{

						//Borrar Red social
						std::list<std::string> :: iterator itr;
						bool borrada=false;	//Partimos de que la Red social no se encuentra.

						for(itr=redesSocialesContacto.begin();(itr!=redesSocialesContacto.end() && borrada==false);itr++){

							if( (*itr) == redSocial ){

								//Se encontró la Red social. Se borra.
								redesSocialesContacto.erase(itr);
								borrada=true;

							}

						}

						if(borrada==false){

							cout << "No se encontró la Red social " << redSocial << " para borrar." << endl;

						}else{

							c.setRedessociales(redesSocialesContacto);

							cout << "La Red social " << redSocial << " se borró correctamente." << endl;

						}

					}

					pulsaIntro(1);

				}

				break;
		}

		cout << endl;

		cout << "Desea hacer otra modificación...: (S/N)";
		cin >> continuar;

	}while (continuar=="S" || continuar=="s");

	cout << endl;

}



bool menuListadoPacientes(Agenda &a) {

	int formato;
	string nomFichero;
	string correcto;

	bool resultado=false;	//Partimos de que el listado no se genera correctamente.

	while(resultado==false){

		do{

			borraPantalla();
			cout << "Listar Pacientes\n";
			cout << "----------------\n\n";

			cout << "1.- Texto plano" << endl;
			cout << "2.- HTML" << endl;

			cout << endl;

			cout << "Introduzca el formato del listado (1,2) ..: ";
			cin >> formato;

		}while(formato<1 || formato>2);

		cout << "Introduzca el nombre del fichero (sin extensión) ..: " << endl;
		cin >> nomFichero;

		cout << "¿ Datos correctos ? (S/N)..: ";
		cin >> correcto;

		if(correcto=="S" || correcto=="s"){

			resultado=a.listadoPaciente(formato, nomFichero);

			cout << endl;

		}

	}

	return (resultado);

}


bool menuInsertarPaciente(Agenda &a){

	std::string DNI;
	std::string nombre;
	std::string apellido;
	std::string tlf_fijo;
	std::string tlf_movil;
	std::string email;
	std::string direccionpostal;
	std::string observaciones;
	std::list<std::string> redessociales;
	bool favorito;
	int frecuente;

	std::string redSocial;

	std::string masRedes;
	std::string datosCorrectos;
	bool resultado;

	do{

		//Para quitar el /n
		getchar();

		borraPantalla();
		cout << "Insertar Paciente\n";
		cout << "-----------------\n\n";

		cout << "Introduzca los datos del paciente ..: \n";

		do{

			cout << "DNI .................: ";
			getline(std::cin, DNI);
			if(DNI==""){
				cout << "El DNI no se puede introducir en blanco." << endl;
			}

		}while(DNI=="");

		cout << "Nombre ..............: ";
		getline(std::cin, nombre);

		cout << "Apellidos ...........: ";
		getline(std::cin, apellido);

		cout << "Teléfono fijo .......: ";
		getline(std::cin, tlf_fijo);

		cout << "Teléfono móvil ......: ";
		getline(std::cin, tlf_movil);

		cout << "Correo electrónico ..: ";
		getline(std::cin, email);

		cout << "Dirección postal ....: ";
		getline(std::cin, direccionpostal);

		cout << "Observaciones .......: ";
		getline(std::cin, observaciones);

		cout << "¿ Están correctos los datos (S/N)?";
		cin >> datosCorrectos;

	}while(datosCorrectos!="S" && datosCorrectos!="s");

	do{

		//Para quitar el /n
		getchar();

		cout << "Redes sociales ....: ";
		getline(std::cin, redSocial);

		redessociales.push_back(redSocial);

		cout << "¿ Desea introducir otra red más (S/N)? ";
		cin >> masRedes;

	}while(masRedes=="S" || masRedes=="s");

	cout << endl;

	favorito=false;
	frecuente=0;

	Contacto c(DNI,nombre,apellido,tlf_fijo,tlf_movil,email,direccionpostal,observaciones,redessociales,favorito,frecuente);

	resultado=a.insertarPaciente(c);

	return resultado;

}



bool comparacion (const Contacto &Primero,const Contacto &Segundo) {

	bool resultado;		//Resultado de la comparación

	//Ordenamos por apellidos.

	if ( ( Primero.getApellido() ).compare( Segundo.getApellido() ) < 0 ){

		resultado=true;

	} else{

		if ( ( Primero.getApellido() ).compare( Segundo.getApellido() ) == 0 ){

			//Coinciden los apellidos, ordenamos por nombre.

			if ( ( Primero.getNombre() ).compare( Segundo.getNombre() ) < 0 ){

				resultado=true;

			}else{

				resultado=false;

			}

		}else{

			resultado=false;

		}

	}

	//Retornamos el resultado de la comparación.
	return (resultado);

}



void pulsaIntro(int veces){

		//Función que limpia el buffer del teclado y espera a que se pulse INTRO

		cout << endl << "Pulse [INTRO] para continuar." << endl;

		for(int i=0;i<veces;i++){

			getchar();

		}

		return;

}


void borraPantalla(){

		//Función que imprime líneas en blanco para borrar la pantalla.

		for(int i=0;i<50;i++){

			cout << endl;

		}


	return;

}
