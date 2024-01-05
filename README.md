# Java to UML Generator 

Generate basic UML Class Diagramm out of Java Code with a CLI tool writen in C.

## Usage
```bash
Usage:
  jtuml                           Analyze this ('.') directory
  jtuml -h                        Show help
  jtuml -p [PATH] -e [EXCLUSIONS] -n -c

Options:
  -h, --help                      Display the help message
  -p, --path                      Root path to analyze
  -e, --exclusions                Exclusions for the analysis, file- and directory names, separated with ',' without space between
  -n, --names_of_files_list       List all scanned filenames
  -c, --content_of_file_list      List content of all scanned files
  -a, --analyzed_files_counter    Show number of analyzed files

```

## Improvements
- show differences between class, enum, interface, record
- add fields
- add references