#include "ingrediente.hpp"

using namespace std;

Ingrediente::Ingrediente() {
  this->nombre = "";
  this->cantidad = "";
}

Ingrediente::Ingrediente(const Ingrediente& i) {
  this->nombre = i.nombre;
  this->cantidad = i.cantidad;
}

Ingrediente::~Ingrediente() {}

void Ingrediente::setNombre(const string& s) { this->nombre = s; }
void Ingrediente::setCantidad(const string& c) { this->cantidad = c; }

string Ingrediente::getNombre() const { return nombre; }
string Ingrediente::getCantidad() const { return cantidad; }

string Ingrediente::toString() const {
  string str;
  str += "\t- " + nombre + ": " + cantidad + "\n";
  return str;
}

int Ingrediente::compareByNombre(const Ingrediente& a, const Ingrediente& b) {
  return a.nombre.compare(b.nombre);
}

Ingrediente& Ingrediente::operator=(const Ingrediente& i) {
  if (this == &i) {
    return *this;
  }

  this->nombre = i.nombre;
  this->cantidad = i.cantidad;

  return *this;
}

std::ostream& operator<<(std::ostream& os, const Ingrediente& i) {
  os << i.getNombre() << endl;
  os << i.getCantidad();

  return os;
}

std::istream& operator>>(std::istream& is, Ingrediente& i) {
  std::getline(is, i.nombre);
  std::getline(is, i.cantidad);

  return is;
}