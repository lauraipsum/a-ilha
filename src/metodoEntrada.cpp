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

    // Preenche um vetor com o valores do arquivo
    void saida () {
      entrada.push_back (this -> largura);
      entrada.push_back (this -> altura);
      entrada.push_back (this -> comprimento);
      entrada.push_back (this -> ilha);
      entrada.push_back (this -> lagos);
      entrada.push_back (this -> terrestre1);
      entrada.push_back (this -> terrestre2);
      entrada.push_back (this -> plantas1);
      entrada.push_back (this -> plantas2);

      // Imprime o vetor preenchido para confirmacao dos dados
      // A funcao foi deixada como comentario por nao fazer parte do programa
      // print(entrada);
    }
};

// Executa o código conferindo se algum arquivo foi dado como entrada
int main( int argc , char **arquivo ){
  if( argc > 1 ){
    criaJogo game;
    game.readfile(arquivo[1]);
    game.saida();
  } else {
    std::cerr << "Informe o arquivo.\n";
    return 1;
  }
  return 0;
}