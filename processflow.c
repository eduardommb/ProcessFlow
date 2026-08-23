#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct Tarefa {
    char *nome;
    char *programa;
    char **args;
    int num_args;
    char *input;
    char *output;
    int append;
} Tarefa;

#define MAX_TAREFAS 64
#define MAX_ARGS 32

Tarefa tarefas[MAX_TAREFAS];
int ntarefas = 0;

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

int cadastrar(char **tokens, int n)
{
    if(n < 3)
    {
        printf("uso: task <nome> <programa> [argumentos...]\n");
        return -1;
    }

    for (int i = 0; i < ntarefas; i++)
    {
        if (strcmp(tarefas[i].nome, tokens[1]) == 0)
        {
            printf("processflow: tarefa '%s' ja existe\n", tokens[1]);
            return -1;
        }
    }

    if (ntarefas >= MAX_TAREFAS) {
        printf("processflow: erro. numero maximo de tarefas excedido\n");
        return -1;
    }

    Tarefa *t = &tarefas[ntarefas];
    t->nome = strdup(tokens[1]);
    t->programa = strdup(tokens[2]);

    t->num_args = n - 3;
    t->args = malloc((t->num_args + 2) * sizeof(char *));
    t->args[0] = strdup(tokens[2]);
    for (int i = 0; i < t->num_args; i++)
    {
        t->args[i + 1] = strdup(tokens[3 + i]);
    }
    t->args[t->num_args + 1] = NULL;

    t->input = NULL;
    t->output = NULL;
    t->append = 0;

    ntarefas++;
    return 0;

}

Tarefa *buscar(char *nome)
{
    for (int i = 0; i < ntarefas; i++)
    {
        if (strcmp(tarefas[i].nome, nome) == 0)
        {
            return &tarefas[i];
        }
    }
    return NULL;
}

void executar(Tarefa *t)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        printf("processflow: fork falhou\n");
    }
    else if (pid == 0)
    {
        execvp(t->programa, t->args);

        printf("processflow: nao foi possivel executar '%s'\n", t->programa);
        _exit(127);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
        {
            printf("processflow: tarefa '%s' terminou com codigo %d\n", t->nome, WEXITSTATUS(status));
        }
    }
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

        if (strcmp(tokens[0], "task") == 0)
        {
            if (cadastrar(tokens, n) == 0)
            {
                printf("Tarefa '%s' cadastrada\n", tokens[1]);
            }
        }

        else if (strcmp(tokens[0], "list") == 0)
        {
            for (int i = 0; i < ntarefas; i++)
            {
                printf("%d: %s -> %s\n", i, tarefas[i].nome, tarefas[i].programa);
            }
        }

        else if (strcmp(tokens[0], "run") == 0)
        {
            if (n != 2)
            {
                printf("uso: run <tarefa>\n");
            }
            else
            {
                Tarefa *t = buscar(tokens[1]);

                if (t == NULL)
                {
                    printf("processflow: tarefa '%s' nao existe\n", tokens[1]);
                }
                else
                {
                    executar(t);
                }
            }
        }

        else
        {
            printf("processflow: comando desconhecido '%s'\n", tokens[0]);
        }

    }

    if (entrada != stdin) {
        fclose(entrada);
    }

    return 0;
}
