/*
 * Funciones.h
 *
 *  Created on: 18/12/2014
 *      Author: i32goora
 */

#ifndef FUNCIONES_H_
#define FUNCIONES_H_

	#include "Agenda.h"
	#include "Contacto.h"

	using namespace consulta;

	//Funciones auxiliares.

	int menu();

	void mostrarContacto(Contacto c);

	void menuBuscarPaciente(Agenda &a);

	void ModificarBorrarPaciente(Agenda &a, Contacto &c);

	void pideDatosModificarPaciente(Contacto &c);

	bool menuListadoPacientes(Agenda &a);

	bool menuInsertarPaciente(Agenda &a);

	bool comparacion(const Contacto &Primero,const Contacto &Segundo);

	void pulsaIntro(int veces=2);

	void borraPantalla();

#endif /* FUNCIONES_H_ */

