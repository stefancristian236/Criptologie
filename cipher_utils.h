#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

inline char toUp(char c) {
    return (char)std::toupper((unsigned char)c);
}

inline bool isLetter(char c) {
    return std::isalpha((unsigned char)c) != 0;
}

inline std::string readText(std::ifstream& fin) {
    std::string text, line;
    while (std::getline(fin, line)) {
        if (!text.empty()){
            text += '\n';
        }
        text += line;
    }
    return text;
}

inline bool checkFiles(const std::ifstream& fin, const std::ofstream& fout) {
    if (!fin.is_open()) {
        std::cerr << "Eroare : nu pot deschide fiserul de input\n"; return false;
    }
    if (!fout.is_open()) {
        std::cerr << "Eroare : nu pot deschide fisierul de output \n"; return false;
    }
    return true;
}