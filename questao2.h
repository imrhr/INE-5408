#ifndef MATRIZ_QUESTAO2
#define MATRIZ_QUESTAO2

#include <cstdint>
#include <stdexcept>
#include <utility>
#include "LinkedQueue.h"

namespace structures{

template<typename T>
class Matriz {
 public:

    Matriz(int linhas, int colunas);
	T get_item_pos(int linha, int coluna);
	void set_item_pos(int linha, int coluna, T& dado );
    int get_linha();
    int get_coluna();
    ~Matriz();

 private:
    int linhas_;
    int colunas_;
    T* conteudos;
};

}  // namespace structures

#endif  // MATRIZ_QUESTAO2

structures::Matriz::Matriz(int linhas, int colunas) {
    linhas_ = linhas; colunas_ = colunas;
    conteudos = new T[linhas_];
    for (int l = 0; l < linhas_; l++) {
        conteudos[l] = new T[colunas_];
        for (int c = 0; c < colunas_; c++) {
            conteudos[l][c] = 0;
        }
    }
}

T structures::Matriz::get_item_pos(int linha, int coluna) {
    if (linha > linhas_ || coluna > colunas_) {
        throw std::out_of_range("Posição inválida");
    }
    return conteudos[linha][coluna];
}

void structures::Matriz::set_item_pos(int linha, int coluna, T& dado) {
    if (linha > linhas_ || coluna > colunas_) {
        throw std::out_of_range("Posição inválida");
    }
    conteudos[linha][coluna] = dado;
}

int structures::Matriz::get_linha(){
    return linhas_;
}

int structures::Matriz::get_coluna(){
    return colunas_;
}

structures::Matriz::~Matriz() {
    for (int l = 0; l < linhas_; i++) {
        delete [] conteudos[l];
    }
    delete [] conteudos;
}
