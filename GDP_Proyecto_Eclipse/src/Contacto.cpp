/*
 * Contacto.cpp
 *
 *  Created on: 03/12/2014
 *      Author: i32goora
 */

#include "Contacto.h"

using namespace consulta;

Contacto::Contacto() {

	DNI_="";
	nombre_="";
	apellido_="";
	tlf_fijo_="";
	tlf_movil_="";
	email_="";
	direccionpostal_="";
	observaciones_="";
	favorito_=false;
	frecuente_=0;

}


Contacto::Contacto(std::string DNI, std::string nombre, std::string apellido,std::string tlf_fijo,std::string tlf_movil,std::string email,std::string direccionpostal,std::string observaciones,std::list<std::string> redessociales, bool favorito,int frecuente){

	DNI_=DNI;
	nombre_=nombre;
	apellido_=apellido;
	tlf_fijo_=tlf_fijo;
	tlf_movil_=tlf_movil;
	email_=email;
	direccionpostal_=direccionpostal;
	observaciones_=observaciones;
	favorito_=favorito;
	frecuente_=frecuente;
	redessociales_=redessociales;

}
Contacto::~Contacto() {
	// TODO Auto-generated destructor stub
}

const std::string& Contacto::getApellido() const {
	return apellido_;
}

void Contacto::setApellido(const std::string& apellido) {
	apellido_ = apellido;
}

const std::string& Contacto::getDireccionpostal() const {
	return direccionpostal_;
}

void Contacto::setDireccionpostal(const std::string& direccionpostal) {
	direccionpostal_ = direccionpostal;
}

const std::string& Contacto::getDni() const {
	return DNI_;
}

void Contacto::setDni(const std::string& dni) {
	DNI_ = dni;
}

const std::string& Contacto::getEmail() const {
	return email_;
}

void Contacto::setEmail(const std::string& email) {
	email_ = email;
}

bool Contacto::isFavorito() const {
	return favorito_;
}

void Contacto::setFavorito(bool favorito) {
	favorito_ = favorito;
}

int Contacto::getFrecuente() const {
	return frecuente_;
}

void Contacto::setFrecuente(int frecuente) {
	frecuente_ = frecuente;
}

const std::string& Contacto::getNombre() const {
	return nombre_;
}

void Contacto::setNombre(const std::string& nombre) {
	nombre_ = nombre;
}

const std::string& Contacto::getObservaciones() const {
	return observaciones_;
}

void Contacto::setObservaciones(const std::string& observaciones) {
	observaciones_ = observaciones;
}

const std::list<std::string>& Contacto::getRedessociales() const {
	return redessociales_;
}

void Contacto::setRedessociales(const std::list<std::string>& redessociales) {
	redessociales_ = redessociales;
}

const std::string& Contacto::getTlfFijo() const {
	return tlf_fijo_;
}

void Contacto::setTlfFijo(const std::string& tlfFijo) {
	tlf_fijo_ = tlfFijo;
}

const std::string& Contacto::getTlfMovil() const {
	return tlf_movil_;
}

void Contacto::setTlfMovil(const std::string& tlfMovil) {
	tlf_movil_ = tlfMovil;
}
