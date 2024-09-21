# Minishell

Welcome to the Minishell project, a simple yet functional shell implemented as part of the 42 Network cursus. This project serves as an educational experience in systems programming, allowing you to explore the inner workings of a Unix-like shell.
![193665518-0c0c7fec-38a9-4f6c-91ca-fef606abfb0d](https://github.com/user-attachments/assets/578b9287-cc26-479c-885a-4c567722adaa)

## Overview

Minishell is a lightweight shell that supports basic commands and features, including command execution, environment variable management, and input/output redirection. This project aims to deepen your understanding of process management and the Unix operating system.

## Features

- Execute built-in commands (`cd`, `exit`, `echo`, etc.)
- Support for external commands
- Input/output redirection (`>`, `<`, `>>`, `<<`)
- Piping between commands (`|`)
- Logical operators: AND (`&&`), OR (`||`)
- Command grouping with parentheses (`()`)
- Environment variable management (`export`, `unset`, `env`)
- Command history
- Signal handling (e.g., handling Ctrl+C)

## Installation

To build and start the Minishell, follow these steps:
   ```bash
   git clone https://github.com/lmakinaa/minishell.git
   cd minishell
   make
   ./minishell```
