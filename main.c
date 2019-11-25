/**
 * @file main.c
 * @brief Arquivo principal de execução
 *
 * @warning Leia o README caso ainda saiba como compilar corretamente.
 * @copyright PaintC - Samuel Costa e Paulo Lima
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./modules/auxiliary.h"
#include "./modules/verification.h"

int main(){
    /**
    * Constrói os valores padrões das primitivas
    */
    makeDefaultStructs();
    /**
    * Ler o arquivo de primitivas
    */
    readPrimitesFile();
}