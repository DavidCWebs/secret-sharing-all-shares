#include "helpers.hpp"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char const *argv[])
{
    for (size_t i = 0; i < argc; i++) {
        std::cout << "Argument " << i << " = " << argv[i] << std::endl;
    }
    std::string secret;
    std::vector<std::vector<int>> fragments;
    int nShares;
    getUserInput(secret, nShares);
    generateFragments(fragments, nShares, secret.length(), secret);

    std::cout << "Fragments" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    for(std::vector<int>& fragment : fragments) {
        std::cout << toHexString(fragment) << std::endl;
    }
    std::cout << std::string(80, '-') << std::endl;

    // Overload toHexString()
    std::cout << "Secret, hex encoded plaintext: " << toHexString(secret) << std::endl;

    return 0;
}
