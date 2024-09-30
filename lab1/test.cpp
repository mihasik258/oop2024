#include <stdexcept>

#include "catch2/catch.hpp"

using MenuOptionMap = std::map<std::string, std::function<int()>>;

class MenuOptionException : public std::exception {
public:
    explicit MenuOptionException(const std::string& message) : message(message) {}
    const char* what() const noexcept override { return message.c_str(); }

private:
    std::string message;
};

int negr() {
    std::cout << "Солнце еще высоко, возвращайся к работе\n";
    return 0;
}

int china() {
    std::cout << "Всегда найдется азиат, работающий лучше тебя\n";
    return 0;
}

int exitt() {
    return -1;
}

int help() {
    return 1;
}

void printMenu(const MenuOptionMap& options) {
    std::cout << "Доступные опции:\n";
    auto printOption = [](const std::pair<std::string, std::function<int()>>& option) {
        std::cout << option.first << std::endl;
    };
    std::for_each(options.begin(), options.end(), printOption);
}

int menuButOptions(const MenuOptionMap& options) {
    std::string input;
    std::cout << "Введите название опции: ";
    // Заменим inputW на std::getline для тестирования
    std::getline(std::cin, input);
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

MenuOptionMap conv(const Option *options, int count){
    MenuOptionMap cppOptions;
    std::for_each(options, options + count, [&cppOptions](const Option& opt) { cppOptions[opt.name] = opt.callback; });
    return cppOptions;
}

int menu(const Option *options, int count){
  MenuOptionMap options2 = conv(options,count);
  menu(options2);
  return 0;
}

TEST_CASE("Test Menu Functions", "[menu]") {
    SECTION("Test menuButOptions") {
        MenuOptionMap options = {
            {"negr", negr},
            {"china", china},
        };

        SECTION("Valid input") {
            std::stringstream ss;
            std::cin.rdbuf(ss.rdbuf());
            ss << "negr" << std::endl;
            REQUIRE(menuButOptions(options) == 0);
            ss << "china" << std::endl;
            REQUIRE(menuButOptions(options) == 0);
        }

        SECTION("Invalid input") {
            std::stringstream ss;
            std::cin.rdbuf(ss.rdbuf());
            ss << "invalid" << std::endl;
            REQUIRE_THROWS_AS(menuButOptions(options), MenuOptionException);
        }

        SECTION("Ambiguous input") {
            std::stringstream ss;
            std::cin.rdbuf(ss.rdbuf());
            ss << "ch" << std::endl;
            REQUIRE_THROWS_AS(menuButOptions(options), MenuOptionException);
        }
    }

    SECTION("Test menu") {
        MenuOptionMap options = {
            {"negr", negr},
            {"china", china},
        };

        SECTION("Valid input") {
            std::stringstream ss;
            std::cin.rdbuf(ss.rdbuf());
            ss << "negr" << std::endl << "china" << std::endl << "exit" << std::endl;
            REQUIRE(menu(options) == 0);
        }

        SECTION("Invalid input") {
            std::stringstream ss;
            std::cin.rdbuf(ss.rdbuf());
            ss << "invalid" << std::endl << "exit" << std::endl;
            REQUIRE(menu(options) == 0);
        }

        SECTION("Help option") {
            std::stringstream ss;
            std::cin.rdbuf(ss.rdbuf());
            ss << "help" << std::endl << "negr" << std::endl << "exit" << std::endl;
            REQUIRE(menu(options) == 0);
        }

        SECTION("Exit option") {
            std::stringstream ss;
            std::cin.rdbuf(ss.rdbuf());
            ss << "exit" << std::endl;
            REQUIRE(menu(options) == 0);
        }
    }

    SECTION("Test conv") {
        Option options[] = {
            {"negr", negr},
            {"china", china}
        };

        MenuOptionMap expectedOptions = {
            {"negr", negr},
            {"china", china}
        };

        MenuOptionMap actualOptions = conv(options, 2);

        REQUIRE(actualOptions == expectedOptions);
    }
}
