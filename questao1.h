#ifndef xml_h
#define xml_h

#include <string>
#include <cstddef>
#include "LinkedStack.h"

namespace structures {
class Xml {
 public: 
    Xml(std::string valor);
    bool verificador();
    std::string valor(const std::string& inicio, const std::string& fim, std::size_t& posicao);
 private:
    std::string valor_entrada;
};
  
} //namespace xml

#endif
//-----------------------------------------------

structures::Xml::Xml(std::string valor) {
  valor_entrada = valor;
}

bool structures::Xml::verificador() {
  std::size_t posicao = 0;
  std::size_t tamanho_entrada = valor_entrada.length();
  structures::LinkedStack<std::string> xml_tamanho;

  do {
    std::size_t inicio = valor_entrada.find("<", posicao);
    std::size_t fim = valor_entrada.find(">", inicio);
    
    if (inicio== std::string::npos) { break;} 
    else if (fim == std::string::npos) { return false;}
    
    std::size_t tamanho = (fim + 1) - (inicio);
    std::string marcacao = valor_entrada.substr(inicio, tamanho);
    posicao = fim + 1;
    tamanho_entrada = valor_entrada.length();
    if (marcacao[1] != '/') {
			xml_tamanho.push(marcacao.insert(1, "/"));
		} else if (xml_tamanho.top() == marcacao) {
            xml_tamanho.pop();
        } else {
            return false;
        }
    
    } while (posicao < tamanho_entrada);
    return xml_tamanho.empty();
}

std::string structures::Xml::valor(const std::string& inicio, const std::string& fim, std::size_t& posicao) {
    std::size_t posicao_inicial = valor_entrada.find(inicio, posicao);
    std::size_t posicao_final = valor_entrada.find(fim, posicao_inicial);
    if (posicao_inicial != -1 || posicao_final != -1) {
        posicao = posicao_final + fim.length();
        posicao_inicial += inicio.length();
        std::size_t tamanho = posicao_final - posicao_inicial;
        return valor_entrada.substr(posicao_inicial, tamanho);
    } else {
    posicao = -1;
    return "";
    }
}
