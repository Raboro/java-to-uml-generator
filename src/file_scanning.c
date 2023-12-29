#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

int count_files(char *root_path);

int is_dir(struct dirent *dirent)
{
    return dirent->d_type == DT_DIR;
}

int is_file(struct dirent *dirent)
{
    return dirent->d_type == DT_REG;
}

int count_files_(DIR *dir, char *path, int counter)
{
    struct dirent *dir_read;
    while (NULL != (dir_read = readdir(dir)))
    {
        if (is_dir(dir_read))
        {
            if (strcmp(dir_read->d_name, ".") != 0 && strcmp(dir_read->d_name, "..") != 0)
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