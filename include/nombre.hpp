#ifndef __NOMBRE_H__
#define __NOMBRE_H__

#include <iostream>
#include <string>

class Nombre {
 private:
  std::string firstName, lastName;

 public:
  Nombre();
  Nombre(const Nombre&);
  ~Nombre(){};

  void setFirstName(const std::string&);
  void setLastName(const std::string&);

  std::string getFirstName() const;
  std::string getLastName() const;

  std::string toString() const;

  Nombre& operator=(const Nombre&);

  friend std::ostream& operator<<(std::ostream&, const Nombre&);
  friend std::istream& operator>>(std::istream&, Nombre&);
};

#endif  // __NOMBRE_H__