#include <dirent.h>

#ifndef FILE_SCANNING_H
#define FILE_SCANNING_H

/**
 * @brief counts all relevant files for the UML conversions
 * @param root_path char*; root path of the whole analysis to count all relevant files
 * @return int; number of all files, which are relevant for the conversion into UML
 */
int count_files(char *root_path);

/**
 * @brief counts all relevant files for the UML conversions
 * @param dir DIR*; current directory
 * @param path char*; path of the current subpath to collect all files and count them in it
 * @param counter int; current counter of files
 * @return int; number of all files, which are relevant for the conversion into UML
 */
int count_files_(DIR *dir, char *path, int counter);

/**
 * @brief checks if the current object is a directory
 * @param dirent
 * @return if directory 1, else 0
 */
int is_dir(struct dirent dirent);

/**
 * @brief checks if the current object is a file
 * @param dirent
 * @return if file 1, else 0
 */
int is_file(struct dirent dirent);

#endif