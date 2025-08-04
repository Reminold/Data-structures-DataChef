#ifndef __MENU_H__
#define __MENU_H__

#include <fstream>
#include <iostream>
#include <string>

#include "LDLCCED.hpp"
#include "LSLLSE.hpp"
#include "ingrediente.hpp"
#include "nombre.hpp"
#include "receta.hpp"

class Menu {
 private:
  std::string opcionesMenu, opcionesRecetario, opcionesMostrar;
  std::string opcionesDisco, opcionesReceta, opcionesEliminar;
  std::string opcionesOrdenar, confirmar;

  bool ciclar;

  List<Receta>::Position pos;

  List<Receta> recetario;

 public:
  Menu();

  // Metodos para opcion 2
  void agregarReceta();
  void eliminarReceta();
  void modificarReceta();

  // Metodo para opcion 3
  void guardarRecetario(const List<Receta>& recetario);
  void leerRecetario();  // Pendiente

  // Metodo auxiliar
  List<Receta>::Position getRecetaPos(const char&) const;
  int subMenu(const string&, const int&) const;
  bool confirmacion() const;

  // Metodo principal
  int programa();
};

// Definimos el clear screen para mejor presentacion del recetario
#ifdef _WIN32
#define CLEAR "cls"
#elif
defined(unix) || defined(_unix) || defined(_unix) || defin ed(_APPLE) ||
    defined(MACH_)
#define CLEAR "clear"
#else
#error "SO no soportado para limpiar pantalla"
#endif

Menu::Menu() {
  opcionesMenu =
      "Bienvenido al recetario, ingrese la opcion que desea: "
      "\n\t0) Salir. \n\t1) Mostrar recetas. \n\t2) Modificar recetario. "
      "\n\t3) Guardar o leer en disco. ";
  opcionesMostrar =
      "Mostrar recetas: \n\t0) Salir. \n\t1) Mostrar todas las recetas. \n\t2) "
      "Mostrar todas las recetas filtradas por categoria. \n\t3) Mostrar "
      "receta por nombre. \n\t4) Mostrar receta por categoria.";
  opcionesRecetario =
      "Modificar recetario: \n\t0) Salir. \n\t1) Agregar nueva receta. \n\t2) "
      "Eliminar receta. \n\t3) Modificar receta. \n\t4) Ordenar recetas "
      "existentes.";
  opcionesReceta =
      "Modificar receta: \n\t0) Salir. \n\t1) Agregar ingrediente. \n\t2) "
      "Modificar cantidad de ingrediente \n\t3) Eliminar un ingrediente. "
      "\n\t4) Eliminar todos los ingredientes. \n\t5) "
      "Modificar procedimiento.";
  opcionesEliminar =
      "Eliminar receta: \n\t0) Salir. \n\t1) Eliminar una receta. \n\t2) "
      "Eliminar todas las recetas.";
  opcionesDisco =
      "Guardar o leer en disco: \n\t0) Salir. \n\t1) Guardar en disco. \n\t2) "
      "Leer de disco.";
  opcionesOrdenar =
      "Ordenar recetas existentes: \n\t0) Salir. \n\t1) Ordenar por nombre. "
      "\n\t2) Ordenar por tiempo de preparacion.";
  confirmar = "Esta seguro de que desea realizar la accion? (S/N): ";

  ciclar = true;

  pos = nullptr;
}

List<Receta>::Position Menu::getRecetaPos(const char& atributo) const {
  Receta r;
  std::string info;

  if (atributo == 'N') {
    // Solicitamos la informacion requerida para la busqueda
    std::cout << "Ingrese el nombre de la receta: ";
    std::cin.ignore();
    std::getline(cin, info);
    r.setNombre(info);

    return recetario.findData(r, Receta::compareByNombre);
  }

  if (atributo == 'C') {
    // Solicitamos la informacion requerida para la busqueda
    std::cout << "Ingrese la categoria de la receta: \n\tDesayuno \n\tComida "
                 "\n\tCena \n\tNavidad \n";
    std::cin.ignore();
    std::getline(cin, info);
    r.setCategoria(info);

    return recetario.findData(r, Receta::compareByCategoria);
  }

  return nullptr;
}

int Menu::subMenu(const string& menu, const int& max) const {
  int opcion(-1);
  do {
    std::cout << menu << std::endl;
    std::cin >> opcion;
  } while (opcion < 0 || opcion > max);

  return opcion;
}

bool Menu::confirmacion() const {
  do {
    std::cout << confirmar << std::endl;
    char confirmacion;
    std::cin >> confirmacion;

    // Confirmamos si el usuario desea continuar
    if (confirmacion == 'S' || confirmacion == 's') {
      return true;
    } else if (confirmacion == 'N' || confirmacion == 'n') {
      std::cout << "Operacion cancelada" << std::endl;
      return false;
    } else {
      continue;
    }
  } while (true);
}

void Menu::agregarReceta() {
  // Generamos las instancias necesarias para registrar la receta
  Receta r;
  int contador(1);
  ListS<Ingrediente> listaIngredientes;
  std::string procedimiento, info;
  Nombre autor;

  std::cout << "A continuacion ingrese los datos de la receta: " << std::endl;

  // Capturar los datos proporcionados por el usuario
  std::cout << "Nombre de la receta: ";
  std::cin.ignore();
  std::getline(std::cin, info);
  r.setNombre(info);

  do {  // Iteracion para los los ingredientes
    Ingrediente i;
    std::cout << "Nombre del ingrediente: ";
    if (contador > 1) {
      /* Limpiamos el flujo solo despues de la primera iteracion para evitar
      perdida de caracteres */
      std::cin.ignore();
    }
    std::getline(std::cin, info);
    i.setNombre(info);

    std::cout << "Cantidad del ingrediente (agregue la unidad al final): ";
    std::getline(std::cin, info);
    i.setCantidad(info);

    // Insertamos el ingrediente en la instancia de lista
    std::cout << "Ingrediente registrado." << std::endl;
    listaIngredientes.insertData(listaIngredientes.getLastPos(), i);

    // Preguntar al usuario si desea agregar otro ingrediente
    std::cout << "Agregar otro ingrediente? (Ingrese 's' para continuar): ";
    char respuesta;
    std::cin >> respuesta;

    if (respuesta == 'S' || respuesta == 's') {
      contador++;
      continue;
    } else {
      break;
    }
  } while (true);
  r.setIngredientes(listaIngredientes);

  contador = 1;
  do {  // Iteracion para la categoria
    std::cout << "Categoria de la receta: \n\tDesayuno. \n\tComida. \n\tCena. "
                 "\n\tNavidad. \n";
    if (contador > 1) {
      /* Limpiamos el flujo solo despues de la primera iteracion para evitar
      perdida de caracteres */
      std::cin.ignore();
    }
    std::getline(std::cin, info);
  } while (info != "Desayuno" && info != "Comida" && info != "Cena" &&
           info != "Navidad");
  r.setCategoria(info);

  contador = 1;
  std::cout << "Procedimiento de la receta, a continuacion agregue los pasos "
               "del procedimiento: \n";
  do {  // Iteracion para el procedimiento
    std::cout << "Paso " << contador << ": ";
    if (contador > 1) {
      /* Limpiamos el flujo solo despues de la primera iteracion para evitar
      perdida de caracteres */
      std::cin.ignore();
    }
    std::getline(std::cin, info);

    // Agregamos el paso numerado al procedimiento
    procedimiento += std::to_string(contador) + ". " + info;

    // Preguntar al usuario si desea agregar otro paso
    std::cout << "Agregar otro paso? (Ingrese 's' para continuar): ";
    char respuesta;
    std::cin >> respuesta;

    if (respuesta == 'S' || respuesta == 's') {
      procedimiento += "\n";
      contador++;
      continue;
    } else {
      break;
    }
  } while (true);
  r.setProcedimiento(procedimiento);

  std::cout << "Tiempo de preparacion (en minutos): ";
  std::cin.ignore();
  std::getline(std::cin, info);
  r.setTiempoProc(info);

  std::cout << "Nombre del autor (primer nombre): ";
  std::cin >> info;
  autor.setFirstName(info);

  std::cout << "Nombre del autor (apellido): ";
  std::cin >> info;
  autor.setLastName(info);

  r.setAutor(autor);

  // Agregar la nueva receta al recetario
  if (confirmacion()) {
    recetario.insertData(recetario.getLastPos(), r);
    std::cout << "Receta agregada con exito." << std::endl;
  }
}

void Menu::eliminarReceta() {
  int n = subMenu(opcionesEliminar, 2);

  if (n == 0) {  // Opcion salir
    return;
  } else if (n == 1) {  // Eliminar una receta
    std::cout << "A continuacion ingrese el nombre de la receta a eliminar"
              << std::endl;
    pos = getRecetaPos('N');
    if (pos != nullptr && confirmacion()) {
      recetario.deleteData(pos);
    } else {
      std::cout << "Operacion cancelada" << std::endl;
    }
  } else if (n == 2 && confirmacion()) {  // Eliminar todas las recetas
    recetario.deleteAll();
  }
}

void Menu::modificarReceta() {
  std::cout << "A continuacion ingrese el nombre de la receta a modificar"
            << std::endl;
  pos = getRecetaPos('N');
  if (pos != nullptr) {
    // clearscreen
    system(CLEAR);
    std::cout << "Elemento localizado" << std::endl;
    std::cout << recetario.retrieve(pos).toString() << std::endl;

    int op;
    op = subMenu(opcionesReceta, 5);
    std::string info;
    Receta r(recetario.retrieve(pos));

    switch (op) {
      case 0: {  // Salir
        return;
      }
      case 1: {  // Agregar Ingrediente
        Ingrediente i;
        std::cout << "Nombre del ingrediente: ";
        std::cin.ignore();
        std::getline(std::cin, info);
        i.setNombre(info);

        std::cout << "Cantidad del ingrediente (agregue la unidad al final): ";
        std::getline(std::cin, info);
        i.setCantidad(info);

        // Insertamos el ingrediente en la instancia de lista directamente
        r.getIngredientes().insertData(r.getIngredientes().getLastPos(), i);
        // r.getIngredientes().sortData(Ingrediente::compareByNombre);

        recetario.insertData(pos, r);
        recetario.deleteData(pos);
        std::cout << "Ingrediente registrado." << std::endl;
        break;
      }
      case 2: {  // Editar cantidad de Ingrediente
        Ingrediente i;
        ListS<Ingrediente>::Position p;
        std::cout << "Nombre del ingrediente a modificar: ";
        std::cin.ignore();
        std::getline(std::cin, info);
        i.setNombre(info);

        p = r.getIngredientes().findData(i, Ingrediente::compareByNombre);

        if (p != nullptr) {  // En caso de encontrar el ingrediente
          Ingrediente i(r.getIngredientes().retrieve(p));
          std::cout
              << "Cantidad del ingrediente (agregue la unidad al final): ";
          std::getline(std::cin, info);
          i.setCantidad(info);

          r.getIngredientes().insertData(p, i);
          r.getIngredientes().deleteData(p);

          if (confirmacion()) {
            recetario.insertData(pos, r);
            recetario.deleteData(pos);
            std::cout << "Ingrediente modificado." << std::endl;
          }

        } else {  // En caso de no encontrar el ingrediente
          std::cout << "Ingrediente no encontrado." << std::endl;
        }
        break;
      }
      case 3: {  // Eliminar un ingrediente
        Ingrediente i;
        ListS<Ingrediente>::Position p(nullptr);
        std::cout << "Nombre del ingrediente a eliminar: ";
        std::cin.ignore();
        std::getline(std::cin, info);
        i.setNombre(info);

        p = r.getIngredientes().findData(i, Ingrediente::compareByNombre);

        if (p != nullptr) {
          std::cout << "Elemento localizado. " << std::endl;
          r.getIngredientes().deleteData(p);
          recetario.insertData(pos, r);
          recetario.deleteData(pos);
          std::cout << "Ingrediente eliminado." << std::endl;
        } else {
        }
        break;
      }
      case 4: {  // Eliminar todos los ingredientes
        if (confirmacion()) {
          r.getIngredientes().deleteAll();
          recetario.insertData(pos, r);
          recetario.deleteData(pos);
          std::cout << "Ingredientes eliminados." << std::endl;
        }
        break;
      }
      case 5: {  // Modificar procedimiento
        int contador(1);
        std::string procedimiento;
        std::cout
            << "Procedimiento de la receta, a continuacion agregue los pasos "
               "del procedimiento: \n";
        do {  // Iteracion para el procedimiento
          std::cout << "Paso " << contador << ": ";
          if (contador >= 1) {
            /* Limpiamos el flujo solo despues de la primera iteracion para
            evitar perdida de caracteres */
          }
          std::cin.ignore();
          std::getline(std::cin, info);

          // Agregamos el paso numerado al procedimiento
          procedimiento += std::to_string(contador) + ". " + info;

          // Preguntar al usuario si desea agregar otro paso
          std::cout << "Agregar otro paso? (Ingrese 's' para continuar): ";
          char respuesta;
          std::cin >> respuesta;

          if (respuesta == 'S' || respuesta == 's') {
            procedimiento += "\n";
            contador++;
            continue;
          } else {
            break;
          }
        } while (true);

        if (confirmacion()) {
          r.setProcedimiento(procedimiento);

          recetario.insertData(pos, r);
          recetario.deleteData(pos);
          std::cout << "Procedimiento modificado." << std::endl;
        }
        break;
      }
    }
  } else {
    std::cout << "Elemento no encontrado" << std::endl;
    return;
  }
}

void Menu::guardarRecetario(const List<Receta>& recetario) {
  string nombreArchivo;
  std::cout << "Ingrese el nombre del archivo para guardar el recetario: ";
  cin.ignore();
  getline(cin, nombreArchivo);

  nombreArchivo += ".txt";

  ofstream archivo(nombreArchivo, ios::trunc);

  if (!archivo.is_open()) {
    cout << "No se pudo abrir el archivo " << nombreArchivo
         << " para guardar el recetario." << std::endl;
    return;
  }

  List<Receta>::Position aux = recetario.getFirstPos();
  while (aux != nullptr) {
    Receta r = recetario.retrieve(aux);
    archivo << r << std::endl;
    aux = recetario.getNextPos(aux);
  }
}

void Menu::leerRecetario() {
  string nombreArchivo, aux;
  cout << "Ingrese el nombre del archivo para leer el recetario: ";
  cin.ignore();
  getline(cin, nombreArchivo);

  nombreArchivo += ".txt";

  ifstream archivo(nombreArchivo);

  if (!archivo.is_open()) {
    cout << "No se pudo abrir el archivo " << nombreArchivo
         << " para leer el recetario." << std::endl;
    return;
  }

  recetario.deleteAll();
  std::getline(archivo, aux);  // Cargamos el primer inicioReceta
  if (aux == "inicioReceta") {
    do {
      Receta r;
      archivo >> r;

      recetario.insertData(recetario.getLastPos(), r);

      std::getline(archivo, aux);
    } while (aux == "inicioReceta");
    cout << "Recetario cargado exitosamente." << std::endl;
  }
}

int Menu::programa() {  // Metodo principal para el programa
  while (ciclar) {
    // Limpiar consola
    int n(-1);
    int valor = subMenu(opcionesMenu, 3);
    switch (valor) {  // Switch case para cada opcion del menu
      case 0: {       // Opcion 0: Salir
        std::cout << "Programa finalizado exitosamente." << std::endl;
        ciclar = false;  // Terminamos las iteraciones con la bandera de control
        break;
      }

      case 1: {  // Opcion 1: Mostrar recetas
        // Limpiar consola
        system(CLEAR);
        n = subMenu(opcionesMostrar, 4);

        if (n == 0) {  // Opcion salir
          break;
        } else if (n == 1) {  // Mostrar todas las recetas
          std::cout << recetario.toString();
          break;
        } else if (n == 2) {  // Mostrar todas las recetas x categoria
          // Metodo auxiliar
          List<Receta> recetarioTemp(recetario);
          recetarioTemp.sortData(Receta::compareByCategoria);
          std::cout << recetarioTemp.toString();
          recetarioTemp.deleteAll();
          break;
        } else if (n == 3) {  // Mostrar una receta por nombre
          // Metodo auxiliar
          pos = getRecetaPos('N');
          if (pos != nullptr) {
            system(CLEAR);
            std::cout << "Elemento localizado." << std::endl;
            std::cout << recetario.retrieve(pos).toString() << std::endl;
          } else {
            std::cout << "Elemento no encontrado" << std::endl;
          }
          break;
        } else if (n == 4) {  // Mostrar una receta por categoria
          // Metodo auxiliar
          pos = getRecetaPos('C');
          if (pos != nullptr) {
            std::cout << recetario.retrieve(pos).toString() << std::endl;
          } else {
            std::cout << "Elemento no encontrado" << std::endl;
          }
          break;
        } else {
          break;
        }
      }

      case 2: {  // Opcion 2: Modificar recetario
        // Limpiar consola
        system(CLEAR);
        n = subMenu(opcionesRecetario, 4);

        if (n == 0) {  // Opcion salir
          break;
        } else if (n == 1) {  // Agregar receta
          agregarReceta();
          break;
        } else if (n == 2) {  // Eliminar receta
          eliminarReceta();
          break;
        } else if (n == 3) {  // Modificar receta
          modificarReceta();
          break;
        } else if (n == 4) {  // Ordenar recetario
          int num = subMenu(opcionesOrdenar, 2);

          if (num == 0) {  // Opcion salir
            break;
          } else if (num == 1) {  // Ordenar por nombre
            recetario.sortData(Receta::compareByNombre);
            std::cout << "Rectas ordenadas por nombre." << std::endl;
          } else if (num == 2) {  // Ordenar por tiempo
            recetario.sortData(Receta::compareByTiempo);
            std::cout << "Rectas ordenadas por tiempo." << std::endl;
          }
          break;
        } else {
          break;
        }
      }

      case 3: {  // Opcion 3: Lectura o guardado en disco
        // Limpiar consola
        system(CLEAR);
        n = subMenu(opcionesDisco, 2);

        if (n == 0) {  // Opcion salir
          break;
        } else if (n == 1) {  // Guardar en disco
          // Metodo para guardar en disco
          guardarRecetario(recetario);
          break;
        } else if (n == 2) {  // Leer de disco
          // Metodo para leer de disco
          leerRecetario();
          break;
        } else {
          break;
        }
      }
    }
  }

  return 0;  // return 0 para la funcion main
}

#endif  // __MENU_H__