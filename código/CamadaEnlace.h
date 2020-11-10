#include <stdexcept>
#include <iostream>
#include <string>
#include <stdlib.h>


// CODIFICAÇÃO RELATIVA AO TRABALHO 2
// (implementação de camada de enlace)

// https://github.com/gui1080/TR1_Trabalho_Camada_de_Enlace
// (repositório privado na entrega do trabalho)


#define ENQUADRAMENTO 2

// Transmissão
void CamadaEnlaceDadosTransmissora(int* quadro);
int *CamadadeEnlaceTransmissoraEnquadramento(int* quadro);

// Recepção
int *CamadaDeEnlaceReceptoraEnquadramento(int* quadro);
void CamadaEnlaceDadosReceptora(int* quadro);

// Codificação
int *CamadaDeEnlaceTransmissoraEnquadramentoContagemDeCaracteres(int *quadro);
int *CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBytes(int *quadro);
int *CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBits(int *quadro);

// Decodificação
int *CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBytes(int *quadro);
int *CamadaDeEnlaceReceptoraEnquadramentoContagemDeCaracteres(int *quadro);
int *CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBits(int *quadro);
