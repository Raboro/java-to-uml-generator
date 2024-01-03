#include <stdio.h>
#include <stdlib.h>

#include "file_scanning.h"
#include "cli_parser.h"
#include "uml_parser.h"

int main(int argc, char *argv[])
{
    cli_parse_obj_t *cli_parse_obj = (cli_parse_obj_t *)malloc(sizeof(cli_parse_obj_t));
    parse(cli_parse_obj, argc, argv);

    if (cli_parse_obj->skip)
    {
        return 0;
    }

    int file_counter = count_files(cli_parse_obj->root_path, cli_parse_obj->exclusions, cli_parse_obj->number_of_exclusion);
    printf("%d\n", file_counter);

    uml_obj_t uml_objects[file_counter];
    int counter = 0;
    collect_uml_objects(cli_parse_obj->root_path, uml_objects, &counter, cli_parse_obj->exclusions, cli_parse_obj->number_of_exclusion);

    parse_to_file(uml_objects);

    for (int i = 0; i < counter; i++)
    {
        if (cli_parse_obj->list_file_names)
        {
            printf("File %d: %s with path: %s\n", i + 1, uml_objects[i].name, uml_objects[i].path);
        }
        free(uml_objects[i].name);
        free(uml_objects[i].path);
    }

    free(cli_parse_obj);
    return 0;
}