/*
 * Agenda.h
 *
 *  Created on: 03/12/2014
 *      Author: i32goora
 */

#ifndef AGENDA_H_
#define AGENDA_H_

#include <list>
#include <string>
#include "Contacto.h"
#include "GestorBD.h"

using namespace gestor;	//GestorBD


namespace consulta {

	class Agenda {

		private:
			// Declaramos una variable de tipo puntero a objeto de la clase GestorBD
			GestorBD* gestorbd_;

			std::list<Contacto> listaContactos_;
			void ordenarLista();
			void masFrecuentes(std::string dni);

			bool listadoPacienteHTML(string nomFichero);
			bool listadoPacienteTextoPlano(string nomFichero);

			bool compruebaDNI( string DNI);

		public:
			Agenda(GestorBD* gestorbd);

			virtual ~Agenda();

			bool insertarPaciente(const Contacto &c);
			bool modificarPaciente(string DNI, Contacto &c);
			bool borrarPaciente(std::string dni);
			std::list<Contacto> buscarPaciente(std::string apellido, std::string DNI="");
			bool listadoPaciente(int formato, string nomFichero);

			//Funciones implicadas en el desacople de la BD.
				bool copiaSeguridad();
				bool restaurarCopiaSeguridad();
				bool escribeBD(list<Contacto> listaContactos);
				list<Contacto> leeBD();
			//

	};

} /* namespace consulta */
#endif /* AGENDA_H_ */
