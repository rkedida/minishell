# minishell
MiniShell is a simple shell created as a learning project to understand processes and file descriptors in C programming language.
  
It's a recreation of a tiny bit of bash shell functionality.

## Table of Contents

1. [Introduction](#Introduction)

2. [Features](#Features)

3. [Getting Started](#Getting-Started)

4. [Builtins](#Builtins)

5. [Contributing](#Contributing)

6. [License](#License)

## Introduction

The shell is a command-line interpreter that offers a user interface for the operating system's services.
  
MiniShell replicates some of the basic functionalities of a Unix-like command-line user interface.

## Features

MiniShell supports the following features:

- Displaying a prompt when waiting for a new command.

- Executing commands with their parameters.

- Handling absolute and relative paths for commands.

- Redirections: < (input), > (output), >> (output in append mode), and << (input until a delimiter).

- Pipes (|): the output of each command in the pipeline is connected to the input of the next command via a pipe.

- Environment variables expansion: `$` followed by a sequence of characters.

- Special variable expansion: `$?` (the exit status of the most recently executed foreground pipeline).

- Ctrl-C, Ctrl-D, and Ctrl-\ signals handling.

- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.
  
## Getting Started

To compile, run `make`.
This will create an executable named `minishell`.

Start the program by running:

```bash
./minishell
```

## Builtins
MiniShell implements the following builtins:

echo with option -n

cd with only a relative or absolute path

pwd with no options

export with no options

unset with no options

env with no options or arguments

exit with no options

## Contributors
This project was completed by:
Kheireddine Fergani @khirooo

Robel Kedida @robelkedida


## Contributing
Contributions are welcome. Please open an issue or submit a pull request for any bugs/improvements.
