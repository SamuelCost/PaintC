/**
 * @file verification.h
 * @brief Contém as assinaturas das verificações das primitivas
*/

#ifndef primitives
#define primitives

void checkPrimitive(char *name, char *arguments[100]);

void extractArgumentsPrimitive(char *primitiveLine);

void readPrimitesFile();

#endif
