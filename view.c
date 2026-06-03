#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include "header.h"

void view(FILE *fp)
{
    char tag[5];          // To store frame ID (e.g., TIT2, TPE1)
    int size;             // Size of frame data
    char info[100];       // To store tag content
    int count = 0;        // To track number of required tags printed
    unsigned char s[4];   // To store size bytes

    printf("---------------------------------------------------------------\n");
    printf("                   MP3 TAG INFORMATIONS\n");
    printf("---------------------------------------------------------------\n");

    // Skip ID3 header (first 10 bytes)
    fseek(fp, 10, SEEK_SET);

    /* ===================== READ FRAMES ===================== */
    while(count < 6)
    {
        // Read tag (4 bytes)
        fread(tag, 1, 4, fp);
        tag[4] = '\0';

        // Read size (4 bytes)
        fread(s, 1, 4, fp);

        // Convert size bytes to integer
        size = (s[0] << 24) | (s[1] << 16) | (s[2] << 8) | s[3];
        
        // Skip 2 bytes of flags
        fseek(fp, 2, SEEK_CUR);

        // Prevent buffer overflow
        if(size > 99)
            size = 99;

        // Skip text encoding byte
        fseek(fp, 1, SEEK_CUR);

        // Read actual tag content
        fread(info, size - 1, 1, fp);
        info[size - 1] = '\0';

        /* ===================== TAG MATCHING ===================== */

        if(strcmp(tag, "TIT2") == 0)
        {
            printf("%-10s= %s\n", "Title", info);
            count++;
        }
        else if(strcmp(tag, "TYER") == 0)
        {
            printf("%-10s= %s\n", "Year", info);
            count++;
        }
        else if(strcmp(tag, "TPE1") == 0)
        {
            printf("%-10s= %s\n", "Artist", info);
            count++;
        }
        else if(strcmp(tag, "TALB") == 0)
        {
            printf("%-10s= %s\n", "Album", info);
            count++;
        }
        else if(strcmp(tag, "TCON") == 0)
        {
            printf("%-10s= %s\n", "Genre", info);
            count++;
        }
        else if(strcmp(tag, "COMM") == 0)
        {
            printf("%-10s= %s\n", "Comment", info);
            count++;
        }
    }
}