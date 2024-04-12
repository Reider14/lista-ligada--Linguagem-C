#include <stdio.h>
#include <stdlib.h>

struct listNode { 
    char data;
    struct listNode *nextPtr;
};

typedef struct listNode LISTNODE;
typedef LISTNODE *LISTNODEPTR;

void insert(LISTNODEPTR *, char);
char delete(LISTNODEPTR *, char);
int isEmpty(LISTNODEPTR);
void printList(LISTNODEPTR);
void instructions(void);

int main() {
    LISTNODEPTR startPtr = NULL;
    int choice;
    char item;

    instructions(); 
    printf("? ");
    scanf("%d", &choice);

    while (choice != 3) {
        switch (choice) {
            case 1:
                printf("Digite um caractere: ");
                scanf(" %c", &item);
                insert(&startPtr, item);
                printList(startPtr);
                break;

            case 2:
                if (!isEmpty(startPtr)) {
                    printf("Digite o caractere a ser removido: ");
                    scanf(" %c", &item);

                    if (delete(&startPtr, item)) {
                        printf("%c removido.\n", item);
                        printList(startPtr);
                    } else {
                        printf("%c nao encontrado.\n\n", item);
                    }
                } else {
                    printf("A lista esta vazia.\n\n");
                }
                break;

            default:
                printf("Escolha invalida.\n\n");
                break;
        }
        
        instructions();
        printf("? ");
        scanf("%d", &choice);
    }

    printf("Fim do Programa.\n");
    return 0;
}

void instructions(void) {
    printf("Digite sua escolha:\n"
           "1 para inserir um elemento na lista.\n"
           "2 para remover um elemento da lista.\n"
           "3 para finalizar.\n");
}

void insert(LISTNODEPTR *sPtr, char value) {
    LISTNODEPTR newPtr, previousPtr, currentPtr;

    newPtr = malloc(sizeof(LISTNODE));
    if (newPtr != NULL) {
        newPtr->data = value;
        newPtr->nextPtr = NULL;

        previousPtr = NULL;
        currentPtr = *sPtr;

        while (currentPtr != NULL && value > currentPtr->data) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        if (previousPtr == NULL) {
            newPtr->nextPtr = *sPtr;
            *sPtr = newPtr;
        } else {
            previousPtr->nextPtr = newPtr;
            newPtr->nextPtr = currentPtr;
        }
    } else {
        printf("%c nao inserido. Nao existe memoria disponivel.\n", value);
    }
}

char delete(LISTNODEPTR *sPtr, char value) {
    LISTNODEPTR previousPtr, currentPtr, tempPtr;

    if (value == (*sPtr)->data) {
        tempPtr = *sPtr;
        *sPtr = (*sPtr)->nextPtr; 
        free(tempPtr); 
        return value;
    } else {
        previousPtr = *sPtr;
        currentPtr = (*sPtr)->nextPtr;

        while (currentPtr != NULL && currentPtr->data != value) {
            previousPtr = currentPtr;
            currentPtr = currentPtr->nextPtr;
        }

        if (currentPtr != NULL) {
            tempPtr = currentPtr;
            previousPtr->nextPtr = currentPtr->nextPtr;
            free(tempPtr);
            return value;
        }
    }
    return '\0';
}

int isEmpty(LISTNODEPTR sPtr) {
    return sPtr == NULL;
}

void printList(LISTNODEPTR currentPtr) {
    if (currentPtr == NULL) {
        printf("A lista esta vazia.\n\n");
    } else {
        printf("A lista e:\n");
        while (currentPtr != NULL) {
            printf("%c --> ", currentPtr->data);
            currentPtr = currentPtr->nextPtr;
        }
        printf("NULL\n\n");
    }
}
