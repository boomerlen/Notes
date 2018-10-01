/*  Main.cpp
*   Author: Hugo Sebesta
*   Project primarily for personal use so probably no one will ever see this
*   If anyone does then I said hi!
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <algorithm>

// Not STL
#include <windows.h>

// My files
#include "note.h"
#include "subject.h"

#define TAG_ADDR "..\\storage\\tags.txt"
#define NOTE_OUTLINE_ADDR "..\\storage\\notes.txt"
#define NOTE_STORAGE_ADDR "..\\notes"

#define DEL_OLD_NOTE false

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
  vector<note> tempNoteVector;

  ifstream file;
  file.open(NOTE_OUTLINE_ADDR, ios::in);
  if(!file.is_open())
  {
    cout << "Could not open " << NOTE_OUTLINE_ADDR << endl;
    return tempNoteVector;
  }
  string buffer;
  int count = 0;
  note TempNote;
  while(getline(file, buffer, ';'))
  {
    if(count == 0)
    {
      // Beginning of line: Note name and init the object
      TempNote.setName(buffer);
      count++;
    }
    else if(count == 1)
    {
      // Address
      TempNote.setLocation(buffer);
      count++;
    }
    else if(count == 2)
    {
      // Subjects
      stringstream str(buffer);
      int x = 0;
      str >> x;
      subjects sub = static_cast<subjects>(x);
      TempNote.setSubject(sub);
      count++;
    }
    else if(count == 3)
    {
      string tempStr = buffer;
      char buf[2];
      while(tempStr.size() > 1)
      {
        size_t lastComma = tempStr.rfind(",");
        tempStr.copy(buf, 1, lastComma+1);
        tempStr = tempStr.substr(0, lastComma);
        TempNote.addTag(stoi(buf));
      }
      TempNote.addTag(stoi(tempStr));

      tempNoteVector.push_back(TempNote);
      count = 0;
    }
  }
  return tempNoteVector;
}

vector<note *> initSubjectVector(subjects s, vector<note> *Notes) // Returns vector of notes of subject s
{
  vector<note *> correctNotes;
  for(vector<note>::iterator it = Notes->begin(); it != Notes->end(); it++)
  {
      if(it->getSubject() == s)
        correctNotes.push_back(&*it);
  }
  return correctNotes;
}

vector<note *> initTagVector(int t, vector<note> *Notes) // Returns vector of notes with subject id t
{// Could have errors with pointers cuz i still don't quite understand how to use them lol
  vector<note *> correctNotes;
  for(vector<note>::iterator it = Notes->begin(); it != Notes->end(); it++)
  {
    vector<int> ts = it->getTags();
    for(vector<int>::iterator it2 = ts.begin(); it2 != ts.end(); it2++)
    {
      if(*it2 == t)
      {
        correctNotes.push_back(&*it);
        break;
      }
    }
  }
  return correctNotes;
}

bool addNoteToFile(note *n)
{
  ofstream file;
  file.open(NOTE_OUTLINE_ADDR, ios::out | ios::app);
  if(!file.is_open())
  {
    cout << "Could not open " << NOTE_OUTLINE_ADDR << endl;
    return false;
  }

  file << n->getName() << ";";
  file << n->getLocation() << ";";
  file << static_cast<int>(n->getSubject()) << ";";
  for(int i = 0; i < n->getTags().size(); i++)
  {
    int l = n->getTags()[i];
    file << l << ","; // fix this
  }
  return true;
}

bool addNote(note *n) // Sticks note on file and moves it to local dir
{
  if(!addNoteToFile(n))
    return false;

  string newLoc = NOTE_STORAGE_ADDR + n->getName();
  CopyFile(n->getLocation().c_str(), newLoc.c_str(), false); // old addr, new addr, whether or not to get mad if its still there

  if(DEL_OLD_NOTE)
  {
    // Windows code to delete the old file
    DeleteFileA(n->getLocation().c_str());
    // Makes no sense to retain old file location
    n->setLocation("");
  }

  return true;
}

int main()
{
  cout << "Hello World!" << endl;
  // Init and debug
  map<int, string> tagDef = initTagDef();
  if(tagDef.empty())
    return 1;

  vector<note> noteList = initNotesVector();
  if(noteList.empty())
  {
    cout << "Notelist empty" << endl;
    return 1;
  }

  // Initialise lists for each subject.
  // Tags first
  vector<note *>  noteTagVector[tagDef.size()]; // Array of vectors
  for(int i = 0; i < tagDef.size(); i++)
  {
    noteTagVector[i] = initTagVector(i, &noteList);
  }

  vector<note *> noteSubjectVector[15]; // Note that subjects follow their cast in enum
  for(int i = 0; i < 15 /* hard coded */; i++)
  {
    noteSubjectVector[i] = initSubjectVector(static_cast<subjects>(i), &noteList);
  }

  /*  Now have these containers:
  *   map<int, string> tagDef
  *   vector<note> noteLIst
  *   vector< vector<*note> > noteTagVector
  *   vector< vector<*note> > noteSubjectVector
  */

  // Testing addNoteToFile
  /* Works like a dream
  note *p_note = new note("loc.txt", "notenotenote", S_MATHS_HL);
  p_note->addTag(1);
  p_note->addTag(3);
  p_note->addTag(2);

  addNote(p_note);
  delete p_note;
  */

  // Not gonna lie this console based UI is a pain in the fucken neck I feel like I'd have less touble with
  // a GUI

  // Basic Console-Based UI
  //string input;
  /*
  while(1)
  {
    cout << "> ";
    getline(cin, input);
    transform(input.begin(), input.end(), input.begin(), ::tolower); // Case doesn't matter
    if(input == "h" || input == "help" || input == "?")
    {
      cout << "> Help Dialogue, Commands:" << endl;
      cout << "> add note: Adds a note to the list" << endl;
      cout << "> add tag: Adds a tag to the database" << endl;
      cout << "> edit note: Edits information on a note including adding or removing tags" << endl;
      cout << "> display [notename]: Displays information for a specific note" << endl;
      cout << "> subject [subject]: Displays all notes (names) that fall under that subject" << endl;
      cout << "> tag [tag]: Displays all notes (names) that have that tag" << endl;
      cout << "> list tags: Lists tags in the database" << endl;
      cout << "> list subjects: Lists subjects in the database" << endl;
      cout << "> (q)uit: Exits the program" << endl;
    }
    else if(input == "add note")
    {
      string in_name;
      string in_sub;
      string in_file_addr;

      note new_note;

      cout << "> Note Add Dialogue:" << endl;
      cout << "> Specify a name for the note: ";
      getline(cin, in_name);

      do {
        cout << "> Specify a subject for " << in_name << " by specifying the number of the subject you would like, or typing ? to list the subjects: ";
        cin >> in_sub;
        if(in_sub == "?")
        {
          // List subjects
          for(int i = 0; i < 16; i++)
          {
            cout << i << ": ";
            cout << static_cast<subjects>(i) << endl;
          }
        }
      } while(in_sub == "?");
      int i_sub = stoi(in_sub);

      ofstream testFile;
      cout << "Specify the address of the file: ";
      getline(cin, in_file_addr);
      while(!testFile.is_open()) // Make sure file exists
      {
        cout << "Could not open file. Specify a new file name: ";
        getline(cin, in_file_addr);
      }
      testFile.close();
      string new_file_addr = "notes\\" + in_name;

      //if(!CopyFile(in_file_addr, new_file_addr, false))
      //  cout << "ERROR LINE 237";

      new_note.setName(in_name);
      new_note.setSubject(static_cast<subjects>(stoi(in_sub)));
      new_note.setLocation(in_file_addr);

      cout << "Would you like to add tags? (y/n): ";
      cin >> in_name;
      if(in_name == "y")
      {
        vector<int> in_tags;
        in_name = "";
        cout << "Enter a new tag ID on each line then type (q)uit to stop." << endl;
        while(in_name != "q" || in_name != "quit")
        {
          cin >> in_name;
          new_note.addTag(stoi(in_name));
        }

      }
      cout << "Added " << new_note.getName() << endl;
      noteList.push_back(new_note);
    }
  }
  */
  return 0;

}
