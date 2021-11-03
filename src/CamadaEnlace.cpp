#include "CamadaFisica.hpp"
#include "CamadaEnlace.hpp"
#include "Helpers.hpp"
#include <bitset>
#include <iostream>
#include <math.h>

//transmissora
int tipoDeEnquadramento; //alterar de acordo com o teste
int tipoDeControleDeErro; //alterar de acordo com teste

void CamadaEnlaceDadosTransmissora(int quadro[], int size){

  PrintHeader("CAMADA DE ENLACE TRANSMISSORA");
  // controle de erro
  int* quadroCE = CamadaEnlaceDadosTransmissoraControleDeErro(quadro, size);

  PrintQuadro("Quadro com controle de erro: ", quadroCE, size);

  int* quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramento(quadroCE, size);

  PrintQuadro("Mensagem enquadrada: ", quadroEnquadrado, size);

  CamadaFisicaTransmissora(quadroEnquadrado, size);
} //fim do metodo CamadaEnlaceDadosTransmissora

int* CamadaEnlaceDadosTransmissoraEnquadramento(int quadro[], int &size){
  std::cout << "Escolha um tipo de enquadramento:" << std::endl;
  std::cout << "1 - Contagem de Caracteres" << std::endl;
  std::cout << "2 - Insercao de Bytes" << std::endl;
  std::cin >> tipoDeEnquadramento;

  if (std::cin.fail()) {
    std::cout << "Opcao invalida";
  }
  
  int* quadroEnquadrado;

  switch(tipoDeEnquadramento-1){
    case 0: //contagem de caracteres  
      quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(quadro, size);
      break;
    case 1: //insercao de bytes
      quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(quadro, size);
      break;
    default: {
      std::cout << "Opcao invalida";
      exit(1);
    } break;
  } //fim do switch case

  return quadroEnquadrado;
} //fim do metodo CamadaEnlaceDadosTransmissoraEnquadramento

int* CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(int quadro[], int &size){
  //implementacao de algoritmo
  size += 1;
  int* quadroEnquadrado = (int*) malloc(4 * (size));

  quadroEnquadrado[0] = size;
  for(int i = 1; i < size; i++){
    quadroEnquadrado[i] = quadro[i-1];
  }

  free(quadro);
  return quadroEnquadrado;
} //fim do metodo CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres

int* CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(int quadro[], int &size){
  //implementacao de algoritmo
  int old_size = size;
  const int flag_size = 8;
  size = size + (flag_size * 2);
  int* quadroEnquadrado = (int*) malloc(4 * size);
  int flag[flag_size] = {0, 0, 0, 0, 1, 1, 1, 1};
  
  for(int i = 0; i < flag_size; i++){
    quadroEnquadrado[i] = flag[i];
  }

  for(int i = flag_size, j = 0; i < flag_size + old_size; i++, j++){
    quadroEnquadrado[i] = quadro[j]; 
  }

  for(int i = flag_size + old_size, j = 0; i < flag_size * 2 + old_size; i++, j++){
    quadroEnquadrado[i] = flag[j];
  }

  free(quadro);
  return quadroEnquadrado;
} //fim do metodo CamadaEnlaceDadosTransmissoraInsercaoDeBytes


int* CamadaEnlaceDadosTransmissoraControleDeErro(int quadro[], int& size){
  std::cout << "Escolha um metodo de controle de erro:" << std::endl;
  std::cout << "1 - Bit Paridade Par" << std::endl;
  std::cout << "2 - CRC" << std::endl;
  std::cout << "3 - Codigo de Hamming" << std::endl;
  std::cin >> tipoDeControleDeErro;

  if (std::cin.fail()) {
    std::cout << "Opcao invalida";
  }

  int* new_quadro;

  switch(tipoDeControleDeErro - 1){
    case 0: //bit de paridade par
        new_quadro = CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro, size);
        break; 
    case 1: //CRC
        new_quadro = CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro, size);
        break; 
    case 2: //Codigo de Hamming
        new_quadro = CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(quadro, size);
        break; 
    default:
      std::cout << "Opcao invalida" << std::endl;
      exit(1);
      break;
  }//fim do switch/case
  
  return new_quadro;
} //fim do metodo CamadaEnlaceDadosTransmissoraControleDeErro

int* CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(int quadro[], int& size){
  int* new_quadro = (int*) malloc(4 * (size+1));
  int one_counter = 0;
  
  // copia do quadro
  for(int i = 0; i < size; i++){
    new_quadro[i] = quadro[i];
    if(new_quadro[i] == 1){
      one_counter++;
    }
  }

  // adiciona bit de paridade
  if(one_counter % 2){
    new_quadro[size] = 1;
  } else new_quadro[size] = 0;

  free(quadro);
  size += 1;
  
  return new_quadro;
} //fim do metodo CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar

int* CamadaEnlaceDadosTransmissoraControleDeErroCRC(int quadro[], int& size){
  //implementacao do algoritmo
  //usar polinomio CRC-32(IEEE802)

  int n = 4;
  int crc_size = n-1;

  int* new_quadro = (int*) malloc(4 * (size+crc_size));

  // divisor = 1101
  int divisor = 13;

  for(int i=0; i<size; i++) {
    new_quadro[i] = quadro[i];
  }
  for(int i=size; i<size+crc_size; i++) {
    new_quadro[i] = 0;
  }

  uint32_t remainder = 0; 
  for(int i = size+crc_size -1, index = 0; i >= 0; i--, index++){
    remainder += new_quadro[index] * (int)pow(2,i);
  }

  int aux;
  for (uint32_t bit = size+crc_size; bit > crc_size; --bit)
  {
    if (remainder & (int)pow(2,(bit-1))){
      aux = remainder;
      aux = aux >> (bit - n);
      remainder = ((aux ^ divisor) << bit - n) | (remainder & ((int)pow(2,(bit-n))-1));
    } 
    else {
      aux = remainder;
      aux = aux >> (bit - n);
      remainder = ((aux ^ 0) << bit - n) | (remainder & ((int)pow(2,(bit-n))-1));
    }
  }
  // size = old_size;

  for(int i = 0; i < crc_size; i++){
    new_quadro[size+i] = (remainder >> crc_size - 1 - i) & 1 ? 1 : 0;
  }

  size += crc_size;

  free(quadro);
  return new_quadro;
} //fim do metodo CamadaEnlaceDadosTransmissoraControleDeErroCRC

int* CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(int quadro[], int& size){
  
  return quadro;
}


/* receptora */

void CamadaEnlaceDadosReceptora(int quadroEnquadrado[], int size){

  PrintHeader("CAMADA DE ENLACE RECEPTORA");
  
  int* quadroDesenquadrado = CamadaEnlaceDadosReceptoraEnquadramento(quadroEnquadrado, size); //enquadramento feito por contagem de caracteres
  PrintQuadro("Mensagem desenquadrada: ", quadroDesenquadrado, size);

  std::cout << "Deteccao de erros:" << std::endl;
  int* quadroEnquadradoCE = CamadaEnlaceDadosReceptoraControleDeErro(quadroDesenquadrado, size);
  PrintQuadro("Quadro com controle de erro retirado: ", quadroEnquadradoCE, size);

  //chama proxima camada
  CamadaDeAplicacaoReceptora(quadroEnquadradoCE, size);
} //fim do metodo CamadaEnlaceDadosReceptora

int* CamadaEnlaceDadosReceptoraEnquadramento(int quadroEnquadrado[], int& size){
  int* quadro;

  switch(tipoDeEnquadramento-1){
    case 0: //contagem de caracteres
      quadro = CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(quadroEnquadrado, size);
      break;
    case 1: //insercao de bytes
      quadro = CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(quadroEnquadrado, size);
      break;
    default:
      exit(1);
      break;
  } //fim do switch case

   return quadro;
} //fim do metodo CamadaEnlaceDadosReceptoraEnquadramento

int* CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(int quadroEnquadrado[], int& size){
  //implementacao de algoritmo
  size = quadroEnquadrado[0] - 1;
  int* quadro = (int*) malloc(4 * size);

  for(int i = 1; i < size + 1; i++){
    quadro[i-1] = quadroEnquadrado[i];
  }

  free(quadroEnquadrado);
  return quadro;
} //fim do metodo CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres

int* CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(int quadroEnquadrado[], int& size){
  //implementacao de algoritmo
  bool first_flag = false;
  bool last_flag = false;
  int first_flag_index;
  int last_flag_index;
  const int flag_size = 8;
  int flag[flag_size] = {0, 0, 0, 0, 1, 1, 1, 1};

  int old_size = size;
  size = size - flag_size * 2;
  int* quadro = (int*) malloc(4 * size);

  int current = 0;
  for(int i = 0; i < old_size; i++){
    if(quadroEnquadrado[i] == flag[current]){
      current++;
      if(current == 8){
        current = 0;
        if(first_flag){
          last_flag = true;
          last_flag_index = i;
        } else {
          first_flag = true;
          first_flag_index = i;
        }
      }
    } else {
      current = 0;
      if(quadroEnquadrado[i] == flag[current]){
        current++;
      }
    }
  }

  for(int i = first_flag_index + 1, j = 0; i < last_flag_index - flag_size + 1, j < size; i++, j++){
    quadro[j] = quadroEnquadrado[i];
  }

  free(quadroEnquadrado);
  return quadro;
} //fim do metodo CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes

int* CamadaEnlaceDadosReceptoraControleDeErro(int quadro[], int& size){
  int* quadroCE;

  switch(tipoDeControleDeErro - 1){
    case 0: //bit de paridade par
      quadroCE = CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(quadro, size);
      break;
    case 1: //CRC
      quadroCE = CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro, size);
      break;
    case 2: //bit de paridade par
      quadroCE = CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(quadro, size);
      break;
    default:
      exit(1);
      break;
  }//fim do switch/case

  return quadroCE;
} //fim do metodo CamadaEnlaceDadosReceptoraControleDeErro

int* CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(int quadro[], int &size){
  int* new_quadro = (int*) malloc(4 * (size-1));
  int one_counter = 0;
  
  for(int i = 0; i < size; i++){
    if(i != size - 1) new_quadro[i] = quadro[i];
    if(quadro[i] == 1){
      one_counter++;
    }
  }

  // adiciona bit de paridade
  one_counter % 2 ? std::cout << "erro detectado" << std::endl : std::cout << "nenhum erro detectado" << std::endl;

  free(quadro);
  size -= 1;

  return new_quadro;
} //fim do metodo CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar

int* CamadaEnlaceDadosReceptoraControleDeErroCRC(int quadro[], int& size){
  //implementacao do algoritmo
  //usar polinomio CRC-32(IEEE802)

  int n = 4;
  int crc_size = n - 1;

  int* new_quadro = (int*) malloc(4 * (size-crc_size));

  // divisor = 1101
  int divisor = 13;

  for(int i=0; i < size - crc_size; i++) {
    new_quadro[i] = quadro[i];
  }

  uint32_t remainder = 0; 
  for(int i = size-1, index = 0; i >= 0; i--, index++){
    remainder += quadro[index] * (int)pow(2,i);
  }

  int aux;
  for (uint32_t bit = size; bit > crc_size; --bit)
  {
    if (remainder & (int)pow(2,(bit-1))){
      aux = remainder;
      aux = aux >> (bit - n);
      remainder = ((aux ^ divisor) << bit - n) | (remainder & ((int)pow(2,(bit-n))-1));
    } 
    else {
      aux = remainder;
      aux = aux >> (bit - n);
      remainder = ((aux ^ 0) << bit - n) | (remainder & ((int)pow(2,(bit-n))-1));
    }
  }
  
  remainder ? std::cout << "erro detectado" << std::endl : std::cout << "nenhum erro detectado" << std::endl;

  size -= crc_size;

  free(quadro);
  return new_quadro;
} //fim do metodo CamadaEnlaceDadosReceptoraControleDeErroCRC


int* CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(int quadro[], int& size){
  return quadro;
}