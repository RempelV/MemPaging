#include <stdio.h>
#include <stdlib.h>


int main_menu(int *menuOptAddr){
    printf("Memory Paging\n\n\
Selecione uma opção: \n\
    1 - Visualizar Memória\n\
    2 - Visualizar Tabela de Página\n\
    3 - Criar um Processo\n\
    Outro - Sair\n\n\
Entrada: ");
    scanf("%d", menuOptAddr);
    return 0;
}

int get_params(int *physicalSizeAddr, int *pageSizeAddr, int *processMaxSizeAddr) {
    printf("Parâmetros Paginação de Memória\n\nDigite o tamanho da memória física em bytes: ");
    scanf("%d", physicalSizeAddr);

    printf("\nDigite o tamanho das páginas ou quadros em bytes: ");
    scanf("%d", pageSizeAddr);

    printf("\nDigite o tamanho máximo de um processo em bytes: ");
    scanf("%d", processMaxSizeAddr);

    return 0;
}

int main() { 
    _Bool running = 1;
    int physicalSize;
    int pageSize;
    int processMaxSize;
    int menuOpt;

    get_params(&physicalSize, &pageSize, &processMaxSize);
    printf("\nParâmetros configurados:\n\n\
    - Tamanho Memória Física: %d bytes \n\
    - Tamanho Página: %d bytes \n\
    - Tamanho Máximo Processo: %d bytes\n\n", physicalSize, pageSize, processMaxSize);

    int physicalMemory[physicalSize/pageSize];


while (running) {
    main_menu(&menuOpt);
    switch (menuOpt) {
        case 1:
            printf("Opção selecionada: Visualizar Memória\n");
            // Percorre memoria fisica e printa cada quadro (vazio ou valor dentro)
            // Printa porcentagem entre livres/ocupados
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

            // verifica se eh maior que o tamanho maximo
            // se sim mensagem de erro
            // senao verifica se há disponibilidade no endereço logico
            // se houver: adiciona um processo na lista encadeada de processos com os quadros disponiveis na lista encadeada de quadros
            // senao mensagem de erro
            break;
        default:
            printf("Opção selecionada: Sair. Saindo...\n");
            running = 0;
            break;
    }
}
    return 0; 
} 