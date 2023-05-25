READ ME 
Assignment 2: Recreating the System-Wide FD Tables
-----------------------------------------------------------  
Student name:Vaibhav Lakshmi Santhanam 
Student number: 1007642400
-----------------------------------------------------------
=================
Note to the user:
=================
this assignment has been split into three files
-------------------------------------------------
A2_final.h : A header file that contains the declaration of the struct for the linked list and then header declaration of all the functions used in the assignment 
A2_linkedlist.c : A c file that contains functions of the type pidnode* , it contains the functions related to creating a linked list ,updating its head and freeing the linked list 
A2_final.c :A c file that contains functions handling the output and creation of the text files and also contains the main().
A makefile has been created for this assignment. 

"make: Nothing to be done for 'all'." In case this message is shown pls use make clean command and then call make again to recompile the flags.

the executable for this assignment has been named showFDtables. pls call ./showFDtables to run the program

for safety sake a makefile.txt has been given in the zip file 

 
--------------------------------------------------------------------------------------------------------------------

Note: for  flags 
      ---------
+When running the program with positional arguments.Pls make sure that the PID passed in is currently running . If not it doesnt display anyoutput for the PID

+ when the program is run with one pid and the threshold flag is called the table is printed for that pid with the offending processes and then prints the pid composite table again 

+ threshold for a particular pid  prints the composite table once for that pid and then prints the offending processes and then prints the composite table again for the pid.

+ the printf statement produced for the binary file tells text file ( meant to be binary file) with the name compositeTable.bin has been produced . It is a binary file that has been produced like wanted. 

+ for printing it prints in specific order ( composite , systemwide , perprocess and vnodes) table because of the if statements for the printing functions when called with various combination of flags 
   ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Flags and possible combination to run the program
###########################################################################################################################

(Single flag calls)
-------------------
a)--per-process or --per : displays the perprocess table 
b)--systemWide or --sw : displays the systemwide table 
c)--vnodes or --vn : displays the vnodes table 
d)--composite or --c : displays the composite table 
e)--threshold=X (X) is the count of fd numbers opened : Displays all the PIDS that have more than the given threshold + the composite table


(BONUS)
f)--output_TXT or --ot : produces the compositeTable.txt with the composite table content written in text 
g)--output_binary or --ob : produces the compositeTable.bin with the composite table content written in binary


h) Positional arguments : Takes in A currently running pid number and then displays the output of the composite table for that pid by default 
                          if called with other flags will print the output for that pid alone in the specified format.z



(Different Combination of flag calls)
-------------------------------------
a) --per-process --systemWide --composite ( it prints the composite table and then system wide and then per process) 
b) --systemWide --per-process --vnodes --composite ( it prints the systemWide per process vnodes composite)
----------------------------------------------------------------------------------------------------------------



##########################################################################################################################

The various functions within the assignment 
########################################################################################################################

pidnode* create_linked_list (pidnode*head, int pid, int fd,char*file_name,long int inodes)-:Creates the linked list that stores the content for FDTABLE that is pid,fd,file_name and the inodes


void generate_composite(pidnode*head,bool search_there, int search)-: traverses through the linked list and prints the composite table by accessing the data from the fields of pidnode which contains the pid,fd,filename,inodes


void generate_per_process(pidnode*head,bool search_there , int search)-: traverses through the linked list and prints the per process table by accessing the data from the fields of pidnode which contains the pid,fd


void generate_vnodes(pidnode*head,bool search_there, int search)-:traverses through the linked list and prints the vnodes table by accessing the data from the fields of pidnode which contains the pid,inodes


void generate_systemwide(pidnode *head,bool search_there,int search)-:traverses through the linked list and prints the systemwide table by accessing the data from the fields of pidnode which contains the pid,fd,filename



void generate_threshold(pidnode*head,int threshold,bool search_there,int search)-:traverses through the linked list and prints the composite table by accessing the data from the fields of pidnode which contains the pid,fd,filename,inodes


void generate_text_file(pidnode*head,int search,bool search_there) -:Generates the text file with the composite table's content


void generate_bin(pidnode*head,int search,bool search_there)-:Generates the binary file with the composite table's content


pidnode* generate_specifics (uid_t uid )-:
The main function that collects the data for all the current processes that are running using get uid and the it opens the proc/pid/status and the proc/pid/fd and then returns the 
head of the linked list with the updated information.

Step by step explaination of what happens in the function 

First the proc/pid/status is read to get the pids that have the same uid as the current user.

Secondly the proc/pid/fd is read to get the information about the fd like the fd number, filename opened. 

Thirdly to get the inode number we use the stat structure and access the inode number

the head of the linked list gets updated in this function 
stores the info and passes the info to the create linked list function which does the initialisation and then add  the info to the linked list and updates the head.

the updated head is then returned by the function.

 

pidnode *free_linked_list(pidnode*head) -: frees the linked list to avoid memory leak . by freeing every node in the linked list called at the end of main



+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
The Analysis for the bonus has been done in the pdf with the name analysis b09.pdf has been attached in the zip file submitted for the assignement.

the main results of the analysis are 
1) Binary file more effective in generating file with time analysis
2) Text file take up less space (size analysis ) 




#######################################################################################################################################################################################

The libraries used 
==================
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
#########################################################################################################################################################################################

The resources used 
------------------
https://www.man7.org/linux/man-pages/man3/readdir.3.html
https://www.man7.org/linux/man-pages/man0/sys_stat.h.0p.html
https://man7.org/linux/man-pages/man0/pwd.h.0p.html
https://man7.org/linux/man-pages/man5/proc.5.htmls
https://www.man7.org/linux/man-pages/man2/readlink.2.html
https://www.delftstack.com/howto/c/printf-align-columns-in-c/ for format specifiers for the output
https://overiq.com/c-programming-101/fwrite-function-in-c/ to write in binary format

######################################################################################################################################################################################


