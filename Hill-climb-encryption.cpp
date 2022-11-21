#include <iostream>
#include <string>
using namespace std;
#define M 3
int inverse(int b)
{
	int inv;
	int q, r, r1 = 26, r2 = b, t, t1 = 0, t2 = 1;

	while (r2 > 0) {
		q = r1 / r2;
		r = r1 - q * r2;
		r1 = r2;
		r2 = r;

		t = t1 - q * t2;
		t1 = t2;
		t2 = t;
	}

	if (r1 == 1) {
		inv = t1;
		if (inv < 0)
			inv = inv + 26;
		return inv;
	}

	return -1;
}

void inverseMatrix(int key[][3], int inv[][3])
{
	int C[3][3];
	int A[3][3];
	C[0][0] = key[1][1] * key[2][2] - key[2][1] * key[1][2];
	C[0][1] = -(key[1][0] * key[2][2] - key[2][0] * key[1][2]);
	C[0][2] = key[1][0] * key[2][1] - key[1][1] * key[2][0];
	C[1][0] = -(key[0][1] * key[2][2] - key[2][1] * key[0][2]);
	C[1][1] = key[0][0] * key[2][2] - key[2][0] * key[0][2];
	C[1][2] = -(key[0][0] * key[2][1] - key[2][0] * key[0][1]);
	C[2][0] = key[0][1] * key[1][2] - key[0][2] * key[1][1];
	C[2][1] = -(key[0][0] * key[1][2] - key[1][0] * key[0][2]);
	C[2][2] = key[0][0] * key[1][1] - key[1][0] * key[0][1];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			A[i][j] = C[j][i];
		}
	}
	int det = key[0][0] * C[0][0] + key[0][1] * C[0][1] + key[0][2] * C[0][2];

	if (det == 0 || det % 2 == 0 || det % 13 == 0) {
		printf("The text cannot be encrypted. Take valid key.\n");
		exit(1);
	}
	int invs = inverse(det);
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			inv[i][j] = A[i][j] * invs;
		}
	}
	printf("\nInverse of a Key-\n\n");
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (inv[i][j] >= 0) {
				inv[i][j] = inv[i][j] % 26;
				printf("%3d", inv[i][j]);
			}
			else {
				for (int x = 0;; x++) {
					if (x * 26 + inv[i][j] > 0) {
						inv[i][j] = x * 26 + inv[i][j];
						break;
					}
				}
				printf("%3d", inv[i][j]);
			}
		}
		printf("\n");
	}
}
string encrypt(string text, int key[][3])
{
	string c = "";
	int k = 0;
	int input[3];
	while (k < text.length()) {
		input[0] = text[k++] - 65;
		input[1] = text[k++] - 65;
		input[2] = text[k++] - 65;
		for (int i = 0; i < M; i++) {
			int cipher = 0;
			for (int j = 0; j < M; j++) {
				cipher += key[i][j] * input[j];
			}
			c += (cipher % 26) + 65;
		}
	}
	return c;
}
string decrypt(string s, int inv[][3])
{
	string d = "";
	int k = 0;
	int input[3];
	while (k < s.length()) {
		input[0] = s[k++] - 65;
		input[1] = s[k++] - 65;
		input[2] = s[k++] - 65;
		for (int i = 0; i < M; i++) {
			int decipher = 0;
			for (int j = 0; j < M; j++) {
				decipher += inv[i][j] * input[j];
			}
			d += (decipher % 26) + 65;
		}
	}
	return d;
}
int main()
{
	int key[3][3] = {
		{ 7, 4, 17 },
		{ 12, 1, 12 },
		{ 0, 15, 5 }
	};
	string text = "DURGASHANKARBHANDARIX";
	string c = encrypt(text, key);
	cout << "Corresponding cipher text is - " << c;
	int inv[3][3];
	inverseMatrix(key, inv);
	cout << "\nCorresponding decrypted text is - " << decrypt(c, inv);
	return 0;
}
