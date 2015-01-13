/*
 * GestorBD.h
 *
 *  Created on: 18/12/2014
 *      Author: i32goora
 */

#ifndef GESTORBD_H_
#define GESTORBD_H_

	#include "Contacto.h"

	using namespace std;
	using namespace consulta;

	namespace gestor {

		class GestorBD {

			public:

				GestorBD() {};
				virtual ~GestorBD() {};

				virtual bool copiaSeguridad() = 0;
				virtual bool restaurarCopiaSeguridad() = 0;
				virtual bool escribeBD(list<Contacto> listaContactos)= 0;
				virtual list<Contacto> leeBD() = 0;

		};

}

#endif /* GESTORBD_H_ */

