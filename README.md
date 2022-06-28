# minishell
This is simple shell. School42 project

Available functionality:
Execute file by a given path
Built-in functions such as:
 - cd (with "-" and "~" handlers)
 - echo (with "-n" option)
 - pwd
 - env
 - export
 - unset
 - (non mandatory) cat (only reads given files)\n
It is still possible to use /bin/cat\n
Connect several commands with a pipe.
Example: "simple command | simple command | ...".
It will transfer output of the command to the left of the pipe
as the input of the command to right of the pipe.\n
