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

  // coloca o enquadramento
  CamadadeEnlaceTransmissoraEnquadramento(quadro);

  // manda para a camada física transmissora mandar a mensagem com enquadramento
  CamadaFisicaTransmissora(quadro);

}

void CamadadeEnlaceTransmissoraEnquadramento(int quadro[]){

  cout << "\033[1;35mCamada Enlace Transmissora ENQUADRAMENTO\n \033[0m\n";

  int tipoDeEnquadramento = ENQUADRAMENTO;

  int *quadroEnquadrado;
  int i, size;

  switch(tipoDeEnquadramento){
    case 0:
    quadroEnquadrado = CamadaDeEnlaceTransmissoraEnquadramentoContagemDeCaracteres(quadro);

    size = find_size(quadroEnquadrado);
    for(i = 0; i < size; i++){
      printf("%d", quadroEnquadrado[i]);
    }
    printf("\n");
    break;

    case 1:
    //quadroEnquadrado = CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBytes(quadro);
    break;

    case 2:
    //quadroEnquadrado = CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBits(quadro);
    break;

  }


}

int *CamadaDeEnlaceTransmissoraEnquadramentoContagemDeCaracteres(int quadro[]){

  int i, j, x = 0;
  int cont = 0;
  int i_aux = 0;
  int tamanho_fluxo;
  int size = find_size(quadro);
  int tam_quadro = 5;
  int cinco_binario[8] = {0,0,0,0,0,1,0,1};
  int quatro_binario[8] = {0,0,0,0,0,1,0,0};
  int tres_binario[8] = {0,0,0,0,0,0,1,1};
  int dois_binario[8] = {0,0,0,0,0,0,1,0};
  int um_binario[8] = {0,0,0,0,0,0,0,1};
  int num_quadros = (size/((tam_quadro -1)*8));
  int resto = (size%((tam_quadro -1)*8));

  for(i = 0; i < size; i++){
    printf("%d", quadro[i]);
  }
  printf("\n");

  if( resto == 0){

    tamanho_fluxo = size + (8 * num_quadros);

  } else {

    tamanho_fluxo = size + (8 * num_quadros) + 8;

  }

  int *fluxoCodificado;
  fluxoCodificado = new (nothrow) int[tamanho_fluxo];

  if(resto == 0){

    i = 0;
    x = 0;
    while(i < tamanho_fluxo){

      if(x == 0){

        for(j = 0; j < 8; j++){

          fluxoCodificado[j+i] = cinco_binario[j];

        }
        x = 1;
        i = i + 8;

      } else if(x == 1){

        for(cont = 0; cont < 32;  cont++){

          fluxoCodificado[cont+i] = quadro[cont+i_aux];

        }
        i = i+32;
        x = 0;
        i_aux = i_aux + 32;
      }

    }

  } else if((resto != 0) && (num_quadros != 0)) {

    i = 0;
    x = 0;
    int cont_quadr = 0;
    while(i < tamanho_fluxo){

      if(x == 0){

        for(j = 0; j < 8; j++){

          fluxoCodificado[j+i] = cinco_binario[j];

        }
        x = 1;
        cont_quadr++;
        i = i + 8;

      } else if(x == 1){

        for(cont = 0; cont < 32;  cont++){

          fluxoCodificado[cont+i] = quadro[cont+i_aux];

        }
        i = i+32;
        x = 0;
        i_aux = i_aux + 32;
      }
      if(cont_quadr == num_quadros){
        if(resto == 3){

          for(j = 0; j < 8; j++){

            fluxoCodificado[j+i] = quatro_binario[j];

          }
          i = i+8;
          for(cont = 0; cont < 24;  cont++){

            fluxoCodificado[cont+i] = quadro[cont+i_aux];

          }
        }
        if(resto == 2){

          for(j = 0; j < 8; j++){

            fluxoCodificado[j+i] = tres_binario[j];

          }
          i = i+8;
          for(cont = 0; cont < 16;  cont++){

            fluxoCodificado[cont+i] = quadro[cont+i_aux];

          }
        }  if(resto == 1){

            for(j = 0; j < 8; j++){

              fluxoCodificado[j+i] = dois_binario[j];

            }
            i = i+8;
            for(cont = 0; cont < 8;  cont++){

              fluxoCodificado[cont+i] = quadro[cont+i_aux];

            }
          }
      }
    }

  }


  fluxoCodificado[tamanho_fluxo] = 2;

  //int *fluxoCodificado;

  //return fluxoCodificado; // passa a codificação a diante

  return fluxoCodificado;

}

// implementa esses enquadramentos aqui

void CamadaEnlaceDadosReceptora(int quadro[]){

  // tira do enquadramento
  CamadaDeEnlaceReceptoraEnquadramento(quadro);

  // passa adiante para a camada receptora transformar os bits em strings
  CamadaDeAplicacaoReceptora(quadro);

}

void CamadaDeEnlaceReceptoraEnquadramento(int quadro[]){

  printf("\n\nrecepção, enlace\n\n");

  int tipoDeEnquadramento = ENQUADRAMENTO;

  switch(tipoDeEnquadramento){
    case 0:
    //quadroEnquadrado = CamadaDeEnlaceReceptoraEnquadramentoContagemDeCaracteres(quadro);
    break;

    case 1:
    //quadroEnquadrado = CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBytes(quadro);
    break;

    case 2:
    //quadroEnquadrado = CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBits(quadro);
    break;

  }


}

// implementa a retirada dos enquadramentos aqui
