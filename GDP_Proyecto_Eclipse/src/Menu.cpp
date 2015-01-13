/*
 * Menu.cpp
 *
 *  Created on: 03/12/2014
 *      Author: i32goora
 */

#include <iostream>
#include <cstdlib>
#include <list>

#include "Agenda.h"
#include "Contacto.h"
#include "Ficherotexto.h"	//Funciones relacionadas con el fichero de texto que almacena la agenda.
#include "Funciones.h"		//Funciones auxiliares.

using namespace std;
using namespace gestor;
using namespace consulta;



int main() {

	//La agenda se almacena en el fichero agenda.txt
	Ficherotexto* f = new Ficherotexto("","agenda.txt");

	Agenda a = Agenda(f);

	int opcion;
	bool resultado;

	do {

		opcion = menu();

		switch (opcion){

			case 1: //Insertar paciente

					resultado=menuInsertarPaciente(a);

					if(resultado==false){

						cout << "No se pudo insertar correctamente el contacto. Compruebe el DNI" << endl;
					}
					else{

						cout << "El contacto se insertó correctamente." << endl;

					}
					pulsaIntro();

					break;

			case 2: //Consultar paciente

					menuBuscarPaciente(a);

					break;

			case 3: //Listar pacientes

					resultado=menuListadoPacientes(a);

					if(resultado==true){

						cout << "Listado creado correctamente." << endl;


					}else{

						cout << "El Listado no se pudo crear." << endl;

					}

					pulsaIntro();

					break;

			case 4: //Copia de seguridad

					resultado=a.copiaSeguridad();

					if(resultado==true){

						cout << "Copia de Seguridad realizada con éxito." << endl;


					}else{

						cout << "La Copia de Seguridad no pudo ser realizada con éxito." << endl;

					}

					pulsaIntro(1);

					break;

			case 5: //Restaurar copia de seguridad

					resultado=a.restaurarCopiaSeguridad();

					if(resultado==true){

						cout << "Copia de Seguridad restaurada con éxito." << endl;


					}else{

						cout << "La Copia de Seguridad no se pudo restaurar." << endl;

					}

					pulsaIntro(1);

					break;

			case 6: //Salir.

					cout<<"¡Hasta luego!"<<endl;
					break;

			default : //Opción incorreta.

					cout << "La opción elegida no es correcta!" << endl;
					pulsaIntro();

					break;

		}

	} while (opcion != 6);

	return 0;

}
