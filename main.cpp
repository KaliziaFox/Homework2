#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main(int argc, const char *argv[]) {
    if (argc != 3) {
        std::cerr << "Error: Use three parameters\n";
        return 5;
    }
    const std::string mode(argv[1]); // Режим работы
    const std::string file_name(argv[2]); // Имя файла
    unsigned int key;
    std::cout << "Enter key:";
    std::cin >> key;
    if (mode == "encryption") {
        // Режим шифрование
        std::string password;
        std::cout << "Enter password:";
        std::cin >> password;
        unsigned char b1, b2, r1, r2;
        unsigned int block, xore, shift, gamma;
        srand(key);
        std::ofstream put_in_file;
        put_in_file.open(file_name, std::ios::binary);
        for (size_t i = 0; i < password.size(); i += 2) {
            gamma = rand();
            b1 = password[i];
            if (i + 1 < password.size()) {
                b2 = password[i + 1];
            } else {
                b2 = 0u;
            }
            block = ((static_cast<unsigned int>(b1) << 8u | static_cast<unsigned int>(b2)));
            xore = block ^ gamma;
            shift = (xore << 3u) | (xore >> 13u);
            r1 = shift >> 8u;
            r2 = shift;
            put_in_file << r1 << r2;
        }
    } else if (mode == "decryption") {
        // Режим расшифрования
        unsigned char b1, b2;
        unsigned int block, xore, shift, gamma;
        srand(key);
        std::ifstream take_from_file;
        take_from_file.open(file_name, std::ios::binary);
        std::vector<char> result;
        std::string oldstr;
        getline(take_from_file, oldstr);
        take_from_file.close();
        for (size_t i = 0; i < oldstr.size(); i += 2) {
            gamma = rand();
            b1 = oldstr[i];
            if (i + 1 < oldstr.size()) {
                b2 = oldstr[i + 1];
            } else {
                b2 = 0u;
            }
            block = ((static_cast<unsigned int>(b1) << 8u | static_cast<unsigned int>(b2)));
            shift = (block >> 3u) | (block << 13u);
            xore = shift ^ gamma;
            result.push_back(xore >> 8u);
            result.push_back(xore);
        }
        for (char symbol: result) {
            std::cout << symbol;
        }
    }
    return 0;
}

