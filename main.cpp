#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

#include "xml.h"
#include "questao2.h"

int main() {

    char xmlfilename[100];

    std::cin >> xmlfilename;  // entrada
    std::ifstream file(xmlfilename);
    std::string xmls;
    std::string linha;
    if (file.is_open()) {
        do{ xmls += linha;}while (getline(file, linha));
        file.close();
    } else {
        std::cout << "error\n";
        return -1;
    }

    std::cout << xml_string << std::endl;  // esta linha deve ser removida

    return 0;
}