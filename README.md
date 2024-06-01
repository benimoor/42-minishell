# Minishell

Minishell is a minimal version of a Unix shell created as part of the 42 École curriculum. It aims to replicate basic functionalities of a shell, including command execution, environment variable management, input/output redirection, and pipe handling.

## Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Built-ins](#built-ins)
- [Implementation Details](#implementation-details)
- [License](#license)
- [Contact](#contact)

## Features

- Execute binary files located in the system's PATH.
- Handle the following built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.
- Environment variable management.
- Input and output redirection using `<` and `>`.
- Pipe (`|`) support for chaining commands.
- Basic signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`).

## Installation

To build and run the minishell project, follow these steps:

1. **Clone the repository**
   ```sh
   git clone https://github.com/your_username/minishell.git
   cd minishell

    Build the project

    sh

    make

Usage

To start the minishell, simply run the compiled executable:

sh

./minishell

Examples

    Running a command

    sh

minishell> ls -l

Using built-ins

sh

minishell> cd /path/to/directory
minishell> echo "Hello, world!"

Redirections

sh

minishell> echo "Hello, file!" > output.txt
minishell> cat < input.txt

Pipes

sh

    minishell> ls -l | grep minishell

Built-ins

    echo [args]: Display a line of text.
    cd [dir]: Change the current directory.
    pwd: Print the current working directory.
    export [name[=value] ...]: Set or export environment variables.
    unset [name ...]: Unset environment variables.
    env: Display the environment.
    exit [n]: Exit the shell.

Implementation Details

    Execution: Commands are parsed and executed using fork, execve, and wait system calls.
    Redirection: Input and output redirection is handled by manipulating file descriptors.
    Pipes: Pipes are implemented using the pipe system call to link the output of one process to the input of another.
    Signal Handling: Signals such as SIGINT (Ctrl+C) are captured and handled to ensure the shell remains interactive.


YErik Grigoryan - ergrigor@student.42yerevan.am
