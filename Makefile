processflow: processflow.c ; cc -std=c11 -Wall -Wextra -D_POSIX_C_SOURCE=200809L processflow.c -o processflow
clean: ; rm -f processflow
