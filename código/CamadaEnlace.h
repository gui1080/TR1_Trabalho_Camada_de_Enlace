#include <stdexcept>
#include <iostream>
#include <string>
#include <stdlib.h>


// CODIFICAÇÃO RELATIVA AO TRABALHO 2
// (implementação de camada de enlace)

// https://github.com/gui1080/TR1_Trabalho_Camada_de_Enlace
// (repositório privado na entrega do trabalho)

//-----------------------------------------------------

#define ENQUADRAMENTO 2
// Enquadramento 0 = Contagem de Caracteres
// Enquadramento 1 = Inserção de Bytes
// Enquadramento 2 = Inserção de Bits
// esse define vai atualizar não apenas o enquadramento como também o desenquadramento, simplificando os testes

// Transmissão
//-----------------------------------------------------
void CamadaEnlaceDadosTransmissora(int* quadro);
int *CamadadeEnlaceTransmissoraEnquadramento(int* quadro);

// Recepção
//-----------------------------------------------------
int *CamadaDeEnlaceReceptoraEnquadramento(int* quadro);
void CamadaEnlaceDadosReceptora(int* quadro);

// Enquadrando
//-----------------------------------------------------
int *CamadaDeEnlaceTransmissoraEnquadramentoContagemDeCaracteres(int *quadro);
int *CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBytes(int *quadro);
int *CamadaDeEnlaceTransmissoraEnquadramentoInsercaoDeBits(int *quadro);

// Desenquadrando
//-----------------------------------------------------
int *CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBytes(int *quadro);
int *CamadaDeEnlaceReceptoraEnquadramentoContagemDeCaracteres(int *quadro);
int *CamadaDeEnlaceReceptoraEnquadramentoInsercaoDeBits(int *quadro);

//-----------------------------------------------------
