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
