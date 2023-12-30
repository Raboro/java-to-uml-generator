#include <stdio.h>
#include <getopt.h>

static struct option options[] = {
    {"help", no_argument, 0, 'h'},
    {0, 0, 0, 0}};

void print_help()
{
    printf("Usage:\n  jtuml -h\n");
    printf("Options:\n");
    printf("  -h, --help     Display the help message\n");
}

void parse(int argc, char *argv[])
{
    int opt;

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