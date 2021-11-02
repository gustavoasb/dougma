#ifndef _ENLACE_H
#define _ENLACE_H

void CamadaEnlaceDadosTransmissora(int quadro [], int size);

int* CamadaEnlaceDadosTransmissoraEnquadramento(int quadro [], int& size);
int* CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(int quadro [], int& size);
int* CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(int quadro [], int& size);

int* CamadaEnlaceDadosTransmissoraControleDeErro(int quadro [], int& size);
int* CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(int quadro[], int& size);
int* CamadaEnlaceDadosTransmissoraControleDeErroCRC(int quadro[], int& size);

void CamadaEnlaceDadosReceptora(int quadroEnquadrado [], int size);

int* CamadaEnlaceDadosReceptoraEnquadramento(int quadroEnquadrado[], int& size);
int* CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(int quadroEnquadrado [], int& size);
int* CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(int quadroEnquadrado [], int& size);

int* CamadaEnlaceDadosReceptoraControleDeErro(int quadro [], int& size);
int* CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(int quadro[], int& size);
int*  CamadaEnlaceDadosReceptoraControleDeErroCRC(int quadro[], int& size);

#endif