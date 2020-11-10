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

void CamadaEnlaceDadosTransmissora (int quadro[]){
  // se recebe o fluxo bruto da string transformada em um vetor de 0 e 1
  cout << "\033[1;34mCamada de Enlace de dados Transmissora\033[0m\n";

  int i;
  int size = find_size(quadro);
  for (i = 0; i < size; i++)
  {
    cout << quadro[i];
  }
  cout << endl << endl;


  int *quadro_novo; 
  // coloca o enquadramento
  quadro_novo = CamadadeEnlaceTransmissoraEnquadramento(quadro);

  // manda para a camada física transmissora mandar a mensagem com enquadramento
  CamadaFisicaTransmissora(quadro_novo);

}

int *CamadadeEnlaceTransmissoraEnquadramento(int quadro[]){

  cout << "\033[1;35mCamada Enlace Transmissora ENQUADRAMENTO\n \033[0m\n";

  int tipoDeEnquadramento = ENQUADRAMENTO;

  int *quadroEnquadrado;
  int i, size;

  switch(tipoDeEnquadramento){
    case 0:
    quadroEnquadrado = CamadaDeEnlaceTransmissoraEnquadramentoContagemDeCaracteres(quadro); 

    printf("\n quadro enquadrado eae\n"); 

    size = find_size(quadroEnquadrado);
    for(i = 0; i < size; i++){
      printf("%d", quadroEnquadrado[i]);
    }
    printf("\n");
    break;

    case 1:
    quadroEnquadrado = CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBytes(quadro);
    
    break;

    case 2:
    //quadroEnquadrado = CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBits(quadro);
    break;

  }

  return quadroEnquadrado; 


}

int *CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBytes(int quadro[]){

  // flag 00001111

  printf("\nINSERINDO FLAG\n\n"); 

  int size = find_size(quadro);


  printf("\nquadro:\n"); 
  for(int zap = 0; zap < size ; zap++){
    printf("%d", quadro[zap]); 
  }
  printf("\n");

  int tamanho_fluxo;

  int flag[8] = {0,0,0,0,1,1,1,1};

  int resto = ((size % 40)/8); // qntd de bytes que tem q entrar 

  if(size < 40){
    
    tamanho_fluxo = size + 16; 
  
  }else if(resto == 0){

    tamanho_fluxo = size + (size/40) * 16; 
  
  }else{
    tamanho_fluxo = size + (((size/40) * 16) + 16);
  }

  int quantidade_total_quadros;
  
  if(resto == 0){
    quantidade_total_quadros = (size/40); 
  }
  else{
    quantidade_total_quadros = (size/40) + 1;
  }

  printf("tamanho do fluxo: %d / resto: %d\n / quantidade de coiso: %d", tamanho_fluxo, resto, quantidade_total_quadros); 

  int *fluxoCodificado;
  fluxoCodificado = new (nothrow) int[tamanho_fluxo];

  int *vetor_aux; 
  vetor_aux = new (nothrow) int[quantidade_total_quadros];

  int i, i_aux, x, y; 


  for(x = 0 ; x < quantidade_total_quadros ; x++){
    if((x == quantidade_total_quadros - 1) && (resto != 0)){

      vetor_aux[x] = resto; 

    }else{

      vetor_aux[x] = 5; 
    
    }
    
  }

  printf("\n\nAUX:"); 
  for(x = 0 ; x < quantidade_total_quadros ; x++){
    printf("%d", vetor_aux[x]); 
  }

  i = 0; 
  i_aux = 0; 
  int k = 0; 

  while(i < tamanho_fluxo){

    for(x = 0; x < 8 ; x++){

      fluxoCodificado[i+x] = flag[x]; 
    
    }

    i = i + 8; 

    for(y = 0; y < (vetor_aux[k] * 8) ; y++){

      fluxoCodificado[i + y] = quadro[i_aux + y]; 
    
    }

    i = i + (vetor_aux[k] * 8);
    i_aux = i_aux + (vetor_aux[k] * 8);  

    for(x = 0; x < 8 ; x++){

      fluxoCodificado[i+x] = flag[x]; 
    
    }

    i = i + 8;

     k++; 

  }

  printf("\nresultado kkkk:\n"); 

  for(x = 0; x < tamanho_fluxo ; x++){

    printf("%d", fluxoCodificado[x]); 
    
  }

  printf("\n\n");


  fluxoCodificado[tamanho_fluxo] = 2; 

  return fluxoCodificado;

}

int *CamadaDeEnlaceTransmissoraEnquadramentoContagemDeCaracteres(int quadro[]){

  int i, j, x = 0;
  int cont = 0;
  int i_aux = 0;
  int tamanho_fluxo;
  int size = find_size(quadro);
  int tam_quadro = 4;

  int quatro_binario[8] = {0,0,0,0,0,1,0,0};
  int tres_binario[8] =   {0,0,0,0,0,0,1,1};
  int dois_binario[8] =   {0,0,0,0,0,0,1,0};

  int num_quadros = (size/((tam_quadro -1)*8));
  int resto = ((size%((tam_quadro -1)*8))/8);

  for(i = 0; i < size; i++){
    printf("%d", quadro[i]);
  }
  printf("\n");

  if( resto == 0){

    tamanho_fluxo = (size + (8 * num_quadros));

  } else {

    tamanho_fluxo = ((size) + (8 * (num_quadros + 1) ));

  }

  printf("\n\ntamanho de fluxo: %d\n\n", tamanho_fluxo); 

  int *fluxoCodificado;
  fluxoCodificado = new (nothrow) int[tamanho_fluxo];

  printf("\n\nresto: %d\n\n", resto); 
  printf("\n\n num de quadros: %d\n\n", num_quadros); 

  int quantidade_total_quadros;
  
  if(resto == 0){
    quantidade_total_quadros = (size/24); 
  }
  else{
    quantidade_total_quadros = (size/24) + 1;
  }

  int *aux; 
  aux = new (nothrow) int[quantidade_total_quadros];

  for(x = 0 ; x < quantidade_total_quadros ; x++){
    if((x == quantidade_total_quadros - 1) && (resto != 0)){

      aux[x] = resto; 

    }else{

      aux[x] = 3; 
    
    }
    
  }

  printf("\n\nAUX:"); 
  for(x = 0 ; x < quantidade_total_quadros ; x++){
    printf("%d", aux[x]); 
  }
  printf("\n"); 

  int k = 0; 

    i = 0;
    x = 0;
    while(i < tamanho_fluxo){

      if(x == 0){

        if(aux[k] == 3){

          for(j = 0; j < 8; j++){

            fluxoCodificado[j+i] = quatro_binario[j];

          }

        }
        if(aux[k] == 2){

          for(j = 0; j < 8; j++){

            fluxoCodificado[j+i] = tres_binario[j];

          }

        }

        if(aux[k] == 1){

          for(j = 0; j < 8; j++){

            fluxoCodificado[j+i] = dois_binario[j];

          }

        }

        x = 1;
        i = i + 8;

      } 
      if(x == 1){

        for(cont = 0; cont < (aux[k]*8) ;  cont++){

          fluxoCodificado[cont+i] = quadro[cont+i_aux];

        }
        i = i+(aux[k]*8);
        x = 0;
        i_aux = i_aux + (aux[k]*8);

      }

      k++; 
      
    }
  

// 00000100 011010000110000101110100 00000100 011100110111010101101110 00000010 01100101
//          011010000110000101110100          011100110111010101101110          01100101


  printf("RESULTADO AQUIIIIIII :)\n\n"); 

  for(x=0; x < tamanho_fluxo ; x++){

    printf("%d", fluxoCodificado[x]);

  } 


  fluxoCodificado[tamanho_fluxo] = 2;

  //int *fluxoCodificado;

  //return fluxoCodificado; // passa a codificação a diante

  return fluxoCodificado;

}

// implementa esses enquadramentos aqui

void CamadaEnlaceDadosReceptora(int quadro[]){

  int *quadro_novo; 

  // tira do enquadramento
  quadro_novo = CamadaDeEnlaceReceptoraEnquadramento(quadro);

  // passa adiante para a camada receptora transformar os bits em strings
  CamadaDeAplicacaoReceptora(quadro_novo);

}

int *CamadaDeEnlaceReceptoraEnquadramento(int quadro[]){

  printf("\n\nrecepção, enlace\n\n");

  int tipoDeEnquadramento = ENQUADRAMENTO;

  int *quadroEnquadrado;

  switch(tipoDeEnquadramento){
    case 0:

    printf("passeando pela recepção enlace :)");

    quadroEnquadrado = CamadaDeEnlaceReceptoraEnquadramentoContagemDeCaracteres(quadro);
    break;

    case 1:
    quadroEnquadrado = CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBytes(quadro);
    break;

    case 2:
    //quadroEnquadrado = CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBits(quadro);
    break;

  }

  return quadroEnquadrado; 


}

// implementa a retirada dos enquadramentos aqui

int *CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBytes(int quadro[]){

  int size = find_size(quadro);
  // flag 00001111
  
  int i = 0;
  int x = 0; 
  int i_aux = 0; 


  int aux[8]; 

  int *FluxoFinal;
  FluxoFinal = new (nothrow) int[size];

  while(i < size){

    for(x = 0; x < 8 ; x++){

      aux[x] = quadro[x + i]; 

    }


    if( (aux[0] == 0) && (aux[1] == 0) && (aux[2] == 0) && (aux[3] == 0)
        && (aux[4] == 1) && (aux[5] == 1) && (aux[6] == 1) && (aux[7] == 1)){

          // é flag

    }  else{

      for(x = 0; x < 8 ; x++){

        FluxoFinal[x + i_aux] = aux[x]; 

      }

      i_aux = i_aux + 8; 

    }


    i = i + 8; 

  }
  
  printf("\n\nresultado do q fizemos:\n\n");
  for(x = 0; x< i_aux; x++){
    printf("%d", FluxoFinal[x]); 
  }
  printf("\n\n");

  FluxoFinal[size] = 2;

  return FluxoFinal; 
}

int *CamadaDeEnlaceReceptoraEnquadramentoContagemDeCaracteres(int quadro[]){


  int size = find_size(quadro);
  
  int i = 0;
  int x = 0; 
  int i_aux = 0; 


  int aux[8]; 

  int k = 0; 

  int *FluxoFinal;
  FluxoFinal = new (nothrow) int[size];

  while(i < size){

    // pegamos os primeiros 8 bits

    for(x = 0; x < 8 ; x++){

      aux[x] = quadro[i + x]; 

    }

    // atualizamos em qual posição estamos no quadro

    i = i + 8;

    // definimos qual o tamanho do bloco que vai para o fluxo final

    if((k == 0)){
      if( (aux[0] == 0) && (aux[1] == 0) && (aux[2] == 0) && (aux[3] == 0)
          && (aux[4] == 0) && (aux[5] == 1) && (aux[6] == 0) && (aux[7] == 0)){

        // é o cabeçalho de um quadro completo

        k = 3; 

      }

      if((aux[0] == 0) && (aux[1] == 0) && (aux[2] == 0) && (aux[3] == 0)
          && (aux[4] == 0) && (aux[5] == 0) && (aux[6] == 1) && (aux[7] == 1)){

        // restam 2 bytes para passarmos

        k = 2; 

      }

      if((aux[0] == 0) && (aux[1] == 0) && (aux[2] == 0) && (aux[3] == 0)
          && (aux[4] == 0) && (aux[5] == 0) && (aux[6] == 1) && (aux[7] == 0)){

        // resta 1 byte para passar

        k = 1; 

      }

    }

    // copia a "k" quantidade de bytes pro fluxo

    for(x = 0; x < (8*k) ; x++){

        FluxoFinal[x + i_aux] = quadro[x + i]; 

    }

    // atualiza a posição que estamos no quadro e no fluxo final

    i_aux = i_aux + (8*k); 
    i = i + (8*k);

    k = 0; 

    // dps o fluxo final tem um tamanho igual a i_aux

    // para cada (k*8) posições q o fluxo final anda, o quadro anda (k*8 + 8),jogando o header fora

  }
  
  printf("\n\nresultado do q fizemos (inserindo header):\n\n");
  
  for(x = 0; x< i_aux; x++){

    printf("%d", FluxoFinal[x]); 
  
  }

  printf("\n\n");

  FluxoFinal[i_aux] = 2;

  return FluxoFinal; 


}