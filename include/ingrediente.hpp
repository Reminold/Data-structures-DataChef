#ifndef __INGREDIENTE_H__
#define __INGREDIENTE_H__

#include <iostream>
#include <string>

class Ingrediente {
 private:
  std::string nombre, cantidad;

 public:
  Ingrediente();
  Ingrediente(const Ingrediente& i);
  ~Ingrediente();

  void setNombre(const std::string&);
  void setCantidad(const std::string&);

  std::string getNombre() const;
  std::string getCantidad() const;

  std::string toString() const;

  static int compareByNombre(const Ingrediente&, const Ingrediente&);

  Ingrediente& operator=(const Ingrediente&);

  friend std::ostream& operator<<(std::ostream&, const Ingrediente&);
  friend std::istream& operator>>(std::istream&, Ingrediente&);
};

#endif  // __INGREDIENTE_H__