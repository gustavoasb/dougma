#include "Helpers.hpp"
#include <iostream>

void PrintQuadro(std::string mensagem, int* quadro, int size){
  std::cout << mensagem;
  for(int i = 0; i < size; i++){
    std::cout << quadro[i];
  }
  std::cout << std::endl;
}

void PrintDivider(){
  std::cout << "============================= " << std::endl;
}

void PrintHeader(std::string mensagem){
  PrintDivider();
  std::cout << mensagem << std::endl;
}