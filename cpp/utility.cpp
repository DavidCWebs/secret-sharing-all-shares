#include "utility.hpp"

namespace utility
{
	/**
	 * @see https://answers.yahoo.com/question/index?qid=20120103153728AAh2PjZ
	 * @see https://stackoverflow.com/a/145309/3590673
	 * @param cCurrentPath [description]
	 */
	std::string getcwd()
	{
		const size_t chunkSize = 255;
		const int maxChunks = 10240; // 2550 KiBs of current path are more than enough
		char path[PATH_MAX]; // Stack buffer for the "normal" case

		// Success. getcwd() returns a null pointer on failure
		if (::getcwd(path, PATH_MAX) != NULL) {
			return path;
		}
		// Fail: inadequate permissions
		if (errno == EACCES) {
			throw std::runtime_error("Can't get current working directory - permission denied.");
		}
		// Fail: Not ERANGE/EACCES, so we don't know how to handle it
		if (errno != ERANGE && errno != EACCES) {

			throw std::runtime_error("Cannot determine the current path.");
		}
		// The size argument is less than the length of the working directory name.
		// Fallback to heap allocation
		for(int chunks=2; chunks < maxChunks; chunks++) {
			std::unique_ptr<char> cwd(new char[chunkSize*chunks]);
			if(::getcwd(cwd.get(), chunkSize*chunks) != NULL) {
				return cwd.get();
			}
			if(errno != ERANGE) {
				// It's not ERANGE, so we don't know how to handle it
				throw std::runtime_error("Cannot determine the current path.");
			}
		}
		throw std::runtime_error("Cannot determine the current path; the path is apparently unreasonably long");
	}

	std::string currentTimestamp()
	{
		time_t now = time(0); // seconds since start of UNIX epoch
		tm *ltm = localtime(&now);
		std::stringstream timestamp;
		timestamp << std::setfill('0') << std::setw(2) << ltm->tm_mday << "-"
			<< std::setfill('0') << std::setw(2) << ltm->tm_mon + 1 << "-"
			<< ltm->tm_year + 1900 << ":"
			<< std::setfill('0') << std::setw(2) << ltm->tm_hour << ":"
			<< std::setfill('0') << std::setw(2) << ltm->tm_min << ":"
			<< std::setfill('0') << std::setw(2) << ltm->tm_sec;
		return timestamp.str().c_str();
	}

	/**
	 * Write a random byte into a buffer.
	 * Uses libgcrypt as a source of randomness.
	 */
	int generateRandom(unsigned char *buf, size_t length, int printable)
	{
		const char *version = "1.6.5";
		const char *outputVersion;
		if (!(outputVersion = gcry_check_version (version)))
		{
			fputs("libgcrypt version mismatch\n", stderr);
			exit(2);
		}

		size_t i = 0;
		while (i < length) {
			unsigned char tmp[1];
			gcry_randomize(tmp, 1, GCRY_STRONG_RANDOM);
			if (printable) {
				if (isprint(tmp[0])) {
					buf[i++] = tmp[0];
				}
			} else {
				buf[i++] = tmp[0];
			}
		}
		return 0;
	}

	//int randomByteNative(unsigned char *buf, size_t length)

	/**
	 * Build a vector of hex strings representing char values from an input string.
	 * See: https://stackoverflow.com/a/5990913/3590673
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

	std::string toHexString(const std::vector<unsigned char>& input)
	{
		std::string hexString = "";
		for (size_t i = 0; i < input.size(); i++) {
			std::ostringstream result;
			result << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << (int)input[i];
			hexString += result.str();
		}
		return hexString;
	}

}
