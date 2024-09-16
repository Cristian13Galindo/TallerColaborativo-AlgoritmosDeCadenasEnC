#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "tools.h"
#define MAX 100

void verifyString(char *text);

void validateParentheses(char *parentheses);

int lastOccurrence(char *string, char *frase);

void capitalizeText(char *text);


int main() {
    int option;
    char *menu = "------------------------------------------------ \n "
            "1. Verificar si la cadena de texto es palíndroma \n "
            "2. Validar parentesis \n "
            "3. Buscar ultima ocurrencia de un substring \n "
            "4. Capitalizar primera letra de cada palabra \n "
            "5. Formatear valor numerico \n "
            "6. Verificar si una cadena finaliza con otra \n "
            "9. Salir \n\n"
            "Digite una opcion \n";

    do {
        printf("%s", menu);
        scanf("%d", &option);
        getchar(); // Consumir el carácter de nueva línea residual
        switch (option) {
            case 1: {
                char text[100];
                printf("Ingrese la cadena de texto a verificar \n");
                fgets(text, sizeof(text), stdin);
                size_t len = strlen(text);
                if (len > 0 && text[len - 1] == '\n') {
                    text[len - 1] = '\0'; // Eliminar el salto de línea
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
                    frase[len - 1] = '\0'; // Eliminar el salto de línea
                }
                printf("Ingrese el substring a buscar \n");
                fgets(substring, sizeof(substring), stdin);
                len = strlen(substring);
                if (len > 0 && substring[len - 1] == '\n') {
                    substring[len - 1] = '\0'; // Eliminar el salto de línea
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
                    text[len - 1] = '\0'; // Eliminar el salto de línea
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
 * Metodo que determina si una cadena de texto ingresada por consola en n palindromo
 * @param text Cadena de texto para a verificar
 */
void verifyString(char *text) {
    int lenght = strlen(text);
    char text2[100] = "";
    int trueOrNot = 0, a = 0;

    for (size_t i = 0; text[i]; i++) {
        // Pasar la cadena de carax¿cteres a minusculas
        text[i] = tolower((unsigned char) text[i]);
    }

    while (text[a] != '\0') {
        // Eliminar los espacios entre las palabras
        if (text[a] == ' ') {
            for (int l = a; l < lenght; l++) {
                text[l] = text[l + 1];
            }
            lenght--;
        }
        a++;
    }

    for (int j = lenght - 1; j >= 0; j--) {
        // Copiar la cadena en un array de derecha a izquierda
        text2[lenght - 1 - j] = text[j];
    }
    text2[lenght] = '\0';

    for (int k = 0; k < lenght; k++) {
        // Evalaur si el contenido de la cadena es el mismo por ambos sentidos
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
    return '\0'; // Retorna un caracter nulo si la pila esta va
}

char peek(Stack *stack) {
    if (!isEmpty(stack)) {
        return stack->data[stack->top];
    }
    return '\0'; // Retorna un caracter nulo si la pila esta vacia
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
            // Si es un parentesis de apertura, se agrega a la pila
            push(&stack, *parentheses);
        } else if (*parentheses == ')' || *parentheses == ']' || *parentheses == '}') {
            // Si es un parentesis de cierre, se verifica si corresponde con el tope de la pila
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
        // Si la pila está vacía al final, los paréntesis están balanceados
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

    // Usamos strstr para encontrar la última ocurrencia
    while ((currentPos = strstr(currentPos, substring)) != NULL) {
        lastPos = currentPos; // Guardamos la posición actual como la última encontrada
        currentPos++; // Avanzamos para buscar más ocurrencias
    }

    // Si encontramos la última posición, calculamos el índice
    if (lastPos != NULL) {
        return (int) (lastPos - frase); // Convertir a entero para obtener la posición relativa al inicio
    } else {
        return 0; // Retornar 0 si no se encontró la palabra
    }
}

/**
 * Metodo que permite capitalizar un texto
 * @param text texto para capitalizar
 */
void capitalizeText(char *text) {
    int inWord = 0;
    int wordLength = 0;  // Para contar la longitud de cada palabra
    char *wordStart = NULL;  // Para recordar el inicio de la palabra

    while (*text != '\0') {
        if (*text == ' ') {
            // Si estamos al final de una palabra y la palabra tiene más de 1 letra
            if (inWord && wordLength > 1) {
                *wordStart = toupper(*wordStart);  // Convertimos la primera letra a mayúscula
            }
            // Reiniciamos el estado para la próxima palabra
            inWord = 0;
            wordLength = 0;
        } else {
            // Si es el primer carácter de una palabra
            if (inWord == 0) {
                inWord = 1;  // Ahora estamos dentro de una palabra
                wordStart = text;  // Guardamos la posición del inicio de la palabra
            }
            wordLength++;  // Incrementamos el contador de la longitud de la palabra
        }
        text++;  // Avanzamos al siguiente carácter
    }

    // Verificamos la última palabra (si no está seguida de un espacio)
    if (inWord && wordLength > 1) {
        *wordStart = toupper(*wordStart);
    }
}