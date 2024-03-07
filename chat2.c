#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_MSG_SIZE 2048

int main() {
    int fd1, fd2; 
    char lettura[MAX_MSG_SIZE];
    char scrittura[MAX_MSG_SIZE];
    
    fd1 = open("myfifo", O_RDONLY);
    fd2 = open("myfifo2", O_WRONLY);
    
    printf("La chat si sta per aprire, scrivi 'HALT' per terminare\n");
    
    do {
        read(fd1, lettura, sizeof(lettura));
        printf("\033[0;35muser1: %s\033[0m\n", lettura); // user1 in viola
        
        if (strcmp(lettura, "fine\n") == 0)
            break;
        
        printf("\033[0;32muser2: \033[0m"); // user2 in verde
        fgets(scrittura, MAX_MSG_SIZE, stdin);
        write(fd2, scrittura, strlen(scrittura) + 1);

    } while (strcmp(scrittura, "HALT\n") != 0 && strcmp(lettura, "HALT\n") != 0);
  
    close(fd1);
    close(fd2);
    
    return 0;
}