#include "A2_final.h"




void generate_composite(pidnode *head,bool search_there, int search) { // generates composite table with the related fields 
int count=0;
   for ( pidnode*ptr=head; ptr!=NULL;ptr=ptr->next){
    if ( search_there){ 
        if ( ptr->pid == search){
        printf("%-8d%-8d%-8d%-24s%ld\n", count,ptr->pid,ptr->fd,ptr->file_name, ptr->inodes);
        }
    }
     else {
     printf("%-8d%-8d%-8d%-24s%ld\n ",count,ptr->pid,ptr->fd,ptr->file_name, ptr->inodes);
     }
     count++;
    }

   return;
   }

   void generate_per_process(pidnode *head,bool search_there , int search) {
   for (pidnode*ptr=head;ptr!=NULL;ptr=ptr->next){
     if (search_there){
      if(ptr->pid==search){
        printf("%-8d%-8d\n",ptr->pid,ptr->fd);
      }
     }
     else {
         printf("%-8d%-8d\n",ptr->pid,ptr->fd);
     }
    }
    
  return;

}
void generate_vnodes(pidnode *head,bool search_there, int search) {

   for ( pidnode*ptr=head; ptr!=NULL; ptr=ptr->next){
    if (search_there){
        if(ptr->pid==search){
        printf("%-8d %ld\n",ptr->pid,ptr->inodes);
        }
    }
    else {
      printf("%-8d%ld\n ",ptr->pid,ptr->inodes);
      
    }
    }
   
  return;

}

void generate_systemwide(pidnode *head,bool search_there,int search) {
   //pidnode *ptr=NULL; // traversal pointer 
   //ptr=head; // traversal pointer points to head
   for ( pidnode*ptr=head; ptr!=NULL; ptr=ptr->next){
    if ( search_there){
        if(ptr->pid==search){
            printf("%-8d%-8d%-24s\n ",ptr->pid,ptr->fd,ptr->file_name);
        }
    }
    else{
     printf("%-8d%-8d%-24s\n ",ptr->pid,ptr->fd,ptr->file_name);
    }
   }
   

  
    
  return;

}







void generate_threshold(pidnode*head,int threshold,bool search_there,int search){  
    char get_off_proc[1000][100];
    
    int final_count=0; 
    int ind=0;   
   for(pidnode*ptr=head; ptr!=NULL;ptr=ptr->next){
        int count1=1;
         while (ptr->next != NULL && ptr->pid == ptr->next->pid) {            
            count1++; 
            final_count=count1;          
            ptr = ptr->next;        
            }        
            if(final_count>threshold){
                sprintf(get_off_proc[ind],"%d(%d)\t",ptr->pid,final_count); 
                ind++;                  
            }        
    }
   printf("offending processes :");
    for ( int i=0;i<ind;i++){
        printf("%s",get_off_proc[i]);
    }
    printf("\n");
}

void generate_text_file(pidnode*head,int search,bool search_there){

char filepath[1024];
sprintf(filepath, "compositeTable.txt");
FILE *file = fopen(filepath, "w");
if (file == NULL) {
    printf("cannot open file\n");
    return; 
}
fprintf(file, "%-8s%-8s%-24s%s\n","PID", "FD", "Filename", "Inode");
fprintf(file,"=================================================\n");
for (pidnode*ptr=head; ptr!=NULL;ptr=ptr->next){
if (search_there) {
        if (ptr->pid == search) {
            
            fprintf(file, "%d    %d    %s   %ld\n", ptr->pid, ptr->fd, ptr->file_name, ptr->inodes);
        }
    } else {
        
        fprintf(file, "%d   %d   %s    %ld\n", ptr->pid, ptr->fd, ptr->file_name, ptr->inodes);
    }
}
fclose(file);

}


void generate_bin(pidnode*head,int search,bool search_there){
char filepath[1000];
sprintf(filepath, "compositeTable.bin");
FILE *file = fopen(filepath, "wb");
if (file == NULL) {
    printf("cannot open file");
    return;
}
// char header[70];
// sprintf(header, "%-8s%-8s%-24s%s\n", "PID", "FD", "Filename", "Inode");
// fwrite(header, sizeof(char), strlen(header), file);

for ( pidnode*ptr=head; ptr!=NULL; ptr=ptr->next){
if (search_there) {
    if (ptr->pid == search) {
            fwrite(ptr, sizeof(pidnode), 1, file);
    }
} else {
        fwrite(ptr, sizeof(pidnode), 1, file);
    }

}
fclose(file);
}








int main( int argc , char **argv)
{
    uid_t current_uid=getuid();
    pidnode*head=generate_specifics(current_uid); // gets the head of the linked lists with the pids
    bool per_process = false;
    bool system_wide = false;
    bool vnodes = false;
    bool composite = false;
    bool threshold_there =false;
    bool search_there=false;
    bool text=false;
    bool bin=false;
    bool only_search=false;
    int threshold=-1;
    int search=0;
    //int count=0;
    if  (argc>1){
        for(int i=0; i<argc;i++){
        if (( strcmp(argv[i],"--per-process"))==0||( strcmp(argv[i],"--per"))==0){
            per_process=true;
        }
        else if (( strcmp(argv[i],"--systemWide"))==0||( strcmp(argv[i],"--sw"))==0){
            system_wide=true;
        }
        else if (atoi(argv[i])!=0) // for positional arguments
			{
                only_search=true;
                search = atoi(argv[i]);
                search_there=true;
				
                //printf("%d search",search);
			}
        else if (( strcmp(argv[i],"--vnodes"))==0||( strcmp(argv[i],"--vn"))==0){
            vnodes=true;
        }
        else if (( strcmp(argv[i],"--composite"))==0||( strcmp(argv[i],"--c"))==0){
            composite=true;
        }
        else if  ( strncmp(argv[i],"--threshold=X",11)==0){
                threshold_there=true;
				char get_cla [30];
				strncpy(get_cla,argv[i],14);
				char *words=strtok(get_cla,"=");
				int c=0;
				
				while ( words!=NULL)
				{c++;
					if ( c==2){
					threshold=atoi(words);
					}
					
					words=strtok(NULL,"=");
				}
			}
        else if (( strcmp(argv[i],"--output_TXT"))==0||( strcmp(argv[i],"--ot"))==0){
            text=true;
            
        }
        else if (( strcmp(argv[i],"--output_binary"))==0||( strcmp(argv[i],"--ob"))==0){
            bin=true;
        }
        
        }
    }
    if (argc==1||composite){
        if ( !only_search){
        printf("%-8s%-8s%-8s%-24s%s\n","ROW", "PID", "FD", "Filename", "Inode");
        printf(" ==============================================================\n"); 
        generate_composite(head,search_there,search);
        }
        else 
        {
            if(only_search){
                 printf("%-8s%-8s%-8s%-24s%s\n","ROW", "PID", "FD", "Filename", "Inode");
                printf(" ==============================================================\n"); 
                generate_composite(head,search_there,search);

            }
        }
        }
    if (system_wide){
      printf("%-8s%-8s%-24s\n", "PID", "FD", "Filename");
      printf("=================================================\n");
      generate_systemwide(head,search_there,search);
    }
    if (per_process) {
        printf("%-8s%-8s\n", "PID", "FD");
        printf(" ================================================\n"); 
        generate_per_process(head,search_there,search);

    }
    if (vnodes){
        printf("%-8s%s\n", "PID", "Inode");
        printf(" ===============================================\n");
        generate_vnodes(head,search_there,search);

    }
    if (threshold_there){
       
        if( composite!=true){
        printf("%-8s%-8s%-8s%-24s%s\n","ROW", "PID", "FD", "Filename", "Inode");
        printf(" ==============================================================\n"); 
        generate_composite(head,search_there,search);
        }
        generate_threshold(head,threshold,search_there,search);
    }
    if (text){
        printf("the text file output with the name compositeTable.txt has been produced\n");
        generate_text_file(head,search,search_there);
    }
    if(bin){
        printf("the text file output with the name compositeTable.bin has been produced\n");
        generate_bin(head,search,search_there);
    }
    if (!text && !bin && !composite &&!vnodes &&!per_process && !system_wide && only_search)
    {
      printf("%-8s%-8s%-8s%-24s%s\n","ROW", "PID", "FD", "Filename", "Inode");
      printf(" ==============================================================\n"); 
      generate_composite(head,search_there,search);
    }
    
    free_linked_list(head);

}

