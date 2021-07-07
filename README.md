# Ștefan MĂGIRESCU

## VIM Editor

Basic VIM-like editor with basic operations such as:
- insert mode
- view mode
- goto line
- delete line
- goto character
- delete character
- replace word
- delete word
- replace word everywhere
- delete word everywhere
- save
- quit

-> Undo and redo are implemented by using two stacks. The input characters are saved as dynamic list elements
and all intrusive operations work by cutting, extracting sequences and optionally, gluing other sequences
in their places.

-> Every operation applies right away, after having been read from the input file. That makes 
the undo operation quite challenging (keep in mind many of the variables are passed as pointers, or references
to pointers etc.) 

-> If the editor quits before the text being saved, it obviously, returns to the state that was last saved, or empty,
if never saved.

-> Input is in *editor.in* file and the program outputs to *editor.out*.

For more on how the input should be, check *description.pdf* or head over to input folder and take a look at the tests.

*For more on how the functions work, check comments.*
