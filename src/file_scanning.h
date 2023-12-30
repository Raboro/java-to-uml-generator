#include <dirent.h>

#ifndef FILE_SCANNING_H
#define FILE_SCANNING_H

/**
 * @brief type, which holds the information about an UML object, collected out of a file
 * this is needed for the parsing into UML
 */
typedef struct uml_obj
{
    char *path;
    char *name;
} uml_obj_t;

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

/**
 * @brief collects all information of all UML objects
 * @param root_path char*; root path of the whole analysis to collect UML objects
 * @param uml_objects uml_obj_t*; array of UML objects to be collected in this method
 * @param counter int*; current selected file
 */
void collect_uml_objects(char *root_path, uml_obj_t *uml_objects, int *counter);

/**
 * @brief parse dirent information into UML object at counter
 * @param dirent dirent*; information object of the current file
 * @param uml_objects uml_obj_t*; array of UML objects; at position counter will be data inserted in this method
 * @param counter int*; current selected file
 */
void insert_file(struct dirent *dirent, uml_obj_t *uml_objects, int *counter);

#endif