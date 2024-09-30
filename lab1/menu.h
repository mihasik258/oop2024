#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <cstring>
#include <algorithm>

/*!
 \brief Реализация функций меню и обработки опций.
 */
class MenuOptionException : public std::exception {
public:
    /*!
     \brief Конструктор исключения.
     \param message Сообщение об ошибке.
    */
    explicit MenuOptionException(const std::string& message) : message(message) {}

    /*!
     \brief Возвращает сообщение об ошибке.
     \return Сообщение об ошибке.
     */
    const char* what() const noexcept override { return message.c_str(); }

private:
    std::string message;
};
/*!
 * @brief Тип, представляющий карту опций меню.
 *
 * Хранит пары "имя опции" - "функция обратного вызова".
 * Используется для хранения и доступа к опциям меню.
 */
using MenuOptionMap = std::map<std::string, std::function<int()>>;
/*!
 * @brief Структура, представляющая опцию меню.
 */
struct Option {
    /*!
     * @brief Имя опции.
     */
    const char *name;
    /*!
     * @brief Указатель на функцию обратного вызова, выполняющую действия опции.
     */
    int (*callback)();
};

/*!
 * @brief Шаблонная функция для безопасного ввода данных типа T.
 * @tparam T Тип данных, который нужно ввести.
 * @return Введенное значение типа T.
 */
template<class T>
T get() {
    T a;
    while (true) {
        std::cin >> a;
        if (std::cin.eof())
            throw std::runtime_error("Failed to read number: EOF");
        else if (std::cin.bad())
            throw std::runtime_error(std::string("Failed to read number: ") + strerror(errno));
        else
            return a;
    }
}

#endif
