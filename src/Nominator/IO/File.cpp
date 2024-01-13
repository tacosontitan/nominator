/*
Copyright 2024 tacosontitan and contributors

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

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
