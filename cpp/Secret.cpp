#include "Secret.h"
#include "utility.hpp"

Secret::Secret() {}
Secret::Secret(const std::string inputSecret, const int inputNShares)
: secret(inputSecret), nShares(inputNShares)
{
    generateShares();
}


void Secret::generateShares()
{
    std::vector<int> finalShare;
    srand(static_cast<unsigned int>(time(0)));
    // Create fragments comprised of random ints 0 > 255
    for (int i = 0; i < nShares - 1; i++) {
        std::vector<int> currentShare;
        for (size_t j = 0; j < secret.length(); j++) {
            int random = rand() % 255;
            currentShare.push_back(random);
        }
        sharesVec.push_back(currentShare);
    }
    // xor position by position to build a combined xor of all
    for (int i = 0; i < secret.length(); i++) {
        int valAtCurrentPosition;
        // Loop through fragments, so we xor at each position
        for (int j = 0; j < nShares -1; j++) {
            valAtCurrentPosition = (j == 0)
            ? sharesVec[j][i]
            : sharesVec[j][i] ^ valAtCurrentPosition;
        }
        // finally xor the value of the secret at this position
        finalShare.push_back(valAtCurrentPosition ^ int(secret[i]));
    }
    sharesVec.push_back(finalShare);
}

/**
* [stringToHexVector description]
* See: https://stackoverflow.com/a/5990913/3590673
* @param inputString [description]
*/
std::vector<std::string> Secret::stringToHexVector(const std::string& inputString)
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

std::string Secret::toHexString(const std::string& inputString)
{
    std::string hexString = "";
    for (size_t i = 0; i < inputString.length(); i++) {
        std::ostringstream result;
        result << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << (int)inputString[i];
        hexString += result.str();
    }
    return hexString;
}

std::string Secret::toHexString(const std::vector<int>& input)
{
    std::string hexString = "";
    for (size_t i = 0; i < input.size(); i++) {
        std::ostringstream result;
        result << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << input[i];
        hexString += result.str();
    }
    return hexString;
}

void Secret::outputShares()
{
    const int pad = 1;
    std::string vertBound = "\n+" + std::string((pad * 2) + (secret.length() * 2), '-') + "+";
    std::cout << "Shares" << vertBound << std::endl;
    for(std::vector<int>& share : sharesVec) {
        std::cout << "|" + std::string(pad, ' ')
        << toHexString(share)
        << std::string(pad, ' ') + "|"
        << vertBound << "\n";
    }

    // -------------------------------------------------------------------------
    int createParentDirStatus, createBaseDirStatus;
    std::string parentDir = utility::getcwd() + "/shares";
    std::string baseDir = parentDir + "/shares-" + utility::currentTimestamp();
    createParentDirStatus = mkdir(parentDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    createBaseDirStatus = mkdir(baseDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

    for (int i = 0; i < sharesVec.size(); i++) {
        writeFile(i, toHexString(sharesVec[i]), baseDir);
    }
    std::cout << std::endl;
}

void Secret::writeFile(const int i, const std::string& share, std::string dirPath)
{
    // int createSharesDirStatus;
    // std::string newDir = utility::getcwd() + "/shares";
    // std::string baseDir = utility::currentTimestamp();
    // std::string filePath = newDir + "/shares-" + baseDir + "/share-" + std::to_string(i);

    // std::cout << share << std::endl;
    // std::cout << filePath << std::endl;
    // createSharesDirStatus = mkdir(newDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    // std::cout << ((createStatus != 0) ? "FAIL" : "SUCCESS") << std::endl;
    std::string path = dirPath + "/share-" + std::to_string(i);
    std::ofstream file;
    file.open(path);
    file << share << std::endl;
    file.close();
}
