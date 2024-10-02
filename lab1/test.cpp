#include "menu.h"
#include <stdexcept>

#include "catch2/catch.hpp"


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
