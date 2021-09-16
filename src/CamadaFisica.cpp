#include "CamadaFisica.hpp"
#include <iostream>
#include <string>
#include <bitset>

using namespace std;

void AplicacaoTransmissora(){
  string mensagem;
  cout << "Digite uma mensagem" << endl;
  cin >> mensagem;

  CamadaDeAplicacaoTransmissora(mensagem); // em um exemplo mais
                                           // realistico, aqui seria dado um SEND do SOCKET
}//fim do metodo main

void CamadaDeAplicacaoTransmissora(std::string mensagem){
  int* quadro;
  for (std::size_t i = 0; i < mensagem.size(); ++i)
  {
      quadro[i] = bitset<8>(mensagem.c_str()[i]);
  }

  // convert string to ASCII decimal
  // int test[sizeof(mensagem)]={},i=0,j;
  // while(mensagem[i]!='\0') {test[i]=mensagem[i]; i++;}
  // for(j=0;j<i-1;j++) printf("%d ",test[j]);

  // for (int i = (sizeof(mensagem)*8)-1; i <= 0; i--) { 
  //   cout << (mensagem & (1 << i)) ? '1' : '0'; } 

  //trabalhar com bits!!!

  //chama a proxima camada
  CamadaFisicaTransmissora(quadro);
}//fim do CamadaDeAplicacaoTransmissora

void CamadaFisicaTransmissora(int quadro[]){
  int tipoDeCodificacao = 0; //alterar de acordo com o teste
  int* fluxoBrutoDeBits; //ATENCAO: trabalhar com BITS!!!

  switch(tipoDeCodificacao){
    case 0: //codifica binaria
      fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
      break;
    case 1: //codificacao manchester
      fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
      break;
    case 2: //codificacao bipolar 
      fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro);
      break;
  }//fim do switch/case
  
  MeioDeComunicacao(fluxoBrutoDeBits);
}//fim do metodo CamadaFisicaTransmissora

int* CamadaFisicaTransmissoraCodificacaoBinaria(int quadro[]){
  //implementacao do algoritmo
}//fim do metodo CamadaFisicaTransmissoraCodificacaoBinaria

int* CamadaFisicaTransmissoraCodificacaoManchester(int quadro[]){
  //implementacao do algoritmo
} //fim do metodo CamadaFisicaTransmissoraCodificacaoManchester

int* CamadaFisicaTransmissoraCodificacaoBipolar(int quadro[]){
  //implementacao do algoritmo
}//fim do CamadaFisicaTransmissorCodificacaoBipolar

/* Este metodo simula a transmissao da informacao no meio de comunicacao
*  passando de um ponto A (transmissor) para um ponto B (receptor) */
void MeioDeComunicacao(int fluxoBrutoDeBits[]){
  //OBS IMPORTANTE: trabalhar com BITS e nao com BYTES!!!
  int* fluxoBrutoDeBitsPontoA;
  int* fluxoBrutoDeBitsPontoB;

  fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;
  
  // while(fluxoBrutoDeBitsPontoB != fluxoBrutoDeBitsPontoA){
  //   fluxoBrutoDeBitsPontoB += fluxoBrutoDeBitsPontoA; //BITS! Sendo transferidos
  // } //fim do while
  
  //chama proxima camada
  CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB);
}//fim do metodo MeioDeComunicacao

void CamadaFisicaReceptora(int quadro[]){
  int tipoDeDecodificacao = 0; //alterar de acordo com o teste
  int* fluxoBrutoDeBits; //ATENÇÃO: trabalhar com BITS!!!

  switch(tipoDeDecodificacao){
    case 0: //codificacao binaria
      fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBinaria(quadro);
      break;
    case 1: //codificacao manchester
      fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoManchester(quadro);
      break;
    case 2: //codificacao bipolar 
      fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBipolar(quadro);
      break;
  }//fim do switch/case
  
  CamadaDeAplicacaoReceptora(fluxoBrutoDeBits);
}// fim do metodo CamadaFisicaReceptora

int* CamadaFisicaReceptoraCodificacaoBinaria(int quadro[]){
  //implementacao do algoritmo para decodificar
}//fim do metodo CamadaFisicaReceptoraCodificacaoBinaria

int* CamadaFisicaReceptoraCodificacaoManchester(int quadro[]){
  //implementacao do algoritmo para decodificar
}//fim do metodo CamadaFisicaReceptoraCodificacaoManchester

int* CamadaFisicaReceptoraCodificacaoBipolar(int quadro[]){
  //implementacao do algoritmo para decodificar
}//fim do metodo CamadaFisicaReceptoraCodificacaoBipolar

void CamadaDeAplicacaoReceptora(int quadro[]){
  // string mensagem = quadro[]; //estava trabalhando com bits
  string mensagem;
  //chama proxima chamada
  AplicacaoReceptora(mensagem);
}//fim do metodo CamadaDeAplicacaoReceptora

void AplicacaoReceptora(string mensagem){
  cout << "A mensagem foi:" << mensagem << endl;
}//fim do metodo AplicacaoReceptora






