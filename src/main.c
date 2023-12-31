#include <stdio.h>
#include <stdlib.h>

#include "file_scanning.h"
#include "cli_parser.h"

int main(int argc, char *argv[])
{
    cli_parse_obj_t *cli_parse_obj = (cli_parse_obj_t *)malloc(sizeof(cli_parse_obj_t));
    parse(cli_parse_obj, argc, argv);

    int file_counter = count_files(cli_parse_obj->root_path);
    printf("%d\n", file_counter);

    uml_obj_t uml_objects[file_counter];
    int counter = 0;
    collect_uml_objects(".", uml_objects, &counter);

    for (int i = 0; i < counter; i++)
    {
        printf("File %d: %s with path: %s\n", i + 1, uml_objects[i].name, uml_objects[i].path);
        free(uml_objects[i].name);
        free(uml_objects[i].path);
    }

    free(cli_parse_obj);
    return 0;
}