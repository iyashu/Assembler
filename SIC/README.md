# SIC Assembler
A simple [SIC](http://en.wikipedia.org/wiki/Sic) assembler written in C++ .
## Objective
--------------
Assemble the `simple` program code written in SIC and generate the required `object code` program.

##Usage
-------------
* Clone the Repository using Git .

* Edit the `Input.txt` file with your SIC program code .

<b>Please ensure that your SIC program code should not contain space-seperated comments </b> i.e

           Use :
              .SUBROUTINE_TO_READ_RECORD_INTO_BUFFER
           Instead of :
               .  SUBROUTINE TO READ RECORD INTO BUFFER

* Run the `SIC.cpp` program using required C++ Compiler .

* Note the generated Output files i.e `Overall_program.txt` , `Record.txt` , `SYMTAB.txt` .

* `Overall_program.txt` file contains the whole SIC program along with its object code .

*  `Record.txt`  file contains the whole object code program .

*  `SYMTAB.txt` file contains the required symbol table .



