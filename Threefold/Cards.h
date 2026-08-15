#pragma once
#include <iostream>
#include <string>

class Cards {
public:
    std::string suit;
    std::string rank;

    void show() const {
        std::cout << rank << suit << std::endl;
    }
};
