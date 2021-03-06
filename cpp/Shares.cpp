#include "Shares.h"

Shares::Shares() {}

Shares::Shares(std::string dataFilePath)
{
    setShares(dataFilePath);
    setCombinedShares();
}

void Shares::setShares(std::string dataFilePath)
{
    std::ifstream infile(dataFilePath);

    if (!infile) {
        throw std::runtime_error("The input file could not be opened.");
    }

    std::string line;
    while (std::getline(infile, line)) {
        shares.push_back(line);
    }
}

void Shares::setCombinedShares()
{
    // throw std::runtime_error("Whoops!!!!");
    // Loop through shares, convert to int vector
    std::vector<std::vector<int>> intVecs;
    for (std::string& share : shares) {
        intVecs.push_back(hexStringToIntVec(share));
    }

    // xor position by position to build a combined xor of all
    std::vector<int> xoredShares;
    for (int i = 0; i < intVecs[0].size(); i++) {
        int valAtCurrentPosition;
        // Loop through fragments, so we xor at each position
        for (int j = 0; j < intVecs.size(); j++) {
            valAtCurrentPosition = (j == 0)
                ? intVecs[j][i]
                : intVecs[j][i] ^ valAtCurrentPosition;
        }
        // add the result of xoring all values at this position
        xoredShares.push_back(valAtCurrentPosition);
    }
    std::string s;
    for (auto i : xoredShares) {
        s += static_cast<char>(i);
    }
    combinedShares = s;
}

std::vector<int> Shares::hexStringToIntVec(std::string& input)
{
    std::vector<int> resultVec;
    int current;
    for (size_t i = 0; i < input.length(); i+=2) {
        std::stringstream ss;
        ss << std::hex << input[i] << input[i + 1];
        ss >> current;
        resultVec.push_back(current);
    }
    return resultVec;
}

void Shares::outputCombinedShares() {
    const int pad = 1;
    std::string outputLine = "|" + std::string(pad, ' ') + combinedShares + std::string(pad, ' ') + "|";
    std::string vertBound = "+" + std::string((pad * 2) + combinedShares.length(), '-') + "+";
    std::cout << "The secret represented by the combined shares:" << std::endl;
    std::cout << vertBound << std::endl;
    std::cout << outputLine << std::endl;
    std::cout << vertBound << std::endl;
}
