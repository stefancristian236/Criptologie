//substitutie cu alfabet mixt
#include "cipher_utils.h"

static std::string buildCipherAlpha(const std::string& keyword) {
    std::vector<bool> used(26, false);
    std::string alpha;
    alpha.reserve(26);

    for (char c : keyword) {
        if (isLetter(c)) {
            int i = toUp(c) - 'A';
            if (!used[i]) { alpha += (char)('A' + i); used[i] = true; }
        }
    }
    for (int i = 0; i < 26; ++i)
        if (!used[i]) alpha += (char)('A' + i);

    return alpha;  
}

static std::string applyAlpha(const std::string& text, const std::string& ca) {
    std::string out;
    out.reserve(text.size());
    for (char c : text) {
        if (isLetter(c)) {
            char enc = ca[toUp(c) - 'A'];
            out += std::isupper((unsigned char)c) ? enc : (char)(enc - 'A' + 'a');
        } else {
            out += c;
        }
    }
    return out;
}

static std::string invertAlpha(const std::string& ca) {
    std::string inv(26, ' ');
    for (int i = 0; i < 26; ++i)
        inv[ca[i] - 'A'] = (char)('A' + i);
    return inv;
}

int main() {
    std::ifstream fin("date.in");
    std::ofstream fout("date.out");
    if (!checkFiles(fin, fout)) return 1;

    std::string op, keyword;
    std::getline(fin, op);
    std::getline(fin, keyword);

    std::string ca = buildCipherAlpha(keyword);

    fout << "Alfabet de cifrare:\n"
         << "  Alf1: ABCDEFGHIJKLMNOPQRSTUVWXYZ\n"
         << "  Alf2: " << ca << "\n\n";

    bool doEncrypt = (toUp(op[0]) == 'E');
    std::string result = applyAlpha(readText(fin), doEncrypt ? ca : invertAlpha(ca));
    fout << result << '\n';

    return 0;
}