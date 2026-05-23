#include "cipher_utils.h"

static char rot13(char c) {
    if (!isLetter(c)) return c;
    char base = std::isupper((unsigned char)c) ? 'A' : 'a';
    return (char)(base + (c - base + 13) % 26);
}

static std::string process(const std::string& text) {
    std::string out;
    out.reserve(text.size());
    for (char c : text) out += rot13(c);
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