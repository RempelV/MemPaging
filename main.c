#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linked_list.h"

void main_menu(int *menuOptAddr){
    printf("\n\nMemory Paging\n\n\
Selecione uma opção: \n\
    1 - Visualizar Memória\n\
    2 - Visualizar Tabela de Página\n\
    3 - Criar um Processo\n\
    Outro - Sair\n\n\
Entrada: ");
    scanf(" %d", menuOptAddr);
}

void get_params(int *physicalSizeAddr, int *pageSizeAddr, int *processMaxSizeAddr) {
    printf("Parâmetros Paginação de Memória\n\nDigite o tamanho da memória física em bytes: ");
    scanf(" %d", physicalSizeAddr);

    printf("\nDigite o tamanho das páginas e quadros em bytes: ");
    scanf(" %d", pageSizeAddr);

    printf("\nDigite o tamanho máximo de um processo em bytes: ");
    scanf(" %d", processMaxSizeAddr);
}

int generate_random_byte() {
    return rand() % (255 - 0 + 1) + 0;
}

void load_free_frames(Node **free_frames, int numberOfFrames) {
    for (int i = 0; i < numberOfFrames; i++) {
        insertAtEnd(free_frames, i);
    }
}

void load_frames(unsigned char *physicalMemory) {
    for (int i = 0; i < sizeof(physicalMemory); i++) {
        physicalMemory[i] = generate_random_byte();
    }
}

unsigned char* create_logical_memory(int logicalMemorySize) {
    unsigned char* logicalMemory = (unsigned char*)malloc(logicalMemorySize * sizeof(unsigned char));
    for (int i = 0; i < sizeof(logicalMemory); i++) {
        logicalMemory[i] = generate_random_byte();
    }

    return logicalMemory;
}

int main() { 
    srand(time(NULL));
    unsigned char* logicalMemory;
    int running = 1;
    int physicalSize;
    int pageSize;
    int processMaxSize;
    int menuOpt;
    Node* freeFrames = NULL;

    get_params(&physicalSize, &pageSize, &processMaxSize);
    printf("\nParâmetros configurados:\n\n\
    - Tamanho Memória Física: %d bytes \n\
    - Tamanho Página: %d bytes \n\
    - Tamanho Máximo Processo: %d bytes\n\n", physicalSize, pageSize, processMaxSize);

    int numberOfFrames = physicalSize / pageSize;
    unsigned char physicalMemory[numberOfFrames];
    load_frames(physicalMemory);
    load_free_frames(&freeFrames, numberOfFrames);

    while (running) {
        main_menu(&menuOpt);
        switch (menuOpt) {
            case 1:
                printf("Opção selecionada: Visualizar Memória\n");
                // Percorre memoria fisica e printa cada quadro (vazio ou valor dentro)
                // Printa porcentagem entre livres/ocupados
                for (int i = 0; i < sizeof(physicalMemory); i++) {
                    printf(" %d", physicalMemory[i]);
                }
                break;
            case 2:
                printf("Opção selecionada: Visualizar Tabela de Páginas\n");
                // Percorre lista encadeada
                // Listar id dos processos
                // input processo
                // Mostrar a tabela do processo
                break;
            case 3:
                printf("Opção selecionada: Criar um Processo\n");
                int id;
                int tamanho;
                printf("Digite um id: ");
                scanf("%d", &id);
                printf("Digite um tamanho: ");
                scanf("%d", &tamanho);

                int logicalMemorySize = tamanho / pageSize;
                logicalMemory = create_logical_memory(logicalMemorySize);

                for (int i = 0; i < logicalMemorySize; i++) {
                    printf(" %d\n", logicalMemory[i]);
                }

                // verifica se eh maior que o tamanho maximo
                // se sim mensagem de erro
                // senao verifica se há disponibilidade no endereço logico
                // se houver: adiciona um processo na lista encadeada de processos com os quadros disponiveis na lista encadeada de quadros
                // senao mensagem de erro
                break;
            default:
                printf("Opção selecionada: Sair. Saindo...\n");
        }
    }

    free(logicalMemory);
    return 0; 
} 