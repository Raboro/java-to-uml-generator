#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "file_scanning.h"

char *parse_name(char *name)
{
    char *without_dot = strtok(name, ".");
    return (NULL == without_dot) ? name : without_dot;
}

int names_equal(char *obj_name, char *sub_obj_name)
{
    size_t sub_obj_name_len = strlen(sub_obj_name);
    if (sub_obj_name_len > 0)
    {
        --sub_obj_name_len;
    }
    return !strncmp(obj_name, sub_obj_name, sub_obj_name_len);
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
            // not allow duplicates
            if (names_equal(uml_objects[i].name, uml_objects[i].sub_objs[j]))
            {
                continue;
            }
            fprintf(file, "class %s\n", parse_name(uml_objects[i].sub_objs[j]));
        }
    }

    fprintf(file, "````\n");
    fclose(file);
}