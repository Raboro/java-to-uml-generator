#include <stdio.h>
#include <getopt.h>

typedef struct cli_parse_obj
{
    char *root_path;
} cli_parse_obj_t;

static struct option options[] = {
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}};

void print_help()
{
    printf("Usage:\n  jtuml -h\n");
    printf("Options:\n");
    printf("  -h, --help     Display the help message\n");
}

void parse(cli_parse_obj_t *cli_parse_obj, int argc, char *argv[])
{
    int opt;

    if (1 == argc)
    {
        cli_parse_obj->root_path = ".";
        return;
    }

    while (-1 != (opt = getopt_long(argc, argv, "h", options, NULL)))
    {
        switch (opt)
        {
        case 'h':
            print_help();
            break;

        default:
            printf("Error parsing, try jtuml --help for more information");
        }
    }
}