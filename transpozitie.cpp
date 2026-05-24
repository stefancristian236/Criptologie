#include "cipher_utils.h"

static std::vector<int> columnOrder(const std::string& key) {
    int cols = (int)key.size();
    std::vector<int> order(cols);
    for (int i = 0; i < cols; ++i) order[i] = i;
    std::sort(order.begin(), order.end(), [&](int a, int b){
        return toUp(key[a]) < toUp(key[b]);
    });
    return order;
}

static std::string encrypt(const std::string& text, const std::string& key) {
    int cols = (int)key.size();

    std::string clean;
    for (char c : text)
        if (isLetter(c)) clean += toUp(c);

    while ((int)clean.size() % cols != 0) clean += 'X';
    int rows = (int)clean.size() / cols;

    std::vector<int> order = columnOrder(key);

    std::string out;
    out.reserve(clean.size() + cols); 
    
    for (size_t i = 0; i < order.size(); ++i) {
        int col = order[i];
        for (int row = 0; row < rows; ++row) {
            out += clean[row * cols + col];
        }
        if ((i + 1) % 5 == 0) {
            out += '\n';
        }
       if ((i + 1) % 5 != 0) {
            out += ' ';
       }
    }

    return out;
}

static std::string decrypt(const std::string& text, const std::string& key) {
    int cols = (int)key.size();

    std::string clean;
    for (char c : text)
        if (isLetter(c)) clean += toUp(c);

    int total = (int)clean.size();
    int rows = total / cols;   

    std::vector<int> order = columnOrder(key);

    std::vector<std::vector<char>> grid(rows, std::vector<char>(cols));
    int pos = 0;
    for (int col : order)
        for (int row = 0; row < rows; ++row)
            grid[row][col] = clean[pos++];

    std::string out;
    out.reserve(total);
    for (int row = 0; row < rows; ++row)
        for (int col = 0; col < cols; ++col)
            out += grid[row][col];

    return out;
}

int main() {
    std::ifstream fin("date.in");
    std::ofstream fout("date.out");
    if (!checkFiles(fin, fout)) return 1;

    std::string op, key;
    std::getline(fin, op);
    std::getline(fin, key);

    std::vector<int> order = columnOrder(key);
    bool doEncrypt = (toUp(op[0]) == 'E');
    std::string result = doEncrypt ? encrypt(readText(fin), key)
                                   : decrypt(readText(fin), key);
    fout << result << '\n';

    return 0;
}