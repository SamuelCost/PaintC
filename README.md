# PaintC
Ferramenta de desenho gráfico em C

## Documentação

O projeto possui uma documentação feita com o auxílio do [Doxygen](http://www.doxygen.nl/), e pode ser encontrada [aqui](docs). Basta executar localmente o arquivo `index.html` que se encontra na pasta `/html`. É possível enxergar detalhes sobre a implementação de cada parte do código.

## Tipos de dados utilizados

 - typedef
 - struct
 - int
 - char
 - void

## Considerações iniciais

O programa possui um arquivo chamado `primitives`, em que nele são especificadas as primitivas suportadas descritas mais adiante.

O arquivo deve possuir uma formatação como específicado neste exemplo:
```
image 600 400
clear 0 0 0
color 100 170 200
line 0 400 600 200
polygon 3 0 400 300 200 600 400
circle 200 100 50
color 180 30 50
fill 300 300
color 255 0 0
fill 0 0
flip vertical
flip horizontal
move right 10
move left 10
move top 10
move bottom 10
save test.ppm
```

## Como compilar o programa

```
gcc ./modules/auxiliary.c ./modules/primitives.c ./modules/verification.c main.c -o main
```

## Como executar o programa

```
./main
```

## Primitivas suportadas

### Criar uma nova “imagem”, com a largura e altura especificadas
```
image 100 100
```
> Irá criar uma imagem com o nome padrão "image.ppm" nas dimensões especificadas, largura e altura, respectivamente

### Salvar a imagem atual em um arquivo usando o formato ppm
```
save imageTest.ppm
```
> Irá salvar uma imagem com o nome especificado

### Abre uma imagem no formato ppm e carrega essa imagem no programa para futuras operações de desenho
```
open imageTest.ppm
```
> Irá abrir um arquivo PPM para operações

### Especifica os dois pontos das extremidades da linha a ser desenhada, cada um com suas coordenadas (x, y)
```
line 0 400 600 200
```

### Desenha um círculo nas posições x, y e tamanho especificados
```
circle 200 100 50
```

### Desenha um polígono delimitado por uma lista de pontos
```
polygon 3 0 400 300 200 600 400
```

### Limpa a imagem, setando todos os pixels para a cor especificada
```
clear 0 0 0
```

### Muda a cor atual para uma cor especificada
```
color 100 170 200
```

### Vira a imagem na vertical ou na horizontal
```
flip vertical
flip horizontal
```

### Move a imagem em uma quantidade de pixels para direita, esquerda, cima ou baixo
```
move right 10
move left 10
move top 10
move bottom 10
```

### Rotacionar a imagem em um angulo de 90 graus
```
rotate 90
```

## Contribuidores ✨

<table>
  <tr>
    <td align="center">
        <a href="https://github.com/SamuelCost">
            <img src="https://avatars1.githubusercontent.com/u/12562944?s=460&v=4" width="100px;" alt="SamuelCost"/>
            <br />
            <sub><b>Samuel Costa (SamuelCost)</b></sub>
        </a>
    </td>
    <td align="center">
        <a href="https://github.com/durvaal">
            <img src="https://avatars1.githubusercontent.com/u/10746843?s=460&v=4" width="100px;" alt="Durvaal"/>
            <br />
            <sub><b>Paulo Lima (Durvaal)</b></sub>
        </a>
    </td>
  </tr>
</table>