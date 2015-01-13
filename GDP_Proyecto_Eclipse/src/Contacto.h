/*
 * Contacto.h
 *
 *  Created on: 03/12/2014
 *      Author: i32goora
 */

#ifndef CONTACTO_H_
#define CONTACTO_H_

#include <string>
#include <list>


namespace consulta{

	class Contacto {

		private:

		std::string DNI_;
		std::string nombre_;
		std::string apellido_;
		std::string tlf_fijo_;
		std::string tlf_movil_;
		std::string email_;
		std::string direccionpostal_;
		std::string observaciones_;
		std::list<std::string> redessociales_;
		bool favorito_;
		int frecuente_;

		public:

			Contacto();
			Contacto(std::string DNI, std::string nombre, std::string apellido,std::string tlf_fijo,std::string tlf_movil,std::string email,std::string direccionpostal,std::string observaciones,std::list<std::string> redessociales, bool favorito,int frecuente);
			virtual ~Contacto();

			const std::string& getApellido() const;
			void setApellido(const std::string& apellido);

			const std::string& getDireccionpostal() const;
			void setDireccionpostal(const std::string& direccionpostal);

			const std::string& getDni() const;
			void setDni(const std::string& dni);

			const std::string& getEmail() const;
			void setEmail(const std::string& email);

			bool isFavorito() const;
			void setFavorito(bool favorito);

			int getFrecuente() const;
			void setFrecuente(int frecuente);

			const std::string& getNombre() const;
			void setNombre(const std::string& nombre);

			const std::string& getObservaciones() const;
			void setObservaciones(const std::string& observaciones);

			const std::list<std::string>& getRedessociales() const;
			void setRedessociales(const std::list<std::string>& redessociales);

			const std::string& getTlfFijo() const;
			void setTlfFijo(const std::string& tlfFijo);

			const std::string& getTlfMovil() const;
			void setTlfMovil(const std::string& tlfMovil);

	};

}
#endif /* CONTACTO_H_ */
