/* 
 * File:   HW1.c
 * Author: Tevin Taylor and Benjamin Valentino
 *
 * Created on February 8, 2017, 5:54 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char** argv) {
    
    //Variable declarations
    char *user_dir = malloc(sizeof(char)*100);
    char *user_filename = malloc(sizeof(char)*100);    
    struct node {
        char charID;
        int fileCounter;
        char files[100][50]; //[number of files][amount of allocated memory]
        struct node *next;
    } node;
    
    //Making the 26 node linked list
    struct node *head = malloc(sizeof(node));
    struct node *current = head;
    head -> charID = '0';
    head -> next = NULL;
    for (int i = 1; i < 26; i++) {
        current -> next = malloc(sizeof(node));
        current = current -> next;
        current -> charID = '0';
        current -> fileCounter = 0;
    }
    
    //Obtaining user provided directory
    printf("Enter a folder name: ");
    scanf("%s", user_dir);
    
    //Read all file names in provided directory and sort into linked list
    DIR *dir;
    struct dirent *dirStruct;
    dir = opendir(user_dir);
    while ((dirStruct = readdir(dir)) != NULL) {
        struct node *current = head;
        int a;
        a = 1;
        while (a) {            
            if (current -> charID != '0') {
                if (tolower(current -> charID) == tolower(dirStruct -> d_name[0])) { 
                    //Place file in current node string array
                    strcpy(current -> files[current -> fileCounter], dirStruct -> d_name);
                    current -> fileCounter++;
                    a = 0;
                } 
                current = current -> next;
            } else {
                //Define the current node charID as the first character of the file name
                current -> charID = dirStruct -> d_name[0];
                
                //Place file in current node string array
                strcpy(current -> files[current -> fileCounter], dirStruct -> d_name);
                current -> fileCounter++;
                a = 0;
            }
        }
    }
        closedir(dir); 
        
    //Ask user for beginnings of file names until an empty string is entered and 
    //print matching file names to the screen    
    char *prefix = malloc(sizeof(char)*10);
    fgets(prefix, sizeof(prefix), stdin);
    prefix[strcspn(prefix, "\n")] = '\0';
    do {
        printf("\nEnter the beginning of a filename: ");
        //fflush(stdin);
        fgets(prefix, sizeof(prefix), stdin);
        prefix[strcspn(prefix, "\n")] = '\0';
        
        struct node *current1 = head;
        while (current1 -> next != NULL) {
            if (tolower(current1 -> charID) == tolower(prefix[0])) {
                for (int j = 0; j < 50; j++) {
                    int b;
                    b = strncmp(prefix, current1 -> files[j], strlen(prefix));
                    if(b == 0) {
                        printf("\n%s",current1 -> files[j]);
                    }
                }
                break;
            } else {
            current1 = current1 -> next;
            }
        }
        
    } while (strncmp(prefix, "", sizeof(prefix)));
    
    return (EXIT_SUCCESS);
}
