#include "menu.h"

int main() {
    try {
        std::cout << "Количество: ";
        int count = get<int>();
        Option options[count];
        for (int i = 0; i < count; i++) {
            std::string name;
            std::string funcName;
            std::cout << "Введи имя: ";
            name = get<std::string>();
            std::cout << "Введи функцию: ";
            funcName = get<std::string>();
            std::cin.ignore();
            if (funcName == "negr") {
                options[i].name = name.c_str();
                options[i].callback = negr;
            } else if (funcName == "china") {
                options[i].name = name.c_str();
                options[i].callback = china;
            } else {
                std::cout << "Ввод говно" << std::endl;
            }
        }
        menu(options, count);
        MenuOptionMap options2;
        std::cout << "Количество: ";
        count = get<int>();
        for (int i = 0; i < count; ++i) {
            std::string name;
            std::string funcName;
            std::cout << "Введи имя: ";
            name = get<std::string>();
            std::cout << "Введи функцию: ";
            funcName = get<std::string>();
            if (funcName == "negr") {
                options2[name] = negr;
            } else if (funcName == "china") {
                options2[name] = china;
            }
            else {
                std::cout << "Ввод говно" << std::endl;
            }
        }
        menu(options2);
        return 0;
    }
    catch (const EofException& e) {
        std::cerr << "Обнаружен конец файла при вводе строки." << std::endl;
    }
    catch(const std::exception &e) { 
        std::cerr << e.what() << std::endl;}
}        
