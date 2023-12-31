#include <stdio.h>
#include <getopt.h>

typedef struct cli_parse_obj
{
    char *root_path;
} cli_parse_obj_t;

static struct option options[] = {
    {"help", no_argument, 0, 'h'},
    {"path", required_argument, 0, 'p'},
    {0, 0, 0, 0}};

void print_help()
{
    printf("Usage:\n  jtuml -h\n");
    printf("Options:\n");
    printf("  -h, --help     Display the help message\n");
    printf("  -p, --path     Root path to analyze\n");
}

void parse(cli_parse_obj_t *cli_parse_obj, int argc, char *argv[])
{
    int opt;

    if (1 == argc)
    {
        cli_parse_obj->root_path = ".";
        return;
    }

    while (-1 != (opt = getopt_long(argc, argv, "hp:", options, NULL)))
    {
        switch (opt)
        {
        case 'h':
            print_help();
            break;

        case 'p':
            cli_parse_obj->root_path = optarg;
            break;

        default:
            printf("Error parsing, try jtuml --help for more information");
        }
    }
}