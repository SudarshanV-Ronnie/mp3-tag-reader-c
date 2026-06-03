/* Name: Sudarshan V
   Description: Mp3 Tag Reader

========================= MP3 TAG EDITOR =========================

------------------------- 1. VIEW (-v) ---------------------------
INPUT:
------
Enter the operation: -v
Enter the file name: song.mp3

OUTPUT:
-------
---------------------------------------------------------------
 MP3 TAG INFORMATIONS
---------------------------------------------------------------
Title     = New song
Artist    = Yo Yo Honey Singh - [SongsPk.CC]
Album     = Yaariyan
Year      = 2020
Genre     = Bollywood Music - [SongsPk.CC]
Comment   = english


------------------------- 2. EDIT (-e) ---------------------------
INPUT:
------
Enter the operation: -e
Enter the tag: -t
Enter the new data: New Song Name
Enter the file name: song.mp3

OUTPUT:
-------
File editted successfully

(After editing, if you use -v again:)

---------------------------------------------------------------
MP3 TAG INFORMATIONS
---------------------------------------------------------------
Title     = New Song Name
Artist    = Yo Yo Honey Singh - [SongsPk.CC]
Album     = Yaariyan
Year      = 2020
Genre     = Bollywood Music - [SongsPk.CC]
Comment   = english


------------------------- TAG OPTIONS ---------------------------
-t --> title   (TIT2)
-y --> year    (TYER)
-a --> artist  (TPE1)
-A --> album   (TALB)
-g --> genre   (TCON)
-c --> comment (COMM)


------------------------- 3. HELP (-h) ---------------------------
INPUT:
------
Enter the operation: -h

OUTPUT:
-------
-t --> title
-y --> year
-a --> artist
-A --> album
-g --> genre
-c --> comment

=================================================================
*/
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include "header.h"

int main()
{
    // Display available operations
    printf("-v --> view\n");
    printf("-e --> edit\n");
    printf("-h --> help\n");

    char file_name[100], operation[3];

    // Read operation from user
    printf("Enter the operation:");
    scanf(" %[^\n]", operation);

    /* ===================== VIEW OPERATION ===================== */
    if(strcmp(operation, "-v") == 0)
    {
        printf("Enter the file name:");
        scanf(" %[^\n]", file_name);
        printf("\n");

        FILE *fp;

        // Open file in read mode
        if((fp = fopen(file_name, "r")) == NULL)
        {
            fprintf(stderr, "File not found\n");
            return 0;
        }

        // Check if file is MP3 (ID3 tag)
        char buffer[4];
        fread(buffer, 3, 1, fp);
        buffer[3] = '\0';

        if(strcmp(buffer, "ID3") != 0)
        {
            fprintf(stderr, "File is not mp3 Format\n");
            return 0;
        }

        // Call view function
        view(fp);

        fclose(fp);
    }

    /* ===================== EDIT OPERATION ===================== */
    else if(strcmp(operation, "-e") == 0)
    {
        char tag[5], info[100];

        // Get tag option
        printf("Enter the tag:");
        scanf(" %[^\n]", tag);

        // Get new data
        printf("Enter the new data:");
        scanf(" %[^\n]", info);

        // Get file name
        printf("Enter the file name:");
        scanf(" %[^\n]", file_name);

        printf("\n");

        FILE *fp;

        // Open file in read mode
        if((fp = fopen(file_name, "r")) == NULL)
        {
            fprintf(stderr, "File not found\n");
            return 0;
        }

        // Validate MP3 file using ID3 header
        char buffer[4];
        fread(buffer, 3, 1, fp);
        buffer[3] = '\0';

        if(strcmp(buffer, "ID3") != 0)
        {
            fprintf(stderr, "File is not mp3 Format\n");
            return 0;
        }

        // Convert user-friendly tag to ID3 frame
        if(strcmp(tag, "-t") == 0)
            strcpy(tag, "TIT2");   // Title
        else if(strcmp(tag, "-y") == 0)
            strcpy(tag, "TYER");   // Year
        else if(strcmp(tag, "-a") == 0)
            strcpy(tag, "TPE1");   // Artist
        else if(strcmp(tag, "-A") == 0)
            strcpy(tag, "TALB");   // Album
        else if(strcmp(tag, "-g") == 0)
            strcpy(tag, "TCON");   // Genre
        else if(strcmp(tag, "-c") == 0)
            strcpy(tag, "COMM");   // Comment

        // Call edit function
        edit(fp, tag, info, file_name);

        printf("File editted successfully\n");
    }

    /* ===================== HELP OPERATION ===================== */
    else if(strcmp(operation, "-h") == 0)
    {
        printf("-t --> title\n");
        printf("-y --> year\n");
        printf("-a --> artist\n");
        printf("-A --> album\n");
        printf("-g --> genre\n");
        printf("-c --> comment\n");
    }
}