# PaintC
Ferramenta de desenho gráfico em C

## Tipos de dados utilizados
 - typedef
 - struct
 - int
 - char
 - void

## Como compilar o programa

```
gcc main.c -o main
```

## Primitivas suportadas

### Criar uma nova “imagem”, com a largura e altura especificadas
```
./main image 100 100
```
> Irá criar uma imagem com o nome padrão "image.ppm" nas dimensões especificadas, largura e altura, respectivamente

### Salvar a imagem atual em um arquivo usando o formato ppm
```
./main save imageTest.ppm
```
> Irá salvar uma imagem com o nome especificado
