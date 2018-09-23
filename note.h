// Note.h - header file for parent "note" Class
#include <string>
#include <vector>
#include "subject.h"

#ifndef NOTE_H
#define NOTE_H

class note
{
public:
  note(std::string loc = "", std::string n = "", subjects s = S_UNDEFINED);

  void setLocation(std::string loc);
  void setName(std::string n = "");
  void setSubject(subjects s);
  void addTag(int tag);

  std::string getName();
  subjects getSubject();
  std::vector<int> getTags();

  void removeTag(int);
private:
  std::string location;
  std::string name;
  subjects sub;
  std::vector<int> tags; // Notes can have tags, each have an int ID. IDs are going to be resolved by reading from a seperate file detailing These
};
#endif /* end of include guard:  */
