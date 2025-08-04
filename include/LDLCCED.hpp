#ifndef __LDLCCED_H__
#define __LDLCCED_H__

#include <exception>
#include <iostream>
#include <string>

// Lista autodefinida, clase nodo integrada en el mismo archivo

/// Definicion
template <class T>
class List {
 private:
  class Node {
   private:
    T* dataPtr;
    Node* prev;
    Node* next;

   public:
    class Exception : public std::exception {
     private:
      std::string msg;

     public:
      explicit Exception(const char* message) : msg(message) {}
      explicit Exception(const std::string& message) : msg(message) {}
      virtual ~Exception() throw() {}
      virtual const char* what() const throw() { return msg.c_str(); }
    };

    Node();
    Node(const T&);

    ~Node();

    T* getDataPtr() const;
    T getData() const;
    Node* getPrev() const;
    Node* getNext() const;

    void setDataPtr(T*);
    void setData(const T&);
    void setPrev(Node*);
    void setNext(Node*);
  };

  Node* header;

  void copyAll(const List<T>&);

  bool isValidPos(Node*) const;

 public:
  typedef Node* Position;

  class Exception : public std::exception {
   private:
    std::string msg;

   public:
    Exception() noexcept : msg("Error indefinido") {}
    Exception(const Exception& ex) noexcept : msg(ex.msg) {}
    Exception(const std::string& m) : msg(m) {}
    Exception& operator=(const Exception& ex) noexcept {
      msg = ex.msg;

      return *this;
    }
    virtual ~Exception() {}
    virtual const char* what() const noexcept { return msg.c_str(); }
  };

  List();
  List(const List<T>&);

  ~List();

  bool isEmpty() const;

  void insertData(Node*, const T&);

  void deleteData(Node*);

  Node* getFirstPos() const;
  Node* getLastPos() const;
  Node* getPrevPos(Node*) const;
  Node* getNextPos(Node*) const;

  Node* findData(const T&);

  void swapPtr(const Position&, const Position&);

  void sortData();
  void sortData(const Position&, const Position&);

  // Busqueda y ordenamiento explicito
  Node* findData(const T&, int(const T&, const T&)) const;

  void sortData(int comp(const T&, const T&));
  void sortData(const Position&, Position, int comp(const T&, const T&));

  T retrieve(Node*) const;

  std::string toString() const;

  void deleteAll();

  List<T>& operator=(const List<T>&);
};

/// Implementacion
using namespace std;

template <class T>
List<T>::Node::Node() : dataPtr(nullptr), prev(nullptr), next(nullptr) {}

template <class T>
List<T>::Node::Node(const T& e)
    : dataPtr(new T(e)), prev(nullptr), next(nullptr) {
  if (dataPtr == nullptr) {
    throw Exception("Memoria insuficiente, creando nodo");
  }
}

template <class T>
List<T>::Node::~Node() {
  delete dataPtr;
}

template <class T>
T* List<T>::Node::getDataPtr() const {
  return dataPtr;
}

template <class T>
T List<T>::Node::getData() const {
  if (dataPtr == nullptr) {
    throw Exception("Dato inexistente, getData");
  }

  return *dataPtr;
}

template <class T>
typename List<T>::Node* List<T>::Node::getPrev() const {
  return prev;
}

template <class T>
typename List<T>::Node* List<T>::Node::getNext() const {
  return next;
}

template <class T>
void List<T>::Node::setDataPtr(T* p) {
  dataPtr = p;
}

template <class T>
void List<T>::Node::setData(const T& e) {
  if (dataPtr == nullptr) {
    if ((dataPtr = new T(e)) == nullptr) {
      throw Exception("Memoria no disponible, setData");
    }
  } else {
    *dataPtr = e;
  }
}

template <class T>
void List<T>::Node::setPrev(Node* p) {
  prev = p;
}

template <class T>
void List<T>::Node::setNext(Node* p) {
  next = p;
}

template <class T>
void List<T>::copyAll(const List<T>& l) {
  Node* aux(l.header->getNext());
  Node* newNode;

  while (aux != l.header) {
    try {
      if ((newNode = new Node(aux->getData())) == nullptr) {
        throw Exception("Memoria no disponible, copyAll");
      }
    } catch (typename Node::Exception ex) {
      throw Exception(ex.what());
    }

    newNode->setPrev(header->getPrev());
    newNode->setNext(header);

    header->getPrev()->setNext(newNode);
    header->setPrev(newNode);

    aux = aux->getNext();
  }
}

template <class T>
bool List<T>::isValidPos(Node* p) const {
  Node* aux(header->getNext());

  while (aux != header) {
    if (aux == p) {
      return true;
    }

    aux = aux->getNext();
  }

  return false;
}

template <class T>
List<T>::List() : header(new Node) {
  if (header == nullptr) {
    throw Exception("Memoria no disponible, inicializando lista");
  }

  header->setPrev(header);
  header->setNext(header);
}

template <class T>
List<T>::List(const List<T>& l) : List<T>() {
  copyAll(l);
}

template <class T>
List<T>::~List() {
  deleteAll();

  delete header;
}

template <class T>
bool List<T>::isEmpty() const {
  return header->getNext() == header;
}

template <class T>
void List<T>::insertData(Node* p, const T& e) {
  if (p != nullptr and !isValidPos(p)) {
    throw Exception("Posicion invalida, insertData");
  }

  Node* aux;

  try {
    aux = new Node(e);
  } catch (typename Node::Exception ex) {
    throw Exception(ex.what());
  }

  if (aux == nullptr) {
    throw Exception("Memoria no disponible, insertData");
  }

  if (p == nullptr) {
    p = header;
  }

  // Position insPos(p == nullptr ? header : p);

  aux->setPrev(p);
  aux->setNext(p->getNext());

  p->getNext()->setPrev(aux);
  p->setNext(aux);
}

template <class T>
void List<T>::deleteData(Node* p) {
  if (!isValidPos(p)) {
    throw Exception("Posicion invalida, deleteData");
  }

  p->getPrev()->setNext(p->getNext());
  p->getNext()->setPrev(p->getPrev());

  delete p;
}

template <class T>
typename List<T>::Node* List<T>::getFirstPos() const {
  if (isEmpty()) {
    return nullptr;
  }

  return header->getNext();
}

template <class T>
typename List<T>::Node* List<T>::getLastPos() const {
  if (isEmpty()) {
    return nullptr;
  }

  return header->getPrev();
}

template <class T>
typename List<T>::Node* List<T>::getPrevPos(Node* p) const {
  if (!isValidPos(p) or p == header->getNext()) {
    return nullptr;
  }

  return p->getPrev();
}

template <class T>
typename List<T>::Node* List<T>::getNextPos(Node* p) const {
  if (!isValidPos(p) or p == header->getPrev()) {
    return nullptr;
  }

  return p->getNext();
}

template <class T>
typename List<T>::Node* List<T>::findData(const T& e) {
  Node* aux(header->getNext());

  while (aux != header) {
    if (aux->getData() == e) {
      return aux;
    }

    aux = aux->getNext();
  }

  return nullptr;
}

// Sorting

template <class T>
void List<T>::swapPtr(const Position& a, const Position& b) {
  if (a != b) {
    T* aux(a->getDataPtr());
    a->setDataPtr(b->getDataPtr());
    b->setDataPtr(aux);
  }
}

template <class T>
void List<T>::sortData() {
  sortData(header->getNext(), header->getPrev());
}

template <class T>
void List<T>::sortData(const Position& leftEdge, const Position& rightEdge) {
  // Criterio de paro
  if (leftEdge == rightEdge) {
    return;
  }

  // Son solo dos elementos
  if (leftEdge->getNext() == rightEdge) {
    if (leftEdge->getData() > rightEdge->getData()) {
      swapPtr(leftEdge, rightEdge);
    }
    return;
  }

  // Particion
  Position i(leftEdge), j(rightEdge);
  while (i != j) {
    while (i != j and i->getData() <= rightEdge->getData()) {
      i = i->getNext();
    }
    while (i != j and j->getData() >= rightEdge->getData()) {
      j = j->getPrev();
    }
    swapPtr(i, j);
  }

  swapPtr(i, rightEdge);

  // Divide y venceras
  if (i != leftEdge) {
    sortData(leftEdge, i->getPrev());
  }
  if (i != rightEdge) {
    sortData(i->getNext(), rightEdge);
  }
}

// Busqueda y sorting explicitos

template <class T>
typename List<T>::Node* List<T>::findData(const T& e,
                                          int comp(const T&, const T&)) const {
  Node* aux(header->getNext());

  while (aux != header) {
    if (comp(e, aux->getData()) == 0) {
      return aux;
    }

    aux = aux->getNext();
  }

  return nullptr;
}

template <class T>
void List<T>::sortData(int comp(const T&, const T&)) {
  sortData(header->getNext(), header->getPrev(), comp);
}

template <class T>
void List<T>::sortData(const Position& leftEdge, Position rightEdge,
                       int comp(const T&, const T&)) {
  /// Criterio de paro
  if (leftEdge == rightEdge) {
    return;
  }

  /// Son solo dos elementos
  if (leftEdge->getNext() == rightEdge) {
    if (comp(leftEdge->getData(), rightEdge->getData()) > 0) {
      swapPtr(leftEdge, rightEdge);
    }
    return;
  }
  /// Particion
  Position i(leftEdge), j(rightEdge);

  while (i != j) {
    while (i != j and comp(i->getData(), rightEdge->getData()) <= 0) {
      i = i->getNext();
    }
    while (i != j and comp(j->getData(), rightEdge->getData()) >= 0) {
      j = j->getPrev();
    }
    swapPtr(i, j);
  }
  swapPtr(i, rightEdge);

  // Divide y venceras
  if (i != leftEdge) {
    sortData(leftEdge, i->getPrev(), comp);
  }
  if (i != rightEdge) {
    sortData(i->getNext(), rightEdge, comp);
  }
}

template <class T>
T List<T>::retrieve(Node* p) const {
  if (!isValidPos(p)) {
    throw Exception("Posicion invalida, retrieve");
  }

  return p->getData();
}

template <class T>
string List<T>::toString() const {
  Node* aux(header->getNext());
  string result;

  while (aux != header) {
    result += aux->getData().toString() + "\n";

    aux = aux->getNext();
  }

  return result;
}

template <class T>
void List<T>::deleteAll() {
  Node* aux;

  while (header->getNext() != header) {
    aux = header->getNext();

    header->setNext(aux->getNext());

    delete aux;
  }

  header->setPrev(header);
}

template <class T>
List<T>& List<T>::operator=(const List<T>& l) {
  deleteAll();

  copyAll(l);

  return *this;
}

#endif  // __LDLCCED_H__