#include "helpers.hpp"

void getUserInput(std::string& secret, int& nShares)
{
    std::cout << "Please enter the secret that should be split:" << std::endl;
    getline(std::cin, secret);

    std::cout << "Enter the number of fragments into which the secret should be split:" << std::endl;
    std::cin >> nShares;
}

void generateFragments(std::vector<std::vector<int>>& fragmentsVec, const int& nShares, const int& secretLength, const std::string& secret)
{
    std::vector<int> finalFragment;
    srand(static_cast<unsigned int>(time(0)));
    // Create fragments comprised of random ints 0 > 255
    for (int i = 0; i < nShares - 1; i++) {
        std::vector<int> currentFragment;
        for (size_t j = 0; j < secretLength; j++) {
            int random = rand() % 255;
            currentFragment.push_back(random);
        }
        fragmentsVec.push_back(currentFragment);
    }
    // xor position by position to build a combined xor of all
    for (int i = 0; i < secretLength; i++) {
        int valAtCurrentPosition;
        // Loop through fragments, so we xor at each position
        for (int j = 0; j < nShares -1; j++) {
            valAtCurrentPosition = (j == 0)
                ? fragmentsVec[j][i]
                : fragmentsVec[j][i] ^ valAtCurrentPosition;
        }
        // finally xor the value of the secret at this position
        finalFragment.push_back(valAtCurrentPosition ^ int(secret[i]));
    }
    fragmentsVec.push_back(finalFragment);
}

/**
 * [stringToHexVector description]
 * See: https://stackoverflow.com/a/5990913/3590673
 * @param inputString [description]
 */
std::vector<std::string> stringToHexVector(const std::string& inputString)
{
    std::vector<std::string> resultVec;
    for (size_t i = 0; i < inputString.length(); i++) {
        std::ostringstream result;
        result << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << (int)inputString[i];
        std::cout << result.str() << std::endl;
        resultVec.push_back(result.str());
    }
    return resultVec;
}

std::string toHexString(const std::string& inputString)
{
    std::string hexString = "";
    for (size_t i = 0; i < inputString.length(); i++) {
        std::ostringstream result;
        result << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << (int)inputString[i];
        hexString += result.str();
    }
    return hexString;
}

std::string toHexString(const std::vector<int>& input)
{
    std::string hexString = "";
    for (size_t i = 0; i < input.size(); i++) {
        std::ostringstream result;
        result << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << input[i];
        hexString += result.str();
    }
    return hexString;
}
