#ifndef HELPERS_H
#define HELPERS_H

#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <iomanip>

void getUserInput(std::string& secret, int& nShares);
void generateFragments(std::vector<std::vector<int>>& fragments, const int& nShares, const int& secretLength, const std::string& secret);
std::vector<std::string> stringToHexVector(const std::string& inputString);
std::string toHexString(const std::string& input);
std::string toHexString(const std::vector<int>& input);

#endif
