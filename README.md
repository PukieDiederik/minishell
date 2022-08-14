# MINISHELL
Minishell is a project from 42 in which you are tasked to create a small shell which
can launch and execute programs. Other than just launching programs it had a few more
requirements. These requirements are:
* Display a prompt when waiting for a new command.
* Have a working history.
* Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).
* Handle `’` which should prevent the shell from interpreting the meta-characters in the quoted sequence.
* Handle `"` which should prevent the shell from interpreting the meta-characters in the quoted sequence except for `$`.
* Implement redirections.
    * `<` should redirect input.
    * `>` should redirect output.
    * `<<` here documents.
    * `>>` should redirect output in append mode.
* Implement pipes (`|`). The output of each command in the pipeline is connected to the input of the next command
  via a pipe.
* Handle l_environ variables (`$[NAME]`) which should expand to their values.
* Handle $? which should expand to the exit status of the most recently executed foreground pipeline.
* Handle `ctrl+C`, `ctrl+D` and `ctrl+\` which should behave like in bash.
    * In interactive mode:
    * `ctrl+C` displays a new prompt on a new line.
    * `ctrl+D` exits the shell.
    * `ctrl+\` does nothing.
* The shell must implement the following builtins
    * `echo` with `-n`.
    * `cd` with only a relative or absolute path.
    * `pwd` with no options.
    * `export` with no options.
    * `unset` with no options.
    * `env` with no options or arguments.
    * `exit` with no options.
    
## How to install
### 1. Cloning the git repository
This command will clone the repository and install all the submodules
```shell
git clone https://github.com/PukieDiederik/minishell.git --recursive-submodules
```
If you already have this installed without the submodules you need to run:
```shell
git submodule init && git submodule update
```
This will install and update all submodules required for this project

### 2. Compile the program
Compile the project using the following command:
```shell
make
```
For cleaning all the object files run (not required):
```shell
make clean
```
To remove clean everything including the executable run:
```shell
make fclean
```
To recompile the project run:
```shell
make re
```