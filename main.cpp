/*  Main.cpp
*   Author: Hugo Sebesta
*   Project primarily for personal use so probably no one will ever see this
*   If anyone does then I said hi!
*/

#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include "note.h"
#include "subject.h"

#define TAG_ADDR "C:\\Users\\Hugo Sebesta\\Documents\\GitHub\\Notes\\storage\\tags.txt"
#define NOTE_OUTLINE_ADDR "C:\\Users\\Hugo Sebesta\\Documents\\GitHub\\Notes\\storage\\notes.txt"

using namespace std;

map<int, string> initTagDef() // Function for reading from a tag file
{
  ifstream file;
  file.open(TAG_ADDR, ios::in);
  map<int, string> mapTemp;
  if(!file.is_open())
  {
    cout << "Error opening " << TAG_ADDR << endl;
    return mapTemp;
  }
  string line;
  int count = 0; // NOTE THAT TAGS START AT 0 THOUGH MAP SIZES AT 1
  while(getline(file, line))
  {
    mapTemp[count] = line;
    count++;
  }
  file.close();
  return mapTemp;
}

bool tagAdd(string tag) // Function for adding a tag to the tag file.
{
  ofstream file;
  file.open(TAG_ADDR, ios::out | ios::app);
  if(!file.is_open())
    return false;
  file << tag;
  file.close();
  return true;
}

vector<note> initNotesVector()
{
  vector<notes> tempNoteVector;

  ifstream file;
  file.open(NOTE_OUTLINE_ADDR, ios::in);
  if(!file.is_open)
  {
    cout << "Could not open " << NOTE_OUTLINE_ADDR << endl;
    return tempNoteVector;
  }
  string buffer;
  int count = 0;
  while(getline(file, buffer, ";"))
  {
    if(count == 0)
    {
      // Beginning of line: Note name and init the object
      note TempNote;
      TempNote.setName(buffer);
    }
    if(count == 1)
    {
      // Address
      TempNote.setLocation(buffer);
    }
    if(count == 2)
    {
      // Subjects
      stringstream str(buffer);
      int x = 0;
      str >> x;
      subjects sub = static_cast<subjects>(x);
      TempNote.setSubject(sub);
    }
    if(count == 3)
    {
      // TAGS -- NOTE THIS IS MESSY - PROBABLY MANY BUGS HERE
      string tempStr = buffer;
      char buf;
      while(tempStr.size > 1)
      {
        size_t lastComma = tempStr.find_last_of(",");
        tempStr.copy(buf, 1, lastComma+1);
        tempStr = tempStr.substring(0, lastComma-1);
        TempNote.addTag(int(buf));
      }
      TempNote.addTag(int(buf));
      tempNoteVector.push_back(TempNote);
      count = 0;
    }
  }
  return tempNoteVector;
}

int main()
{
  cout << "Hello World!" << endl;

  map<int, string> tagDef = initTagDef();
  if(tagDef.empty())
    return 1;

  return 0;

}
