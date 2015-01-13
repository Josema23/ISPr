/*
 * Ficherotexto.h
 *
 *  Created on: 18/12/2014
 *      Author: i32goora
 */

#ifndef FICHEROTEXTO_H_
#define FICHEROTEXTO_H_

#include "GestorBD.h"
#include "Contacto.h"

using namespace std;
using namespace consulta;

namespace gestor {

	class Ficherotexto: public GestorBD {

		private:

			//Datos necesarios para conectar con el fichero de texto.

			string ruta_;
			string nombreFichero_;

		public:

			Ficherotexto(const std::string& ruta, const std::string& nombreFichero);
			virtual ~Ficherotexto();

			const std::string& getRuta() const;
			void setRuta(const std::string& ruta);

			const std::string& getNombreFichero() const;
			void setNombreFichero(const std::string& nombreFichero);

			//Estas son las funciones que hay que redeclarar del GestorDB.
				bool copiaSeguridad();
				bool restaurarCopiaSeguridad();
				bool escribeBD(list<Contacto> listaContactos);
				list<Contacto> leeBD();
			//

	};

}

#endif

