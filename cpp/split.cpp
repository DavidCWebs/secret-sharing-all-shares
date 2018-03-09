#include "Secret.h"
#include <iostream>
#include <vector>
#include <string>

int main(int argc, char const *argv[])
{
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

    return 0;
}
