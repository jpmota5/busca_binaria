#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool buscaBinaria(char *v[], int n, char x[]) {
    int s = 0, e = n - 1;

    while (s <= e) {
        int m = (s + e) / 2;
        int cmp = strncmp(x, v[m], strlen(x));

        if (cmp == 0) {
            return true;
        } else if (cmp < 0) {
            e = m - 1;
        } else {
            s = m + 1;
        }
    }

    return false;
}


int compararStrings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    FILE *arquivo = fopen("nomes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    char *nomes[1000];
    char linha[100];

    int numNomes = 0;

    // Ler todos os nomes do arquivo e converter para letras minúsculas
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha[strcspn(linha, "\n")] = '\0'; // Remover o caractere de nova linha
        strlwr(linha); // Converter para minúsculas
        nomes[numNomes] = strdup(linha);
        numNomes++;
    }

    fclose(arquivo);

    // Ordenar os nomes
    qsort(nomes, numNomes, sizeof(nomes[0]), compararStrings);

    // Solicitar a consulta de busca
    printf("Digite a consulta de busca: ");
    char consulta[100];
    scanf("%s", consulta);

    // Converter a consulta para letras minúsculas
    strlwr(consulta);

    // Realizar a busca binária e exibir os resultados
    if (buscaBinaria(nomes, numNomes, consulta)) {
        printf("Nomes encontrados que começam com '%s':\n", consulta);
        for (int i = 0; i < numNomes; i++) {
            if (strncmp(nomes[i], consulta, strlen(consulta)) == 0) {
                printf("%s\n", nomes[i]);
            }
        }
    } else {
        printf("Nenhum nome encontrado com a consulta '%s'.\n", consulta);
    }

    // Liberar memória alocada para os nomes
    for (int i = 0; i < numNomes; i++) {
        free(nomes[i]);
    }

    return 0;
}
