#include "cipher_utils.h"

static std::string process(const std::string& text) {
    std::string out;
    out.reserve(text.size());
    for (char c : text) {
        if (isLetter(c)) {
            char base = std::isupper((unsigned char)c) ? 'A' : 'a';
            out += (char)(base + 25 - (c - base));   
        } else {
            out += c;
        }
    }
    return out;
}

int main() {
    std::ifstream fin("date.in");
    std::ofstream fout("date.out");
    if (!checkFiles(fin, fout)) return 1;

    std::string op;
    std::getline(fin, op);   

    fout << process(readText(fin)) << '\n';
    return 0;
}