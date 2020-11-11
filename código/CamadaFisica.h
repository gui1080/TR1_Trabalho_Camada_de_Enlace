#include <stdexcept>
#include <iostream>
#include <string>
#include <stdlib.h>

// CODIFICAÇÃO RELATIVA AO TRABALHO 1
// (atualizada para ter uma camada de enlace)

// https://github.com/gui1080/TR1_Trabalho_Camada_Fisica
// (repositório privado na entrega do trabalho)

#define CODIFICACAO 2
// CODIFICACAO = 0 (Binária)
// CODIFICACAO = 1 (Manchester)
// CODIFICACAO = 2 (Manchester Diferencial)
// esse define vai atualizar não apenas a codificação como também a decodificação, simplificando os testes


// funções auxiliares
void converte(string mensagem, int* quadro, int pos);
int find_size(int* quadro);
int *simplifica(int* quadro[]);

// simulador por parte do transmissor
void CamadaDeAplicacaoTransmissora(string mensagem);
void CamadaFisicaTransmissora(int* quadro);

// Codificação/Decodificação Binária
int *CamadaFisicaTransmissoraCodificacaoBinaria(int *quadro);
int *CamadaFisicaReceptoraDecodificacaoBinaria(int *quadro);

// Codificação/Decodificação Manchester
int *CamadaFisicaTransmissoraCodificacaoManchester(int *quadro);
int *CamadaFisicaReceptoraDecodificacaoManchester(int *quadro);

// Codificação/Decodificação Manchester Diferencial
int *CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(int *quadro);
int *CamadaFisicaReceptoraDecodificacaoManchesterDiferencial (int *quadro);

// Meio entre o transmissor e o receptor
void MeioDeComunicacao(int* fluxoBrutodeBits);

// simulador por parte do receptor
void CamadaFisicaReceptora(int* quadro);
void CamadaDeAplicacaoReceptora(int* quadro);

// simulação da aplicação final recebendo a mensagem enviada do transmissor
void AplicacaoReceptora(string mensagem);