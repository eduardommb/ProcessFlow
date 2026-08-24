# ProcessFlow

Orquestrador de processos em C para a disciplina de Infraestrutura de Software.
Recebe comandos em modo interativo (`processflow>`) ou a partir de um arquivo
workflow (`.pf`) e executa tarefas cadastradas como processos filhos, com
suporte a execução sequencial, paralela, pipes, redirecionamento de entrada e
saída e mudança de diretório de trabalho.

## Arquivos

- `processflow.c` — todo o código-fonte (parser, cadastro de tarefas, execução de processos)
- `Makefile` — compilação e limpeza
- `testes/` — casos de teste fornecidos pelo professor (entrada/saída esperada)

## Como compilar

```sh
make
```

Limpar os arquivos compilados:

```sh
make clean
```

## Como executar

Modo interativo (apresenta o prompt `processflow>`):

```sh
./processflow
```

Modo workflow (lê os comandos de um arquivo `.pf`, ecoando cada linha antes de processá-la):

```sh
./processflow arquivo.pf
```

## Comandos suportados

```text
task <nome> <programa> [argumentos...]   cadastra uma tarefa
run <nome>                               executa uma tarefa (espera o término)
run sequential <t1> <t2> ...             executa em sequência
run parallel <t1> <t2> ...               executa em paralelo
run pipe <t1> <t2> ...                   saída de cada tarefa vira entrada da próxima
input <tarefa> <arquivo>                 redireciona a entrada da tarefa
output <tarefa> <arquivo>                redireciona a saída (sobrescreve)
append <tarefa> <arquivo>                redireciona a saída (acrescenta)
workdir <diretorio>                      muda o diretório de trabalho
list                                     lista as tarefas cadastradas (auxiliar)
exit                                     encerra
```

