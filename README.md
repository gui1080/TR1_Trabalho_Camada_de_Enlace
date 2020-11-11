# Camada de Enlace

Trabalho 2 para a matéria de Teleinformática e Redes na UnB, semestre 2020/01, relativo à camada de enlace, baseando-se no trabalho anterior relativo à camada física.

# Instruções de uso

Para compilar, rode no terminal aberto na pasta "código":

> make

O executável "sim" (de simulador) será criado junto de outros arquivos objeto.

Para rodar, execute:

> ./sim

Para limpar o diretório, rode:

> make clean

Para mudar o tipo de codificação/decodificação, no arquivo CamadaFisica.h existe um #DEFINE que serve como atalho. Implementou-se em C++ um simulador de camada física que utiliza as codificações/decodificações Binária (opção 0), Manchester (opção 1) e Manchester Diferencial (opção 2). Para mudar o tipo de enquadramento, no arquivo CamadaEnlace.h existe um #DEFINE que serve como atalho. Implementou-se em C++ um simulador de camada de enlace que utiliza os enquadramentos com Contagem de Caracteres (opção 0), com a Inserção de Bytes (opção 1) e com a Inserção de Bits (opção 2).


# Alunos

André Filipe da Conceição - 15/0005547

Gabriel Matheus - 17/0103498

Guilherme Braga - 17/0162290


# Link para o repositório do programa no Github

https://github.com/gui1080/TR1_Trabalho_Camada_de_Enlace

(repositório privado no momento da entrega)
