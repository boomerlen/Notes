/*  Main.cpp
*   Author: Hugo Sebesta
*   Project primarily for personal use so probably no one will ever see this
*   If anyone does then I said hi!
*/

#include <iostream>
#include "note.h"
#include "subject.h"

using namespace std;

int main()
{
  cout << "Hello World!" << endl;
  note TextFile;
  TextFile.setName("TextFile");

  cout << TextFile.getName() << endl;
  return 0;

}
