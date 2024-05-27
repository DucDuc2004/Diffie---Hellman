#include <iostream>
#include <cmath>

    // Ham tinh modules (a mu b) % c
int power_modulo(int base, int exponent, int modulus) {
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
    // Ham kiem tra so nguyen to
bool isPrime(int n) 
{
    if (n <= 1) {
        return false;
    }
    if (n <= 3) {
        return true;
    }
    if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        }
    }
    return true;
}

int diffie_hellman(int base, int private_key, int prime_modulus) {
    return power_modulo(base, private_key, prime_modulus);
}

int main() {
    int base;
    int prime_modulus;
    // nhap 2 so tu ban phim
    std::cout << "Enter the base: ";
    std::cin >> base;
    std::cout << "Enter the large prime base ( > base): ";
    std::cin >> prime_modulus;

    if (base >= prime_modulus)
    {
        std::cout << "ERORR" << std::endl;
        return 0;
    }
    

    // kiem tra co so nguyen to
    if (isPrime(prime_modulus) == false)  
    {
        std::cout << "The algorithm does not guarantee security" << std::endl;
        return 0;
    }

    int alice_private_key;
    int bob_private_key;
    // Nhap 2 khoa bi mat cua Alice and Bob
    std::cout << "Enter alice_private_key: ";
    std::cin >> alice_private_key;
    std::cout << "Enter bob_private_key: ";
    std::cin >> bob_private_key;

    // Goi ham tinh modolus tinh khoa public
    int alice_public_key = diffie_hellman(base, alice_private_key, prime_modulus);
    int bob_public_key = diffie_hellman(base, bob_private_key, prime_modulus);

    // Goi ham tinh modulus tinh khoa chia se chung
    int shared_secret_alice = diffie_hellman(bob_public_key, alice_private_key, prime_modulus);
    int shared_secret_bob = diffie_hellman(alice_public_key, bob_private_key, prime_modulus);

    std::cout << "Alice's private key: " << alice_private_key << std::endl;
    std::cout << "Alice's public key: " << alice_public_key << std::endl;
    std::cout << "Bob's private key: " << bob_private_key << std::endl;
    std::cout << "Bob's public key: " << bob_public_key << std::endl;
    std::cout << "Shared secret calculated by Alice: " << shared_secret_alice << std::endl;
    std::cout << "Shared secret calculated by Bob: " << shared_secret_bob << std::endl;

    return 0;
}
