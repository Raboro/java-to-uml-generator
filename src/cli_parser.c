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
    short list_file_names;
    short list_file_content;
    short analyzed_files_counter;
} cli_parse_obj_t;

static struct option options[] = {
    {"help", no_argument, 0, 'h'},
    {"path", required_argument, 0, 'p'},
    {"exclusions", required_argument, 0, 'e'},
    {"list_file_names", no_argument, 0, 'n'},
    {"list_file_content", no_argument, 0, 'c'},
    {"analyzed_files_counter", no_argument, 0, 'a'},
    {0, 0, 0, 0}};

void print_help()
{
    printf("Usage:\n");
    printf("  jtuml                           Analyze this ('.') directory\n");
    printf("  jtuml -h                        Show help\n");
    printf("  jtuml -p [PATH] -e [EXCLUSIONS] -n -c\n\n");
    printf("Options:\n");
    printf("  -h, --help                      Display the help message\n");
    printf("  -p, --path                      Root path to analyze\n");
    printf("  -e, --exclusions                Exclusions for the analysis, file- and directory names, separated with ',' without space between\n");
    printf("  -n, --names_of_files_list       List all scanned filenames\n");
    printf("  -c, --content_of_file_list      List content of all scanned files\n");
    printf("  -a, --analyzed_files_counter    Show number of analyzed files\n");
}

void parse_exclusions(char *optarg, cli_parse_obj_t *cli_parse_obj)
{
    char *sub_exclusions;
    unsigned int number_of_exclusions = 0;
    const char delimiter = ',';

    sub_exclusions = strtok(optarg, &delimiter);

    while (sub_exclusions != NULL)
    {
        cli_parse_obj->exclusions[number_of_exclusions] = sub_exclusions;
        sub_exclusions = strtok(NULL, &delimiter);
        number_of_exclusions++;
    }

    cli_parse_obj->number_of_exclusion = number_of_exclusions;
}

void parse(cli_parse_obj_t *cli_parse_obj, int argc, char *argv[])
{
    int opt;
    cli_parse_obj->skip = 0;
    cli_parse_obj->list_file_names = 0;
    cli_parse_obj->list_file_content = 0;
    cli_parse_obj->analyzed_files_counter = 0;

    if (1 == argc)
    {
        cli_parse_obj->root_path = ".";
        return;
    }

    while (-1 != (opt = getopt_long(argc, argv, "hp:e:nca", options, NULL)))
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
            parse_exclusions(optarg, cli_parse_obj);
            break;

        case 'n':
            cli_parse_obj->list_file_names = 1;
            break;

        case 'c':
            cli_parse_obj->list_file_content = 1;
            break;

        case 'a':
            cli_parse_obj->analyzed_files_counter = 1;
            break;

        default:
            printf("Error parsing, try jtuml --help for more information; parsing error for: %c", opt);
            cli_parse_obj->skip = 1;
            return;
        }
    }
}