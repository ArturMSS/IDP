#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <bitset>
#include <iomanip>

using namespace std;

// Mapeamento dos caracteres Base64 para seus valores binários (0-63)
unordered_map<char, int> base64_map = [] {
    unordered_map<char, int> m;
    string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    for (int i = 0; i < chars.size(); ++i) {
        m[chars[i]] = i;
    }
    return m;
}();

// Função para decodificar uma string Base64 em bytes
vector<unsigned char> base64_decode(const string& input) {
    string binary_string;

    // Converte cada caractere Base64 em 6 bits
    for (char c : input) {
        if (c == '=') continue; // ignorar padding
        int val = base64_map[c];
        binary_string += bitset<6>(val).to_string();
    }

    vector<unsigned char> decoded_bytes;

    // Agrupa os bits de 8 em 8 para formar bytes
    for (size_t i = 0; i + 8 <= binary_string.size(); i += 8) {
        bitset<8> byte(binary_string.substr(i, 8));
        decoded_bytes.push_back(static_cast<unsigned char>(byte.to_ulong()));
    }

    return decoded_bytes;
}

// Função para converter os bytes decodificados para hexadecimal
string to_hex_string(const vector<unsigned char>& bytes) {
    ostringstream oss;
    for (unsigned char byte : bytes) {
        oss << hex << setw(2) << setfill('0') << (int)byte;
    }
    return oss.str();
}

int main() {
    string base64_input;
    getline(cin, base64_input); // Lê a linha da entrada padrão

    vector<unsigned char> decoded = base64_decode(base64_input);
    string hex_output = to_hex_string(decoded);

    cout << hex_output << endl;

    return 0;
}
