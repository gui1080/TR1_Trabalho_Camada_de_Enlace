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

    // coloca o enquadramento
    CamadadeEnlaceTransmissoraEnquadramento(quadro); 

    // manda para a camada física transmissora mandar a mensagem com enquadramento
    CamadaFisicaTransmissora(quadro); 

}

void CamadadeEnlaceTransmissoraEnquadramento(int quadro[]){

    printf("\n\ntransmissão, enlace\n\n"); 

    int tipoDeEnquadramento = ENQUADRAMENTO; 

    switch(tipoDeEnquadramento){
        case 0:
            //quadroEnquadrado = CamadaDeEnlaceTransmissoraEnquadramentoContagemDeCaracteres(quadro); 
            break; 

        case 1:
            //quadroEnquadrado = CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBytes(quadro); 
            break; 
            
        case 2:
            //quadroEnquadrado = CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBits(quadro); 
            break; 
    
    }


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