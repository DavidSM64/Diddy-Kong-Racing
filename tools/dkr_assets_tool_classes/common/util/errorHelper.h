#pragma once

#include <string>
#include <iostream>

// Terminal colors
#define RED_TEXT "\033[1;31m"
#define GREEN_TEXT "\033[1;32m"
#define YELLOW_TEXT "\033[1;33m"
#define BLUE_TEXT "\033[1;34m"
#define MAGENTA_TEXT "\033[1;35m"
#define CYAN_TEXT "\033[1;36m"

#define RESET_TEXT "\033[0m"

// Requires C++17
template<class... Args>
inline void display_error(Args... args) {
    std::cout << RED_TEXT << "Error: ";
    (std::cout << ... << args);
    std::cout << RESET_TEXT << std::endl;
}

// Requires C++17
template<class... Args>
inline void display_error_and_abort(Args... args) {
    display_error(args...);
    std::cout << RED_TEXT << "Aborting!" << RESET_TEXT << std::endl;
    throw 1;
}

