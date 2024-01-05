# Java to UML Generator 

Generate basic UML Class Diagramm out of Java Code with a CLI tool writen in C.

## Install
After cloning the repo and cd into the project, just use ``make`` in your terminal:
```bash
$ make
```

After that link it to your system. For example windows users need to add ``jtuml.exe`` to the system environment variables.
Then it´s usable in the terminal via:
```bash
$ jtuml ...
```

## Usage
```bash
Usage:
  jtuml                           Analyze this ('.') directory
  jtuml -h                        Show help
  jtuml -p [PATH] -e [EXCLUSIONS] -n -c -a

Options:
  -h, --help                      Display the help message
  -p, --path                      Root path to analyze
  -e, --exclusions                Exclusions for the analysis, file- and directory names, separated with ',' without space between
  -n, --names_of_files_list       List all scanned filenames
  -c, --content_of_file_list      List content of all scanned files
  -a, --analyzed_files_counter    Show number of analyzed files
```

## Additional makefile operations
You can cleanup all files if something went wrong with:
```bash
$ make cleanup
```
You can also run directly with make in the current directory with:
```bash
$ make run_here
```

## Improvements
- show differences between class, enum, interface, record
- add fields
- add references