#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linked_list.h"

typedef struct {
    int id;
    int size;
    unsigned char* logicalMemory;
} Process;

typedef struct {
    unsigned char value;
    int set; // 0 = não setado, 1 = setado
} MemoryFrame;

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

void print_physical_memory(MemoryFrame *physicalMemory, int numberOfFrames) {
    int free = 0;
    int used = 0;
    for (int i = 0; i < numberOfFrames; i++) {
        if (physicalMemory[i].set == 0) {
            free ++;
            printf("%02d [   ]\n", i);
        }
        else {
            used ++;
            printf("%02d [ %d ]\n", i, physicalMemory[i].value);
        }
    }
    printf("Free: %d - Used: %d\nMemória disponível: %f", free, used, ((float)free/numberOfFrames)*100);
}

MemoryFrame* initialize_physical_memory(int numberOfFrames){
    MemoryFrame *physicalMemory = (MemoryFrame*)malloc(numberOfFrames * sizeof(MemoryFrame));
    for (int i = 0; i < numberOfFrames; i++) {
        physicalMemory[i].value = 0;
        physicalMemory[i].set = 0;
    }
    return physicalMemory;
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

unsigned char* create_logical_memory(int logicalMemorySize) {
    unsigned char* logicalMemory = (unsigned char*)malloc(logicalMemorySize * sizeof(unsigned char));
    for (int i = 0; i < sizeof(logicalMemory); i++) {
        logicalMemory[i] = generate_random_byte();
    }

    return logicalMemory;
}

Process* create_process(int id, int size){
    Process* newProcess = (Process*)malloc(sizeof(Process));
    newProcess -> id = id;
    newProcess -> size = size;
    return newProcess;
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
    MemoryFrame *physicalMemory = initialize_physical_memory(numberOfFrames);

    printf("Memória física possui: %d quadros", numberOfFrames); // debug

    while (running) {
        main_menu(&menuOpt);
        switch (menuOpt) {
            case 1:
                printf("Opção selecionada: Visualizar Memória\n");
                // Percorre memoria fisica e printa cada quadro (vazio ou valor dentro)
                // Printa porcentagem entre livres/ocupados
                print_physical_memory(physicalMemory, numberOfFrames);
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
                int processSize;
                printf("Digite um id: ");
                scanf("%d", &id);
                do {
                    printf("Digite um tamanho: ");
                    scanf("%d", &processSize);
                    if (processSize > processMaxSize || processSize < 1) {
                        printf("O valor informado está fora dos limites de tamanho para um processo, por favor digite um novo valor ente 1 e %d", processMaxSize);
                }
                } while (processSize > processMaxSize || processSize < 1);

                int logicalMemorySize = processSize / pageSize;
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