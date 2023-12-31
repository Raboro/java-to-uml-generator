#ifndef CLI_PARSER_H
#define CLI_PARSER_H

#define FILENAME_MAX (260)

/**
 * @brief object contains cli options
 */
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

/**
 * @brief parse the input of the user to valid structs for the code later on
 *
 * @param cli_parse_obj cli_parse_obj_t*;
 * @param argc int; parsed from main
 * @param argv[] char*; parsed from main
 */
void parse(cli_parse_obj_t *cli_parse_obj, int argc, char *argv[]);

/**
 * @brief parse the exclusion argument
 *
 * @param optarg char*, exclusion argument parsed
 * @param cli_parse_obj cli_parse_obj_t*;
 */
void parse_exclusions(char *optarg, cli_parse_obj_t *cli_parse_obj);

#endif