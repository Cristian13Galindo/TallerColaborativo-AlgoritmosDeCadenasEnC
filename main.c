#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX 100

void verifyString(char *text);
void validateParentheses(char *parentheses);

int main(void){
    int option;
    char *menu="------------------------------------------------ \n "
               "1. Verificar si la cadena de texto es palindroma \n "
               "2. Validar parentesis \n "
               "3. Salir \n\n"
               "Digite una opcion \n";
    do{
        printf(menu);
        scanf("%d", &option);
        getchar();
        switch (option){
        case 1:
            char text[100];
            printf("%s","Ingrese la cadena de texto a verificar \n");
            fgets(text, sizeof(text), stdin);

            size_t len = strlen(text);
            if (len > 0 && text[len - 1] == '\n') {
                text[len - 1] = '\0';
            }

            if (text!=NULL){
                verifyString(text);
            }
            break;
        case 2:
            char parentheses[100];
            printf("%s","Ingrese la cadena de parentesis \n");
            scanf("%s",parentheses);
            if (parentheses!=NULL){
                validateParentheses(parentheses);
            }
            break;
        }
    }while (option>=1  && option<=2);
    return 0;
}

/**
 * Metodo que determina si una cadena de texto ingresada por consola en n palindromo
 * @param text Cadena de texto para a verificar
 */
void verifyString(char *text){
    int lenght=strlen(text);
    char text2[100]="";
    int trueOrNot=0, a=0;

    for (size_t i = 0; text[i]; i++) {  // Pasar la cadena de carax¿cteres a minusculas
        text[i] = tolower((unsigned char)text[i]);
    }

    while (text[a]!='\0'){  // Eliminar los espacios entre las palabras
        if (text[a]==' '){
            for (int l=a;l<lenght;l++){
                text[l]=text[l+1];
            }
            lenght--;
        }
        a++;
    }

    for (int j=lenght-1;j>=0;j--){ // Copiar la cadena en un array de derecha a izquierda
        text2[lenght-1-j]=text[j];
    }
    text2[lenght]='\0';

    for (int k=0; k<lenght;k++){ // Evalaur si el contenido de la cadena es el mismo por ambos sentidos
        if (text[k]!=text2[k]){
            trueOrNot++;
            break;
        }
    }

    if (trueOrNot==0){
        printf("%s","La palabra es palindroma \n");
    }else{
        printf("%s", "La palabra no es palindroa \n");
    }
}


typedef struct {
    char data[MAX];
    int top;
} Stack;

void initStack(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int isFull(Stack* stack) {
    return stack->top == MAX - 1;
}

void push(Stack* stack, char c) {
    if (!isFull(stack)) {
        stack->data[++(stack->top)] = c;
    }
}

char pop(Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->data[(stack->top)--];
    }
    return '\0'; // Retorna un caracter nulo si la pila esta va
}

char peek(Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->data[stack->top];
    }
    return '\0'; // Retorna un caracter nulo si la pila esta vacia
}

/**
 * Metodo que determina si los parentesis ingresados en una cadea  de texto estan balanceados
 * @param parentheses Cadena de texto con los parentesis a validar
 */
void validateParentheses(char *parentheses){
    Stack stack;
    initStack(&stack);
    while (*parentheses) {
        if (*parentheses == '(' || *parentheses == '[' || *parentheses == '{') { // Si es un parentesis de apertura, se agrega a la pila
            push(&stack, *parentheses);
        } else if (*parentheses == ')' || *parentheses == ']' || *parentheses == '}') { // Si es un parentesis de cierre, se verifica si corresponde con el tope de la pila
            if (isEmpty(&stack)) {
                printf("Los paréntesis no se encuentran balanceados\n");
                return;
            }
            char topChar = pop(&stack);
            if ((*parentheses == ')' && topChar != '(') ||
                (*parentheses == ']' && topChar != '[') ||
                (*parentheses == '}' && topChar != '{')) {
                printf("Los paréntesis no se encuentran balanceados\n");
                return;
                }
        }
        parentheses++;
    }

    if (isEmpty(&stack)) {   // Si la pila está vacía al final, los paréntesis están balanceados
        printf("Los parentesis se encuentran balanceados\n");
    } else {
        printf("Los parentesis no se encuentran balanceados\n");
    }
}