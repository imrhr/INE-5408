#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

int main() {

    char xmlfilename[100];

    std::cin >> xmlfilename;  // entrada
    
    
     
    std::ifstream file(xmlfilename);

    std::string xml_string;
    std::string line;
    if (file.is_open()) {
        while (getline(file, line)) {
            xml_string += line;
        }
        file.close();
    } else {
        std::cout << "error\n";
        return -1;
    }

    std::cout << xml_string << std::endl;  // esta linha deve ser removida

    return 0;
}