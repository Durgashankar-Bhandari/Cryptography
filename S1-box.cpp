#include <iostream>
#include <cstring>

const int S1[64] = {
    14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
     0, 15,  7,  4, 14,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
     4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
    15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
};

unsigned char sbox1(unsigned char input) {
    int row = (input & 0b01000000) >> 5 | (input & 0b10000000) >> 7;
    int col = (input & 0b00111110) >> 1;
    return S1[row * 16 + col];
}

int main() {
    unsigned char input;
    std::cout << "Enter a 6-bit input block in binary: ";
    std::cin >> input;
    unsigned char output = sbox1(input);
    std::cout << "Output block: " << output << std::endl;
    return 0;
}

