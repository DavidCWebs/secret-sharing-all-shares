#include <sys/types.h>
#include <sys/stat.h>
#include <linux/limits.h>
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdio>
#include <memory>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <ctime>
#include <sstream>
#include <gcrypt.h>
#include <ctype.h>

namespace utility
{
    std::string getcwd();
    std::string currentTimestamp();
    int generateRandom(unsigned char *buf, size_t length, int printable);
}
