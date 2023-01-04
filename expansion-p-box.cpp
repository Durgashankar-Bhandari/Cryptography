#include <iostream>
#include <cstring>

const int E[48] = {
    32,  1,  2,  3,  4,  5,
     4,  5,  6,  7,  8,  9,
     8,  9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32,  1
};


void expansion_pbox(unsigned char* input, unsigned char* output) {
    std::memset(output, 0, 6);
    for (int i = 0; i < 48; i++) {
        int bit = E[i] - 1;
        int byte = bit / 8;
        int offset = bit % 8;
        output[i / 8] |= (input[byte] >> offset) & 1;
        if (i % 8 != 7) {
            output[i / 8] <<= 1;
        }
    }
}

int main() {
    unsigned char input[4];
    std::cout << "Enter a 4-byte input block in binary: ";
    std::cin >> input[0] >> input[1] >> input[2] >> input[3];
    unsigned char output[6] = {0};
    expansion_pbox(input, output);
    std::cout << "Expanded block: ";
    for (int i = 0; i < 6; i++) {
        std::cout << output[i];
    }
    std::cout << std::endl;
    return 0;
}
