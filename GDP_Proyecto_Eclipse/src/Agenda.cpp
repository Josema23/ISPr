/*
 * Agenda.cpp
 *
 *  Created on: 03/12/2014
 *      Author: i32goora
 */

#include <iostream>
#include <list>
#include <cstdlib>
#include <fstream>
#include <ctime>
//#include <cstddef>

#include "Agenda.h"
#include "Contacto.h"
#include "Funciones.h"
#include "GestorBD.h"

using namespace std;
using namespace gestor;

namespace consulta {

	Agenda::Agenda(GestorBD* gestorbd) {

		gestorbd_ = gestorbd;

		//Rellena la lista de contactos con los existentes en el fichero.
		listaContactos_=leeBD();

	}


	Agenda::~Agenda() {
		// TODO Auto-generated destructor stub
	}

	bool Agenda::copiaSeguridad() {

		/* Llamamos a la función copiaSeguridad() del GestorBD, Agenda no conoce
		 * el objeto que recibe, pero sabe que tiene un método que se llama copiaSeguridad()
		 */

		bool resultado=true;	//Partimos de que la operación se realizó con éxito.

		try{

			if (gestorbd_ != NULL){

				resultado=gestorbd_->copiaSeguridad();

			}

		}
		catch(...){

			resultado=false;	//Error al hacer la copia de seguridad.

		}

		return (resultado);

	}


	bool Agenda::restaurarCopiaSeguridad() {

		bool resultado=true;	//Partimos de que la operación se realizó con éxito.

		try{

			if (gestorbd_ != NULL){

				resultado=gestorbd_->restaurarCopiaSeguridad();
				if(resultado==true){

					//Rellena la lista de contactos con los existentes en el fichero.
					listaContactos_=leeBD();

				}

			}
		}
		catch(...){

			resultado=false;	//Error al restaurar.

		}

		return (resultado);

	}


	bool Agenda::escribeBD(list<Contacto> listaContactos) {

		bool resultado=true;	//Partimos de que la operación se realizó con éxito.

		try{

			if (gestorbd_ != NULL){

				resultado=gestorbd_->escribeBD(listaContactos);

			}

		}
		catch(...){

			resultado=false;	//Error al escribir.

		}

		return (resultado);

	}


	list<Contacto> Agenda::leeBD() {

		list<Contacto> listaContactos;

		if (gestorbd_ != NULL){

				listaContactos=gestorbd_->leeBD();

			}

		return (listaContactos);

	}


	bool Agenda::insertarPaciente(const Contacto& c) {

		bool resultado;

		resultado=true;	//Partimos de que se hizo correctamente.

		try{

			//Comprobamos que el DNI no exista.
			resultado=compruebaDNI( c.getDni() );

			if(resultado==true){

				listaContactos_.push_back(c);

				resultado=gestorbd_->escribeBD(listaContactos_);

			}

		}
		catch(...){

			resultado=false;	//Error al insertar.

		}

		return resultado;

	}


	list <Contacto> Agenda::buscarPaciente (string apellido, string DNI) {

		list <Contacto> auxC;
		list <Contacto> :: iterator it; //iterador lista

		if(DNI!=""){

			//Se recibe el DNI del contacto para llamar a masFrecuentes.
			masFrecuentes(DNI);
			gestorbd_->escribeBD(listaContactos_);	//Actualiza el cambio en la BD

		}else {

			//No se recibe el DNI del contacto.
			//Busca contactos con el mismo apellido y los guarda en la lista.
			for (it = listaContactos_.begin() ; it != listaContactos_.end() ; it++) {
				if (apellido ==  (*it).getApellido() ) {
					auxC.push_back(*it);
				}
			}

		}

		//Retorna la lista con los contactos encontrados.
		return auxC;
	}


	bool Agenda::compruebaDNI( string DNI){

		//Comprueba que el DNI del contacto no existe en la agenda.

		bool resultado=true;	//Partimos de que el DNI del contacto no existe.

		list <Contacto> :: iterator it;

		for (it = listaContactos_.begin() ; (it != listaContactos_.end() && resultado==true) ; it++) {

			if (DNI == (*it).getDni() ) {

				//Se encontró el DNI
				resultado=false;

			}
		}

		return (resultado);

	}


	bool Agenda::modificarPaciente(string DNI, Contacto &c) {

		bool resultado=true;	//Partimos de que el contacto se modifica correctamente.
		bool modificado=false;

		list <Contacto> :: iterator it;

		if(DNI!=c.getDni()){

			//Se modificó el DNI
			//Comprobamos que el nuevo DNI no exista.
			resultado=compruebaDNI( c.getDni() );

		}

		if(resultado==true){
			//El DNI no existe, el contacto se puede actualizar.

			for (it = listaContactos_.begin() ; (it != listaContactos_.end() && modificado==false) ; it++) {

				if (DNI == (*it).getDni() ) {

					c.setFrecuente((*it).getFrecuente());	//Actualizamos el valor del campo frecuente_

					listaContactos_.erase(it);				//Borramos el contacto antiguo
					listaContactos_.push_back(c);			//Insertamos el nuevo con los cambios
					resultado=gestorbd_->escribeBD(listaContactos_);	//Actualiza el cambio en la BD

					modificado=true;

				}
			}

		}

		return (resultado);
	}


	bool Agenda::borrarPaciente(string dni) {

		list <Contacto> :: iterator it;
		bool resultado;

		for (it = listaContactos_.begin() ; it != listaContactos_.end() ; it++) {
			if (dni == (*it).getDni() ) {
				listaContactos_.erase(it);
				resultado=gestorbd_->escribeBD(listaContactos_);	//Actualiza el cambio en la BD
				return resultado;
			}
		}

		//No se encontró el DNI
		return false;
	}


	bool Agenda::listadoPaciente(int formato, string nomFichero) {

		bool resultado;

		//Primero ordenamos la lista de contactos.
		ordenarLista();

		//Listamos los contactos en el formato elegido.
		switch (formato){

			case 1: //Texto plano

				resultado=listadoPacienteTextoPlano(nomFichero+".txt");

				break;

			case 2: //HTML

				resultado=listadoPacienteHTML(nomFichero+".html");

				break;
		}

		return (resultado);

	}


	bool Agenda::listadoPacienteHTML(string nomFichero){

		int nContactos;			//Número de contactos que hay en la agenda.
		bool resultado=true;	//Partimos de que el listado se genera correctamente.

		std::list<std::string> redessociales;	//Redes sociales de cada contacto.

		list <Contacto> :: iterator it;
		std::list<std::string> :: iterator itr;

		ofstream file;

		nContactos=0;

		//Para imprimir la fecha y hora.
			time_t rawtime;
			struct tm * timeinfo;
			char fecha[30];
			char hora[30];

			time (&rawtime);
			timeinfo = localtime (&rawtime);
		//

		strftime (fecha,30,"Fecha ...: %d-%m-%y",timeinfo);	//obtenemos la fecha
		strftime (hora,30, "Hora ....: %X",timeinfo);	//obtenemos la hora

		try{

			file.open( nomFichero.c_str() );

			//Configuración HTML y CSS
				file << "﻿<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">" << endl;
				file << "<html xmlns=\"http://www.w3.org/1999/xhtml\" xml:lang=\"es\">" << endl;

				file << "<head>" << endl;
				file << "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"/>" << endl;
				file << "<title>Listado de contactos</title>" << endl;

				file << "<style type=\"text/css\">" << endl;

				file << "body {  background: #d6d6ec;" << endl;
				file <<	"		 font-family: Arial;" << endl;
				file << "		 font-size: 13px;" << endl;
				file << "		 text-align: right;" << endl;
				file << "}" << endl;

				file << ".cabecera {  border-style: solid;" << endl;
				file <<	"			  border-width: 1px;" << endl;
				file <<	"			  background-color: #e0f4c5;" << endl;
				file <<	"			  text-align: center;" << endl;
				file <<	"			  font-size: 16px;" << endl;
				file <<	"			  font-weight:bold;" << endl;
				file <<	"}" << endl;

				file << ".pie {  border-style: solid;" << endl;
				file <<	"		 border-width: 1px;" << endl;
				file <<	"		 background-color: #e0f4c5;" << endl;
				file <<	"		 padding: 6px;" << endl;
				file <<	"		 text-align: center;" << endl;
				file <<	"}" << endl;

				file << ".separador {  background-color: #d6d6ec;" << endl;
				file <<	"			   border-color: #00FF66;" << endl;
				file <<	"			   padding: 2px;" << endl;
				file <<	"}" << endl;

				file << ".contenedor {  background-color: #f9f8eb;" << endl;
				file <<	"				border-style: solid;" << endl;
				file <<	"				border-width: 1px;" << endl;
				file <<	"				display: table;" << endl;
				file <<	"				width: 60%;" << endl;
				file <<	"				margin: auto;" << endl;
				file <<	"}" << endl;

				file << ".contfijo {  background-color: #f9f8eb;" << endl;
				file << "			  text-align: right;" << endl;
				file << "			  padding: 20px 20px 20px 10px;" << endl;
				file << "			  font-weight:bold;" << endl;
				file << "			  display: table-cell;" << endl;
				file << "			  width: 25%;" << endl;
				file <<	"}" << endl;

				file << ".contvariable {  background-color: #f9f8eb;" << endl;
				file <<	"				  text-align: left;" << endl;
				file <<	"				  padding: 20px 30px 20px 0px;" << endl;
				file <<	"				  display: table-cell;" << endl;
				file <<	"				  width: 75%;" << endl;
				file <<	"}" << endl;

				file << "</style>" << endl;
				file << "</head>" << endl;
			//Fin configuración HTML y CSS

			//Comienzo del listado.

				//Cabecera del listado.
				file << "<br/>" << fecha << endl;
				file << "<br/>" << hora << endl;

				file << "<div class=\"cabecera\">" << endl;
				file << "<p>LISTADO DE CONTACTOS</p>" << endl;
				file << "</div>" << endl;
				//

				//Separador.
				file << "<div class=\"separador\">" << endl;
				file << "</div>" << endl;
				//

				for (it = listaContactos_.begin(); it != listaContactos_.end() ; it++){

					//Datos del contacto.

					file << "<div class=\"contenedor\">" << endl;

						file << "<div class=\"contfijo\">" << endl;
							file << "<p>Nombre:</p>" << endl;
							file << "<p>Apellidos:</p>" << endl;
							file << "<p>DNI:</p>" << endl;
							file << "<p>Teléfono fijo:</p>" << endl;
							file << "<p>Teléfono móvil:</p>" << endl;
							file << "<p>Dirección postal:</p>" << endl;
							file << "<p>Email:</p>" << endl;
							file << "<p>Observaciones:</p>" << endl;
							file << "<p>Favorito:</p>" << endl;
							file << "<p>Frecuencia:</p>" << endl;
							file << "<p>Redes sociales:</p>" << endl;
						file << "</div>" << endl;

						file << "<div class=\"contvariable\">" << endl;
							file << "<p>" << it->getNombre() << "</p>" << endl;
							file << "<p>" << it->getApellido() << "</p>" << endl;
							file << "<p>" << it->getDni() << "</p>" << endl;
							file << "<p>" << it->getTlfFijo() << "</p>" << endl;
							file << "<p>" << it->getTlfMovil() << "</p>" << endl;
							file << "<p>" << it->getDireccionpostal() << "</p>" << endl;
							file << "<p>" << it->getEmail() << "</p>" << endl;
							file << "<p>" << it->getObservaciones() << "</p>" << endl;
							file << "<p>" << (it->isFavorito()==1?"Sí":"No") << "</p>" << endl;
							file << "<p>" << it->getFrecuente() << "</p>" << endl;
							file << "<p>";

							//Imprimimos las distintas redes sociales del contacto.
							redessociales=(*it).getRedessociales();

							for (itr = redessociales.begin(); itr != redessociales.end() ; itr++){

								//Imprime la red social y la separa de la siguiente por una coma.
								file << *(itr) << ',';

							}

							file << "</p>" << endl;

						file << "</div>" << endl;

					file << "</div>" << endl;

					nContactos++;

					//Separador de un contacto de otro.
					file << "<div class=\"separador\">" << endl;
					file << "</div>" << endl;
					//

				}

				file << "<div class=\"pie\">" << endl;

					if (nContactos==0){
						file << "La agenda está vacía.";
					}else{
						file << "Total contactos listados: " << nContactos;
					}

				file << "</div>" << endl;

				//Separador.
				file << "<div class=\"separador\">" << endl;
				file << "</div>" << endl;
				//

				//Pie del listado.
				file << "<div class=\"pie\">" << endl;
					file << "Final del listado";
				file << "</div>" << endl;

				//Cerramos el fichero.
				file.close();

		}catch(...){

			resultado=false; //Se produjo un error.

		}

		return (resultado);
	}


	bool Agenda::listadoPacienteTextoPlano(string nomFichero){

		int nContactos;			//Número de contactos que hay en la agenda.
		bool resultado=true;	//Partimos de que el listado se genera correctamente.

		std::list<std::string> redessociales;	//Redes sociales de cada contacto.

		list <Contacto> :: iterator it;
		std::list<std::string> :: iterator itr;

		ofstream file;

		nContactos=0;

		//Para imprimir la fecha y hora.
			time_t rawtime;
			struct tm * timeinfo;
			char fecha[30];
			char hora[30];

			time (&rawtime);
			timeinfo = localtime (&rawtime);
		//

		strftime (fecha,30,"Fecha ...: %d-%m-%y",timeinfo);	//obtenemos la fecha
		strftime (hora,30, "Hora ....: %X",timeinfo);	//obtenemos la hora

		try{

			file.open( nomFichero.c_str() );

			//Cabecera del listado.
				file << endl;
				file << "        LISTADO DE CONTACTOS                     " << fecha << endl;
				file << "------------------------------------             " << hora << endl;
				file << endl << endl;
			//


			for (it = listaContactos_.begin(); it != listaContactos_.end() ; it++){

				//Datos del contacto.
				file << "     Nombre ...............: " << it->getNombre() << "\n";
				file << "     Apellidos ............: " << it->getApellido() << "\n";
				file << "     DNI...................: " << it->getDni() << "\n";
				file << "     Teléfono fijo.........: " << it->getTlfFijo() << "\n";
				file << "     Teléfono móvil........: " << it->getTlfMovil() << "\n";
				file << "     Dirección postal......: " << it->getDireccionpostal() << "\n";
				file << "     Email.................: " << it->getEmail() << "\n";
				file << "     Observaciones.........: " << it->getObservaciones() << "\n";
				file << "     Favorito..............: " << (it->isFavorito()==1?"Sí":"No") << "\n";
				file << "     Frecuencia............: " << it->getFrecuente() << "\n";
				file << "     Redes sociales........: ";

				//Imprimimos las distintas redes sociales del contacto.
				redessociales=(*it).getRedessociales();

				for (itr = redessociales.begin(); itr != redessociales.end() ; itr++){

					//Imprime la red social y la separa de la siguiente por una coma.
					file << *(itr) << ',';

				}

				nContactos++;

				//Separador de un contacto de otro.
				file << endl << endl << "        -----****-----" << endl << endl;
			}

			//Pie del listado.
				file << endl;

				if (nContactos==0){
					file << "     La agenda está vacía." << endl;
				}else{
					file << "     Total contactos listados: " << nContactos << endl;
				}

				file << endl;
				file << "          Final del listado         " << endl;
				file << "------------------------------------" << endl;
			//

			//Cerramos el fichero.
			file.close();

		}catch(...){

			resultado=false; //Se produjo un error.

		}

		return (resultado);

	}


	void Agenda::ordenarLista () {

		listaContactos_.sort(comparacion);

	}


	void Agenda::masFrecuentes(string dni) {

		list <Contacto> :: iterator it;
		bool encontrado=false;

		for (it = listaContactos_.begin() ; (it != listaContactos_.end() && encontrado==false); it++) {
			if (dni == (*it).getDni() ) {
				(*it).setFrecuente( (*it).getFrecuente()+1 );
				encontrado=true;	//Una vez encontrado no sigue buscando.
			}
		}

	}


} /* namespace consulta */
