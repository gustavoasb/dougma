#include "CamadaFisica.hpp"
#include "CamadaEnlace.hpp"
#include <iostream>

//transmissora
int tipoDeEnquadramento; //alterar de acordo com o teste

int* CamadaEnlaceDadosTransmissoraEnquadramento(int quadro[], int size){
  std::cout << "Escolha um tipo de enquadramento:" << std::endl;
  std::cout << "1 - Contagem de Caracteres" << std::endl;
  std::cout << "2 - Insercao de Bytes" << std::endl;
  std::cin >> tipoDeEnquadramento;

  if (std::cin.fail()) {
    std::cout << "Opcao invalida";
  }
  
  switch(tipoDeEnquadramento-1){
    case 0: { //contagem de caracteres  
      int* quadroEnquadrado = (int*) malloc(4 * (size + 1));
      quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(quadro, size);
      return quadroEnquadrado;
    } break;
    case 1: { //insercao de bytes
      int* quadroEnquadrado = (int*) malloc(4 * (size + 16)); //flag_size * 2
      quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(quadro, size);
      return quadroEnquadrado;
    } break;
    default: {
      std::cout << "Opcao invalida";
      exit(1);
    } break;
  } //fim do switch case
} //fim do metodo CamadaEnlaceDadosTransmissoraEnquadramento

void CamadaEnlaceDadosTransmissora(int quadro[], int size){
  std::cout << "============================= " << std::endl;
  std::cout << "CAMADA DE ENLACE TRANSMISSORA" << std::endl;
  int* quadroEnquadrado = (int*) malloc(4 * (size + 1));
  quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramento(quadro, size);
  CamadaEnlaceDadosTransmissoraControleDeErro(quadroEnquadrado, size);  

  //proxima etapa do trabalho
//   CamadaEnlaceDadosTransmissoraControleDeErro(quadro);
  
  //chama proxima camada
  if(tipoDeEnquadramento - 1 == 0) {
    CamadaFisicaTransmissora(quadroEnquadrado, size + 1); //enquadramento feito por contagem de caracteres
  } else {
    CamadaFisicaTransmissora(quadroEnquadrado, size + 16); //enquadramento feito por insercao de bytes
  }
} //fim do metodo CamadaEnlaceDadosTransmissora

int* CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(int quadro[], int size){
  //implementacao de algoritmo
  int new_size = size + 1;
  int* quadroEnquadrado = (int*) malloc(4 * (new_size));

  quadroEnquadrado[0] = new_size;
  for(int i = 1; i < new_size; i++){
    quadroEnquadrado[i] = quadro[i-1];
  }

  std::cout << "Mensagem enquadrada: ";
  for(int i = 0; i < new_size; i++){
    std::cout << quadroEnquadrado[i];
  }
  std::cout << std::endl;

  return quadroEnquadrado;
} //fim do metodo CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres

int* CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(int quadro[], int size){
  //implementacao de algoritmo
  const int flag_size = 8;
  int* quadroEnquadrado = (int*) malloc(4 * (size + (flag_size * 2)));
  int flag[flag_size] = {0, 0, 0, 0, 1, 1, 1, 1};
  
  for(int i = 0; i < flag_size; i++){
    quadroEnquadrado[i] = flag[i];
  }

  for(int i = flag_size, j = 0; i < flag_size + size; i++, j++){
    quadroEnquadrado[i] = quadro[j]; 
  }

  for(int i = flag_size + size, j = 0; i < flag_size * 2 + size; i++, j++){
    quadroEnquadrado[i] = flag[j];
  }

  std::cout << "Mensagem enquadrada: ";
  for(int i = 0; i < size + (flag_size * 2); i++){
    std::cout << quadroEnquadrado[i];
  }
  std::cout << std::endl;

  return quadroEnquadrado;
} //fim do metodo CamadaEnlaceDadosTransmissoraInsercaoDeBytes


void CamadaEnlaceDadosTransmissoraControleDeErro(int quadro[], int size){
  int tipoDeControleDeErro = 0; //alterar de acordo com teste

  switch(tipoDeControleDeErro){
    case 0: //bit de paridade par
      CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro, size);
      break;
    case 1: //CRC
      CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro, size);
      break;
    default:
      exit(1);
      break;
  }//fim do switch/case
} //fim do metodo CamadaEnlaceDadosTransmissoraControleDeErro

//receptora

void CamadaEnlaceDadosReceptora(int quadroEnquadrado[], int size){
  int new_size;
  if(tipoDeEnquadramento - 1 == 0) {
    new_size = size - 1;
  } else {
    new_size = size - 16;
  }
  
  int* quadro = (int*) malloc(4 * (new_size));
  quadro = CamadaEnlaceDadosReceptoraEnquadramento(quadroEnquadrado, size); //enquadramento feito por contagem de caracteres
  CamadaEnlaceDadosReceptoraControleDeErro(quadro, size);

  std::cout << "============================= " << std::endl;
  std::cout << "CAMADA DE ENLACE RECEPTORA " << std::endl;
  std::cout << "Mensagem desenquadrada: ";
  for(int i = 0; i < new_size; i++){
    std::cout << quadro[i];
  }
  std::cout << std::endl;

  //chama proxima camada
  CamadaDeAplicacaoReceptora(quadro, new_size);
} //fim do metodo CamadaEnlaceDadosReceptora

int* CamadaEnlaceDadosReceptoraEnquadramento(int quadroEnquadrado[], int size){
  int* quadro = (int*) malloc(4 * (size));

  switch(tipoDeEnquadramento-1){
    case 0: //contagem de caracteres
      quadro = CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(quadroEnquadrado);
      return quadro;
      break;
    case 1: //insercao de bytes
      quadro = CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(quadroEnquadrado, size);
      return quadro;
      break;
    default:
      exit(1);
      break;
  } //fim do switch case
} //fim do metodo CamadaEnlaceDadosReceptoraEnquadramento

int* CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(int quadroEnquadrado[]){
  //implementacao de algoritmo
  int new_size = quadroEnquadrado[0];
  int* quadro = (int*) malloc(4 * (new_size - 1));

  for(int i = 1; i < new_size; i++){
    quadro[i-1] = quadroEnquadrado[i];
  }

  return quadro;
} //fim do metodo CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres

int* CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(int quadroEnquadrado[], int size){
  //implementacao de algoritmo
  bool first_flag = false;
  bool last_flag = false;
  int first_flag_index;
  int last_flag_index;
  const int flag_size = 8;
  int flag[flag_size] = {0, 0, 0, 0, 1, 1, 1, 1};

  int* quadro = (int*) malloc(4 * (size - flag_size * 2));

  int current = 0;
  for(int i = 0; i < size; i++){
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

  return quadro;
} //fim do metodo CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes

void CamadaEnlaceDadosReceptoraControleDeErro(int quadro[], int size){
  int tipoDeControleDeErro = 0; //alterar de acordo com teste

  switch(tipoDeControleDeErro){
    case 0: //bit de paridade par
      CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(quadro, size);
      break;
    case 1: //CRC
      // CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro, size)
      break;
    default:
      exit(1);
      break;
  }//fim do switch/case
} //fim do metodo CamadaEnlaceDadosReceptoraControleDeErro

int* CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(int quadro[], int size){
  int* new_quadro = (int*) malloc(4 * (size+1));
  for(int i = 0; i < size; i++){
    new_quadro[i] = quadro[i];
  }
  new_quadro[size] = 0;
  return new_quadro;
} //fim do metodo CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar

void CamadaEnlaceDadosTransmissoraControleDeErroCRC(int quadro[]){
  //implementacao do algoritmo
  //usar polinomio CRC-32(IEEE802)
} //fim do metodo CamadaEnlaceDadosTransmissoraControleDeErroCRC

void CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar(int quadro[]){
  //implementacao do algoritmo
} //fim do metodo CamadaEnlaceDadosReceptoraControleDeErroBitParidadePar

void CamadaEnlaceDadosReceptoraControleDeErroCRC(int quadro[]){
  //implementacao do algoritmo
  //usar polinomio CRC-32(IEEE802)
} //fim do metodo CamadaEnlaceDadosReceptoraControleDeErroCRC