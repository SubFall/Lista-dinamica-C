#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>


typedef struct NO{
    int dados;
    struct NO* prox;
}NO;

typedef struct LISTA{
    NO* ini;
    NO* fim;
}LISTA;

LISTA lista;

void inseriInicio(int elemento);
void inseriFim(int elemento);
void inserirElemento(int elemento, int valor);
void imprimir();
void erroMemoria();
void menu();
void limparBuffer();
int removeInicio();
int removeFim();
void removerElemento(int elemento);


int main(){
    setlocale(LC_ALL, "Portuguese");

    int opcao, dados, valor;
    lista.ini, lista.fim = NULL;

    do
    {
        system("clear");
        menu();
        printf("Opcão: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao){
        case 0:
            break;
        case 1:
            printf("\n\tDigite o valor, para inserir no inicio: ");
            scanf("%d", &dados);
            limparBuffer();
            inseriInicio(dados);
            system("clear");
            break;
        case 2:
            printf("\n\tDigite o valor, para inserir no fim: ");
            scanf("%d", &dados);
            limparBuffer();
            inseriFim(dados);
            system("clear");
            break;
        case 3:
            dados = removeInicio();
            if(dados == -1){
                printf("\tErro\n");
            }else{
                printf("\tvalor removido %d\n", dados);
            }
            printf("\tPressione qualquer telca para continuar\n");
            getchar();
            limparBuffer();
            break;
        case 4:
            dados = removeFim();
            if(dados == -1){
                printf("\tErro\n");
            }else{
                printf("\tvalor removido %d\n", dados);
            }
            printf("\tPressione qualquer telca para continuar\n");
            getchar();
            limparBuffer();
            break;
        case 5:
            printf("\t\nQual o valor que deseja remover ? ");
            scanf("%d", &dados);
            limparBuffer();
            removerElemento(dados);
            break;
        case 6:
            printf("\t\nQual a posicão que deseja colocar ? ");
            scanf("%d", &valor);
            limparBuffer();
            printf("\t\nQual o valor ? ");
            scanf("%d", &dados);
            limparBuffer();
            inserirElemento(dados, valor);
            break;
        case 7:
            imprimir();
            system("sleep 1");
            printf("\tPressione qualquer telca para continuar\n");
            getchar();
            limparBuffer();
            system("clear");
            break;
        default:
            printf("\n\tOpcão inválida, digite o valor correto\n\n");
            system("sleep 1");
            printf("\tPressione qualquer telca para continuar\n");
            getchar();
            limparBuffer();
            break;
        }
    } while (opcao != 0);
    
}

void inseriInicio(int elemento){
    NO* ptr = (NO*)malloc(sizeof(NO));
    if(ptr == NULL){
        erroMemoria();
    }else{
        ptr->dados = elemento;
        ptr->prox = NULL;
    }

    if(lista.ini == NULL){
        lista.fim = ptr;
    }else{
        ptr->prox = lista.ini;
    }
    lista.ini = ptr;
}

void inseriFim(int elemento){
    NO* ptr = (NO*)malloc(sizeof(NO));
    
    if(ptr == NULL){
        erroMemoria();
    }else{
        ptr->dados = elemento;
        ptr->prox = NULL;
    }

    if(lista.ini == NULL){
        lista.ini = ptr;
    }else{
        lista.fim->prox = ptr;
    }
    lista.fim = ptr;
}

void inserirElemento(int elemento, int valor){//seleciona o valor do elemento e o novo nó em inserido na frente
    NO* current = lista.ini;

    if(current == NULL){
        inseriInicio(elemento);
    }else{
        while (current->dados != valor){
            current = current->prox;
        }
        if(current->prox == NULL){
            inseriFim(elemento);
        }else{
        NO* ptr = (NO*)malloc(sizeof(NO));
        ptr->dados = elemento;
        ptr->prox = NULL;
        ptr->prox = current->prox;
        current->prox = ptr;
        }
        //tem que terminar
    }
}

int removeInicio(){
    NO* ptr = (NO*)malloc(sizeof(NO));
    int bkp;
    ptr = lista.ini;

    if(ptr == NULL){
        printf("\tLista vázia\n");
        return -1;
    }else{
        lista.ini = lista.ini->prox;
        ptr->prox = NULL;
        bkp = ptr->dados;
        free(ptr);
    }
    return bkp;
}

int removeFim() {
    if (lista.ini == NULL) {
        printf("\tLista vazia\n");
        return -1;
    }

    int bkp = lista.fim->dados;

    if (lista.ini == lista.fim) {
        // A lista possui apenas um nó
        free(lista.fim);
        lista.ini = NULL;
        lista.fim = NULL;
    } else {
        // A lista possui mais de um nó
        NO* current = lista.ini;

        while (current->prox != lista.fim) {
            current = current->prox;
        }

        current->prox = NULL;
        free(lista.fim);
        lista.fim = current;
    }

    return bkp;
}

void removerElemento(int elemento) {
    if (lista.ini == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    NO* atual = lista.ini;
    NO* anterior = NULL;

    // Percorre a lista procurando o elemento a ser removido
    while (atual != NULL) {
        if (atual->dados == elemento) {
            // Elemento encontrado, ajusta os ponteiros dos nós vizinhos
            if (anterior == NULL) {
                // O elemento está no início da lista
                lista.ini = atual->prox;
                atual->prox = NULL;
            } else {
                anterior->prox = atual->prox;
                atual->prox = NULL;
            }

            // Libera a memória do nó removido
            free(atual);
            printf("\tElemento removido %d.\n", elemento);
            printf("\tPressione qualquer tecla para continuar");
            getchar();
            return;
        }

        // Avança para o próximo nó
        anterior = atual;
        atual = atual->prox;
    }  

    printf("Elemento não encontrado na lista.\n");
}



void imprimir(){
    NO* ptr = lista.ini;
    printf("\n\tInicio -> ");
    while (ptr != NULL){
        printf("%d - ", ptr->dados);
        ptr = ptr->prox;
    }
    printf("<- Fim\n");
}

void erroMemoria(){
    printf("\tErro! Não foi possível alocar memória\n");
    system("sleep(5)");
}

void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n') {
        // Descarta o caractere
    }
}

void menu(){
    printf("\t\n1 - Inserir no Início\
            \t\n2 - Inserir no Fim\
            \t\n3 - Remover no Início\
            \t\n4 - Remover no FIm\
            \t\n5 - Remove um elemento especifico\
            \t\n6 - Insere Elemento\
            \t\n7 - Imprimir\
            \t\n0 - Sair\n");
}