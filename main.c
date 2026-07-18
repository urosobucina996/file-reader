#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>


long check_file_size(FILE *fp){
    fseek(fp, 0, SEEK_END);
    long temp_filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return temp_filesize;
};

int check_buffer_alloc(char *buffer, FILE *fp){
    if(buffer == NULL){
        perror("Buffer alocation failed");
        fclose(fp);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

void read_buffer(char *buffer, long filesize, FILE *fp){
    fseek(fp, 0, SEEK_SET);
    size_t bytesread = fread(buffer, sizeof(char), filesize, fp);
    buffer[bytesread] = '\0';
   
   printf("\033[2J\033[H");
    printf("Current content of file is -> \n%s\n", buffer);
    fflush(stdout);
}

int main() {
   
  FILE *fp = fopen("data.txt", "r");

  if (fp == NULL){
    perror("Error opening file");
    return EXIT_FAILURE;
  }

  long filesize = check_file_size(fp);

  char *buffer = (char *)malloc(filesize + 1);

  if(check_buffer_alloc(buffer, fp) == EXIT_FAILURE){
    return EXIT_FAILURE;
  }; 
  read_buffer(buffer, filesize, fp);

  while(true){
      long new_size = check_file_size(fp);
      if(filesize != new_size){
        char *temp = realloc(buffer, new_size + 1);

        if(temp == NULL){
            perror("realloc");
            free(buffer);
            fclose(fp);
            return EXIT_FAILURE;
        }
        buffer = temp;
        filesize = new_size;
      }
      read_buffer(buffer, filesize, fp);
      usleep(1000000);
   }

  fclose(fp);
  
  return 0;
}
