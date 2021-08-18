#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

#include "questao1.h"
#include "questao2.h"
#include "LinkedQueue.h"

int main() {

    char xmlfilename[100];

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
        std::size_t pos = 0;
        do {
            const std::string codigoimagem = outxml.valor("<img>", "</img>", pos);
            pos = outxml.get_posicao();
            if (pos == -1) {break;}

            structures::Xml novaimagem = structures::Xml(codigoimagem);
            std::size_t nada = 0;

            std::string nome = novaimagem.valor("<name>", "</name>", nada);
            const int altura = std::stoi(novaimagem.valor("<height>", "</height>",  nada));
            const int largura = std::stoi(novaimagem.valor("<width>", "</width>",  nada));
            const std::string dados = novaimagem.valor("<data>", "</data>",  nada);

            if (!(altura > 0 && largura > 0)) {
                std::cout << "error\n";return -1;
            } else {


            structures::Matriz<int> imagem = structures::Matriz<int>(altura, largura);
            imagem.set_toda_matriz(dados);

            using pixel = std::pair<int, int>; structures::LinkedQueue<pixel> fila;
            structures::Matriz<int> R = structures::Matriz<int>(imagem.get_linha(), imagem.get_coluna());
            int label = 1;

            for (int l = 0; l < imagem.get_linha(); l++) {
                for (int c = 0; c < imagem.get_coluna(); c++) {
                    if (!R.get_item_pos(l, c) && imagem.get_item_pos(l, c)) {
                        R.set_item_pos(l, c, label);
                        fila.enqueue({l, c});
                        while (!fila.empty()) {
                            const pixel p = fila.dequeue();
                            int x = p.first;
                            int y = p.second;
                            
                            if (x - 1 >= 0 && !R.get_item_pos(x-1, y)) {
                                if (imagem.get_item_pos(x-1,y)){
                                    R.set_item_pos(x-1, y, label);
                                    fila.enqueue({x-1, y});
                                }
                            }
                            
                            if (x + 1 < imagem.get_linha()) {
                                if (!R.get_item_pos(x+1, y) ){
                                    if(imagem.get_item_pos(x+1, y)){  
                                        R.set_item_pos(x+1, y, label);
                                        fila.enqueue({x+1, y});
                                    }
                                }
                            }
                            
                            if (y - 1 >= 0 && !R.get_item_pos(x, y-1)) {
                                if (imagem.get_item_pos(x, y-1)){
                                    R.set_item_pos(x, y-1, label);
                                    fila.enqueue({x, y-1});
                                }
                                
                            }
                            
                            if (y + 1 < imagem.get_coluna()) {
                                if (!R.get_item_pos(x, y+1) ){
                                    if (imagem.get_item_pos(x, y+1)){
                                        R.set_item_pos(x, y+1, label);
                                        fila.enqueue({x, y+1});
                                    }
                                }
                                
                            }
                        }
                        label++;
                    }
                }
            }
            
            std::cout << nome << " " << label-1 << "\n";  // esta linha deve ser removida
            }
        } while (pos < xmls.length());
    }

    

    return 0;
}