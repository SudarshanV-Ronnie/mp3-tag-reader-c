#include<stdio.h>
#include<string.h>
#include<unistd.h> 
#include "header.h"

void edit(FILE *fp, char *tag_edit, char *info_edit, char *file_name)
{
    // Move file pointer to beginning
    fseek(fp, 0, SEEK_SET);

    FILE *fp2;

    // Create temporary file to store updated data
    if((fp2 = fopen("temp.mp3", "wb")) == NULL)
    {
        fprintf(stderr, "File not created\n");
        return;
    }

    char buffer[10];

    // New size of tag data (including null character)
    unsigned int new_size = (strlen(info_edit) + 1);

    // Copy first 10 bytes (ID3 header)
    fread(buffer, 1, 10, fp);
    fwrite(buffer, 1, 10, fp2);

    /* ===================== FRAME PROCESSING ===================== */
    while(1)
    {
        char tag[5];              // Frame ID (e.g., TIT2, TPE1)
        unsigned char s[4];      // Original size bytes
        unsigned char s_temp[4]; // New size bytes
        int size;                // Frame size
        char flag[3];            // Frame flags
        char info[100];          // Frame data

        // Read frame tag (4 bytes)
        fread(tag, 1, 4, fp);
        tag[4] = '\0';

        // Read size (4 bytes)
        fread(s, 1, 4, fp);

        // Convert size from bytes to integer
        size = (s[0] << 24) | (s[1] << 16) | (s[2] << 8) | s[3];
        
        // Read flags (3 bytes)
        fread(flag, 1, 3, fp);

        // Read frame content
        fread(info, 1, size - 1, fp);

        /* ===== Check if this is the tag to edit ===== */
        if(strcmp(tag, tag_edit) == 0)
        {
            // Write tag
            fwrite(tag, 1, 4, fp2);

            // Convert new size into 4 bytes
            s_temp[0] = (new_size >> 24) & 0xFF;
            s_temp[1] = (new_size >> 16) & 0xFF;
            s_temp[2] = (new_size >> 8)  & 0xFF;
            s_temp[3] =  new_size        & 0xFF;

            // Write updated size
            fwrite(s_temp, 1, 4, fp2);

            // Write flags
            fwrite(flag, 1, 3, fp2);

            // Write updated info
            fwrite(info_edit, 1, new_size - 1, fp2);

            // Stop after editing required tag
            break;
        }
        else
        {
            // Copy unchanged frame to temp file
            fwrite(tag, 1, 4, fp2);
            fwrite(s, 1, 4, fp2);
            fwrite(flag, 1, 3, fp2);
            fwrite(info, 1, size - 1, fp2);
        }
    }

    /* ===================== COPY REMAINING DATA ===================== */
    char buff[1];

    while((fread(buff, 1, 1, fp)) > 0)
    {
        fwrite(buff, 1, 1, fp2);
    }

    /* ===================== REPLACE ORIGINAL FILE ===================== */
    remove(file_name);              // Delete original file
    rename("temp.mp3", file_name); // Rename temp file to original
}