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

namespace utility
{
    std::string getcwd();
    std::string currentTimestamp();
}
