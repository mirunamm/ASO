#include <stdio.h>
#include <string.h>


int main(void)
{
    char FilePath[256];  
    char Line[1024];     
    FILE *in;            

    printf("Introdu path ul fisierului: ");
    fgets(FilePath, sizeof(FilePath), stdin);

    if (FilePath[strlen(FilePath) - 1] == '\n') {
        FilePath[strlen(FilePath) - 1] = '\0';
    }
    in = fopen(FilePath, "r");

    if (in == NULL) {
        printf("Eroare: fisierul nu exista sau nu poate fi deschis.\n");
        return 1;
    }

    while (fgets(Line, sizeof(Line), in) != NULL) {
        printf("%s", Line);
    }

    fclose(in);

    return 0;
}