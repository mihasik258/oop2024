#include "menu.h"

/*!
 \brief Функция, вызываемая при выборе опции "negr".
 \return 0 в случае успеха.
 */
int negr() {
    std::cout << "Солнце еще высоко, возвращайся к работе\n";
    return 0;
}

/**
 * @brief Функция, вызываемая при выборе опции "china".
 * @return 0 в случае успеха.
 */
int china() {
    std::cout << "Всегда найдется азиат, работающий лучше тебя\n";
    return 0;
}

/**
 * @brief Функция, вызываемая при выборе опции "exit".
 * @return -1, чтобы выйти из меню.
 */
int exitt() {
    return -1;
}

/**
 * @brief Функция, вызываемая при выборе опции "help".
 * @return 1, чтобы вывести справку.
 */
int help() {
    return 1;
}

/**
 * @brief Выводит список доступных опций в меню.
 * @param options Карта, содержащая опции меню.
 */
void printMenu(const MenuOptionMap& options) {
    std::cout << "Доступные опции:\n";
    auto printOption = [](const std::pair<std::string, std::function<int()>>& option) {
        std::cout << option.first << std::endl;
    };
    std::for_each(options.begin(), options.end(), printOption);
}

/**
 * @brief Обрабатывает ввод пользователя и выполняет соответствующую опцию меню.
 * @param options Карта, содержащая опции меню.
 * @return 0 в случае успеха, -1 если пользователь выбрал "exit".
 */
int menuButOptions(const MenuOptionMap& options) {
    std::string input;
    std::cout << "Введите название опции: ";
    std::getline(std::cin, input); // Заменили inputW на std::getline

    auto findMatchingOption = [&input](const std::pair<std::string, std::function<int()>>& option) {
        return option.first.find(input) == 0;
    };

    std::vector<std::pair<std::string, std::function<int()>>> matchingOptions;
    std::copy_if(options.begin(), options.end(), std::back_inserter(matchingOptions), findMatchingOption);

    if (matchingOptions.size() == 0) {
        throw MenuOptionException("Неверный ввод!");
    } else if (matchingOptions.size() > 1) {
        throw MenuOptionException("Неоднозначный ввод! Найдено несколько опций.");
    }

    int ch = matchingOptions[0].second();
    if (ch == -1) {
        return -1;
    }
    if (ch == 1) {
        printMenu(options);
    }
    return 0;
}

/*!
 /brief Главный цикл меню.
 /param options Карта, содержащая опции меню.
 /return 0 в случае успеха.
 */
int menu(const MenuOptionMap& options) {
    try {
        if (options.find("help") != options.end() || options.find("exit") != options.end()) {
            throw MenuOptionException("Опции 'help' и 'exit' не должны присутствовать в массиве!");
        }

        MenuOptionMap newOptions = options;
        newOptions["help"] = help;
        newOptions["exit"] = exitt;

        while (1) {
            try {
                if (menuButOptions(newOptions) == -1) {
                    break;
                }
            } catch (const MenuOptionException &e) {
                std::cerr << "Ошибка: " << e.what() << std::endl;
            }
        }
    }
    catch (const MenuOptionException &e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    return 0;
}

/**
 * @brief Преобразует массив Option в карту MenuOptionMap.
 * @param options Массив Option.
 * @param count Размер массива Option.
 * @return Карта MenuOptionMap, содержащая опции.
 */
MenuOptionMap conv(const Option *options, int count){
    MenuOptionMap cppOptions;
    std::for_each(options, options + count, [&cppOptions](const Option& opt) { cppOptions[opt.name] = opt.callback; });
    return cppOptions;
}

/**
 * @brief Запускает меню с использованием массива Option.
 * @param options Массив Option.
 * @param count Размер массива Option.
 * @return 0 в случае успеха.
 */
int menu(const Option *options, int count){
    MenuOptionMap options2 = conv(options,count);
    menu(options2);
    return 0;
}

