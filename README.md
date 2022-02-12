# WORDLE SOLVER ANY DICTIONARY
Program that helps with wordle. Just have to write ***** ..... +LETTERSINIT -NOLETTERSINIT

## USAGE

Example:
  APOYO
  
  A***O ..Y.. +PY -CUSDLGE
 
-> Knowing that C,U,S,D,L,G,E aren't in the word and A and O are in a correct position. P,Y are in the word but in an unknown position. Moreover we know that Y isn't in the 3º position.

-> "*" Mean that any letter can be placed in that position

If you want to make a empty entry, write this: "***** ..... + - "

## PROGRAMS

The repository have the compiled programs for windows and linux.
Both Windows and linux open a Dialog to open the dictionary selecting the path.

## DICTIONARIES

Every dictionary is in ascii format, all accents have been removed and everthing is upper case.

## COMPILE
You can select the SO modifying the header of the Cpp.
#define WINDOWS
//#define LINUX

Comment the line that you arent using.

Moreover there is a option if you want to change the LENGTH of the words. with the first line. 

#define DEFAULTLENGTH, if you let it uncomment the program will use 5 as the LENGTH. If commented the program will ask for the lenght.
