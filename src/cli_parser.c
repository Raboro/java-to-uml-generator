#include <stdio.h>
#include <string.h>
#include <getopt.h>

#define FILENAME_MAX (260)

typedef struct cli_parse_obj
{
    short skip;
    char *root_path;
    char *exclusions[FILENAME_MAX];
    int number_of_exclusion;
} cli_parse_obj_t;

static struct option options[] = {
    {"help", no_argument, 0, 'h'},
    {"path", required_argument, 0, 'p'},
    {"exclusions", optional_argument, 0, 'e'},
    {0, 0, 0, 0}};

void print_help()
{
    printf("Usage:\n");
    printf("  jtuml                Analyze this ('.') directory\n");
    printf("  jtuml -h             Show help\n");
    printf("  jtuml -p [PATH] -e [EXCLUSIONS]\n\n");
    printf("Options:\n");
    printf("  -h, --help           Display the help message\n");
    printf("  -p, --path           Root path to analyze\n");
    printf("  -e, --exclusions     Exclusions for the analysis, file- and directory names, separated with ',' without space between\n");
}

void parse(cli_parse_obj_t *cli_parse_obj, int argc, char *argv[])
{
    int opt;
    cli_parse_obj->skip = 0;
    char delimiter = ',';
    char *sub_exclusions;
    int number_of_exclusions = 0;

    if (1 == argc)
    {
        cli_parse_obj->root_path = ".";
        return;
    }

    while (-1 != (opt = getopt_long(argc, argv, "hp:e:", options, NULL)))
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

        case 'e':
            sub_exclusions = strtok(optarg, &delimiter);

            while (sub_exclusions != NULL)
            {
                cli_parse_obj->exclusions[number_of_exclusions] = sub_exclusions;
                sub_exclusions = strtok(NULL, &delimiter);
                number_of_exclusions++;
            }

            cli_parse_obj->number_of_exclusion = number_of_exclusions;
            break;

        default:
            printf("Error parsing, try jtuml --help for more information");
        }
    }
}