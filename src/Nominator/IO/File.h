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

#pragma once
#include <future>
#include <string>

/* Represents a file on the filesystem. */
struct File
{
    /* The name of the file, without the extension. */
    std::string Name;

    /* The path to the file, excluding the file's name and extension. */
    std::string Directory;

    /* The extension of the file, excluding the dot. */
    std::string Extension;

    /*
     * Renames the specified file.
     * @param file The file to rename.
     * @param newName The new name of the file, excluding the extension.
     * @return A future that will be set to true if the file was renamed successfully, or false if it was not.
     */
    std::future<bool> rename(std::string newName);
};
