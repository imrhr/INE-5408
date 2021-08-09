#ifndef xml_h
#define xml_h

#include <string>
#include <cstddef>
#include "LinkedStack.h"

namespace processador_xml {
class xml {
 public: 
    xml(const std::string& valor_xml);
    bool verificador();
    std::string valor(const std::string& inicio,
                    const std::string& fim,
                    std::size_t& posicao);
 private:
    std::string xml_string;
};
  
} //namespace xml

#endif
//-----------------------------------------------

processador_xml::xml::xml(const std::string& xml_value) {
  xml_string = xml_value;
}

bool processador_xml::xml::verificador() {
  structures::LinkedStack<std::string> xml_tamanho;
  
  std::size_t posicao = 0;
  while (posicao < xml.length()) {
    
    std::size_t inicio_string = xml.find("<", posicao);
    std::size_t fim_string = xml.find(">", char_begin);
    
    if (inicio_string == std::string::npos()) {
      break;
    }
    
    if (fim_string == std::string::npos()) {
      return false;
    }
    
    std::size_t tamanho = (fim_string - inicio_string) + 1;
    std::string marcacao = xml.substr(inicio_string, tamanho);
    posicao = fim_string + 1;
    if (marcacao[1] != '/') {
			xml_tamanho.push(marcacao.insert(1, "/"));
		} else if (xml_tamanho.top() == marcacao) {
            xml_tamanho.pop();
        } else {
            return false;
        }
    }
    return xml_tamanho.empty();
}

std::string processador_xml::XML::valor(const std::string& inicio,
                                         const std::string& fim,
                                         std::size_t& posicao) {
    std::size_t posicao_inicial = xml.find(inicio, posicao);
    std::size_t posicao_final = xml.find(fim, posicao_inicial);
    
    if (posicao_inicial == std::string::npos ||
        posicao_final == std::string::npos) {
        posicao = std::string::npos;
        return "";
    } else {
        posicao = posicao_final + fim.length();
        posicao_inicial += inicio.length();
        std::size_t tamanho = posicao_final - posicao_inicial;
        return xml.substr(posicao_inicial, tamanho);
    }
}
