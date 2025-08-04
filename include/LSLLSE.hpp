#ifndef __LSLLSE_H__
#define __LSLLSE_H__

#include <functional>
#include <iostream>

template <class T>
class ListS {
 private:
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

  class Node {
   private:
    T data;
    Node* next;

   public:
    Node();
    Node(const T&);

    T getData() const;
    Node* getNext() const;

    void setData(const T&);
    void setNext(Node*);
  };

  Node* anchor;

  void copyAll(const ListS&);

  bool isValidPos(Node*) const;

 public:
  typedef Node* Position;

  ListS();
  ListS(const ListS<T>&);

  ~ListS();

  bool isEmpty() const;

  void insertData(Node*, const T&);

  void deleteData(Node*);

  Node* getFirstPos() const;
  Node* getLastPos() const;
  Node* getPrevPos(Node*) const;
  Node* getNextPos(Node*) const;

  Node* findData(const T&);

  // Busqueda y ordenamiento explicito
  Node* findData(const T&, int(const T&, const T&)) const;

  T retrieve(Node*) const;

  std::string toString() const;

  void deleteAll();

  ListS<T>& operator=(const ListS<T>&);
};

template <class T>
ListS<T>::Node::Node() : next(nullptr) {}

template <class T>
ListS<T>::Node::Node(const T& e) : data(e), next(nullptr) {}

template <class T>
T ListS<T>::Node::getData() const {
  return data;
}

template <class T>
typename ListS<T>::Node* ListS<T>::Node::getNext() const {
  return next;
}

template <class T>
void ListS<T>::Node::setData(const T& d) {
  data = d;
}

template <class T>
void ListS<T>::Node::setNext(Node* p) {
  next = p;
}

template <class T>
void ListS<T>::copyAll(const ListS<T>& l) {
  Node* aux(l.anchor);
  Node* lastInserted(nullptr);
  Node* newNode;

  while (aux != nullptr) {
    newNode = new Node(aux->getData());

    if (lastInserted == nullptr) {
      anchor = newNode;
    } else {
      lastInserted->setNext(newNode);
    }

    lastInserted = newNode;

    aux = aux->getNext();
  }
}

template <class T>
bool ListS<T>::isValidPos(Node* p) const {
  Node* aux(anchor);

  while (aux != nullptr) {
    if (aux == p) {
      return true;
    }

    aux = aux->getNext();
  }

  return false;
}

using namespace std;

template <class T>
ListS<T>::ListS() : anchor(nullptr) {}

template <class T>
ListS<T>::ListS(const ListS<T>& l) : ListS<T>() {
  copyAll(l);
}

template <class T>
ListS<T>::~ListS() {
  deleteAll();
}

template <class T>
bool ListS<T>::isEmpty() const {
  return this->anchor == nullptr;
}

template <class T>
void ListS<T>::insertData(Node* p, const T& e) {
  if (p != nullptr and !isValidPos(p)) {
    throw Exception("Posicion invalida, insertData");
  }

  Node* aux(new Node(e));
  if (aux == nullptr) {
    throw Exception("Memoria no disponible, insertData");
  }

  if (p == nullptr) {  // Al principio
    aux->setNext(anchor);

    anchor = aux;
  } else {  // No al principio
    aux->setNext(p->getNext());
    p->setNext(aux);
  }
}

template <class T>
void ListS<T>::deleteData(Node* p) {
  if (!isValidPos(p)) {
    throw Exception("Posicion invalida, deleteData");
  }

  if (p == anchor) {  // Eliminar el primero
    anchor = p->getNext();
  } else {  // Eliminar cualquier otro
    getPrevPos(p)->setNext(p->getNext());
  }

  delete p;
}

template <class T>
typename ListS<T>::Position ListS<T>::getFirstPos() const {
  return anchor;
}

template <class T>
typename ListS<T>::Position ListS<T>::getLastPos() const {
  if (isEmpty()) {
    return nullptr;
  }

  Node* aux(anchor);

  while (aux->getNext() != nullptr) {
    aux = aux->getNext();
  }

  return aux;
}

template <class T>
typename ListS<T>::Position ListS<T>::getPrevPos(Node* p) const {
  if (isEmpty() or p == anchor) {
    return nullptr;
  }

  Node* aux(anchor);

  while (aux != nullptr and aux->getNext() != p) {
    aux = aux->getNext();
  }

  return aux;
}

template <class T>
typename ListS<T>::Position ListS<T>::getNextPos(Node* p) const {
  if (!isValidPos(p)) {
    return nullptr;
  }

  return p->getNext();
}

template <class T>
typename ListS<T>::Position ListS<T>::findData(const T& e) {
  Node* aux(anchor);

  while (aux != nullptr and aux->getData() != e) {
    aux = aux->getNext();
  }

  return aux;
}

template <class T>
typename ListS<T>::Position ListS<T>::findData(const T& e,
                                   int comp(const T&, const T&)) const {
  Node* aux(anchor);

  while (aux != nullptr) {
    if (comp(e, aux->getData()) == 0) {
      return aux;
    }

    aux = aux->getNext();
  }

  return aux;
}

template <class T>
T ListS<T>::retrieve(Node* p) const {
  if (!isValidPos(p)) {
    throw Exception("Posicion invalida, retrieve");
  }

  return p->getData();
}

template <class T>
string ListS<T>::toString() const {
  string result;
  Node* aux(anchor);

  while (aux != nullptr) {
    result += aux->getData().toString();

    aux = aux->getNext();
  }

  return result;
}

template <class T>
void ListS<T>::deleteAll() {
  Node* aux;

  while (anchor != nullptr) {
    aux = anchor;

    anchor = anchor->getNext();

    delete aux;
  }
}

template <class T>
ListS<T>& ListS<T>::operator=(const ListS<T>& l) {
  deleteAll();

  copyAll(l);

  return *this;
}
#endif  // __LSLLSE_H__