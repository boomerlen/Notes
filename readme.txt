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
