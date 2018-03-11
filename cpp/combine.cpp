#include "Shares.h"
#include <fstream>

int main(int argc, char const *argv[])
{
    std::string filePath;
    if (argc <= 1) {
        std::cout << "Please enter the full path to a data file containing the shares to be combined:" << std::endl;
        std::getline(std::cin, filePath);
    } else if (argc == 2) {
        filePath = argv[1];
    } else {
        std::cout << "usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    try {
        Shares s(filePath);
        s.outputCombinedShares();
    } catch(std::exception & e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
