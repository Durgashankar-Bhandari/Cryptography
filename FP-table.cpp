#include <iostream>
#include <cstring>

const int FP[64] = {
    40,  8, 48, 16, 56, 24, 64, 32,
    39,  7, 47, 15, 55, 23, 63, 31,
    38,  6, 46, 14, 54, 22, 62, 30,
    37,  5, 45, 13, 53, 21, 61, 29,
    36,  4, 44, 12, 52, 20, 60, 28,
    35,  3, 43, 11, 51, 19, 59, 27,
    34,  2, 42, 10, 50, 18, 58, 26,
    33,  1, 41,  9, 49, 17, 57, 25
};

void final_permutation(unsigned char* input, unsigned char* output) {
    std::memset(output, 0, 8);
    for (int i = 0; i < 64; i++) {
        int bit = FP[i] - 1;
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
    unsigned char output[8];
    std::cout << "Enter an 8-byte input block in hexadecimal: ";
    std::cin >> std::hex >> input[0] >> input[1] >> input[2] >> input[3] >> input[4] >> input[5] >> input[6] >> input[7];
    final_permutation(input, output);
    std::cout << "Output block: " << std::hex << (int)output[0] << " " << (int)output[1] << " " << (int)output[2] << " " << (int)output[3] << " " << (int)output[4] << " " << (int)output[5] << " " << (int)output[6] << " " << (int)output[7] << std::endl;
    return 0;
}
