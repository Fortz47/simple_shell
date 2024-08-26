
# Simple Shell

**UNIX Command Line Interpreter**

---

## Overview

This project is a simple UNIX command line interpreter, often referred to as a shell. It functions similarly to the standard shell (`/bin/sh`), providing users with an interface to interact with the operating system via command-line commands.

---

## Output

The program's output is designed to mirror that of `sh` (`/bin/sh`), including identical error messages. The primary difference is that when an error is encountered, the program name is equivalent to `argv[0]`.

### Example of Error Handling

#### Using `sh`:

```sh
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found

$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
```

#### Same error with The program `hsh` (program name after compilation):
```sh
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$
```

### Compilation
The shell was compiled this way
```sh
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh<br>
```
### Testing
The shell should work like this in interactive mode
```sh
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```
#### But also in non-interactive mode:
```sh
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```

### List of functions and system calls this project was limited to
> access (man 2 access)<br>
> chdir (man 2 chdir)<br>
> close (man 2 close)<br>
> closedir (man 3 closedir)<br>
> execve (man 2 execve)<br>
> exit (man 3 exit)<br>
> \_exit (man 2 \_exit)<br>
> fflush (man 3 fflush)<br>
> fork (man 2 fork)<br>
> free (man 3 free)<br>
> getcwd (man 3 getcwd)<br>
> getline (man 3 getline)<br>
> getpid (man 2 getpid)<br>
> isatty (man 3 isatty)<br>
> kill (man 2 kill)<br>
> malloc (man 3 malloc)<br>
> open (man 2 open)<br>
> opendir (man 3 opendir)<br>
> perror (man 3 perror)<br>
> read (man 2 read)<br>
> readdir (man 3 readdir)<br>
> signal (man 2 signal)<br>
> stat (\_\_xstat) (man 2 stat)<br>
> lstat (\_\_lxstat) (man 2 lstat)<br>
> fstat (__fxstat) (man 2 fstat)<br>
> strtok (man 3 strtok)<br>
> wait (man 2 wait)<br>
> waitpid (man 2 waitpid)<br>
> wait3 (man 2 wait3)<br>
> wait4 (man 2 wait4)<br>
> write (man 2 write)<br>
