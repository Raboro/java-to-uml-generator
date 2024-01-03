#include <stdio.h>

#include "file_scanning.h"

void parse_to_file(uml_obj_t *uml_objects)
{
    FILE *file = fopen("uml.md", "w");
    fprintf(file, "````mermaid\n");
    fprintf(file, "classDiagram\n");
    fprintf(file, "````\n");
    fclose(file);
}