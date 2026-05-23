#include "cipher_utils.h"

static char shiftChar(char c, int k) {
    char base = std::isupper((unsigned char)c) ? 'A' : 'a';
    return (char)(base + ((c - base + k) % 26 + 26) % 26);
}

static std::string process(const std::string& text, int k) {
    std::string out;
    out.reserve(text.size());
    for (char c : text)
        out += isLetter(c) ? shiftChar(c, k) : c;
    return out;
}

int main() {
    std::ifstream fin("date.in");
    std::ofstream fout("date.out");
    if (!checkFiles(fin, fout)) return 1;

    std::string op, keyLine;
    std::getline(fin, op);
    std::getline(fin, keyLine);

    //descifrare -> negarea cheii
    int k = std::stoi(keyLine);
    if (toUp(op[0]) == 'D') k = -k;  

    fout << process(readText(fin), k) << '\n';
    return 0;
}