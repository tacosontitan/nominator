#include "File.h"

#include <future>

std::future<bool> File::rename(std::string newName)
{
    auto future = std::async(std::launch::async, [this, newName]() {
        const char* oldPath = (Directory + Name + "." + Extension).c_str();
        const char* newPath = (Directory + newName + "." + Extension).c_str();
        return std::rename(oldPath, newPath) == 0;
    });

    return future;
}
