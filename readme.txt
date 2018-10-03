<h>README</h>
README for Notes - Text and Note organiser (manager) for school students
Primary tasks are to organise, sort and collect text files into helpful categories for the user.
GUI based.
Files overview:
Will store all notes that are added to the manager in a specific directory, C:\Program Files\HSNotesManager\notes
Eventually dump config in C:\Program Files\HSNotesManager\config.txt
These files in C:\Program Files\HSNotesManager
Class "note" with methods: set, delete.
Class textNote which extends from "note", with additional methods: read, edit (eventually) summarise
Class imageNote which extends from "note", with additional methods: read.
LATER support more note types, including (hopefully) Word and PDF, once I'm up to there and find a nice library to parse it all.

Subjects will be hardcoded in. Maybe one day if this becomes like actually proper Ill change that but for now thats fine. Enum for this is in subjects.h
Will include tags for both this year and next year's subjects, depending on when this actually becomes usable.
Each file will contain all of its category and tag information, but it will also be stored in a directory file that will contain all of this information for easier access


Directory system:
One file will contain all the members for "note" per note so the long term storage does exist.
Initialisation will consist of taking all the tags from their file and placing them onto RAM,
Taking all the note objects and placing them on RAM,
Creating vectors for all of the notes of each subject


Windows headers were too complicated and were going to cause too many issues. Back to GTK

Compiling is an absolute nightmare. I need to use bash to get command substitution to work,
which means using msys2 for the pkg-config gtk+-3.0 --cflags --libs substitution.
It's so ridiculously complicated.

The command (inside msys) is g++ -std=c++11 main.cpp note.cpp note.h subject.h -o bin/out `pkg-config gtk+-3.0 --cflags --libs` or `cat gtkInclude.txt` if It cant find it

Except that of course pkg-config doesn't find anything for gtk+-3.0 in msys cuz then my life would be too easy

Its ok I fixed it. I stuck a text file wit the pkg-config stuff in it and then am opening that in msys and its complicated but it works and the commands above
Nevermind, doing that compiles for linux (not a .exe) because of course it would its bloody ubuntu bash simulation not Windows
So i gotta somehow command either the pkg-config thing back into cmd or an cat textfile.text
Any help would be extremely greatly appreciated.

Using powershell to compile allows me to do command substitution in the form of $(pkg-config gtk+-3.0 --cflags --libs)
So that could work
Except that when I do that, g++ complains that what has been parsed from pkg-config is not a valid command line option or something


Ok I finally have it working.
In order to compile this is what you have to do.
Inside msys you navigate to it and run:
g++ -std=c++11 main.cpp note.h note.cpp subject.h `cat gtkInclude.txt` -o bin/out
This can now be run in cmd at the location by running 'out'
This works also because I downloaded the extra .dlls which msys means that we need.
We wouldn't need them if I could compile it with CMD except that I can't figure out how to substitute the whole pkg-config thing into CMD
So yeah this works now and that only took quite a long time and effort and mental willpower.
Ima push this online now and probably take a break, after opening and closing my fancy new GUI a couple of times.
