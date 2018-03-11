#ifndef SECRET_H
#define SECRET_H

#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>

class Secret
{
std::vector<std::vector<int>> sharesVec;
std::string secret;
int nShares;

public:
    Secret();
    Secret(const std::string secret, const int nShares);
    void generateShares();
    std::vector<std::string> stringToHexVector(const std::string& inputString);
    std::string toHexString(const std::string& input);
    std::string toHexString(const std::vector<int>& input);
    void outputShares();
    void writeFile(const int i, const std::string& share, std::string dirPath);
};

#endif
