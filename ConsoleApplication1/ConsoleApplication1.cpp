#include <iostream>
#include <string>
#include <bitset>
#include <iomanip>
using namespace std;
// Nhan hai da thuc trong GF(2^n)
unsigned int gf_mul(unsigned int a, unsigned int b, unsigned int irr, int n) {
    unsigned int result = 0;
    for (int i = 0; i < n; i++) {
        if (b & (1u << i)) {
            result ^= (a << i);
        }
    }
    for (int i = 2 * n - 2; i >= n; i--) {
        if (result & (1u << i)) {
            result ^= (irr << (i - n));
        }
    }
    return result & ((1u << n) - 1u);
}
string poly_str(unsigned int p, int n) {
    string s = "";
    bool first = true;
    for (int i = n - 1; i >= 0; i--) {
        if (p & (1u << i)) {
            if (!first) s += " + ";
            if (i == 0) s += "1";
            else if (i == 1) s += "x";
            else s += "x^" + to_string(i);
            first = false;
        }
    }
    return first ? "0" : s;
}
int main() {
    unsigned int a, b;
    int n;
    cout << "Chon truong (4 hoac 8): ";
    if (!(cin >> n) || (n != 4 && n != 8)) {
        cout << "Truong khong hop le.\n";
        return 1;
    }
    cout << "Nhap a va b (he 16): ";
    if (!(cin >> hex >> a >> b) ||
        a >= (1u << n) || b >= (1u << n)) {
        cout << "Gia tri khong hop le.\n";
        return 1;
    }
    unsigned int poly = (n == 4) ? 0x13u : 0x11Bu;
    unsigned int result = gf_mul(a, b, poly, n);
    cout << uppercase << hex;
    cout << "Ket qua: 0x" << a
        << " * 0x" << b
        << " = 0x" << result
        << " trong GF(2^" << dec << n << ")\n";
    cout << "Ket qua da thuc: "
        << poly_str(result, n) << "\n";
    return 0;
}
