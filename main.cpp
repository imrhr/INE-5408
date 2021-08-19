#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

#include "questao1.h"
#include "questao2.h"
#include "LinkedQueue.h"

int main() {

    char xmlfilename[100];
    const std::string imgb= "<img>";
    const std::string imge= "</img>";
    const std::string nameb= "<name>";
    const std::string namee= "</name>";
    const std::string he= "</height>";
    const std::string hb= "<height>";
    const std::string wb= "<width>";
    const std::string we= "</width>";
    const std::string datab= "<data>";
    const std::string datae= "</data>";
    std::size_t nada = 0;
    std::size_t pos = 0;

    std::cin >> xmlfilename;  // entrada
    std::ifstream file(xmlfilename); std::string xmls; std::string linha;

    if (file.is_open()) {
        do { xmls += linha; } while (getline(file, linha));
        file.close();
    } else { std::cout << "error\n"; return -1;}

    structures::Xml outxml = structures::Xml(xmls);

    if(!outxml.verificador() ){
        std::cout << "error\n";
        return -1;
    } else {
        
        do {
            const std::string codigoimagem = outxml.valor(imgb, imge, pos);
            pos = outxml.get_posicao();
            if (pos == -1) {break;}

            structures::Xml novaimagem = structures::Xml(codigoimagem);

            std::string nome = novaimagem.valor(nameb, namee, nada);
            const int altura = std::stoi(novaimagem.valor(hb, he,  nada));
            const int largura = std::stoi(novaimagem.valor(wb, we,  nada));
            const std::string dados = novaimagem.valor(datab, datae,  nada);

            if (!(altura > 0 && largura > 0)) {
                std::cout << "error\n";return -1;
            } else {


            structures::Matriz<int> imagem = structures::Matriz<int>(altura, largura);
            imagem.set_toda_matriz(dados);

            using pixel = std::pair<int, int>; structures::LinkedQueue<pixel> fila;
            structures::Matriz<int> R = structures::Matriz<int>(imagem.get_linha(), imagem.get_coluna());
            int rotulo = 1;

            for (int l = 0; l < imagem.get_linha(); l++) {
                for (int c = 0; c < imagem.get_coluna(); c++) {
                    if (!R.get_item_pos(l, c) && imagem.get_item_pos(l, c)) {
                        R.set_item_pos(l, c, rotulo);
                        fila.enqueue({l, c});
                        while (!fila.empty()) {
                            const pixel p = fila.dequeue();
                            int x = p.first;
                            int y = p.second;
                            
                            if (x - 1 >= 0 && !R.get_item_pos(x-1, y)) {
                                if (imagem.get_item_pos(x-1,y)){
                                    R.set_item_pos(x-1, y, rotulo);
                                    fila.enqueue({x-1, y});
                                }
                            }
                            
                            if (x + 1 < imagem.get_linha()) {
                                if (!R.get_item_pos(x+1, y) ){
                                    if(imagem.get_item_pos(x+1, y)){  
                                        R.set_item_pos(x+1, y, rotulo);
                                        fila.enqueue({x+1, y});
                                    }
                                }
                            }
                            
                            if (y - 1 >= 0 && !R.get_item_pos(x, y-1)) {
                                if (imagem.get_item_pos(x, y-1)){
                                    R.set_item_pos(x, y-1, rotulo);
                                    fila.enqueue({x, y-1});
                                }
                                
                            }
                            
                            if (y + 1 < imagem.get_coluna()) {
                                if (!R.get_item_pos(x, y+1) ){
                                    if (imagem.get_item_pos(x, y+1)){
                                        R.set_item_pos(x, y+1, rotulo);
                                        fila.enqueue({x, y+1});
                                    }
                                }
                                
                            }
                        }
                        rotulo++;
                    }
                }
            }
            
            std::cout << nome << " " << rotulo-1 << "\n";  // esta linha deve ser removida
            }
        } while (pos < xmls.length());
        
    }

    

    return 0;
}