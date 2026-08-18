#include <stdio.h>

int main() {

    char linha[256];

    printf("processflow> ");
    fflush(stdout);
    fgets(linha, sizeof(linha), stdin);

    printf("%s", linha);

    return 0;
}
