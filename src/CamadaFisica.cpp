#include "CamadaFisica.hpp"
#include "CamadaEnlace.hpp"
#include <iostream>
#include <string>
#include <bitset>
#include <stdlib.h> 
#define DEBUG 0

using namespace std;

int tipoDeCodificacao; //alterar de acordo com o teste

void AplicacaoTransmissora(){
  std::cout << "============================= " << std::endl;
  std::cout << "CAMADA DE APLICACAO TRANSMISSORA" << std::endl;
  string mensagem;
  cout << "Digite uma mensagem:" << endl;
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

  std::cout << "Mensagem transmitida: ";
  for(int i = 0; i < 8 * size; i++){
    std::cout << quadro[i];
  }
  std::cout << std::endl;

  //chama a camada de enlace
  CamadaEnlaceDadosTransmissora(quadro, array_size);
}//fim do CamadaDeAplicacaoTransmissora

void CamadaFisicaTransmissora(int quadro[], int size){
  std::cout << "============================= " << std::endl;
  std::cout << "CAMADA FISICA TRANSMISSORA" << std::endl;
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
  
  std::cout << "Mensagem codificada: ";
  for(int i = 0; i < size; i++){
    std::cout << fluxoBrutoDeBits[i];
  }
  std::cout << std::endl;

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
    }
    else if(quadro[i] == 1){
      if(flag) {
        new_quadro[i] = 1;
      } else {
        new_quadro[i] = -1;
      }
      flag = flag ? false : true; 
    }
    else new_quadro[i] = quadro[i];
    
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

  int porcentagemDeErros = 0; //10%, 20%, 30%, 40%, ..., 100%
  
  for(int i = 0; i < size * multiplier; i++){
    if((rand()%100) >= porcentagemDeErros) //fazer a probabilidade de erro
    fluxoBrutoDeBitsPontoB[i] = fluxoBrutoDeBitsPontoA[i]; //BITS! Sendo transferidos
    else { //ERRO! INVERTER (usa condicao ternaria)
      fluxoBrutoDeBitsPontoA[i] = fluxoBrutoDeBitsPontoB[i] == 0 ? fluxoBrutoDeBitsPontoB[i]+1 : fluxoBrutoDeBitsPontoB[i]-1;
    }
  }

  std::cout << "============================= " << std::endl;
  std::cout << std::endl;
  std::cout << "Transmissao da Informacao" << std::endl;
  std::cout << std::endl;
  
  //chama proxima camada
  CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB, size);
}//fim do metodo MeioDeComunicacao

void CamadaFisicaReceptora(int quadro[], int size){
  int* fluxoBrutoDeBits; //ATENÇÃO: trabalhar com BITS!!!

  std::cout << "============================= " << std::endl;
  std::cout << "CAMADA FISICA RECEPTORA" << std::endl;

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
  
  std::cout << "Mensagem decodificada: ";
  for(int i = 0; i < size; i++){
    std::cout << fluxoBrutoDeBits[i];
  }
  std::cout << std::endl;
  CamadaEnlaceDadosReceptora(fluxoBrutoDeBits, size);
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
    } 
    else if(quadro[i] == 1 || quadro[i] == -1) {
      new_quadro[i] = 1;
    }
    else new_quadro[i] = quadro[i];
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
  std::cout << "============================= " << std::endl;
  std::cout << "CAMADA DE APLICACAO RECEPTORA " << std::endl;
  std::cout << "Mensagem recebida: ";
  std::cout << mensagem << std::endl << std::endl;
  
  AplicacaoReceptora(mensagem);
}//fim do metodo CamadaDeAplicacaoReceptora

void AplicacaoReceptora(string mensagem){
  cout << "A mensagem foi:" << mensagem << endl;
}//fim do metodo AplicacaoReceptora