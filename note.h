// Note.h - header file for parent "note" Class

#include <iostream>
#include <string>
#include <vector>
#include "subject.h"

#ifndef note_H
#define note_H

class note
{
public:
  note(string, string, subject);

  void setLocation(string);
  void setName(string = "");
  void setSubject(subject);
  void addTag(int);

  string getName();
  subject getSubject();
  vector getTags();

  void removeTag(int);
  ~note();
private:
  string location;
  string name;
  subject sub;
  vector tags; // Notes can have tags, each have an int ID. IDs are going to be resolved by reading from a seperate file detailing These
}
#endif /* end of include guard:  */
