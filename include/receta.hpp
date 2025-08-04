#ifndef __RECETA_H__
#define __RECETA_H__

#include <iomanip>
#include <iostream>
#include <string>

#include "LSLLSE.hpp"
#include "ingrediente.hpp"
#include "nombre.hpp"

class Receta {
 private:
  std::string nombreReceta, categoria, procedimiento;

  int tiempoProc;

  Nombre autor;

  ListS<Ingrediente> listaIngredientes;

 public:
  Receta();
  Receta(const Receta&);
  ~Receta(){};

  void setNombre(const std::string&);
  void setCategoria(const std::string&);
  void setProcedimiento(const std::string&);
  void setTiempoProc(const std::string&);
  void setAutor(const Nombre&);
  void setIngredientes(const ListS<Ingrediente>&);

  std::string getNombre() const;
  std::string getCategoria() const;
  std::string getProcedimiento() const;
  int getTiempoProc() const;
  Nombre getAutor() const;
  ListS<Ingrediente>& getIngredientes();

  std::string toString() const;

  static int compareByNombre(const Receta&, const Receta&);
  static int compareByCategoria(const Receta&, const Receta&);
  static int compareByTiempo(const Receta&, const Receta&);

  Receta& operator=(const Receta&);

  friend std::ostream& operator<<(std::ostream&, const Receta&);
  friend std::istream& operator>>(std::istream&, Receta&);
};

#endif  // __RECETA_H__