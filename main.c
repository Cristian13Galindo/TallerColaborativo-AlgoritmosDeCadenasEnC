#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include "tools.h"
#define MAX 100

void verifyString(char *text);
void validateParentheses(char *parentheses);
int lastOccurrence(char *string, char *frase);
void capitalizeText(char *text);
char** splitString(char *text, int *count);
char* joinString(char separator, char **words, int count);

int main() {
    int option;
    char *menu = "------------------------------------------------ \n "
            "1. Verificar si la cadena de texto es palíndroma \n "
            "2. Validar parentesis \n "
            "3. Buscar ultima ocurrencia de un substring \n "
            "4. Capitalizar primera letra de cada palabra \n "
            "5. Formatear valor numerico \n "
            "6. Verificar si una cadena finaliza con otra \n "
            "7. Dividir cadena en arreglo de palabras \n "
            "8. Unir arreglo de palabras en cadena \n "
            "9. Salir \n\n"
            "Digite una opcion \n";

    do {
        printf("%s", menu);
        scanf("%d", &option);
        getchar();
        switch (option) {
            case 1: {
                char text[100];
                printf("Ingrese la cadena de texto a verificar \n");
                fgets(text, sizeof(text), stdin);
                size_t len = strlen(text);
                if (len > 0 && text[len - 1] == '\n') {
                    text[len - 1] = '\0';
                }
                if (text != NULL) {
                    verifyString(text);
                }
                break;
            }
            case 2: {
                char parentheses[100];
                printf("Ingrese la cadena de paréntesis \n");
                scanf("%s", parentheses);
                if (parentheses != NULL) {
                    validateParentheses(parentheses);
                }
                break;
            }
            case 3: {
                char frase[200];
                char substring[100];
                printf("Ingrese la cadena en la que buscar \n");
                fgets(frase, sizeof(frase), stdin);
                size_t len = strlen(frase);
                if (len > 0 && frase[len - 1] == '\n') {
                    frase[len - 1] = '\0';
                }
                printf("Ingrese el substring a buscar \n");
                fgets(substring, sizeof(substring), stdin);
                len = strlen(substring);
                if (len > 0 && substring[len - 1] == '\n') {
                    substring[len - 1] = '\0';
                }
                int posicion = lastOccurrence(substring, frase);
                if (posicion != 0) {
                    printf("La última ocurrencia de '%s' está en la posición: %d\n", substring, posicion);
                } else {
                    printf("No se encontró '%s' en la frase.\n", substring);
                }
                break;
            }
            case 4: {
                char text[200];
                printf("Ingrese la cadena de texto para capitalizar la primera letra de cada palabra \n");
                fgets(text, sizeof(text), stdin);
                size_t len = strlen(text);
                if (len > 0 && text[len - 1] == '\n') {
                    text[len - 1] = '\0';
                }
                capitalizeText(text);
                printf("Texto capitalizado: %s\n", text);
                break;
            }
            case 5: {
                double valor;
                printf("Ingrese un valor numérico: ");
                scanf("%lf", &valor);
                formatearValor(valor);
                break;
            }
            case 6: {
                char cadena[100];
                char subcadena[100];
                printf("Ingrese la cadena de texto: ");
                scanf("%s", cadena);
                printf("Ingrese la subcadena: ");
                scanf("%s", subcadena);
                if (verificarFinalCadena(cadena, subcadena)) {
                    printf("La cadena finaliza con la subcadena.\n");
                } else {
                    printf("La cadena NO finaliza con la subcadena.\n");
                }
                break;
            }
            case 7: {
                char text[200];
                printf("ingrese la cadena a ser dividida en palabras \n");
                fgets(text, sizeof(text), stdin);
                size_t len = strlen(text);
                if (len > 0 && text[len - 1] == '\n') {
                    text[len - 1] = '\0';
                }
                int count;
                char **words = splitString(text, &count);
                printf("palabras divididas:\n");
                for (int i = 0; i < count; i++) {
                    printf("%s\n", words[i]);
                }
                for (int i = 0; i < count; i++) {
                    free(words[i]);
                }
                free(words);
                break;
            }
            case 8: {
                char separator;
                printf("ingrese el caracyer separador de palabras: ");
                scanf(" %c", &separator);
                getchar();
                int count;
                printf("ingrese el numero de palabras: ");
                scanf("%d", &count);
                getchar();
                char **words = (char **)malloc(count * sizeof(char *));
                for (int i = 0; i < count; i++) {
                    words[i] = (char *)malloc(100 * sizeof(char));
                    printf("ingrese la palabra %d: ", i + 1);
                    fgets(words[i], 100, stdin);
                    size_t len = strlen(words[i]);
                    if (len > 0 && words[i][len - 1] == '\n') {
                        words[i][len - 1] = '\0';
                    }
                }
                char *result = joinString(separator, words, count);
                printf("esta es la cadena unida: %s\n", result);
                for (int i = 0; i < count; i++) {
                    free(words[i]);
                }
                free(words);
                free(result);
                break;
            }
            case 9:
                printf("Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida\n");
                break;
        }
    } while (option != 9);

    return 0;
}

/**
 * Metodo para dividir una cadena de texto en un arreglo de palabras
 * @param text La cadena de texto a dividir
 * @param count Puntero a un entero donde se almacenará el número de palabras
 * @return Un puntero a un arreglo de cadenas de texto (palabras)
 */
char** splitString(char *text, int *count) {
    char **result = (char **)malloc(MAX * sizeof(char *));
    char *token = strtok(text, " ");
    int index = 0;
    while (token != NULL) {
        result[index] = (char *)malloc((strlen(token) + 1) * sizeof(char));
        strcpy(result[index], token);
        index++;
        token = strtok(NULL, " ");
    }
    *count = index;
    return result;
}

/**
 * Metodo para unir un arreglo de palabras en una sola cadena de texto
 * @param separator El carácter separador entre las palabras
 * @param words El arreglo de palabras a unir
 * @param count El número de palabras en el arreglo
 * @return Una cadena de texto resultante de unir las palabras con el separador
 */
char* joinString(char separator, char **words, int count) {
    int totalLength = 0;
    for (int i = 0; i < count; i++) {
        totalLength += strlen(words[i]) + 1;
    }
    char *result = (char *)malloc(totalLength * sizeof(char));
    result[0] = '\0';
    for (int i = 0; i < count; i++) {
        strcat(result, words[i]);
        if (i < count - 1) {
            int len = strlen(result);
            result[len] = separator;
            result[len + 1] = '\0';
        }
    }
    return result;
}


/**
 * Metodo que determina si una cadena de texto ingresada por consola en n palindromo
 * @param text Cadena de texto para a verificar
 */
void verifyString(char *text) {
    int lenght = strlen(text);
    char text2[100] = "";
    int trueOrNot = 0, a = 0;

    for (size_t i = 0; text[i]; i++) {
        text[i] = tolower((unsigned char) text[i]);
    }

    while (text[a] != '\0') {
        if (text[a] == ' ') {
            for (int l = a; l < lenght; l++) {
                text[l] = text[l + 1];
            }
            lenght--;
        }
        a++;
    }

    for (int j = lenght - 1; j >= 0; j--) {
        text2[lenght - 1 - j] = text[j];
    }
    text2[lenght] = '\0';

    for (int k = 0; k < lenght; k++) {
        if (text[k] != text2[k]) {
            trueOrNot++;
            break;
        }
    }

    if (trueOrNot == 0) {
        printf("%s", "La palabra es palindroma \n");
    } else {
        printf("%s", "La palabra no es palindroa \n");
    }
}


typedef struct {
    char data[MAX];
    int top;
} Stack;

void initStack(Stack *stack) {
    stack->top = -1;
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

int isFull(Stack *stack) {
    return stack->top == MAX - 1;
}

void push(Stack *stack, char c) {
    if (!isFull(stack)) {
        stack->data[++(stack->top)] = c;
    }
}

char pop(Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->data[(stack->top)--];
    }
    return '\0';
}

char peek(Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->data[stack->top];
    }
    return '\0';
}

/**
 * Metodo que determina si los parentesis ingresados en una cadea  de texto estan balanceados
 * @param parentheses Cadena de texto con los parentesis a validar
 */
void validateParentheses(char *parentheses) {
    Stack stack;
    initStack(&stack);
    while (*parentheses) {
        if (*parentheses == '(' || *parentheses == '[' || *parentheses == '{') {
            push(&stack, *parentheses);
        } else if (*parentheses == ')' || *parentheses == ']' || *parentheses == '}') {
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

    if (isEmpty(&stack)) {
        printf("Los parentesis se encuentran balanceados\n");
    } else {
        printf("Los parentesis no se encuentran balanceados\n");
    }
}

/**
 * Metodo para saber la ultima ocurreccion de un subString en un string
 * @param substring el subString que se quiere saber su ultima ocurrencia
 * @param frase la frase en donde se quiere buscar el subString
 * @return la pocicion en donde esta el ultimo subString o 0 si no existe
 */
int lastOccurrence(char *substring, char *frase) {
    char *lastPos = NULL;
    char *currentPos = frase;
    while ((currentPos = strstr(currentPos, substring)) != NULL) {
        lastPos = currentPos;
        currentPos++;
    }

    if (lastPos != NULL) {
        return (int) (lastPos - frase);
    } else {
        return 0;
    }
}

/**
 * Metodo que permite capitalizar un texto
 * @param text texto para capitalizar
 */
void capitalizeText(char *text) {
    int inWord = 0;
    int wordLength = 0;
    char *wordStart = NULL;

    while (*text != '\0') {
        if (*text == ' ') {
            if (inWord && wordLength > 1) {
                *wordStart = toupper(*wordStart);
            }
            inWord = 0;
            wordLength = 0;
        } else {
            if (inWord == 0) {
                inWord = 1;
                wordStart = text;
            }
            wordLength++;
        }
        text++;
    }
    if (inWord && wordLength > 1) {
        *wordStart = toupper(*wordStart);
    }
}