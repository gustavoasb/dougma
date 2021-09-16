#include <string>

void AplicacaoTransmissora();
void CamadaDeAplicacaoTransmissora(std::string mensagem);
void CamadaFisicaTransmissora(int quadro[]);

int* CamadaFisicaTransmissoraCodificacaoBinaria(int quadro[]);
int* CamadaFisicaTransmissoraCodificacaoManchester(int quadro[]);
int* CamadaFisicaTransmissoraCodificacaoBipolar(int quadro[]);

void MeioDeComunicacao(int fluxoBrutoDeBits[]);
void CamadaFisicaReceptora(int quadro[]);

int* CamadaFisicaReceptoraCodificacaoBinaria(int quadro[]);
int* CamadaFisicaReceptoraCodificacaoManchester(int quadro[]);
int* CamadaFisicaReceptoraCodificacaoBipolar(int quadro[]);

void CamadaDeAplicacaoReceptora(int quadro[]);
void AplicacaoReceptora(std::string mensagem);