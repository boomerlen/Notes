// Note.cpp

#include "subject.h"
#include "note.h"
#include <string>

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
