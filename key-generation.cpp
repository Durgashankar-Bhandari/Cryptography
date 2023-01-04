#include <iostream>
#include <cstring>

const int PC1[56] = {
    57, 49, 41, 33, 25, 17,  9,
     1, 58, 50, 42, 34, 26, 18,
    10,  2, 59, 51, 43, 35, 27,
    19, 11,  3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
     7, 62, 54, 46, 38, 30, 22,
    14,  6, 61, 53, 45, 37, 29,
    21, 13,  5, 28, 20, 12,  4
};

const int PC2[48] = {
    14, 17, 11, 24,  1,  5,
     3, 28, 15,  6, 21, 10,
    23, 19, 12,  4, 26,  8,
    16,  7, 27, 20, 13,  2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

const int LS[16] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

void generate_round_keys(unsigned char* key, unsigned char round_keys[16][6]) {
    unsigned char pc1_key[7] = {0};
    for (int i = 0; i < 56; i++) {
        int bit = PC1[i] - 1;
        int byte = bit / 8;
        int offset = bit % 8;
        pc1_key[i / 8] |= (key[byte] >> offset) & 1;
        if (i % 8 != 7) {
            pc1_key[i / 8] <<= 1;
        }
    }
    unsigned char c[4] = {pc1_key[0], pc1_key[1], pc1_key[2], pc1_key[3]};
    unsigned char d[4] = {pc1_key[4], pc1_key[5], pc1_key[6], 0};
    for (int round = 0; round < 16; round++) {
        int shift = LS[round];
        unsigned char c_new[4] = {0};
        unsigned char d_new[4] = {0};
        for (int i = 0; i < 4; i++) {
            c_new[i] = (c[i] << shift) | (c[(i + 1) % 4] >> (8 - shift));
            d_new[i] = (d[i] << shift) | (d[(i + 1) % 4] >> (8 - shift));
        }
        unsigned char cd[8] = {c_new[0], c_new[1], c_new[2], c_new[3], d_new[0], d_new[1], d_new[2], d_new[3]};
        for (int i = 0; i < 48; i++) {
            int bit = PC2[i] - 1;
            int byte = bit / 8;
            int offset = bit % 8;
            round_keys[round][i / 8] |= (cd[byte] >> offset) & 1;
            if (i % 8 != 7) {
                round_keys[round][i / 8] <<= 1;
            }
        }
        std::memcpy(c, c_new, 4);
        std::memcpy(d, d_new, 4);
    }
}

int main() {
    unsigned char key[8];
    unsigned char round_keys[16][6];
    std::cout << "Enter a 64-bit key in hexadecimal: ";
    std::cin >> std::hex >> key[0] >> key[1] >> key[2] >> key[3] >> key[4] >> key[5] >> key[6] >> key[7];
    generate_round_keys(key, round_keys);
    std::cout << "Round keys:" << std::endl;
    for (int round = 0; round < 16; round++) {
        std::cout << "  Round " << round + 1 << ": " << std::hex << (int)round_keys[round][0] << " " << (int)round_keys[round][1] << " " << (int)round_keys[round][2] << " " << (int)round_keys[round][3] << " " << (int)round_keys[round][4] << " " << (int)round_keys[round][5] << std::endl;
    }
    return 0;
}

