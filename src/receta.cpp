#include "receta.hpp"

using namespace std;

Receta::Receta() {
  this->nombreReceta = "";
  this->tiempoProc = 0;
  this->categoria = "";
  this->procedimiento = "";
}

Receta::Receta(const Receta& r) {
  this->nombreReceta = r.nombreReceta;
  this->tiempoProc = r.tiempoProc;
  this->categoria = r.categoria;
  this->procedimiento = r.procedimiento;
  this->autor = r.autor;
  this->listaIngredientes = r.listaIngredientes;
}

void Receta::setNombre(const string& s) { this->nombreReceta = s; }
void Receta::setCategoria(const string& s) { this->categoria = s; }
void Receta::setProcedimiento(const string& s) { this->procedimiento = s; }
void Receta::setTiempoProc(const string& m) { this->tiempoProc = stoi(m); }
void Receta::setAutor(const Nombre& n) { this->autor = n; }
void Receta::setIngredientes(const ListS<Ingrediente>& l) {
  this->listaIngredientes = l;
}

string Receta::getNombre() const { return nombreReceta; }
string Receta::getCategoria() const { return categoria; }
string Receta::getProcedimiento() const { return procedimiento; }
int Receta::getTiempoProc() const { return tiempoProc; }
Nombre Receta::getAutor() const { return autor; }
ListS<Ingrediente>& Receta::getIngredientes() { return listaIngredientes; }

int Receta::compareByNombre(const Receta& a, const Receta& b) {
  return a.nombreReceta.compare(b.nombreReceta);
}

int Receta::compareByCategoria(const Receta& a, const Receta& b) {
  return a.categoria.compare(b.categoria);
}

int Receta::compareByTiempo(const Receta& a, const Receta& b) {
  if (a.tiempoProc < b.tiempoProc) {
    return -1;
  } else if (a.tiempoProc > b.tiempoProc) {
    return 1;
  } else {
    return 0;
  }
}

string Receta::toString() const {
  // Crear un string para representar la receta
  string str;

  // Agregar separacion con setfill y setw una vez sobrecargados los operadores
  str += "Nombre de la receta: " + nombreReceta + "\n";
  str += "Categoria: " + categoria + "\n";
  str += "Tiempo de preparacion: " + std::to_string(tiempoProc) + " minutos.\n";
  str += "Autor: " + autor.toString() + "\n";

  // Ingredientes
  str += "\n\tIngredientes:\n";
  str += listaIngredientes.toString();

  // Procedimiento
  str += "\n\tProcedimiento:\n";
  str += procedimiento + "\n";

  return str;
}

Receta& Receta::operator=(const Receta& r) {
  if (this == &r) {
    return *this;
  }

  this->nombreReceta = r.nombreReceta;
  this->tiempoProc = r.tiempoProc;
  this->categoria = r.categoria;
  this->procedimiento = r.procedimiento;
  this->autor = r.autor;
  this->listaIngredientes = r.listaIngredientes;

  return *this;
}

std::ostream& operator<<(std::ostream& os, const Receta& r) {
  os << "inicioReceta" << endl;
  os << r.nombreReceta << endl;
  os << r.categoria << endl;
  os << r.tiempoProc << endl;
  os << r.autor << endl;

  ListS<Ingrediente>::Position pos;
  pos = r.listaIngredientes.getFirstPos();
  while (pos != nullptr) {
    os << r.listaIngredientes.retrieve(pos) << endl;

    pos = r.listaIngredientes.getNextPos(pos);
  }
  os << "finIngredientes" << endl;

  os << r.procedimiento << endl;
  os << "finReceta";

  return os;
}

std::istream& operator>>(std::istream& is, Receta& r) {
  std::string aux, proc;
  aux = "";

  std::getline(is, r.nombreReceta);
  std::getline(is, r.categoria);
  std::getline(is, aux);
  r.tiempoProc = stoi(aux);

  std::getline(is, aux);
  r.autor.setFirstName(aux);
  std::getline(is, aux);
  r.autor.setLastName(aux);

  r.listaIngredientes.deleteAll();
  std::getline(is, aux);
  if (aux != "finIngredientes") {
    // Solo si la receta tiene ingredientes registrados en el archivo:
    do {  // Iteracion postprueba para almacenar ingredientes
      Ingrediente i;
      i.setNombre(aux);
      std::getline(is, aux);
      i.setCantidad(aux);

      r.listaIngredientes.insertData(r.listaIngredientes.getLastPos(), i);
      std::getline(is, aux);
    } while (aux != "finIngredientes");
  }

  std::getline(is, aux);
  if (aux != "finReceta") {
    // Solo si la receta tiene procedimiento registrado en el archivo:
    do {  // Iteracion postprueba para almacenar el procedimiento
      proc += aux;
      std::getline(is, aux);
      if (aux != "finReceta") {
        proc += "\n";
      }
    } while (aux != "finReceta");
  }

  r.procedimiento = proc;

  return is;
}