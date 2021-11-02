#include "CamadaFisica.hpp"
#include "CamadaEnlace.hpp"
#include "Helpers.hpp"
#include <bitset>
#include <iostream>

//transmissora
int tipoDeEnquadramento; //alterar de acordo com o teste
int tipoDeControleDeErro; //alterar de acordo com teste

void CamadaEnlaceDadosTransmissora(int quadro[], int size){

  PrintHeader("CAMADA DE ENLACE TRANSMISSORA");

  int* quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramento(quadro, size);

  PrintQuadro("Mensagem enquadrada: ", quadroEnquadrado, size);

  // controle de erro
  int* quadroCE = CamadaEnlaceDadosTransmissoraControleDeErro(quadroEnquadrado, size);

  PrintQuadro("Quadro com controle de erro: ", quadroCE, size);

  CamadaFisicaTransmissora(quadroCE, size);
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

  int* new_quadro = (int*) malloc(4 * (size+4));

  // divisor = 1101
  int divisor = 13, crc;

  for(int i=0; i<size; i++) {
    new_quadro[i] = quadro[i];
  }
  for(int i=size; i<size+4; i++) {
    new_quadro[i] = 0;
  }

  long quadro_integer = 0; 
  for(int i = 0; i < size; i++){
    quadro_integer += quadro[i] * 2^i;
  }

  PrintQuadro("debug", new_quadro, size+4);
  // 100100000
    uint32_t remainder = 3664;	
    for (uint32_t bit = 32; bit > 0; --bit)
    {
        /** If the uppermost bit is a 1...*/
        if (remainder & 0x80000000)
        {
            remainder ^= divisor; 
            std::cout << remainder << " - " << bit << " ,";
        }
        remainder = (remainder << 1);
    }
    // std::cout << remainder;
    // remainder = remainder >> 5;
    std::bitset<32> crc2(remainder);

    std::cout << crc2 << std::endl;
  
  new_quadro[size]   = (crc & 1000) >> 3;
  new_quadro[size+1] = (crc & 0100) % 1000 >> 2;
  new_quadro[size+2] = (crc & 0010) % 100 >> 1;
  new_quadro[size+3] = (crc & 0001) % 10;

  //  PrintQuadro("debug3", new_quadro, size+4);

  // PrintQuadro("Quadro com controle de erro: ", quadroCE, size);
  return new_quadro;
} //fim do metodo CamadaEnlaceDadosTransmissoraControleDeErroCRC


/* receptora */

void CamadaEnlaceDadosReceptora(int quadroEnquadrado[], int size){

  PrintHeader("CAMADA DE ENLACE RECEPTORA");
  
  std::cout << "Deteccao de erros:" << std::endl;
  int* quadroEnquadradoCE = CamadaEnlaceDadosReceptoraControleDeErro(quadroEnquadrado, size);
  PrintQuadro("Quadro com controle de erro retirado: ", quadroEnquadradoCE, size);

  int* quadroDesenquadrado = CamadaEnlaceDadosReceptoraEnquadramento(quadroEnquadradoCE, size); //enquadramento feito por contagem de caracteres
  PrintQuadro("Mensagem desenquadrada: ", quadroDesenquadrado, size);

  //chama proxima camada
  CamadaDeAplicacaoReceptora(quadroDesenquadrado, size);
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

  for(int i = first_flag_index + 1, j = 0; i < last_flag_index - flag_size + 1; i++, j++){
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
      // CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro, size)
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
  int dividendo = quadro[0], divisor = 1101;

  for (int i=1; i<size+4; i++) {
    dividendo = (dividendo << 1) + quadro[i];
    if(i >= 3) { // a partir de i = 3
      dividendo = dividendo^divisor;
    }
  }
  
  if(dividendo %10000 == 0) {
    std::cout << "nenhum erro detectado";
  } else {
    std::cout << "erro detectado";
  }

  return quadro;
} //fim do metodo CamadaEnlaceDadosReceptoraControleDeErroCRC