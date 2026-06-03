#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>   // Required for FILE type

/* 
 * Function: view
 * ----------------
 * Displays metadata (ID3 tags) from the MP3 file
 * fp : pointer to opened file
 */
void view(FILE *fp);

/* 
 * Function: edit
 * ----------------
 * Edits a specific ID3 tag in the MP3 file
 * fp        : pointer to opened file
 * tag_edit  : tag to modify (e.g., TIT2, TPE1)
 * info      : new data to write into the tag
 * file_name : original file name (used for replacement)
 */
void edit(FILE *fp, char *tag_edit, char *info, char *file_name);

#endif