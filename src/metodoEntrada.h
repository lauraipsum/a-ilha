#include <iostream>
#include <fstream>
#include <vector>

class criaJogo {

    std::string nameCena, nameIlha, nameLagos, nameTerrestres_1, nameTerrestres_2, namePlantas_1, namePlantas_2;
    int largura, altura, comprimento;
    int ilha;
    int lagos;
    int terrestre1, terrestre2;
    int plantas1, plantas2;
    std::vector<int> entrada;

  public:
    criaJogo(){}

    // Funcao que le um arquivo e atribui seus valores a variaveis
    void readfile(std::string str){
      std::ifstream file(str);
      if( file.is_open() ){
        file >> this -> nameCena >> this -> largura >> this -> altura >> this -> comprimento; // Linha 1
        file >> this -> nameIlha >> this -> ilha;                                             // Linha 2
        file >> this -> nameLagos >> this -> lagos;                                           // Linha 3
        file >> this -> nameTerrestres_1 >> this-> terrestre1;                                // Linha 4
        file >> this -> nameTerrestres_2 >> this-> terrestre2;                                // Linha 5
        file >> this -> namePlantas_1 >> this -> plantas1;                                    // Linha 6
        file >> this -> namePlantas_2 >> this -> plantas2;                                    // Linha 7
      }
    }

    // Funcao para imprimir um vetor
    void print(std::vector<int> const &input) {
        for (int i = 0; i < input.size(); i++)
            std::cout << input.at(i) << ' ';
    }

    int getL(){
      return largura;
    }

    int getA(){
      return altura;
    }

    int getC(){
      return comprimento;
    }

    int getI(){
      return ilha;
    }

    int getLg(){
      return lagos;
    }

    int getT1(){
      return terrestre1;
    }

    int getT2(){
      return terrestre2;
    }

    int getP1(){
      return plantas1;
    }

    int getP2(){
      return plantas2;
    }
};