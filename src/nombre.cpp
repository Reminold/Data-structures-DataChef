#include "nombre.hpp"

using namespace std;

Nombre::Nombre() {
  this->firstName = "";
  this->lastName = "";
}

Nombre::Nombre(const Nombre& n) {
  this->firstName = n.firstName;
  this->lastName = n.lastName;
}

void Nombre::setFirstName(const std::string& s) { this->firstName = s; }
void Nombre::setLastName(const std::string& s) { this->lastName = s; }

std::string Nombre::getFirstName() const { return firstName; }
std::string Nombre::getLastName() const { return lastName; }

string Nombre::toString() const { return firstName + " " + lastName; }

Nombre& Nombre::operator=(const Nombre& n) {
  if (this == &n) {
    return *this;
  }

  this->firstName = n.firstName;
  this->lastName = n.lastName;

  return *this;
}

std::ostream& operator<<(std::ostream& os, const Nombre& n) {
  os << n.getFirstName() << endl;
  os << n.getLastName();

  return os;
}

std::istream& operator>>(std::istream& is, Nombre& n) {
  std::getline(is, n.firstName);
  std::getline(is, n.lastName);

  return is;
}