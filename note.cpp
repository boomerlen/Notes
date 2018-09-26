// Note.cpp

#include <string>
#include <vector>
#include "subject.h"
#include "note.h"

using namespace std;

note::note(string loc, string n, subjects s)
{
  location = loc;
  name = n;
  sub = s;
}

void note::setLocation(string loc)
{
  location = loc;
  return;
}

void note::setName(string n /*""*/)
{
  if(n == "")
  {
    // Set it equal to the end of the location
    string key = "\\";
    size_t pos = location.rfind(key);
    char buffer[32];
    name = location.copy(buffer, 32, pos);
    return;
  }
  name = n;
  return;
}

void note::setSubject(subjects s)
{
  sub = s;
  return;
}

void note::addTag(int tag)
{
  tags.push_back(tag);
  return;
}

string note::getName()
{
  return name;
}

subjects note::getSubject()
{
  return sub;
}

std::vector<int> note::getTags()
{
  return tags;
}

std::string note::getLocation()
{
  return location;
}
