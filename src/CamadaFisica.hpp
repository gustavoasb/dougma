#ifndef _FISICA_H
#define _FISICA_H

#include <string>

void AplicacaoTransmissora();
void CamadaDeAplicacaoTransmissora(std::string mensagem);
void CamadaFisicaTransmissora(int quadro[], int& size);

int* CamadaFisicaTransmissoraCodificacaoBinaria(int quadro[], int& size);
int* CamadaFisicaTransmissoraCodificacaoManchester(int quadro[], int& size);
int* CamadaFisicaTransmissoraCodificacaoBipolar(int quadro[], int& size);

void MeioDeComunicacao(int fluxoBrutoDeBits[], int size);
void CamadaFisicaReceptora(int quadro[], int size);

int* CamadaFisicaReceptoraCodificacaoBinaria(int quadro[], int size);
int* CamadaFisicaReceptoraCodificacaoManchester(int quadro[], int size);
int* CamadaFisicaReceptoraCodificacaoBipolar(int quadro[], int size);

void CamadaDeAplicacaoReceptora(int quadro[], int size);
void AplicacaoReceptora(std::string mensagem);

#endif