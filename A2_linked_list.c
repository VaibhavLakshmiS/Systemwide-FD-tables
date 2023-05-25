
#include "A2_final.h"

pidnode* create_linked_list (pidnode* head, int pid, int fd,char*file_name,long int inodes){ // creates the linked list 
    pidnode*new_node=(pidnode*)calloc(1,sizeof(pidnode));
    new_node->pid = pid;
    new_node->fd=fd;
    strcpy(new_node->file_name,file_name);
    new_node->inodes=inodes;
    new_node->next = NULL;
    pidnode* node = new_node;

    if (head == NULL){
    return node;
    }
    pidnode*t=NULL;
    t=head;
    while ( t->next !=NULL){
        t=t->next;
    }
    t->next=node;
    return head;
}
pidnode *free_linked_list(pidnode*head)
{
	pidnode*ptr=NULL;//p
    pidnode*temp=NULL;//q
    ptr=head;
    while(ptr!=NULL)
    {
	   temp=ptr->next;
	   free(ptr);
	   ptr=temp;
    }
  return NULL;
}


pidnode* generate_specifics (uid_t uid ){
pidnode*head=NULL;
ino_t ino=0;
char proc_dir[1024];
DIR* dir = opendir("/proc"); //  "/proc" directory
    struct dirent* entry; // gets the entries in the proc directory
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) { // Check if the entry is a directory
            char path[280];
            snprintf(path, sizeof(path), "/proc/%s/status", entry->d_name);
            FILE* file = fopen(path, "r"); // Open the "/proc/PID/status" file
            if (file) {
                char line[256];
                while (fgets(line, sizeof(line), file)) {
                    if (strncmp(line, "Uid:", 4) == 0) {
                        // passes the UID field
                        uid_t proc_uid = atoi(line + 4); // access the uid
                        if (proc_uid == uid) { // checks if the users uid match
                         int pid = atoi(entry->d_name);
                            snprintf(proc_dir, 1024,"/proc/%d/fd/",pid); // copies the path to proc_directory
                            // Open the proc directory
                            DIR *dir = opendir(proc_dir);
                            if (dir == NULL) {
                                //printf("Error: could not open proc directory for PID %d\n", pid);
                               
                                continue;
                            }
   

                            struct dirent *readfd;
                            
                            
                            while ((readfd = readdir(dir)) != NULL) {
                                
                                if (strcmp(readfd->d_name, ".") == 0 || strcmp(readfd->d_name, "..") == 0) {
                                    continue;
                                }
                                
                                
                                char fd_path[1280];
                                snprintf(fd_path, 1280, "/proc/%d/fd/%s",pid, readfd->d_name);
                                struct stat get_ino; // to get inode 
                                if (stat(fd_path,&get_ino) == -1) {
                                                continue;
                                }
                                else{
                                ino = get_ino.st_ino;
                                }

                                char link[1000];
                                ssize_t link_size = readlink(fd_path,link, 1000);// to get filename
                                link[link_size] = '\0';
                                

                                head=create_linked_list(head,pid,atoi(readfd->d_name),link,ino);
                                
                            }
                                                
                        }
                        break;
                    }
                
            }
            fclose(file);
        }


    }
}
  return head;
}
