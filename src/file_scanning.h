#include <dirent.h>

#ifndef FILE_SCANNING_H
#define FILE_SCANNING_H

#define FILENAME_MAX (260)

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
 * @param exclusions char[FILENAME_MAX]*; exclusions by the user
 * @param number_of_exclusion int
 * @return int; number of all files, which are relevant for the conversion into UML
 */
int count_files(char *root_path, char *exclusions[FILENAME_MAX], int number_of_exclusion);

/**
 * @brief counts all relevant files for the UML conversions
 * @param dir DIR*; current directory
 * @param path char*; path of the current subpath to collect all files and count them in it
 * @param counter int; current counter of files
 * @param exclusions char[FILENAME_MAX]*; exclusions by the user
 * @param number_of_exclusion int
 * @return int; number of all files, which are relevant for the conversion into UML
 */
int count_files_(DIR *dir, char *path, int counter, char *exclusions[FILENAME_MAX], int number_of_exclusion);

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
 * @brief checks if the current filename should be excluded per default
 *
 * @param d_name char[FILENAME_MAX]; filename
 * @return int; if 1 then should be excluded, else 0
 */
int is_default_exclusion(char d_name[FILENAME_MAX]);

/**
 * @brief checks if the current filename is excluded per default or by the user option input
 *
 * @param d_name char[FILENAME_MAX]; filename
 * @param exclusions char[FILENAME_MAX]*; exclusions by the user
 * @param number_of_exclusion int
 * @return int
 */
int is_not_excluded(char d_name[FILENAME_MAX], char *exclusions[FILENAME_MAX], int number_of_exclusion);

/**
 * @brief collects all information of all UML objects
 * @param root_path char*; root path of the whole analysis to collect UML objects
 * @param uml_objects uml_obj_t*; array of UML objects to be collected in this method
 * @param counter int*; current selected file
 * @param exclusions char[FILENAME_MAX]*; exclusions by the user
 * @param number_of_exclusion int
 */
void collect_uml_objects(char *root_path, uml_obj_t *uml_objects, int *counter, char *exclusions[FILENAME_MAX], int number_of_exclusion);

/**
 * @brief parse dirent information into UML object at counter
 * @param dirent dirent*; information object of the current file
 * @param uml_objects uml_obj_t*; array of UML objects; at position counter will be data inserted in this method
 * @param counter int*; current selected file
 */
void insert_file(struct dirent *dirent, uml_obj_t *uml_objects, int *counter);

#endif