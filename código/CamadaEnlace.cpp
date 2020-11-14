#include <string>
using namespace std;

#include <stdexcept>
#include <iostream>
#include <bits/stdc++.h>
#include <bitset>
#include <stdlib.h>
#include <array>
#include <cmath>

#include "CamadaFisica.h"
#include "CamadaEnlace.h"

// CODIFICAÇÃO RELATIVA AO TRABALHO 2
// (implementação de camada de enlace)

// https://github.com/gui1080/TR1_Trabalho_Camada_de_Enlace
// (repositório privado na entrega do trabalho)

// TRANSMISSÃO
//-----------------------------------------------------

void CamadaEnlaceDadosTransmissora(int quadro[])
{
  // se recebe o fluxo bruto da string transformada em um vetor de 0 e 1
  cout << "\033[1;34mCamada de Enlace de dados Transmissora\033[0m\n";

  int i;
  int size = find_size(quadro);
  for (i = 0; i < size; i++)
  {
    cout << quadro[i];
  }
  cout << endl
       << endl;

  int *quadro_novo;
  // coloca o enquadramento
  quadro_novo = CamadadeEnlaceTransmissoraEnquadramento(quadro);

  // manda para a camada física transmissora mandar a mensagem com enquadramento
  CamadaFisicaTransmissora(quadro_novo);
}

int *CamadadeEnlaceTransmissoraEnquadramento(int quadro[])
{

  cout << "\033[1;35mCamada Enlace Transmissora ENQUADRAMENTO\n \033[0m\n";

  // se escolhe o tipo de enquadramento
  int tipoDeEnquadramento = ENQUADRAMENTO;

  int *quadroEnquadrado;
  int i, size;

  // se enquadra o fluxo de bits passado
  switch (tipoDeEnquadramento)
  {
  case 0:
    quadroEnquadrado = CamadaDeEnlaceTransmissoraEnquadramentoContagemDeCaracteres(quadro);

    printf("\n quadro enquadrado eae\n");

    size = find_size(quadroEnquadrado);
    for (i = 0; i < size; i++)
    {
      printf("%d", quadroEnquadrado[i]);
    }
    printf("\n");

    break;

  case 1:
    quadroEnquadrado = CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBytes(quadro);

    break;

  case 2:
    quadroEnquadrado = CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBits(quadro);

    printf("\n quadro enquadrado eae\n");

    size = find_size(quadroEnquadrado);
    for (i = 0; i < size; i++)
    {
      printf("%d", quadroEnquadrado[i]);
    }
    printf("\n");

    break;
  }

  // retornamos o fluxo de bits enquadrado
  return quadroEnquadrado;
}

// Enquadramentos
//-----------------------------------------------------

int *CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBits(int quadro[])
{

  // flag 011111110

  printf("\nINSERINDO FLAG\n\n");

  int size = find_size(quadro);

  printf("\nquadro:\n");
  for (int zap = 0; zap < size; zap++)
  {
    printf("%d", quadro[zap]);
  }
  printf("\n");

  int tamanho_fluxo;

  int flag[8] = {0, 1, 1, 1, 1, 1, 1, 0};

  int divisao = ((size / 40)); // quantidade de grupos inteiros que se forma com o numero de bits passado
  int resto = ((size % 40) / 8); // qntd de bytes que tem q entrar

  /*
  if(size < 40){

    tamanho_fluxo = (size + 16) + 1;

  }else if(resto == 0){

    tamanho_fluxo = (size + (size/40) * 16) + divisao;

  }else{
    tamanho_fluxo = size + (((size/40) * 16) + 16) + divisao;
  }
*/
// 01111110 0011111 0 10011111 0 1 01111110
//          0011111   10011111   1


  int quantidade_total_quadros;

  if (resto == 0)
  {
    quantidade_total_quadros = (size / 40);
  }
  else
  {
    quantidade_total_quadros = (size / 40) + 1; // o mais 1 indica que não teremos um quadro com o tamanho inteiro como os outros
  }

  printf("tamanho do fluxo: %d / resto: %d\n / quantidade de coiso: %d / divisao: %d\n", tamanho_fluxo, resto, quantidade_total_quadros, divisao);

  int *fluxoCodificado;
  int tam_bits_adicionais = (quantidade_total_quadros * 16) + ((quantidade_total_quadros)*5) + resto;
  tamanho_fluxo = size + tam_bits_adicionais;
  fluxoCodificado = new (nothrow) int[tamanho_fluxo];

  // o vetor auxiliar irá indicar a quantidade de bits que entra no grupo que se está passando
  // do fluxo não enquadrado para o fluxo enquadrado
  int *vetor_aux;
  vetor_aux = new (nothrow) int[quantidade_total_quadros];

  int i, i_aux, x, y;

  for (x = 0; x < quantidade_total_quadros; x++)
  {
    if ((x == quantidade_total_quadros - 1) && (resto != 0))
    {

      vetor_aux[x] = resto;

    }
    else
    {

      vetor_aux[x] = 5;

    }
  }

  printf("\n\nAUX:");
  for (x = 0; x < quantidade_total_quadros; x++)
  {
    printf("%d", vetor_aux[x]);
  }
  printf("\n");

  i = 0;
  i_aux = 0;
  int k = 0;
  int cont_um = 0;

  // øøøø

  while (i < size)
  {

    // copia a flag
    for (x = 0; x < 8; x++)
    {
      fluxoCodificado[i_aux + x] = flag[x];
    }

    i_aux = i_aux + 8;

    // se aloca a quantidade de bits certa dependendo do que o vetor auxiliar indica
    for (y = 0; y < (vetor_aux[k] * 8); y++)
    {

      if( y == 4){
      if ((quadro[i + y] == 1) && (quadro[i + y - 1] == 1) && (quadro[i + y - 2] == 1) && (quadro[i + y - 3] == 1) && (quadro[i + y - 4] == 1))
        {
          // caso ocorra uma sequencia grande de 1's, se adiciona um zero        
          fluxoCodificado[i_aux + y] = 0;
          i_aux++;
        }
      }
      fluxoCodificado[i_aux + y] = quadro[i + y];
    }

    // atualizamos de acordo as variaveis que irão iterar por cada vetor
    cont_um = 0;
    i = i + (vetor_aux[k] * 8);
    i_aux = i_aux + (vetor_aux[k] * 8);

    // coloca a flag denovo delimitando este grupo
    for (x = 0; x < 8; x++)
    {

      fluxoCodificado[i_aux + x] = flag[x];
    }

    i_aux = i_aux + 8;

    k++;
  }

  printf("\nresultado kkkk:\n");

  for (x = 0; x < tamanho_fluxo; x++)
  {

    printf("%d", fluxoCodificado[x]);
  }

  printf("\n\n");
  printf("tamanho_fluxo: %d\n", tamanho_fluxo);
  printf("i: %d\n", i_aux);

  //zona de testes
  //         0011111  1001111110011111100111111001111110011111100111111
  //01111110 00111110 1001111101001111101001111101001111101011111100111111000111110100111110101111110

  // 01111110 0011111 0 10011111 0 10011111 0 10011111 0 10011111 0 1 01111110
  //          0011111   10011111   10011111   10011111   10011111   1


  // se passa adiante o fluxo com o tamanho correto

  fluxoCodificado[i_aux] = 2;

  int *FluxoLegal; 

  FluxoLegal = new (nothrow) int[i_aux];

  for(int f = 0; f < i_aux ; f++){
    FluxoLegal[f] = fluxoCodificado[f];  
  }

  FluxoLegal[i_aux] = 2; 

  return FluxoLegal;
}

int *CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBytes(int quadro[])
{

  // flag 00001111

  printf("\nINSERINDO FLAG\n\n");

  int size = find_size(quadro);

  printf("\nquadro:\n");
  for (int zap = 0; zap < size; zap++)
  {
    printf("%d", quadro[zap]);
  }
  printf("\n");

  int tamanho_fluxo;

  int flag[8] = {0, 0, 0, 0, 1, 1, 1, 1};

  int resto = ((size % 40) / 8); // qntd de bytes que tem q entrar

  // se aloca o novo tamanho do bloco de mensagem dependendo da
  // quantidade de grupos que se aloca em um tamanho certo entre as flags

  if (size < 40)
  {

    tamanho_fluxo = size + 16;
  }
  else if (resto == 0)
  {

    tamanho_fluxo = size + (size / 40) * 16;
  }
  else
  {
    tamanho_fluxo = size + (((size / 40) * 16) + 16);
  }

  int quantidade_total_quadros;

  if (resto == 0)
  {
    quantidade_total_quadros = (size / 40);
  }
  else
  {
    quantidade_total_quadros = (size / 40) + 1;
  }

  printf("tamanho do fluxo: %d / resto: %d\n / quantidade de coiso: %d", tamanho_fluxo, resto, quantidade_total_quadros);

  int *fluxoCodificado;
  fluxoCodificado = new (nothrow) int[tamanho_fluxo];


  // o vetor auxiliar irá indicar a quantidade de bits que entra no grupo que se está passando
  // do fluxo não enquadrado para o fluxo enquadrado
  int *vetor_aux;
  vetor_aux = new (nothrow) int[quantidade_total_quadros];

  int i, i_aux, x, y;

  for (x = 0; x < quantidade_total_quadros; x++)
  {
    if ((x == quantidade_total_quadros - 1) && (resto != 0))
    {

      vetor_aux[x] = resto;
    }
    else
    {

      vetor_aux[x] = 5;
    }
  }

  printf("\n\nAUX:");
  for (x = 0; x < quantidade_total_quadros; x++)
  {
    printf("%d", vetor_aux[x]);
  }

  i = 0;
  i_aux = 0;
  int k = 0;

  while (i < tamanho_fluxo)
  {

    // se coloca a flag no começo do grupo de bits
    for (x = 0; x < 8; x++)
    {

      fluxoCodificado[i + x] = flag[x];
    }

    i = i + 8;

    // se coloca a quantidade correta de bits dentro do fluxo enquadrado
    // de acordo com o vetor auxiliar
    for (y = 0; y < (vetor_aux[k] * 8); y++)
    {

      fluxoCodificado[i + y] = quadro[i_aux + y];
    
    }

    // atualizamos de acordo as variaveis que irão iterar por cada vetor
    i = i + (vetor_aux[k] * 8);
    i_aux = i_aux + (vetor_aux[k] * 8);

    // se bota a flag novamente delimitando tamanho
    for (x = 0; x < 8; x++)
    {

      fluxoCodificado[i + x] = flag[x];
    }

    i = i + 8;

    k++;
  }

  printf("\nresultado kkkk:\n");

  for (x = 0; x < tamanho_fluxo; x++)
  {

    printf("%d", fluxoCodificado[x]);
  }

  printf("\n\n");

  // se determina o final e passa adiante o fluxo enquadrado

  fluxoCodificado[tamanho_fluxo] = 2;

  return fluxoCodificado;
}

int *CamadaDeEnlaceTransmissoraEnquadramentoContagemDeCaracteres(int quadro[])
{

  int i, j, x = 0;
  int cont = 0;
  int i_aux = 0;
  int tamanho_fluxo;
  int size = find_size(quadro);
  int tam_quadro = 4;

  int quatro_binario[8] = {0, 0, 0, 0, 0, 1, 0, 0};
  int tres_binario[8] = {0, 0, 0, 0, 0, 0, 1, 1};
  int dois_binario[8] = {0, 0, 0, 0, 0, 0, 1, 0};

  int num_quadros = (size / ((tam_quadro - 1) * 8));
  int resto = ((size % ((tam_quadro - 1) * 8)) / 8);

  for (i = 0; i < size; i++)
  {
    printf("%d", quadro[i]);
  }
  printf("\n");

  if (resto == 0)
  {

    tamanho_fluxo = (size + (8 * num_quadros));
  }
  else
  {

    tamanho_fluxo = ((size) + (8 * (num_quadros + 1)));
  }

  printf("\n\ntamanho de fluxo: %d\n\n", tamanho_fluxo);

  int *fluxoCodificado;
  fluxoCodificado = new (nothrow) int[tamanho_fluxo];

  printf("\n\nresto: %d\n\n", resto);
  printf("\n\n num de quadros: %d\n\n", num_quadros);

  int quantidade_total_quadros;

  // se aloca a quantidade total de quadros para se determinar quantos grupos de tamanho especifico podem ser criados
  // para que então se faça um grupo com o resto

  if (resto == 0)
  {
    quantidade_total_quadros = (size / 24);
  }
  else
  {
    quantidade_total_quadros = (size / 24) + 1;
  }

  // o vetor auxiliar irá indicar a quantidade de bits que entra no grupo que se está passando
  // do fluxo não enquadrado para o fluxo enquadrado

  int *aux;
  aux = new (nothrow) int[quantidade_total_quadros];

  for (x = 0; x < quantidade_total_quadros; x++)
  {
    if ((x == quantidade_total_quadros - 1) && (resto != 0))
    {

      aux[x] = resto;
    }
    else
    {

      aux[x] = 3;
    }
  }

  printf("\n\nAUX:");
  for (x = 0; x < quantidade_total_quadros; x++)
  {
    printf("%d", aux[x]);
  }
  printf("\n");

  int k = 0;

  i = 0;
  x = 0;
  while (i < tamanho_fluxo)
  {

    // se coloca a "flag", nesse caso
    // o tamanho do bloco que se esta colocando em um quadro

    if (x == 0)
    {

      if (aux[k] == 3)
      {

        for (j = 0; j < 8; j++)
        {

          fluxoCodificado[j + i] = quatro_binario[j];
        }
      }
      if (aux[k] == 2)
      {

        for (j = 0; j < 8; j++)
        {

          fluxoCodificado[j + i] = tres_binario[j];
        }
      }

      if (aux[k] == 1)
      {

        for (j = 0; j < 8; j++)
        {

          fluxoCodificado[j + i] = dois_binario[j];
        }
      }

      x = 1;
      i = i + 8;
    }

    // dependendo do tamanho, se coloca a quantidade de bits certa na mensagem

    if (x == 1)
    {

      for (cont = 0; cont < (aux[k] * 8); cont++)
      {

        fluxoCodificado[cont + i] = quadro[cont + i_aux];
      }
      // atualizamos de acordo as variaveis que irão iterar por cada vetor
      i = i + (aux[k] * 8);
      x = 0; // a variavel x acaba fazendo com que os dois ifs neste loop se alternem
      i_aux = i_aux + (aux[k] * 8);
    }

    k++;
  }

  // 00000100 011010000110000101110100 00000100 011100110111010101101110 00000010 01100101
  //          011010000110000101110100          011100110111010101101110          01100101

  printf("RESULTADO AQUIIIIIII :)\n\n");

  for (x = 0; x < tamanho_fluxo; x++)
  {

    printf("%d", fluxoCodificado[x]);
  }

  // se delimita o final e passa o fluxo correto adiante

  fluxoCodificado[tamanho_fluxo] = 2;

  //int *fluxoCodificado;

  //return fluxoCodificado; // passa a codificação a diante

  return fluxoCodificado;
}

// RECEPÇÃO
//-----------------------------------------------------

void CamadaEnlaceDadosReceptora(int quadro[])
{

  printf("\n é pra ir agr! \n\n"); 

  int i = find_size(quadro);

  int *quadro_novo;

  quadro_novo = new (nothrow) int[i];

  // tira do enquadramento
  quadro_novo = CamadaDeEnlaceReceptoraEnquadramento(quadro);

  printf("\n eae, aqui o quadro:\n");
  for(int x = 0; x < i; x++){
    printf("%d", quadro_novo[x]); 
  }
  printf("\n\n");

  int *quadroFinal;
  int l = find_size(quadro_novo);

  quadroFinal = new (nothrow) int[l];

  for(int x = 0; x<l; x++){
    quadroFinal[x] = quadro_novo[x]; 
  }
  quadroFinal[l] = 2; 

  printf("\n eae, aqui o quadro legal:\n");
  for(int x = 0; x < l ; x++){
    printf("%d", quadroFinal[x]); 
  }
  printf("\n\n");

  // passa adiante para a camada receptora transformar os bits em strings
  CamadaDeAplicacaoReceptora(quadroFinal);
}

int *CamadaDeEnlaceReceptoraEnquadramento(int quadro[])
{

  printf("\n\nrecepção, enlace\n\n");

  // aqui se escolhe o tipo de enquadramento que se deseja retirar
  int tipoDeEnquadramento = ENQUADRAMENTO;

  int *quadroDesenquadrado;

  int i = find_size(quadro);

  quadroDesenquadrado = new (nothrow) int[i];
  int *quadroFinal;

  // desenquadramos de acordo com a abordagem escolhida
  switch (tipoDeEnquadramento)
  {
  case 0:

    printf("passeando pela recepção enlace :)");

    quadroDesenquadrado = CamadaDeEnlaceReceptoraEnquadramentoContagemDeCaracteres(quadro);

    break;

  case 1:

    quadroDesenquadrado = CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBytes(quadro);
    //
    break;

  case 2:

    quadroDesenquadrado = CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBits(quadro);
    //
    int l = find_size(quadroDesenquadrado); 

    printf("\n\n velho: %d novo: %d\n\n", i, l); 

    break;
  }

  // passa o quadro pronto adiante
  return quadroDesenquadrado;
}

// Desenquadramentos
//-----------------------------------------------------

int *CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBits(int quadro[])
{
  int size = find_size(quadro);

  printf("Quadro dentro da funcao: ");
  for (int pop = 0; pop < size; pop++){
      printf("%d", quadro[pop]);
  }
  printf("\n");
  

  // flag 01111110

  int i = 0;
  int x = 0;
  int i_aux = 0;
  int y = 0;
  int cont_um = 0;

  int aux[8];

  int *FluxoFinal;
  FluxoFinal = new (nothrow) int[size];

  while (i < size)
  {
    
    // se analisa de 8 em 8 bits atrás da flag
    for (x = 0; x < 8; x++)
    {

      aux[x] = quadro[x + i];
    }

    if ((aux[0] == 0) && (aux[1] == 1) && (aux[2] == 1) && (aux[3] == 1) && (aux[4] == 1) && (aux[5] == 1) && (aux[6] == 1) && (aux[7] == 0))
    {

      // é flag
      
    }
    else
    {

      // se busca sequencias de 1, para que o zero da sequencia seja descartado
      if (quadro[i] == 1 && quadro[i - 1] == 1)
      {
        cont_um++;
      }
      else
      {
        cont_um = 0;
      }

      if (cont_um == 4 && quadro[i] == 0)
      {
        i++;
      }

      FluxoFinal[i_aux] = quadro[i];

      // copia o que é mensagem para o fluxo, 
      // jogando flags fora
      for (x = 0; x < 8; x++)
      {

        FluxoFinal[x + i_aux] = aux[x];
      }

      // atualizamos de acordo as variaveis que irão iterar por cada vetor
      i_aux = i_aux + 8;
    }

    i = i + 8;
  }

  printf("\n\nresultado do q fizemos:\n\n");
  for (x = 0; x < i_aux; x++)
  {
    printf("%d", FluxoFinal[x]);
  }
  printf("\n\n");

  FluxoFinal[i_aux] = 2;

  printf("Resposta ultimo: ");
  
  // 00111111111111000011110000111111001111000000001100111100000011000011111100001100001111001100001100111111111111000011111111111100 001111000011001100111100111100000011111111111100 - ultimo
  // 0111111001100111011000010110001001110010011010010111111001111110011001010110110001111110 - eae

  for (i = 0; i < i_aux; i++)
  {
    printf("%d", FluxoFinal[i]);
  }
  
  printf("\n");

  // passa o resultado adiante
  return FluxoFinal;
}

int *CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBytes(int quadro[])
{

  int size = find_size(quadro);

  int i = 0;
  int x = 0;
  int i_aux = 0;

  int aux[8];

  int *FluxoFinal;
  FluxoFinal = new (nothrow) int[size];

  while (i < size)
  {

    // se faz a análise de 8 em 8 bits
    for (x = 0; x < 8; x++)
    {

      aux[x] = quadro[x + i];
    }

    // buscamos a flag
    if ((aux[0] == 0) && (aux[1] == 0) && (aux[2] == 0) && (aux[3] == 0) && (aux[4] == 1) && (aux[5] == 1) && (aux[6] == 1) && (aux[7] == 1))
    {

      // é flag
    }
    else
    {
      // se não é a flag, podemos copiar os bits para o resultado final
      for (x = 0; x < 8; x++)
      {

        FluxoFinal[x + i_aux] = aux[x];
      }

      // atualizamos de acordo as variaveis que irão iterar por cada vetor

      i_aux = i_aux + 8;
    }

    i = i + 8;
  }

  printf("\n\nresultado do q fizemos:\n\n");
  for (x = 0; x < i_aux; x++)
  {
    printf("%d", FluxoFinal[x]);
  }
  printf("\n\n");

  // delimitamos um final e passamos o fluxo adiante

  FluxoFinal[size] = 2;

  return FluxoFinal;
}

int *CamadaDeEnlaceReceptoraEnquadramentoContagemDeCaracteres(int quadro[])
{

  int size = find_size(quadro);

  int i = 0;
  int x = 0;
  int i_aux = 0;

  int aux[8];

  int k = 0;

  int *FluxoFinal;
  FluxoFinal = new (nothrow) int[size];

  while (i < size)
  {

    // pegamos os primeiros 8 bits

    for (x = 0; x < 8; x++)
    {

      aux[x] = quadro[i + x];
    }

    // atualizamos em qual posição estamos no quadro

    i = i + 8;

    // definimos qual o tamanho do bloco que vai para o fluxo final

    if ((k == 0))
    {
      if ((aux[0] == 0) && (aux[1] == 0) && (aux[2] == 0) && (aux[3] == 0) && (aux[4] == 0) && (aux[5] == 1) && (aux[6] == 0) && (aux[7] == 0))
      {

        // é o cabeçalho de um quadro completo

        k = 3;
      }

      if ((aux[0] == 0) && (aux[1] == 0) && (aux[2] == 0) && (aux[3] == 0) && (aux[4] == 0) && (aux[5] == 0) && (aux[6] == 1) && (aux[7] == 1))
      {

        // restam 2 bytes para passarmos

        k = 2;
      }

      if ((aux[0] == 0) && (aux[1] == 0) && (aux[2] == 0) && (aux[3] == 0) && (aux[4] == 0) && (aux[5] == 0) && (aux[6] == 1) && (aux[7] == 0))
      {

        // resta 1 byte para passar

        k = 1;
      }
    }

    // copia a "k" quantidade de bytes pro fluxo

    for (x = 0; x < (8 * k); x++)
    {

      FluxoFinal[x + i_aux] = quadro[x + i];
    }

    // atualiza a posição que estamos no quadro e no fluxo final

    i_aux = i_aux + (8 * k);
    i = i + (8 * k);

    k = 0;

    // dps o fluxo final tem um tamanho igual a i_aux

    // para cada (k*8) posições q o fluxo final anda, o quadro anda (k*8 + 8),jogando o header fora
  }

  printf("\n\nresultado do q fizemos (retirando header):\n\n");

  for (x = 0; x < i_aux; x++)
  {

    printf("%d", FluxoFinal[x]);
  }

  printf("\n\n");

  // delimitamos o final e passamos o fluxo adiante

  FluxoFinal[i_aux] = 2;

  return FluxoFinal;
}

//-----------------------------------------------------