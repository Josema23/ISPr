/*
 * Ficherotexto.cpp
 *
 *  Created on: 18/12/2014
 *      Author: Antonio
 */

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "Ficherotexto.h"
#include "Agenda.h"
#include "Contacto.h"
#include "Funciones.h"

using namespace std;

namespace gestor {

	Ficherotexto::Ficherotexto(const std::string& ruta, const std::string& nombreFichero) {

		ruta_=ruta;
		nombreFichero_=nombreFichero;

		//Se comprueba si existe el fichero y en caso contrario se crea.

		fstream fichero;	//Puntero al fichero con el que vamos a trabajar.

		fichero.open( (ruta_+nombreFichero_).c_str(), ios::in); // abrimos en modo lectura.

		if(fichero.is_open() == true){

			//El fichero existe. Lo cerramos.
			fichero.close();

		}else{

			//El fichero no existe, lo creamos.

			fichero.open( (ruta_+nombreFichero_).c_str(), ios::out); // abrimos en modo escritura.
			if(fichero.is_open() == true){

				//El fichero se ha creado correctamente. Lo cerramos.
				fichero.close();

			}
			else{

				//Error al crear el fichero.
				cout << endl << "ERROR!! No se pudo crear el fichero.. : " << ruta_+nombreFichero_ << endl;
				pulsaIntro();

			}

		}

	}

	Ficherotexto::~Ficherotexto() {

	}

	const std::string& Ficherotexto::getRuta() const {
		return ruta_;
	}

	void Ficherotexto::setRuta(const std::string& ruta) {
		ruta_ = ruta;
	}

	const std::string& Ficherotexto::getNombreFichero() const {
		return nombreFichero_;
	}

	void Ficherotexto::setNombreFichero(const std::string& nombreFichero) {
		nombreFichero_ = nombreFichero;
	}

	bool Ficherotexto::copiaSeguridad() {

		string nombreCopia;
		string ruta;
		string correcto;
		bool resultado=false;	//Partimos de que la operación no se realizó con éxito.

		while(resultado==false){

			nombreCopia="copia";
			ruta="copiaseg/";

			borraPantalla();
			cout << "Copia de Seguridad\n";
			cout << "------------------\n\n";

			cout << "El nombre del fichero para la copia es ' " << ruta+nombreCopia << " '\n";
			cout << "Desea cambiar el nombre de la copia? (S/N)..: ";
			cin >> correcto;

			if (correcto=="S" || correcto=="s"){

				cout << "Nueva ruta ...: ";

				//Para quitar el /n
				getchar();

				getline(cin, ruta);

				cout << "Nuevo nombre..: (sin extensión) ";

				getline(cin, nombreCopia);

			}

			nombreCopia+=".txt";

			ifstream compruebacopiaFile( (ruta+nombreCopia).c_str() );

			if (compruebacopiaFile){

				//El fichero de copia existe
				compruebacopiaFile.close();
				cout << "El fichero de copia ya existe. Introduzca otro." << endl;
				pulsaIntro(1);

			}else{

				ifstream file( (ruta_+nombreFichero_).c_str() );
				ofstream copiaFile ( (ruta+nombreCopia).c_str() );

				if (!file || !copiaFile ){

					cout << "Error en la apertura de los ficheros." << endl;

					pulsaIntro();

				} else {

					const streamsize size=1024;
					char * buffer = new char [size];

					file.read (buffer,size);

					while (file){

						copiaFile.write (buffer,size);
						file.read (buffer,size);

					}

					//Final de fichero alzanzado.
					//Sólo copiamos los que se han leído.
					copiaFile.write (buffer,file.gcount());

					file.close();
					copiaFile.close();

					delete[] buffer;

					resultado=true;	//Copia realizada con éxito.

				}

			}

		}

		cout << endl;

		return (resultado);
	}

	bool Ficherotexto::restaurarCopiaSeguridad() {

		string nombreCopia;
		string ruta;
		string correcto;
		bool resultado=false;	//Partimos de que la operación no se realizó con éxito.

		while(resultado==false){

			nombreCopia="copia";
			ruta="copiaseg/";

			borraPantalla();
			cout << "Restaurar Copia de Seguridad\n";
			cout << "----------------------------\n\n";

			cout << "El nombre del fichero con la copia es ' " << ruta+nombreCopia << " '\n";
			cout << "Desea cambiar el nombre de la copia? (S/N)..: ";
			cin >> correcto;

			if (correcto=="S" || correcto=="s"){

				cout << "Nueva ruta ...: ";

				//Para quitar el /n
				getchar();

				getline(cin, ruta);

				cout << "Nuevo nombre..: (sin extensión) ";
				getline(cin, nombreCopia);

			}

			nombreCopia+=".txt";

			ifstream restauraFile( (ruta+nombreCopia).c_str() );

			if (!restauraFile){

				//El fichero con la copia no existe-
				cout << "El fichero con la copia no existe. Introduzca otro." << endl;

				pulsaIntro();

			}else{

				ofstream file( (ruta_+nombreFichero_).c_str() );

				if (!file ){

					restauraFile.close();
					cout << "Error en la apertura del fichero." << endl;

					pulsaIntro(1);

				} else {

					const streamsize size=1024;
					char * buffer = new char [size];

					restauraFile.read (buffer,size);

					while (restauraFile){

						file.write (buffer,size);
						restauraFile.read (buffer,size);

					}

					//Final de fichero alzanzado.
					//Sólo copiamos los que se han leído.
					file.write (buffer,restauraFile.gcount());

					file.close();
					restauraFile.close();

					delete[] buffer;

					resultado=true;	//Restauración realizada con éxito.

				}

			}

		}

		cout << endl;

		return (resultado);
	}

	bool Ficherotexto::escribeBD(list<Contacto> listaContactos) {

		bool resultado=true;	//Partimos de que la operación se realizó con éxito.

		std::list<std::string> redessociales;	//Redes sociales de cada contacto.

		list <Contacto> :: iterator it;
		std::list<std::string> :: iterator itr;

		ofstream file;

		try{

			file.open( (ruta_+nombreFichero_).c_str() );

			for (it = listaContactos.begin(); it != listaContactos.end() ; it++){

				file << it->getNombre() << "\n";
				file << it->getApellido() << "\n";
				file << it->getDni() << "\n";
				file << it->getTlfFijo() << "\n";
				file << it->getTlfMovil() << "\n";
				file << it->getDireccionpostal() << "\n";
				file << it->getEmail() << "\n";
				file << it->getObservaciones() << "\n";
				file << it->isFavorito() << "\n";
				file << it->getFrecuente() << "\n";

				//Escribimos las distintas redes sociales del contacto.
				redessociales=(*it).getRedessociales();

				for (itr = redessociales.begin(); itr != redessociales.end() ; itr++){

					//Guarda la red social y la separa de la siguiente por una coma.
					file << *(itr) << ',';

				}

				//Doble coma para saber que ya no tiene más redes sociales.
				file << ',';

				//Salto de línea.
				file << "\n";
			}

			file.close();

		}catch(...){

				resultado=false; //Se produjo un error.

		}

		return (resultado);

	}

	list<Contacto> Ficherotexto::leeBD() {

		list<Contacto> listaContactos;

		std::string DNI;
		std::string nombre;
		std::string apellido;
		std::string tlf_fijo;
		std::string tlf_movil;
		std::string email;
		std::string direccionpostal;
		std::string observaciones;
		std::list<std::string> redessociales;
		std::string favorito;	//Al crear el contacto se pasará a bool
		std::string frecuente;	//Al crear el contacto se pasará a int

		std::string redSocial;

		ifstream file;

		file.open( (ruta_+nombreFichero_).c_str() );

		while(getline(file,nombre,'\n')){

			//Leemos los datos del contacto.

			getline(file,apellido,'\n');

			getline(file,DNI,'\n');

			getline(file,tlf_fijo,'\n');

			getline(file,tlf_movil,'\n');

			getline(file,direccionpostal,'\n');

			getline(file,email,'\n');

			getline(file,observaciones,'\n');

			getline(file,favorito,'\n');

			getline(file,frecuente,'\n');

			//Leemos las distintas redes sociales del contacto.

			getline(file,redSocial,',');
			while(redSocial!=""){

				redessociales.push_back(redSocial);
				getline(file,redSocial,',');

			}

			//Creamos el contacto con los datos leídos.

			{
				Contacto c(DNI,nombre,apellido,tlf_fijo,tlf_movil,email,direccionpostal,observaciones,
					   redessociales,
					   (favorito=="1"?true:false),
					   atoi(frecuente.c_str()));

				//Añadimos el contacto a la lista de contactos.

				listaContactos.push_back(c);

			}

			//Borramos las redes sociales del contacto creado.
			redessociales.clear();

			//Lee el salto de línea para posicionarse al principio del campo nombre.
			getline(file,redSocial,'\n');

		}

		//Cerramos el fichero.
		file.close();

		//Retornamos la lista de contactos.
		return (listaContactos);

	}

}

