#include <iostream>
#include <cmath>

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


int diffie_hellman(int base, int private_key, int prime_modulus) {
    return power_modulo(base, private_key, prime_modulus);
}

int main() {
    int base = 5;

    int prime_modulus = 23;
    // nhap 2 so tu ban phim
    // them phan check so nguyen to
    // co so base la so bat ki, so nguyen to hoac so binh thuong
    // co so g bat buoc la so nguyen to > base
    
    int alice_private_key = 6;

    int bob_private_key = 15;

    int alice_public_key = diffie_hellman(base, alice_private_key, prime_modulus);

    int bob_public_key = diffie_hellman(base, bob_private_key, prime_modulus);

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
