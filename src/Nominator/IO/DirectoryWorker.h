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
#include <filesystem>
#include "../Logging/Logger.h"

/* Represents a worker that works in a directory. */
class DirectoryWorker
{
public:
    /*
     * Creates a new directory worker.
     * @param logger The logger to use.
     * @param directory The directory to work in.
     */
    DirectoryWorker(Logger* logger, const std::string& directory)
    {
        this->logger = logger;
        this->directory = directory;
    }

    /*
     * Starts the directory worker.
     * @return A future that will be set when the directory worker has finished.
     */
    void start();

protected:
    /* The logger to use. */
    Logger* logger;

    /* The directory to work in. */
    std::string directory;

private:
    /*
     * Gets the name of the directory.
     * @return The name of the directory.
     */
    static std::string getDirectoryName(std::string path);

    /*
     * Gets the children of the directory.
     * @return The children of the directory.
     */
    std::vector<std::string> getChildren() const;

    /*
     * Renames the files in the directory.
     * @return A future that will be set when the files have been renamed.
     */
    void renameFiles();

    /*
     * Renames a file in the directory.
     * @param path The path of the file to rename.
     * @return A future that will be set when the file has been renamed.
     */
    void renameFile(const std::filesystem::directory_entry& entry, int& index);
};
