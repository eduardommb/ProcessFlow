#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *entrada = stdin;
    int interativo = 1;

    char linha[256];


    if (argc == 2)
    {
        entrada = fopen(argv[1], "r");
        if (entrada == NULL)
        {
            printf("ERRO: Arquivo esta em uma crise de vazio imensuravel");
            return 1;
        }
        interativo = 0;
    }

    else if (argc > 2)
    {
        printf("ERRO: Argumentos astronomicos...");
        return 1;
    }


    while (1)
    {
        if(interativo)
        {
            printf("processflow> ");
            fflush(stdout);
        }

        if(fgets(linha, sizeof(linha), entrada) == NULL)
        {
            break;
        }

        linha[strcspn(linha, "\n")] = '\0';
        if (strcmp(linha, "exit") == 0)
        {
            break;
        }

        if (linha[0] == '\0')
        {
            continue;
        }

        if(!interativo)
        {
            printf("%s\n", linha);
        }
    }

    if (entrada != stdin) {
        fclose(entrada);
    }

    return 0;
}
