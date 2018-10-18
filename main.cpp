/*
 *  Notes by Hugo Sebesta - main.cpp
 *  This is my code not yours, not that you'd probably actually be anyone apart from me anyways
 *  Though this is on GitHub so maybe
*/
#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif
// TODO: Finish function on making/reading config files -- bug fix

// STL
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <algorithm>
#include <cstring>

// WINDOWS
#include <tchar.h>
#include <windows.h>

// MINE
#include "note.h"
#include "subject.h"

// Config file addresses
#define CONFIG_ADDR "C:\\"
#define ALT_CONFIG_ADDR "config.conf"
// Figure out where to place it later, for now just check local.

#define DEL_OLD_NOTE false

using namespace std;

// Global vars
string TAG_ADDR;
string NOTE_OUTLINE_ADDR;
string NOTE_STORAGE_ADDR;
string CONFIG_FILE_ADDR;

struct strArray{
    string tagaddr;
    string noteoutaddr;
    string notestorageaddr;
};

// All of my functions
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
{
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

strArray initConfigFile()
{
    ifstream confFile;
    strArray stringArray;

    confFile.open(CONFIG_ADDR, ios::in);
    if(confFile.is_open())
    {
        CONFIG_FILE_ADDR = CONFIG_ADDR;
        confFile.close();
    }
    else
    {
        confFile.open(ALT_CONFIG_ADDR, ios::in);
        if(confFile.is_open())
        {
            CONFIG_FILE_ADDR = ALT_CONFIG_ADDR;
            confFile.close();
        }
        else
        {
           cout << "No config file!" << endl;
           return stringArray;
        }
    }

    // Each line will have a different config file to return
    confFile.open(CONFIG_FILE_ADDR, ios::in);
    // this file has been verified by the logic below
    string buf;
    confFile >> buf;
    stringArray.tagaddr = buf;

    confFile >> buf;
    stringArray.noteoutaddr = buf;

    confFile >> buf;
    stringArray.notestorageaddr = buf;

    confFile.close();
    return stringArray;
}

bool updateConfigFile(string *tagAddr, string *noteOutAddr, string *noteStorageAddr)
{
    ofstream configFile;
    configFile.open(CONFIG_FILE_ADDR, ios::out | ios::trunc);
    if(!configFile.is_open())
        return false;

    configFile << tagAddr /*<< "\n"*/;
    configFile << noteOutAddr /*<< "\n"*/;
    configFile << noteStorageAddr /*<< "\n"*/;
    configFile.close();
    return true;
}

// Windows stuff
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("Notes");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    cout << "Hello World!" << endl;


    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           544,                 /* The programs width */
           375,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    // All of my code (to now integrate with the window)
    // Find and load config file
    strArray strA = initConfigFile();
    TAG_ADDR = strA.tagaddr;
    NOTE_OUTLINE_ADDR = strA.noteoutaddr;
    NOTE_STORAGE_ADDR = strA.notestorageaddr;

    bool needToUpdate = false;
    if(TAG_ADDR.empty())
    {
        cout << "Please enter the address of the tag configuration file: ";
        cin >> TAG_ADDR;
        needToUpdate = true;
    }

    if(NOTE_OUTLINE_ADDR.empty())
    {
        cout << "Please enter the address of the note outline file: ";
        cin >> NOTE_OUTLINE_ADDR;
        needToUpdate = true;
    }

    if(NOTE_STORAGE_ADDR.empty())
    {
        cout << "Please enter the address of the note storage folder: ";
        cin >> NOTE_STORAGE_ADDR;
        needToUpdate = true;
    }

    bool allGood = true;
    if(needToUpdate)
        allGood = updateConfigFile(&TAG_ADDR, &NOTE_OUTLINE_ADDR, &NOTE_STORAGE_ADDR);

    if(!allGood)
        cout << "Error modifying config file!" << endl;

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

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
