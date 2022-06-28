# minishell
This is simple shell. School42 project

To create an executable, cd to a project folder and type "make".

Available functionality:

= Execute file by a given path

= Built-in functions such as:
 - cd (with "-" and "~" handlers)
 - echo (with "-n" option)
 - pwd
 - env
 - export
 - unset
 - (non mandatory) cat (only reads given files)
It is still possible to use /bin/cat

= Connect several commands with a pipe.
Example: "simple command | simple command | ...".
It will transfer output of the command to the left of the pipe
as the input of the command to right of the pipe.

= Redirect input and output of the program to a file.
Possible redirects are: ">", ">>", "<" and "<<".

">" will write output of a programm to a file specified to the right of the arrow. All contents of a file will be lost.

">>" will add output of a programm to the end of a file specified to the right of the arrow.

"<" will put all contents of a file specified to the right of the arrow as an input to a program.

"<<" will read from stdin untill the delimiter is met and put read contents as an input to a program.
