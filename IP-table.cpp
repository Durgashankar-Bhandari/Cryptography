#include <iostream>
#include <cstring>

// The initial permutation table for DES
const int IP[64] = {
    58, 50, 42, 34, 26, 18, 10,  2,
    60, 52, 44, 36, 28, 20, 12,  4,
    62, 54, 46, 38, 30, 22, 14,  6,
    64, 56, 48, 40, 32, 24, 16,  8,
    57, 49, 41, 33, 25, 17,  9,  1,
    59, 51, 43, 35, 27, 19, 11,  3,
    61, 53, 45, 37, 29, 21, 13,  5,
    63, 55, 47, 39, 31, 23, 15,  7
};

void initial_permutation(unsigned char* input, unsigned char* output) {
    for (int i = 0; i < 64; i++) {
        int bit = IP[i] - 1;
        int byte = bit / 8;
        int offset = bit % 8;
        output[i / 8] |= (input[byte] >> offset) & 1;
        if (i % 8 != 7) {
            output[i / 8] <<= 1;
        }
    }
}

int main() {
    unsigned char input[8];
    std::cout << "Enter an 8-byte input block in binary: ";
    std::cin >> input[0] >> input[1] >> input[2] >> input[3] >> input[4] >> input[5] >> input[6] >> input[7];
    unsigned char output[8] = {0};
    initial_permutation(input, output);
    std::cout << "Permuted block: ";
    for (int i = 0; i < 8; i++) {
        std::cout << output[i];
    }
    std::cout << std::endl;
    return 0;
}
