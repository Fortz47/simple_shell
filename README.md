# simple_shell
UNIX command line interpreter. Shell

****Output****<br>
The program has the exact same output as sh (/bin/sh) as well as the exact same error output.
The only difference is when an error is printed, the name of the program is equivalent to the argv[0] (See below)

Example of error with sh:<br>

$ echo "qwerty" | /bin/sh<br>
/bin/sh: 1: qwerty: not found<br>
$ echo "qwerty" | /bin/../bin/sh<br>
/bin/../bin/sh: 1: qwerty: not found<br>
$<br>
Same error with The program hsh (program name after compilation):<br>

$ echo "qwerty" | ./hsh<br>
./hsh: 1: qwerty: not found<br>
$ echo "qwerty" | ./././hsh<br>
./././hsh: 1: qwerty: not found<br>
$<br>

**List of allowed functions and system calls**<br>
access (man 2 access)<br>
chdir (man 2 chdir)<br>
close (man 2 close)<br>
closedir (man 3 closedir)<br>
execve (man 2 execve)<br>
exit (man 3 exit)<br>
_exit (man 2 _exit)<br>
fflush (man 3 fflush)<br>
fork (man 2 fork)<br>
free (man 3 free)<br>
getcwd (man 3 getcwd)<br>
getline (man 3 getline)<br>
getpid (man 2 getpid)<br>
isatty (man 3 isatty)<br>
kill (man 2 kill)<br>
malloc (man 3 malloc)<br>
open (man 2 open)<br>
opendir (man 3 opendir)<br>
perror (man 3 perror)<br>
read (man 2 read)<br>
readdir (man 3 readdir)<br>
signal (man 2 signal)<br>
stat (__xstat) (man 2 stat)<br>
lstat (__lxstat) (man 2 lstat)<br>
fstat (__fxstat) (man 2 fstat)<br>
strtok (man 3 strtok)<br>
wait (man 2 wait)<br>
waitpid (man 2 waitpid)<br>
wait3 (man 2 wait3)<br>
wait4 (man 2 wait4)<br>
write (man 2 write)<br>

**Compilation**<br>
The shell was compiled this way:<br>

gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh<br>

**Testing**<br>
The shell should work like this in **interactive mode**:<br>

$ ./hsh<br>
($) /bin/ls<br>
hsh main.c shell.c<br>
($)<br>
($) exit<br>
$<br>

But also in **non-interactive mode**:<br>

$ echo "/bin/ls" | ./hsh<br>
hsh main.c shell.c test_ls_2<br>
$<br>
$ cat test_ls_2<br>
/bin/ls<br>
/bin/ls<br>
$<br>
$ cat test_ls_2 | ./hsh<br>
hsh main.c shell.c test_ls_2<br>
hsh main.c shell.c test_ls_2<br>
$<br>
