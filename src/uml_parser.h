#ifndef UML_PARSER_H
#define UML_PARSER_H

#include "file_scanning.h"

/**
 * @brief parse uml objects into an md file to a uml structure
 *
 * @param uml_objects uml_obj_t*; uml objects to be parsed
 */
void parse_to_file(uml_obj_t *uml_objects);

#endif