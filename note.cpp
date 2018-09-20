// Note.cpp

#include "subject.h"
#include "note.h"

note::note(char[256] loc, char[32] n, subject s)
{
  location = loc;
  name = n;
  sub = s;
  return note;
}

void note::setLocation(char[256] loc)
{
  location = loc;
  return;
}

void note::setName(char[32] n = "")
{
  
}
