//
// Created by Alejandro Villanueva on 15/09/2024.
//
#ifndef TOOLS_H
#define TOOLS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

// Autor: Alejandro Villanueva

// Función para formatear un valor numérico con separador de miles y signo de pesos
// Argumentos:
//    - valor: número a formatear (double)
// Retorno:
//    - cadena de texto con el valor numérico formateado

void formatearValor(double valor) {
    setlocale(LC_NUMERIC, "");
    char resultado[50];
    sprintf(resultado, "$%'0.2f", valor);
    printf("Valor formateado: %s\n", resultado);
}


// Autor: Alejandro Villanueva
// Función para verificar si una cadena de texto finaliza con una subcadena
// Argumentos:
//    - cadena: cadena de texto original (char[])
//    - subcadena: subcadena a verificar (char[])
// Retorno:
//    - 1 si la cadena finaliza con la subcadena, 0 si no
int verificarFinalCadena(const char *cadena, const char *subcadena) {
    int longitudCadena = strlen(cadena);
    int longitudSubcadena = strlen(subcadena);

    if (longitudSubcadena > longitudCadena) {
        return 0;
    }

    if (strcmp(cadena + longitudCadena - longitudSubcadena, subcadena) == 0) {
        return 1;
    } else {
        return 0;
    }
}

#endif
