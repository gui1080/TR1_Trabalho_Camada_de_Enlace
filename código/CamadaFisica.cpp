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

// CODIFICAÇÃO RELATIVA AO TRABALHO 1
// (atualizada para ter uma camada de enlace)

// https://github.com/gui1080/TR1_Trabalho_Camada_Fisica
// (repositório privado na entrega do trabalho)

// FUNÇÕES AUXILIARES
//--------------------------------------------------------------------------------------------

int *simplifica(int quadro[]){


	int i = 0;
	i = find_size(quadro);
	int tamanho_quadro = i;
	int tamanho_mensagem_ascii = i / 2;

	int *fluxoFinal;

	fluxoFinal = new (nothrow) int[tamanho_mensagem_ascii];

	int j = 0;

	for (i = 0; i < tamanho_quadro; i = i + 2)
	{

		fluxoFinal[j] = quadro[i]; // tamanho = tamanho_mensagem_ascii

		j++;
	}

	fluxoFinal[tamanho_mensagem_ascii] = 2;

	return fluxoFinal;

}

int find_size(int quadro[]){

	int i = 0;
	while (1)
	{

		if (quadro[i] == 2)     // utilizou-se a convenção de o próximo elemento dps do último elemento
		{						// util do array é 2 pra demarcar o final
			break;
		}
		i++;
	}

	// se conta até achar o 2 retorna o tamanho

	return i;
}

void converte(string mensagem, int quadro[], int pos)
{

	int x, j, i;

	j = ((pos * 8) - 1) + 8;	// cálculo da posição no array transformado em binário

	bitset<8> set(mensagem[pos]);

	if (mensagem[pos] == ' ')
	{

		// um espaço vazio teve que virar um caso especial
		set.reset();   // todos são zero
		set.set(5, 1); // 32 == espaço

	}

	for (i = 0; i < 8; i++)
	{

		if (set.test(i))		// testa se é 1 ou 0, e aloca de acordo no resultado da conversão como int
		{

			quadro[j] = 1;
			j--;

		}
		else
		{

			quadro[j] = 0;
			j--;

		}
	}

	return;
}

// TRANSMISSÃO
//--------------------------------------------------------------------------------------------

void CamadaDeAplicacaoTransmissora(string mensagem)
{

	// int quadro[] = mensagem
	// trabalhando com bits

	cout << "\033[1;34mCamada de Aplicacao Transmissora\033[0m\n";

	int i, j, x;
	int tamanho_quadro_final = 8 * (mensagem.length());

	int *quadro, *letra_atual;

	quadro = new (nothrow) int[tamanho_quadro_final];

	// se aloca o tamanho da mensagem em binário com tamanho do número de letras  * 8
	// se itera e converte letra a letra

	for (j = 0; j < mensagem.size(); j++)
	{

		converte(mensagem, quadro, j);

	}
	for(i = 0; i < tamanho_quadro_final; i++){

		cout << quadro[i];

	}

	cout << endl << endl;

	quadro[tamanho_quadro_final] = 2;

	// trabalho 2
	CamadaEnlaceDadosTransmissora(quadro);

	// trabalho 1
	//CamadaFisicaTransmissora(quadro);

} // fim do metodo

void CamadaFisicaTransmissora(int quadro[])
{

	cout << "\033[1;34mCamada Fisica Transmissora: \033[0m\n";
	int tipoDeCodificacao = CODIFICACAO;	// utilizou-se um define pra facilitar a mudança da codificação/decodificação

	int i = 0;
	int tamanho_fluxo;
	tamanho_fluxo = ((find_size(quadro)) * 2);  // convenção: o fluxo vai ter o dobro de quantidade de 0s e 1 por conta da codificação manchester e manchester diferencial

	int *fluxoBrutoDeBits;

	fluxoBrutoDeBits = new (nothrow) int[tamanho_fluxo];

	switch (tipoDeCodificacao)
	{
		case 0: //codificacao binaria

		fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);

		cout << "\033[1;35mCodificacao Binaria: \033[0m\n";
		for (i = 0; i < tamanho_fluxo; i++)
		{
			cout << fluxoBrutoDeBits[i];
		}
		cout << endl << endl;

		break;

		case 1: //codificacao manchester

		fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);

		cout << "\033[1;35mCodificacao Manchester: \033[0m\n";
		for (i = 0; i < tamanho_fluxo; i++)
		{
			cout << fluxoBrutoDeBits[i];
		}
		cout << endl << endl;

		break;

		case 2: //codificacao manchester diferencial

		fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(quadro);

		cout << "\033[1;35mCodificacao Manchester Diferencial: \033[0m\n";
		for (i = 0; i < tamanho_fluxo; i++)
		{
			cout << fluxoBrutoDeBits[i];
		}
		cout << endl << endl;

		break;

	} // fim do switch/case

	MeioDeComunicacao(fluxoBrutoDeBits);

}

// CODIFICAÇÃO
//--------------------------------------------------------------------------------------------

int *CamadaFisicaTransmissoraCodificacaoManchester(int quadro[])
{

	int i = 0;
	int tamanho_fluxo;
	i = find_size(quadro);
	tamanho_fluxo = i * 2;

	int *fluxoCodificado;

	fluxoCodificado = new (nothrow) int[tamanho_fluxo];

	int j;
	int x = 0;

	for (j = 0; j < i; j++)
	{

		// xor 00 e 01 = 01
		// xor 11 e 01 = 10
		// clock = 01 01 01 01 ...

		// se temos 00, vira 01 por conta do xor
		if (quadro[j] == 0)
		{
			fluxoCodificado[x] = 0;
			x++;
			fluxoCodificado[x] = 1;
			x++;
		}

		// se temos 11, vira 10 por conta do xor
		if (quadro[j] == 1)
		{
			fluxoCodificado[x] = 1;
			x++;
			fluxoCodificado[x] = 0;
			x++;
		}
	}

	fluxoCodificado[tamanho_fluxo] = 2; // delimita o final

	return fluxoCodificado; // passa a codificação a diante

} // fim do metodo CamadaFisicaTransmissoraCodificacaoManchester

int *CamadaFisicaTransmissoraCodificacaoBinaria(int quadro[])
{

	// basicamente se passa o fluxo bruto para frente, mas cada 0 e cada 1 é duplicado
	// para satisfazer a mesma função que converterá as outras codificações de volta (clock 01 01 01...)

	int i = 0;
	int tamanho_fluxo;
	i = find_size(quadro);
	tamanho_fluxo = i * 2;

	int *fluxoCodificado;

	fluxoCodificado = new (nothrow) int[tamanho_fluxo];

	int j;

	int x = 0;

	for (j = 0; j < i; j++)
	{

		fluxoCodificado[x] = quadro[j];
		x++;

		fluxoCodificado[x] = quadro[j];
		x++;
	}

	fluxoCodificado[tamanho_fluxo] = 2;

	return fluxoCodificado; // passa a diante o fluxo codificado

} // fim do metodo CamadaFisicaTransmissoraCodificacaoBinaria

int *CamadaFisicaTransmissoraCodificacaoManchesterDiferencial(int quadro[])
{

	int i = 0;
	int tamanho_fluxo;
	i = find_size(quadro);
	tamanho_fluxo = i * 2;

	int *fluxoCodificado;

	fluxoCodificado = new (nothrow) int[tamanho_fluxo];

	int j;
	int x = 0;

	// Na codificação manchester diferencial, se importa apenas as mudanças de 0 pra 1 ou 1 pra 1
	// um exemplo:

	// z
	// 0  1  1  1  1  0  1  0
	// 00 11 11 11 11 00 11 00
	// 01 10 01 10 01 01 10 10

	// o resultado fica em termos de 01 e 10 pois se mantém a informação do clock que é 01 01 01...

	// se o primeiro termo a ser codificado é 0, o resultado sai igual ao clock
	// se o primeiro termo a ser codificado é 1, o resultado é 10 pra indicar que houve mudança, a referencia seria o clock nesse caso

	int passado[2];

	passado[0] = 0;
	passado[1] = 1; // começa com 01 por conta da referencia do clock

	for (j = 0; j < i; j++)
	{
		if (quadro[j] == 0) // se faz a comparação e se guarda se antes havia um 01 ou 10
		{

			fluxoCodificado[x] = passado[0];
			x++;
			fluxoCodificado[x] = passado[1];
			x++;
		}
		else
		{

			if (quadro[j] == 1)
			{

				if (passado[0] == 0)
				{

					passado[0] = 1;
					passado[1] = 0;

					fluxoCodificado[x] = 1;
					x++;
					fluxoCodificado[x] = 0;
					x++;
				}

				else if (passado[0] == 1)
				{

					passado[0] = 0;
					passado[1] = 1;

					fluxoCodificado[x] = 0;
					x++;
					fluxoCodificado[x] = 1;
					x++;
				}
			}
		}
	}

	fluxoCodificado[tamanho_fluxo] = 2; // se delimita o final

	return fluxoCodificado; // passa a codificação a diante

} // fim do metodo CamadaFisicaTransmissoraCodificacaoManchesterDiferencial

// MEIO
//--------------------------------------------------------------------------------------------

void MeioDeComunicacao(int fluxoBrutodeBits[])
{


	// essa função aloca dinamicamente os fluxos de bits,
	// copia um fluxo A para um fluxo B e passa o B adiante
	// para concretizar uma simulação entre parte transmissora e receptora


	int i = 0;

	cout << "\033[1;33mMeio de Transmissao\033[0m\n";

	int tamanho = find_size(fluxoBrutodeBits);

	int *fluxoBrutoDeBitsPontoA;
	int *fluxoBrutoDeBitsPontoB;


	fluxoBrutoDeBitsPontoA = new (nothrow) int[tamanho];
	fluxoBrutoDeBitsPontoB = new (nothrow) int[tamanho];


	for (i = 0; i < tamanho; i++) // copia original pro A
	{
		fluxoBrutoDeBitsPontoA[i] = fluxoBrutodeBits[i];

		printf("%d", fluxoBrutoDeBitsPontoA[i]);

	}

	for (i = 0; i < tamanho; i++) // copia A pro B
	{
		fluxoBrutoDeBitsPontoB[i] = fluxoBrutoDeBitsPontoA[i];
	}
	cout << endl;

	fluxoBrutoDeBitsPontoB[tamanho] = 2;

	CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}

// DECODIFICAÇÃO
//--------------------------------------------------------------------------------------------

void CamadaFisicaReceptora(int quadro[])
{

	cout << "\033[1;34m\nCamada Fisica Receptora\033[0m\n";

	int tipoDeDecodificacao = CODIFICACAO; // utilizou-se este define para facilitar a mudança entre codificações e decodificações

	int i = 0;
	i = find_size(quadro);
	int *fluxoBrutoDeBits;
	int *fluxoFinal;
	int z = (i/2);

	fluxoBrutoDeBits = new (nothrow) int[i]; // alocação dinâmica
	fluxoFinal = new (nothrow) int[z];

	switch (tipoDeDecodificacao)
	{

		case 0:

		fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoBinaria(quadro);
		fluxoFinal = simplifica(fluxoBrutoDeBits);

		cout << "\033[1;35mDecodificacao Binaria: \033[0m\n";

		break;

		case 1:

		fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoManchester(quadro);
		fluxoFinal = simplifica(fluxoBrutoDeBits);

		cout << "\033[1;35mDecodificacao Manchester: \033[0m\n";

		break;
		case 2:

		fluxoBrutoDeBits = CamadaFisicaReceptoraDecodificacaoManchesterDiferencial(quadro);
		fluxoFinal = simplifica(fluxoBrutoDeBits);

		cout << "\033[1;35mDecodificacao Manchester Diferencial: \033[0m\n";

		break;
	}

	i = find_size(fluxoFinal);
	for (int j = 0; j < i; j++)
	{
		cout << fluxoFinal[j];
	}
	cout << endl << endl;

	//trabalho 1
	//CamadaDeAplicacaoReceptora(fluxoBrutoDeBits); // passa a diante o fluxo decodificado

	//trabalho 2
	CamadaEnlaceDadosReceptora(fluxoFinal);
}

int *CamadaFisicaReceptoraDecodificacaoBinaria(int quadro[])
{

	// acabou que nesta camada o que deve ser decodificado já está pronto para ser um input
	// da mudança de binário de volta para letra como o resultado final das outras
	// decodificações

	return quadro;
}

int *CamadaFisicaReceptoraDecodificacaoManchester(int quadro[])
{

	int i = 0;
	int tamanho_fluxo;
	i = find_size(quadro);
	tamanho_fluxo = i;

	int *fluxoDecodificado;

	fluxoDecodificado = new (nothrow) int[tamanho_fluxo];

	int j, x;
	x = 0;

	// voltamos o xor da codificação

	// o receptor sabe que 01 xor algo tem que ser 00
	// o receptor sabe que 10 xor algo tem que ser 11
	// se recupera o clock 01 01 01...


	// xor 01 e 01 = 00
	// xor 10 e 01 = 11

	for (j = 0; j < i; j++)
	{

		// clock = 01 01 01 01 ...
		if ((quadro[j] == 0) && (quadro[j + 1] == 1))
		{
			fluxoDecodificado[x] = 0;
			x++;
			fluxoDecodificado[x] = 0;
			x++;
		}
		if ((quadro[j] == 1) && (quadro[j + 1] == 0))
		{
			fluxoDecodificado[x] = 1;
			x++;
			fluxoDecodificado[x] = 1;
			x++;
		}
		j++;

	}

	fluxoDecodificado[tamanho_fluxo] = 2; // delimita o final e passa o fluxo decodificado para frente

	return fluxoDecodificado;
}

int *CamadaFisicaReceptoraDecodificacaoManchesterDiferencial (int quadro[]){

	int i = 0;
	i = find_size(quadro);
	int tamanho_fluxo;
	tamanho_fluxo = i;

	int *fluxoDecodificado;

	fluxoDecodificado = new (nothrow) int[tamanho_fluxo];

	int j, x;
	x = 0;

	int passado[2];

	// outra vez, conclui-se que o clock é 01 01 01...
	// a referencia passado começa 01 para delimitar esse passado
	// se a primeira comparação conclui que 01 = 01, temos um 0
	// passado continua 01, comparações continuam
	// se a primeira comparação conclui que 01 != 10, temos um 1
	// passado vira 10, comparações continuam
	// no final se tem um vetor de inteiros com 0s e 1s como originalmente

	passado[0] = 0;
	passado[1] = 1;

	for (j = 0; j < tamanho_fluxo; j=j+2)
	{

		if ((quadro[j] == 0 && quadro[j+1] == 1)) // temos 01?
		{
			if((passado[0] == 0 && passado[1] == 1)){ // era 01?

				fluxoDecodificado[x] = 0; // não mudou, é 0
				x++;
				fluxoDecodificado[x] = 0;
				x++;

			}else if((passado[0] == 1 && passado[1] == 0)){ // era 10?

				fluxoDecodificado[x] = 1;
				x++;
				fluxoDecodificado[x] = 1; // mudou, é 1
				x++;

				passado[0] = 0; // update
				passado[1] = 1;

			}
		}

		else if ((quadro[j] == 1 && quadro[j+1] == 0)) // temos 10?
		{
			if((passado[0] == 1 && passado[1] == 0)){ // era 10?

				fluxoDecodificado[x] = 0;
				x++;
				fluxoDecodificado[x] = 0; // não mudou, é zero
				x++;

			}else if((passado[0] == 0 && passado[1] == 1)){ // era 01?

				fluxoDecodificado[x] = 1;
				x++;
				fluxoDecodificado[x] = 1; // mudou, é 1
				x++;

				passado[0] = 1; // update
				passado[1] = 0;

			}

		}

	}

	fluxoDecodificado[tamanho_fluxo] = 2;

	return fluxoDecodificado;
}

// RECEPÇÃO
//--------------------------------------------------------------------------------------------

void CamadaDeAplicacaoReceptora(int quadro[])
{

	cout << "\033[1;34mCamada de Aplicação Receptora\033[0m\n";
	// transformando em string

	int i = 0;
	i = find_size(quadro);
	int tamanho_quadro = i;
	int tamanho_mensagem_ascii = i;

	int *fluxoFinal;

	fluxoFinal = new (nothrow) int[tamanho_mensagem_ascii];

	int j = 0;

	for (i = 0; i < tamanho_quadro; i++)
	{
		cout << quadro[i];
	}

	cout << endl << endl;

	string mensagem;

	int decimal = 0;
	int y;

	// se acumula o binário em um inteiro
	// faz o cast daquele inteiro pra ascii
	// dá push na string


	for (i = 0; i < (tamanho_mensagem_ascii / 8); i++)
	{

		decimal = 0;

		y = 0;

		for (j = ((i * 8) + 7); j >= (i * 8); j--)
		{

			if (quadro[j] == 1)
			{

				decimal = decimal + pow(2, y);
			}

			y++;
		}

		mensagem.push_back((char)decimal);
	}

	AplicacaoReceptora(mensagem); // passamos a string a diante
}

void AplicacaoReceptora(string mensagem)
{

	// se recebe a string no resultado!

	cout << "\033[1;34mAplicacao Receptora\033[0m\n";
	cout << "\033[1;32mA mensagem recebida foi: \033[0m";
	cout << mensagem << endl;

	// fim!

}

//-----------------------------------------------------
