#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "linked_list.h"

typedef struct {
    int pageAddress;
    int frameAddress;
} RowPageTable;

typedef struct {
    int id;
    int numberOfPages;
    unsigned char* logicalMemory;
    RowPageTable* pageTable;
} Process;

typedef struct {
    unsigned char* values;
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

void print_physical_memory(MemoryFrame *physicalMemory, int numberOfFrames, int pageSize) {
    int free = 0;
    int used = 0;
    for (int i = 0; i < numberOfFrames; i++) {
        for(int j = 0; j < pageSize; j ++){
            if (physicalMemory[i].set == 0) {
                free++;
                printf("%02d [   ]", i);
            }
            else {
                used++;
                printf("%02d [ %d ] ", i, physicalMemory[i].values[j]);
            }
        }
        printf("\n");
    }
    printf("Free: %d - Used: %d\n\nMemória disponível: %.2f %%", free, used, ((float)free / numberOfFrames) * 100);
}

MemoryFrame* initialize_physical_memory(int numberOfFrames, int pageSize) {
    unsigned char *values = (unsigned char*)malloc(pageSize * sizeof(unsigned char));
    MemoryFrame *physicalMemory = (MemoryFrame*)malloc(numberOfFrames * pageSize * sizeof(MemoryFrame));
    physicalMemory -> values = values;
    for (int i = 0; i < numberOfFrames; i++) {
        for (int j = 0; j < pageSize; j++){
                    physicalMemory[i].values[j] = 0;
        }
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
    return rand() % 256;
}

void load_free_frames(Node **free_frames, int numberOfFrames) {
    for (int i = 0; i < numberOfFrames; i++) {
        insertAtEnd(free_frames, i);
    }
}

unsigned char* create_logical_memory(int logicalMemorySize) {
    unsigned char* logicalMemory = (unsigned char*)malloc(logicalMemorySize * sizeof(unsigned char));
    for (int i = 0; i < logicalMemorySize; i++) {
        logicalMemory[i] = generate_random_byte();
    }
    return logicalMemory;
}

Process* create_process(int id, unsigned char *logicalMemory, int numberOfPages) {
    Process* newProcess = (Process*)malloc(sizeof(Process));
    newProcess->id = id;
    newProcess->numberOfPages = numberOfPages;
    newProcess->logicalMemory = logicalMemory;
    newProcess->pageTable = (RowPageTable*)malloc(numberOfPages * sizeof(RowPageTable));
    return newProcess;
}

void createPageTable(Process* process, int numberOfPages, Node** headFreeFrames, MemoryFrame* physicalMemory) {
    for (int i = 0; i < numberOfPages; i++) {
        Node* randomAvailableFrame = getRandomValue(headFreeFrames);
        process->pageTable[i].pageAddress = i;
        process->pageTable[i].frameAddress = randomAvailableFrame->data;
        deleteNode(headFreeFrames, randomAvailableFrame->data);
        physicalMemory[randomAvailableFrame->data].set = 1;
        physicalMemory[randomAvailableFrame->data].values = process->logicalMemory[i];
    }
}

int main() {
    srand(time(NULL));
    unsigned char* logicalMemory;
    int running = 1;
    int physicalSize;
    int pageSize;
    int processMaxSize;
    int menuOpt;
    Node* headFreeFrames = NULL;

    get_params(&physicalSize, &pageSize, &processMaxSize);
    printf("\nParâmetros configurados:\n\n\
    - Tamanho Memória Física: %d bytes \n\
    - Tamanho Página: %d bytes \n\
    - Tamanho Máximo Processo: %d bytes\n\n", physicalSize, pageSize, processMaxSize);

    int numberOfFrames = physicalSize / pageSize;
    MemoryFrame *physicalMemory = initialize_physical_memory(numberOfFrames, pageSize);
    printf("AAAAAAAAAAA")
    Process *processes[numberOfFrames];
    load_free_frames(&headFreeFrames, numberOfFrames);
    for (int i = 0; i < numberOfFrames; i++) {
        processes[i] = NULL;
    }

    printf("Memória física possui: %d quadros\n", numberOfFrames); // debug

    while (running) {
        main_menu(&menuOpt);
        switch (menuOpt) {
            case 1:
                printf("Opção selecionada: Visualizar Memória\n");
                print_physical_memory(physicalMemory, numberOfFrames, pageSize);
                break;
            case 2:
                printf("Opção selecionada: Visualizar Tabela de Páginas\n");
                // Verificar se faz sentido permitir a criação de processos com o mesmo ID
                Process *process = processes[0];
                if (process == NULL) {
                    printf("Nenhum processo registrado\n");
                    break;   
                }

                printf("Selecione um PID:\n");
                for (int i = 1; process != NULL; i++) {
                    printf("PID: %d\n", process->id);
                    process = processes[i];
                }
                
                int pid;
                printf("Entrada: ");
                scanf(" %d", &pid);

                process = processes[0];
                int found = 0;

                for (int i = 1; process != NULL || found; i++) {
                    if (process->id == pid) {
                        found = 1;
                        printf("Tabela de Páginas do Processo %d:\n", pid);
                        printf("Página\tQuadro\n");
                        for (int j = 0; j < process->numberOfPages; j++) {
                            printf("%d\t%d\n", process->pageTable[j].pageAddress, process->pageTable[j].frameAddress);
                        }
                        break;
                    }
                    process = processes[i];
                }

                if (!found) {
                    printf("Processo não encontrado.");
                }

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
                        printf("ERRO: O valor informado está fora dos limites de tamanho para um processo, por favor digite um novo valor entre 1 e %d\n", processMaxSize);
                    }
                } while (processSize > processMaxSize || processSize < 1);

                int numberOfPages = processSize / pageSize;
                if (processSize % pageSize != 0) {
                    numberOfPages++;
                }

                logicalMemory = create_logical_memory(numberOfPages);
                int countHeadFreeFrames = 0;
                for (int i = 0; i < numberOfFrames; i++) {
                    if (physicalMemory[i].set == 0) {
                        countHeadFreeFrames++;
                    }
                }
                if (countHeadFreeFrames >= numberOfPages) {
                    for (int i = 0; i < numberOfFrames; i++) {
                        if (processes[i] == NULL) {
                            processes[i] = create_process(id, logicalMemory, numberOfPages);
                            createPageTable(processes[i], numberOfPages, &headFreeFrames, physicalMemory);
                            break;
                        }
                    }
                }
                else {
                    printf("\nERRO: Não há quadros suficientes para o número de páginas necessário!\n");
                    free(logicalMemory);
                }
                break;
            default:
                printf("Opção selecionada: Sair. Saindo...\n");
                running = 0;
        }
    }

    free(physicalMemory);
    freeList(headFreeFrames);
    return 0;
}
