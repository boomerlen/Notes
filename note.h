// Note.h - header file for parent "note" Class

#include <iostream>
#include "subject.h"

using namespace std;

#pragma #ifndef note_H
#define note_H

class note
{
public:
  note(char[256], char[32], subject);

  void setLocation(char[256]);
  void setName(char[32] = "");
  void setSubject(subject);
  void addTag(int);

  void removeTag(int);
  ~note();
private:
  char[256] location;
  char[32] name;
  subject sub;
  int[16] tags; // Notes can have up to 16 tags, each have an int ID. IDs are going to be resolved by reading from a seperate file detailing These
}
#endif /* end of include guard:  */
