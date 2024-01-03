#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "file_scanning.h"

char *parse_name(char *name)
{
    char *without_dot = strtok(name, ".");
    return (NULL == without_dot) ? name : without_dot;
}

void parse_to_file(uml_obj_t *uml_objects, int uml_objects_len)
{
    FILE *file = fopen("uml.md", "w");
    fprintf(file, "````mermaid\n");
    fprintf(file, "classDiagram\n");

    for (int i = 0; i < uml_objects_len; i++)
    {
        fprintf(file, "class %s\n", parse_name(uml_objects[i].name));

        // inner classes
        for (int j = 0; j < uml_objects[i].sub_objects_len; j++)
        {
            fprintf(file, "class %s\n", parse_name(uml_objects[i].sub_objs[j]));
        }
    }

    fprintf(file, "````\n");
    fclose(file);
}