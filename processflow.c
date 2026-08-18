#include <stdio.h>
#include <string.h>

int main()
{

    char linha[256];

    while (1)
    {

        printf("processflow> ");
        fflush(stdout);

        if(fgets(linha, sizeof(linha), stdin) == NULL)
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

    }

    return 0;
}
