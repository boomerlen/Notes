// Note.cpp

#include "subject.h"
#include "note.h"
#include <string>
#include <vector>

note::note(string loc, string n, subject s)
{
  location = loc;
  name = n;
  sub = s;
  return note;
}

void note::setLocation(string loc)
{
  location = loc;
  return;
}

void note::setName(string n = "")
{
  if(n == "")
  {
    // Set it equal to the end of the location
    string key = '\\';
    size_t pos = location.rfind(key);
    char[32] buffer;
    name = location.copy(buffer, 32, pos);
    return;
  }
  name = n;
  return;
}

void note::setSubject(subject s);
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

subject note::getSubject()
{
  return sub;
}

vector note::getTags()
{
  return tags;
}
