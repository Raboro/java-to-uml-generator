#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>

#define SEEK_START 0
#define READING_MODE_SINGLE_BYTE 1
#define FILENAME_MAX (260)

int count_files(char *root_path);

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
    return strcmp(d_name, ".") == 0 || strcmp(d_name, "..") == 0;
}

int count_files_(DIR *dir, char *path, int counter)
{
    struct dirent *dir_read;
    while (NULL != (dir_read = readdir(dir)))
    {
        if (is_dir(dir_read))
        {
            if (!is_default_exclusion(dir_read->d_name))
            {
                char new_path[1024];
                sprintf(new_path, "%s/%s", path, dir_read->d_name);
                counter += count_files(new_path);
            }
        }
        else if (is_file(dir_read))
        {
            counter++;
        }
    }
    return counter;
}

int count_files(char *root_path)
{
    DIR *dir = opendir(root_path);

    if (!dir)
    {
        printf("Directory opening error");
        return 0;
    }

    int counter = count_files_(dir, root_path, 0);
    closedir(dir);
    return counter;
}

typedef struct uml_obj
{
    char *path;
    char *name;
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

void insert_file(struct dirent *dirent, uml_obj_t *uml_objects, int *counter, char *path)
{
    char file_name[1024];
    sprintf(file_name, "%s/%s", path, dirent->d_name);
    FILE *file = get_file(file_name);

    size_t file_size = determine_size_of_file(file);
    char *buffer = (char *)malloc(file_size + 1);
    parse_file_into_buffer(file, file_size, buffer);

    buffer[file_size] = '\0';
    printf("%s\n", dirent->d_name);
    printf("%s\n", buffer);

    uml_objects[*counter].name = strdup(dirent->d_name);
    uml_objects[*counter].path = strdup(path);
    if (NULL != uml_objects[*counter].name)
    {
        (*counter)++;
    }
}

void collect_uml_objects(char *root_path, uml_obj_t *uml_objects, int *counter)
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
            if (!is_default_exclusion(dir_read->d_name))
            {
                char new_path[1024];
                sprintf(new_path, "%s/%s", root_path, dir_read->d_name);
                collect_uml_objects(new_path, uml_objects, counter);
            }
        }
        else if (is_file(dir_read))
        {
            insert_file(dir_read, uml_objects, counter, root_path);
        }
    }

    closedir(dir);
}