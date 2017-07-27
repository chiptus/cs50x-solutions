# Shorts -
## Call stack

Terms:
- Call Stack - a stack where the function is saved
- Stack frame or function frame - the chunk of memory that represnts the function
- open frame - a frame that is in the stack
- active frame - the frame on the top
- 


The most recently called function is at the top

## Pointers

- NULL - pointer to nothing
- &x - gives the address of the parameter x
- a name of of an array is a pointer to its first element (?)
 
**Main Purpose* - Allow modification or inspection of the location to which it points.

- * is the dereferncing operator
- * is also used as type name to say that a variable is a pointer
- *NULL will give us "seg fault" - ALWAYS INIT A POINTER WITH A KNOWN OR NULL VALUE
- When declaring a pointer, the star is part of the type name but also a part of the variable name - DO NOT DECLARE MULTIPLE POINTER IN ONE LINE
- any pointer are 4 or 8 bytes - depending on the system - because an adress is 32 or 64 bits.
- &m is the address of m.
- 

## File Pointers
- FILE vs FILE*
- file manipulation is done with stdio.h
- 