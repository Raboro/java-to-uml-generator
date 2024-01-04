#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#define SEEK_START 0
#define READING_MODE_SINGLE_BYTE 1
#define FILENAME_MAX (260)

#define MAX_KEYWORDS 4
const char *keywords[MAX_KEYWORDS] = {"class", "record", "enum", "interface"};

int count_files(char *root_path, char *exclusions[FILENAME_MAX], int number_of_exclusion);

int is_dir(struct dirent *dirent)
{
    return dirent->d_type == DT_DIR;
}

int is_file(struct dirent *dirent)
{
    return dirent->d_type == DT_REG;
}

int is_default_exclusion(char d_name[FILENAME_MAX])
{
    return strcmp(d_name, ".") == 0 || strcmp(d_name, "..") == 0 || !strcmp(d_name, ".git");
}

int is_not_excluded(char d_name[FILENAME_MAX], char *exclusions[FILENAME_MAX], int number_of_exclusion)
{
    if (is_default_exclusion(d_name))
    {
        return 0;
    }

    for (int i = 0; i < number_of_exclusion; i++)
    {
        if (!strcmp(d_name, exclusions[i]))
        {
            return 0;
        }
    }
    return 1;
}

int count_files_(DIR *dir, char *path, int counter, char *exclusions[FILENAME_MAX], int number_of_exclusion)
{
    struct dirent *dir_read;
    while (NULL != (dir_read = readdir(dir)))
    {
        if (is_dir(dir_read))
        {
            if (is_not_excluded(dir_read->d_name, exclusions, number_of_exclusion))
            {
                char new_path[1024];
                sprintf(new_path, "%s/%s", path, dir_read->d_name);
                counter += count_files(new_path, exclusions, number_of_exclusion);
            }
        }
        else if (is_file(dir_read))
        {
            if (is_not_excluded(dir_read->d_name, exclusions, number_of_exclusion))
            {
                counter++;
            }
        }
    }
    return counter;
}

int count_files(char *root_path, char *exclusions[FILENAME_MAX], int number_of_exclusion)
{
    DIR *dir = opendir(root_path);

    if (!dir)
    {
        printf("Directory opening error");
        return 0;
    }

    int counter = count_files_(dir, root_path, 0, exclusions, number_of_exclusion);
    closedir(dir);
    return counter;
}

typedef struct uml_obj
{
    char *path;
    char *name;
    char **sub_objs;
    int sub_objects_len;
} uml_obj_t;

FILE *get_file(char *file_name)
{
    FILE *file = fopen(file_name, "rb");

    if (NULL == file)
    {
        perror("file reading leads to error");
        return NULL;
    }

    return file;
}

size_t determine_size_of_file(FILE *file)
{
    size_t file_size;

    fseek(file, SEEK_START, SEEK_END);
    file_size = ftell(file);
    fseek(file, SEEK_START, SEEK_SET);

    return (file_size + 1); // off by one => increase by one
}

void parse_file_into_buffer(FILE *file, size_t file_size, char *buffer)
{
    fread(buffer, READING_MODE_SINGLE_BYTE, file_size, file);
    fclose(file);
}

int contains_keyword(char *str, const char *keyword)
{
    return (strstr(str, keyword) != NULL) ? 1 : 0;
}

void insert_file(struct dirent *dirent, uml_obj_t *uml_objects, int *counter, char *path, int list_content)
{
    char file_name[1024];
    sprintf(file_name, "%s/%s", path, dirent->d_name);
    FILE *file = get_file(file_name);

    size_t file_size = determine_size_of_file(file);
    char *buffer = (char *)malloc(file_size + 1);
    parse_file_into_buffer(file, file_size, buffer);

    buffer[file_size] = '\0';

    if (list_content)
    {
        printf("%s:\n", dirent->d_name);
        printf("%s\n\n", buffer);
    }

    for (int i = 0; i < MAX_KEYWORDS; i++)
    {
        if (!contains_keyword(buffer, keywords[i]))
        {
            continue;
        }

        char *s = strstr(buffer, keywords[i]);
        int substring_count = 0;
        char **substrings = NULL;

        while (s != NULL)
        {
            char *end = s;
            char *start = s;
            int count = 0;

            while (*end != '\0' && (count < 2 && (*end != '{' && *end != '(')))
            {
                if (*end == ' ')
                {
                    if (start == s)
                    {
                        start = end + 1;
                    }
                    count++;
                }
                end++;
            }

            size_t length = end - start;
            char *substring = malloc(length + 1); // +1 for null terminator
            strncpy(substring, start, length);
            substring[length] = '\0';

            substrings = realloc(substrings, (substring_count + 1) * sizeof(char *));
            substrings[substring_count] = substring;

            substring_count++;

            for (int j = 0; j < MAX_KEYWORDS; j++)
            {
                if (!contains_keyword(buffer, keywords[j]))
                {
                    continue;
                }
                s = strstr(end, keywords[j]);
                break;
            }
        }
        uml_objects[*counter].name = strdup(dirent->d_name);
        uml_objects[*counter].path = strdup(path);
        uml_objects[*counter].sub_objs = substrings;
        uml_objects[*counter].sub_objects_len = substring_count;
    }

    if (NULL != uml_objects[*counter].name)
    {
        (*counter)++;
    }
}

void collect_uml_objects(char *root_path, uml_obj_t *uml_objects, int *counter, char *exclusions[FILENAME_MAX], int number_of_exclusion, int list_content)
{
    DIR *dir = opendir(root_path);

    if (!dir)
    {
        printf("Directory opening error\n");
    }

    struct dirent *dir_read;
    while (NULL != (dir_read = readdir(dir)))
    {
        if (is_dir(dir_read))
        {
            if (is_not_excluded(dir_read->d_name, exclusions, number_of_exclusion))
            {
                char new_path[1024];
                sprintf(new_path, "%s/%s", root_path, dir_read->d_name);
                collect_uml_objects(new_path, uml_objects, counter, exclusions, number_of_exclusion, list_content);
            }
        }
        else if (is_file(dir_read))
        {
            if (is_not_excluded(dir_read->d_name, exclusions, number_of_exclusion))
            {
                insert_file(dir_read, uml_objects, counter, root_path, list_content);
            }
        }
    }

    closedir(dir);
}
