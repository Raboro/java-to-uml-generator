#include <stdio.h>
#include <getopt.h>

typedef struct cli_parse_obj
{
    short skip;
    char *root_path;
} cli_parse_obj_t;

static struct option options[] = {
    {"help", no_argument, 0, 'h'},
    {"path", required_argument, 0, 'p'},
    {0, 0, 0, 0}};

void print_help()
{
    printf("Usage:\n");
    printf("  jtuml           Analyze this ('.') directory\n");
    printf("  jtuml -h        Show help\n");
    printf("  jtuml -p [PATH] \n\n");
    printf("Options:\n");
    printf("  -h, --help     Display the help message\n");
    printf("  -p, --path     Root path to analyze\n");
}

void parse(cli_parse_obj_t *cli_parse_obj, int argc, char *argv[])
{
    int opt;
    cli_parse_obj->skip = 0;
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
            cli_parse_obj->skip = 1;
            break;

        case 'p':
            cli_parse_obj->root_path = optarg;
            break;

        default:
            printf("Error parsing, try jtuml --help for more information");
        }
    }
}