#include "Secret.h"
#include "utility.hpp"

Secret::Secret() {}
Secret::Secret(const std::string inputSecret, const int inputNShares)
	: secret(inputSecret), nShares(inputNShares)
{
	generateShares();
}

/**
 * Makes a std::vector<std::vector<unsigned char>> of nShares number of elements which are the 
 * shares of the secret.
 * 
 * Each of the first (nShares -1) elements is a vector of random bytes supplied by libgcrypt.
 * The last element is the result of XORing each random share with the secret on a 
 * character-by-character basis.
 *
 * See: https://en.wikipedia.org/wiki/Secret_sharing#Trivial_secret_sharing
 */
void Secret::generateShares()
{
	std::vector<unsigned char> finalShare;
	
	// Create fragments comprised of random bytes 
	for (int i = 0; i < nShares - 1; i++) {
		std::vector<unsigned char> currentShare;
		unsigned char *buf = new unsigned char[secret.length()];
		utility::generateRandom(buf, secret.length(), 0);
		while (*buf++) {
			currentShare.push_back(*buf);
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
		finalShare.push_back(valAtCurrentPosition ^ (unsigned char)(secret[i]));
	}
	
	sharesVec.push_back(finalShare);
}

void Secret::outputShares()
{
	const int pad = 1;
	std::string vertBound = "\n+" + std::string((pad * 2) + (secret.length() * 2), '-') + "+";
	std::cout << "Shares" << vertBound << std::endl;
	for(std::vector<unsigned char>& share : sharesVec) {
		std::cout << "|" + std::string(pad, ' ')
			<< utility::toHexString(share)
			<< std::string(pad, ' ') + "|"
			<< vertBound << "\n";
	}

	int createParentDirStatus, createBaseDirStatus;
	std::string parentDir = utility::getcwd() + "/shares";
	std::string baseDir = parentDir + "/shares-" + utility::currentTimestamp();
	createParentDirStatus = mkdir(parentDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	createBaseDirStatus = mkdir(baseDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	for (int i = 0; i < sharesVec.size(); i++) {
		writeFile(i, utility::toHexString(sharesVec[i]), baseDir);
	}
	std::cout << std::endl;
}

void Secret::writeFile(const int i, const std::string& share, std::string dirPath)
{
	std::string path = dirPath + "/share-" + std::to_string(i);
	std::ofstream file;
	file.open(path);
	file << share << std::endl;
	file.close();
}
