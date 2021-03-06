#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iterator>
#include <iostream>

class Shares
{
private:
    std::vector<std::string> shares;
    std::string secret;
    std::string combinedShares;
public:
    Shares();
    Shares(std::string dataFilePath);
    void setShares(std::string dataFilePath);
    void setCombinedShares();
    void outputCombinedShares();
    std::vector<int> hexStringToIntVec(std::string& input);
};
#endif
