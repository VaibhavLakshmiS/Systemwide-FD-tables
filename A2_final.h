#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<sys/types.h> 
#include<pwd.h>
#include<errno.h>
#include<dirent.h>
#include<string.h>
#include<unistd.h>
#include<stdbool.h>
#ifndef A2_final_header
#define A2_final_header

typedef struct PID_Node{
    int pid;
    int fd;
    char file_name[1024];
    ino_t inodes;
    struct PID_Node*next;
}pidnode;
/*Creates the linked list that stores the content for FDTABLE that is pid,fd,file_name and the inodes*/
pidnode*create_linked_list (pidnode*head, int pid, int fd,char*file_name,long int inodes);

/*Prints the composite table*/
void generate_composite(pidnode*head,bool search_there, int search);

/*Prints the per process table*/
void generate_per_process(pidnode*head,bool search_there , int search);

/*Prints the vnodes table*/
void generate_vnodes(pidnode*head,bool search_there, int search);

/*Prints the systemwide table */
void generate_systemwide(pidnode *head,bool search_there,int search);

/*Prints the offending process that have more fds opened compared to the threshold given */
void generate_threshold(pidnode*head,int threshold,bool search_there,int search);

/*Generates the text file with the composite table's content*/
void generate_text_file(pidnode*head,int search,bool search_there);

/*Generates the binary file with the composite table's content*/
void generate_bin(pidnode*head,int search,bool search_there);

/*The main function that collects the data for all the current processes that are running using get uid and the it opens the proc/status and the proc fd and then returns the 
head of the linked list with the updates info*/
pidnode*generate_specifics (uid_t uid );

/*frees the linked list to avoid memory leak*/
pidnode*free_linked_list(pidnode*head);

#endif