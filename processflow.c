#include <stdio.h>
#include <string.h>

int parse(char *linha, char **tokens, int max)
{
    int i = 0;
    char *token;
    char *saveptr = NULL;

    token = strtok_r(linha, " ", &saveptr);
    while (token != NULL)
    {
        if (i >= max)
        {
            break;
        }
        tokens[i] = token;
        i++;
        token = strtok_r(NULL, " ", &saveptr);
    }

    return i;
}

int main(int argc, char *argv[])
{
    char linha[256];
    FILE *entrada = stdin;
    int interativo = 1;
    char *tokens[64];

    if (argc == 2)
    {
        entrada = fopen(argv[1], "r");
        if (entrada == NULL)
        {
            printf("processflow: nao foi possivel abrir o arquivo\n");
            printf("Uso: ./processflow [workflowFile]\n");
            return 1;
        }
        interativo = 0;
    }

    else if (argc > 2)
    {
        printf("processflow: muitos argumentos\n");
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
        if(!interativo)
        {
            printf("%s\n", linha);
        }

        if (strcmp(linha, "exit") == 0)
        {
            break;
        }

        if (linha[0] == '\0')
        {
            continue;
        }

        int n = parse(linha, tokens, 64);

        if (n == 0)
        {
            continue;
        }

        for (int j = 0; j < n; j++)
        {
            printf("token %d: [%s]\n", j, tokens[j]);
        }

    }

    if (entrada != stdin) {
        fclose(entrada);
    }

    return 0;
}
