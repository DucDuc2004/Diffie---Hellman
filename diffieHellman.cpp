#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <cmath>

// Chuyển ký tự thành mã nhị phân (7 bits)
std::string kyTuThanhNhiPhan7(char c) {
    std::bitset<7> b(c); // Sử dụng 7 bits cho mỗi ký tự ASCII
    return b.to_string();
}

// Chuyển chuỗi ký tự thành chuỗi nhị phân (7 bits mỗi ký tự)
std::string chuoiThanhNhiPhan(const std::string &str) {
    std::string binaryString = "";
    for (char c : str) {
        binaryString += kyTuThanhNhiPhan7(c);
    }
    return binaryString;
}

// Chuyển chuỗi nhị phân thành số nguyên 
unsigned long long nhiPhanThanhSoNguyen(const std::string &binaryString) {
    unsigned long long value = 0;
    for (char c : binaryString) {
        value = (value << 1) + (c - '0');
    }
    return value;
}

// Tính toán mô-đun lũy thừa
unsigned long long moduloLuyThua(unsigned long long base, unsigned long long exponent, unsigned long long modulus) {
    if (modulus == 1)
        return 0;
    unsigned long long result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

// Tính khóa Diffie-Hellman
unsigned long long diffieHellman(unsigned long long base, unsigned long long privateKey, unsigned long long primeModulus) {
    return moduloLuyThua(base, privateKey, primeModulus);
}

// Tính toán hệ số nén
double tinhHeSoNen(const std::string &inputKey, unsigned long long outputKey) {
    std::string binaryInputKey = chuoiThanhNhiPhan(inputKey);
    unsigned long long inputKeyBits = binaryInputKey.length();
    unsigned long long outputKeyBits = static_cast<unsigned long long>(log2(outputKey)) + 1;
    return static_cast<double>(inputKeyBits) / outputKeyBits;
}

// Chuyển chuỗi nhị phân thành ma trận 7 cột
std::vector<std::string> chuoiNhiPhanThanhMaTran(const std::string &binaryString) {
    std::vector<std::string> matrix;
    for (size_t i = 0; i < binaryString.length(); i += 7) {
        matrix.push_back(binaryString.substr(i, 7));
    }
    return matrix;
}

// In ma trận nhị phân với khoảng trắng giữa các bit
void inMaTran(const std::vector<std::string> &matrix) {
    for (const std::string &row : matrix) {
        for (char bit : row) {
            std::cout << bit << ' ';
        }
        std::cout << std::endl;
    }
}

int main() {
    // Nhập các khóa đầu vào
    std::string alicePrivateKeyStr;
    std::string bobPrivateKeyStr;
    unsigned long long base;
    unsigned long long primeModulus;
    
    std::cout << "Enter Alice's private key: ";
    std::cin >> alicePrivateKeyStr;
    std::cout << "Enter Bob's private key: ";
    std::cin >> bobPrivateKeyStr;
    std::cout << "Enter base: ";
    std::cin >> base;
    std::cout << "Enter prime modulus: ";
    std::cin >> primeModulus;

    // Chuyển đổi khóa riêng từ nhị phân sang số nguyên
    unsigned long long alicePrivateKey = nhiPhanThanhSoNguyen(chuoiThanhNhiPhan(alicePrivateKeyStr));
    unsigned long long bobPrivateKey = nhiPhanThanhSoNguyen(chuoiThanhNhiPhan(bobPrivateKeyStr));

    // Tính khóa công khai
    unsigned long long alicePublicKey = diffieHellman(base, alicePrivateKey, primeModulus);
    unsigned long long bobPublicKey = diffieHellman(base, bobPrivateKey, primeModulus);

    // Tính khóa chung
    unsigned long long sharedSecretAlice = diffieHellman(bobPublicKey, alicePrivateKey, primeModulus);
    unsigned long long sharedSecretBob = diffieHellman(alicePublicKey, bobPrivateKey, primeModulus);

    // Tính hệ số nén
    double compressionRatioAlice = tinhHeSoNen(alicePrivateKeyStr, alicePublicKey);
    double compressionRatioBob = tinhHeSoNen(bobPrivateKeyStr, bobPublicKey);

    // Chuyển khóa riêng sang ma trận 7 cột
    std::vector<std::string> alicePrivateKeyMatrix = chuoiNhiPhanThanhMaTran(chuoiThanhNhiPhan(alicePrivateKeyStr));
    std::vector<std::string> bobPrivateKeyMatrix = chuoiNhiPhanThanhMaTran(chuoiThanhNhiPhan(bobPrivateKeyStr));

    // Hiển thị kết quả
    std::cout << "Alice's private key in binary (matrix): " << std::endl;
    inMaTran(alicePrivateKeyMatrix);
    std::cout << "Bob's private key in binary (matrix): " << std::endl;
    inMaTran(bobPrivateKeyMatrix);

    std::cout << "Alice's public key: " << alicePublicKey << std::endl;
    std::cout << "Bob's public key: " << bobPublicKey << std::endl;
    std::cout << "Shared secret (Alice): " << sharedSecretAlice << std::endl;
    std::cout << "Shared secret (Bob): " << sharedSecretBob << std::endl;
    std::cout << "Compression ratio for Alice's key: " << compressionRatioAlice << std::endl;
    std::cout << "Compression ratio for Bob's key: " << compressionRatioBob << std::endl;

    return 0;
}
