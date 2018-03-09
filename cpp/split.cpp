#include "Secret.h"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char const *argv[])
{
    // for (size_t i = 0; i < argc; i++) {
    //     std::cout << "Argument " << i << " = " << argv[i] << std::endl;
    // }
    std::string secret;
    int nShares;
    std::cout << "Please enter the secret that should be split:" << std::endl;
    getline(std::cin, secret);

    std::cout << "Enter the number of fragments into which the secret should be split:" << std::endl;
    std::cin >> nShares;

    try {
        Secret s(secret, nShares);
        s.outputShares();
    } catch(std::exception & e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    // getUserInput(secret, nShares);
    // generateFragments(fragments, nShares, secret.length(), secret);

    // std::cout << "Fragments" << std::endl;
    // std::cout << std::string(80, '-') << std::endl;
    // for(std::vector<int>& fragment : fragments) {
    //     std::cout << toHexString(fragment) << std::endl;
    // }
    // std::cout << std::string(80, '-') << std::endl;
    //
    // // Overload toHexString()
    // std::cout << "Secret, hex encoded plaintext: " << toHexString(secret) << std::endl;

    return 0;
}
