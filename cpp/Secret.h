#ifndef SECRET_H
#define SECRET_H

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <iomanip>

class Secret
{
std::vector<std::vector<int>> sharesVec;
std::string secret;
int nShares;
// std::vector<std::string> shares;

public:
    Secret();
    Secret(const std::string secret, const int nShares);
    // void getUserInput(std::string& secret, int& nShares);
    void generateShares();
    std::vector<std::string> stringToHexVector(const std::string& inputString);
    std::string toHexString(const std::string& input);
    std::string toHexString(const std::vector<int>& input);
    void outputShares();
};

#endif
