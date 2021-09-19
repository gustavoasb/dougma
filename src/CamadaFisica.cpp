#include "CamadaFisica.hpp"
#include <iostream>
#include <string>
#include <bitset>
#define DEBUG 0

using namespace std;

int tipoDeCodificacao; //alterar de acordo com o teste

void AplicacaoTransmissora(){
  string mensagem;
  cout << "Digite uma mensagem" << endl;
  getline(cin, mensagem);
  CamadaDeAplicacaoTransmissora(mensagem); // em um exemplo mais
                                           // realistico, aqui seria dado um SEND do SOCKET
}//fim do metodo main

void CamadaDeAplicacaoTransmissora(std::string mensagem){
  // mensagem to bitset
  bitset<8> bits[sizeof(mensagem)];
  for (std::size_t i = 0; i < mensagem.size(); ++i)
  {
      bits[i] = bitset<8>(mensagem.c_str()[i]);
  }

  // bitset to array of ints
  int size = mensagem.length();
  int quadro[8 * size];
  for(int i = 0, index = 0; i < size; ++i){
    for(int j = 0; j < 8; ++j){
      quadro[index++] = bits[i][7 - j];
      if(DEBUG) cout << quadro[index-1];
    }
    if(DEBUG) cout << endl;
  }
  int array_size = sizeof(quadro)/sizeof(quadro[0]);
  //trabalhar com bits!!!

  //chama a proxima camada
  CamadaFisicaTransmissora(quadro, array_size);
}//fim do CamadaDeAplicacaoTransmissora

void CamadaFisicaTransmissora(int quadro[], int size){
  int *fluxoBrutoDeBits; //ATENCAO: trabalhar com BITS!!!
  int multiplier = 1;

  cout << "Escolha um tipo de codificacao:" << endl;
  cout << "1 - Codificacao Binaria" << endl;
  cout << "2 - Codificacao Manchester" << endl;
  cout << "3 - Codificacao Bipolar" << endl;
  cin >> tipoDeCodificacao;

  if (cin.fail()) {
    cout << "Opcao invalida";
  }

  switch(tipoDeCodificacao-1){
    case 0: //codificacao binaria
      fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro, size);
      break;
    case 1: //codificacao manchester
      fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro, size);
      multiplier = 2;
      break;
    case 2: //codificacao bipolar
      fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro, size);
      break;
    default:
      cout << "Opcao invalida";
      exit(1);
      break;
  }//fim do switch/case
  
  MeioDeComunicacao(fluxoBrutoDeBits, size, multiplier);
}//fim do metodo CamadaFisicaTransmissora

int* CamadaFisicaTransmissoraCodificacaoBinaria(int quadro[], int size){
  //implementacao do algoritmo
  return quadro;
}//fim do metodo CamadaFisicaTransmissoraCodificacaoBinaria

int* CamadaFisicaTransmissoraCodificacaoManchester(int quadro[], int size){
  //implementacao do algoritmo
  int* new_quadro = (int*) malloc(4 * size * 2); /* or sizeof(int) */
  if (quadro == NULL) {
    cout << "Cannot allocate memory";
    exit(1);
  }
  int j = 0;
  for(int i = 0; i < size; i++) {
    new_quadro[j] = quadro[i] ^ 0;
    j++;
    new_quadro[j] = quadro[i] ^ 1;
    j++;
  }
  return new_quadro;
} //fim do metodo CamadaFisicaTransmissoraCodificacaoManchester

int* CamadaFisicaTransmissoraCodificacaoBipolar(int quadro[], int size){
  //implementacao do algoritmo
  int* new_quadro = (int*) malloc(4 * size); /* or sizeof(int) */
  if (quadro == NULL) {
    cout << "Cannot allocate memory";
    exit(1);
  }
  bool flag = true;
  for(int i = 0; i < size; i++) {
    if(quadro[i] == 0) {
      new_quadro[i] = 0;
    } else {
      if(flag) {
        new_quadro[i] = 1;
      } else {
        new_quadro[i] = -1;
      }
      flag = flag ? false : true; 
    }
    if (DEBUG) cout << new_quadro[i] << endl;
  }
  return new_quadro;
}//fim do CamadaFisicaTransmissorCodificacaoBipolar

/* Este metodo simula a transmissao da informacao no meio de comunicacao
*  passando de um ponto A (transmissor) para um ponto B (receptor) */
void MeioDeComunicacao(int fluxoBrutoDeBits[], int size, int multiplier){
  //OBS IMPORTANTE: trabalhar com BITS e nao com BYTES!!!
  int* fluxoBrutoDeBitsPontoA = (int*) malloc(4 * size * multiplier); /* or sizeof(int) */
  int* fluxoBrutoDeBitsPontoB = (int*) malloc(4 * size * multiplier); /* or sizeof(int) */

  fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;
  
  for(int i = 0; i < size * multiplier; i++){
    fluxoBrutoDeBitsPontoB[i] = fluxoBrutoDeBitsPontoA[i]; //BITS! Sendo transferidos
  }
  
  //chama proxima camada
  CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB, size);
}//fim do metodo MeioDeComunicacao

void CamadaFisicaReceptora(int quadro[], int size){
  int* fluxoBrutoDeBits; //ATENÇÃO: trabalhar com BITS!!!

  switch(tipoDeCodificacao-1){
    case 0: //codificacao binaria
      fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBinaria(quadro, size);
      break;
    case 1: //codificacao manchester
      fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoManchester(quadro, size);
      break;
    case 2: //codificacao bipolar 
      fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBipolar(quadro, size);
      break;
  }//fim do switch/case
  
  CamadaDeAplicacaoReceptora(fluxoBrutoDeBits, size);
}// fim do metodo CamadaFisicaReceptora

int* CamadaFisicaReceptoraCodificacaoBinaria(int quadro[], int size){
  //implementacao do algoritmo para decodificar
  return quadro;
}//fim do metodo CamadaFisicaReceptoraCodificacaoBinaria

int* CamadaFisicaReceptoraCodificacaoManchester(int quadro[], int size){
  //implementacao do algoritmo para decodificar
  int* new_quadro = (int*) malloc(4 * size); /* or sizeof(int) */
  if (quadro == NULL) {
    cout << "Cannot allocate memory";
    exit(1);
  }
  int j = 0;
  for(int i = 0; i < size*2; i+=2, j++) {
    new_quadro[j] = quadro[i] ^ 0;
  }
  return new_quadro;
}//fim do metodo CamadaFisicaReceptoraCodificacaoManchester

int* CamadaFisicaReceptoraCodificacaoBipolar(int quadro[], int size){
  //implementacao do algoritmo para decodificar
  int* new_quadro = (int*) malloc(4 * size); /* or sizeof(int) */
  if (quadro == NULL) {
    cout << "Cannot allocate memory";
    exit(1);
  }
  for(int i = 0; i < size; i++) {
    if(quadro[i] == 0) {
      new_quadro[i] = 0;
    } else {
      new_quadro[i] = 1;
    }
    // if(DEBUG) cout << new_quadro[i] << endl;
  }
  return new_quadro;
}//fim do metodo CamadaFisicaReceptoraCodificacaoBipolar

void CamadaDeAplicacaoReceptora(int quadro[], int size){
  int base = 128;
  string mensagem;
  int dec_value = 0;
 
  int i = 0;
  for(int index = 0; index < size + 1; index++) {
    if(i == 8){
      mensagem += ((char)dec_value);
      dec_value = 0;
      base = 128;
      i = 0;
    }
    dec_value += quadro[index] * base;
    base = base / 2;
    i++;
  }
  //chama proxima chamada
  AplicacaoReceptora(mensagem);
}//fim do metodo CamadaDeAplicacaoReceptora

void AplicacaoReceptora(string mensagem){
  cout << "A mensagem foi:" << mensagem << endl;
}//fim do metodo AplicacaoReceptora
