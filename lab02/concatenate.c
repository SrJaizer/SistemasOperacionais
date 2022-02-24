//Nome: Jair Gino Paca Huaman
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool recognizeCommand(char str[6]){
    char command[3] = {'c', 'a', 't'};
    if (strlen(str) != 3){
        return false;
    }
    for (int i = 0; i < 3; i++){
        if (str[i] != command[i]){
            return false;
        }
    }
    return true;
}

int main(){
    char str[6];
    //string str;
    char filePath[20];
    
    while(true){ 
        scanf("%s %s", str, filePath);
        //printf("%s",str);
        //printf("%s", filePath);
    
        if (recognizeCommand(str) == false){
            printf("comando incorreto!\n");
            continue;
        }

        FILE *input;
        input = fopen(filePath, "r");
        if (input == NULL){
            printf("caminho de arquivo não encontrado!\n");
            continue;
        }

        int letter = getc(input);
        while(letter != EOF){
            putc(letter, stdout);
            letter = getc(input); 
        }
        printf("\n");
    }
}