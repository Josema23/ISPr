
#include <fstream>
#include <list>
#include "Agenda.h"
#include "Contacto.h"
#include "Ficherotexto.h"	//Funciones relacionadas con el fichero de texto que almacena la agenda.
#include "Funciones.h"		//Funciones auxiliares.

#include "gtest/gtest.h"


using namespace consulta;


TEST(Consulta, Insertar) {

	//Borramos el fichero "agenda.txt" que se genera con los datos de prueba.
	ofstream file;
	file.open( "agenda.txt" );
	file.close();

	//La agenda se almacena en el fichero agenda.txt
	Ficherotexto* f = new Ficherotexto("","agenda.txt");

	//Creamos la agenda.
	Agenda a = Agenda(f);


	Contacto c;
	c.setNombre("Nombre contacto 1");
	c.setApellido("Apellido contacto 1");
	c.setDni("1");

	EXPECT_EQ(true, a.insertarPaciente(c));	//No existe el DNI
	EXPECT_EQ(0, a.insertarPaciente(c));//Ya existe el DNI
	//COMENTARIOS: EXPECT_EQ(false, a.insertarPaciente(NULL));

}


TEST(Consulta, Buscar) {

	//La agenda se almacena en el fichero agenda.txt
	Ficherotexto* f = new Ficherotexto("","agenda.txt");
	list <Contacto> ListaContactos;

	Agenda a = Agenda(f);

	Contacto c;
	c.setNombre("Nombre contacto 2");
	c.setApellido("Apellido contacto 2");
	c.setDni("2");

	EXPECT_EQ("Nombre contacto 2", c.getNombre());
	EXPECT_EQ("Apellido contacto 2", c.getApellido());
	EXPECT_EQ("2", c.getDni());

	EXPECT_EQ(true, a.insertarPaciente(c));//No existe el DNI

	ListaContactos=a.buscarPaciente("Apellido contacto 2");
	EXPECT_EQ(1, ListaContactos.size());

	ListaContactos=a.buscarPaciente("Apellido contacto 3");	//No existe en el fichero.
	EXPECT_EQ(0, ListaContactos.size());

}



TEST(Consulta, Borrar) {

	//La agenda se almacena en el fichero agenda.txt
	Ficherotexto* f = new Ficherotexto("","agenda.txt");
	list <Contacto> ListaContactos;

	Agenda a = Agenda(f);

	EXPECT_EQ(true, a.borrarPaciente("1"));//Existe.
	EXPECT_EQ(true, a.borrarPaciente("2"));//Existe.
	EXPECT_EQ(0, a.borrarPaciente("3"));//No existe

	ListaContactos=a.buscarPaciente("Apellido contacto 2");	//Se ha borrado
	EXPECT_EQ(0, ListaContactos.size());

	ListaContactos=a.buscarPaciente("Apellido contacto 1");	//Se ha borrado
	EXPECT_EQ(0, ListaContactos.size());

}



TEST(Consulta, masFrecuentes) {

	//La agenda se almacena en el fichero agenda.txt
	Ficherotexto* f = new Ficherotexto("","agenda.txt");
	list <Contacto> ListaContactos;
	list <Contacto>::iterator it;

	Contacto c;

	Agenda a = Agenda(f);

	c.setNombre("Nombre contacto 3");
	c.setApellido("Apellido contacto 3");
	c.setDni("3");
	c.setFrecuente(0);
	c.setFavorito(false);

	//Buscamos los contactos que tengan el apellido: Apellido contacto 3
	EXPECT_EQ(true, a.insertarPaciente(c));
	ListaContactos=a.buscarPaciente("Apellido contacto 3");

	EXPECT_EQ(1, ListaContactos.size());


	//Accedemos al contacto.
	it=ListaContactos.begin();

	EXPECT_EQ(0, (*it).isFavorito());
	EXPECT_EQ(0, (*it).getFrecuente());

	//Consultamos el contacto: masfrecuentes++
	a.buscarPaciente("Apellido contacto 3","3");

	//Consultamos el contacto: masfrecuentes++
	a.buscarPaciente("Apellido contacto 3","3");

	//Buscamos los contactos que tengan el apellido: Apellido contacto 3
	ListaContactos=a.buscarPaciente("Apellido contacto 3");

	//Accedemos al contacto.
	it=ListaContactos.begin();

	EXPECT_EQ(1, ListaContactos.size());

	EXPECT_EQ(0, (*it).isFavorito());
	EXPECT_EQ(2, (*it).getFrecuente());	//El contacto se había consultado dos veces previamente.

}

