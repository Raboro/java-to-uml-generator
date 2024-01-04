#ifndef UML_PARSER_H
#define UML_PARSER_H

#include "file_scanning.h"

/**
 * @brief parse uml objects into an md file to a uml structure
 *
 * @param uml_objects uml_obj_t*; uml objects to be parsed
 * @param uml_objects_len int; number of uml objects
 */
void parse_to_file(uml_obj_t *uml_objects, int uml_objects_len);

/**
 * @brief Only get the name of a file without .filetype
 *
 * @param name char*
 * @return char*
 */
char *parse_name(char *name);

/**
 * @brief checks if obj_name and sub_obj_name are equal to not allow duplicated obj
 * Also sub_obj_name got a space at the end, to eliminate this, the comparison is based on len(sub_obj_name) - 1
 *
 * @param obj_name char*;
 * @param sub_obj_name char*;
 * @return int; 1 if equal, else 0
 */
int names_equal(char *obj_name, char *sub_obj_name);

#endif