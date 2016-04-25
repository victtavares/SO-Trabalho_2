#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//TODO: Add validations and remove all prints.
//TODO: Delete origin files.
//Keyboard shortcut is command shift < to add arguments.

void copyFile(const char* originFileName, const char* prefix) {
    
    FILE *fileOrigin, *fileDestination;
    char contentChar;

    printf("on file: %s\n", originFileName);

    fileOrigin = fopen(originFileName, "r");
    if (!fileOrigin) {
        printf("Erro ao abrir o arquivo de origem: %s\n", originFileName);
        exit(1);
    }
    
    char* destinationFileName = malloc(strlen(prefix) + 1);
    strcpy(destinationFileName, prefix);
    strcat(destinationFileName, originFileName);
    fileDestination = fopen(destinationFileName, "w");
    
    if (!fileDestination) {
        printf("Erro ao escrever no arquivo de destino: %s\n", destinationFileName);
        exit(1);
    }
    
    while ((contentChar = fgetc(fileOrigin)) != EOF) {
        fputc(contentChar, fileDestination);
    }
    
    fclose(fileDestination);
    fclose(fileOrigin);
    
}

int main(int argc, const char * argv[]) {
    //number of files + 1
    int fileCount = argc -1;

    char* prefix = malloc(strlen(argv[fileCount]) + 1);
    strcpy(prefix, argv[fileCount]);

    for (int i = 1; i < fileCount; ++i) {
        pid_t pid = fork();
        if (pid == 0) {
            char* originFileName = malloc(strlen(argv[i]) + 1);
            strcpy(originFileName, argv[i]);
            copyFile(originFileName, prefix);
            free(originFileName);
            exit(0);
        } else {
            printf("Criando processo com PID %ld\n", (long) pid);
        }  
    }

    //waiting to exit the parent, to not create zombie projects.
    int status;
    int waitPid;
    int countFiles = fileCount -1;
    while (countFiles > 0) {
        waitPid = wait(&status);
        //printf("Filho finalizado com pid %ld\n", (long)waitPid);
        --countFiles; 
    }   

    free(prefix);
    
    return 0;
}