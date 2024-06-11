#include <iostream>
#include <string>
#include <bitset>
#include <cmath>

// Chuyển ký tự thành mã nhị phân
std::string charToBinary(char c) {
    std::bitset<8> b(c); // Sử dụng 8 bits cho mỗi ký tự ASCII
    return b.to_string();
}

// Chuyển chuỗi ký tự thành chuỗi nhị phân
std::string stringToBinary(const std::string &str) {
    std::string binaryString = "";
    for (char c : str) {
        binaryString += charToBinary(c);
    }
    return binaryString;
}

// Tính toán mô-đun lũy thừa
int powerModulo(int base, int exponent, int modulus) {
    if (modulus == 1)
        return 0;
    int result = 1;
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
int diffieHellman(int base, int privateKey, int primeModulus) {
    return powerModulo(base, privateKey, primeModulus);
}

// Tính toán hệ số nén
double calculateCompressionRatio(const std::string &inputKey, int outputKeyBits) {
    std::string binaryInputKey = stringToBinary(inputKey);
    int inputKeyBits = binaryInputKey.length();
    return static_cast<double>(inputKeyBits) / outputKeyBits;
}

int main() {
    // Các khóa đầu vào
    std::string aliceKey = "Alice15";
    std::string bobKey = "Bob20";
    
    int base = 5; // Cơ số
    int primeModulus = 23; // Số nguyên tố lớn
    
    int alicePrivateKey = 15; // Khóa riêng của Alice
    int bobPrivateKey = 20; // Khóa riêng của Bob

    // Tính khóa công khai
    int alicePublicKey = diffieHellman(base, alicePrivateKey, primeModulus);
    int bobPublicKey = diffieHellman(base, bobPrivateKey, primeModulus);

    // Tính khóa chung
    int sharedSecretAlice = diffieHellman(bobPublicKey, alicePrivateKey, primeModulus);
    int sharedSecretBob = diffieHellman(alicePublicKey, bobPrivateKey, primeModulus);

    // Tính hệ số nén
    double compressionRatioAlice = calculateCompressionRatio(aliceKey, alicePublicKey );
    double compressionRatioBob = calculateCompressionRatio(bobKey, bobPublicKey);

    // Hiển thị kết quả
    std::cout << "Alice's input key in binary: " << stringToBinary(aliceKey) << std::endl;
    std::cout << "Bob's input key in binary: " << stringToBinary(bobKey) << std::endl;
    std::cout << "Alice's public key: " << alicePublicKey << std::endl;
    std::cout << "Bob's public key: " << bobPublicKey << std::endl;
    std::cout << "Shared secret (Alice): " << sharedSecretAlice << std::endl;
    std::cout << "Shared secret (Bob): " << sharedSecretBob << std::endl;
    std::cout << "Compression ratio for Alice's key: " << compressionRatioAlice << std::endl;
    std::cout << "Compression ratio for Bob's key: " << compressionRatioBob << std::endl;

    return 0;
}