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

#include "DirectoryWorker.h"
#include <future>
#include <filesystem>

namespace fs = std::filesystem;

void DirectoryWorker::start()
{
    logger->log(LogLevel::Debug, "Identifying children.");
    auto children = getChildren();

    logger->log(LogLevel::Trace, "Creating workers for children.");
    for (const auto& child : children)
    {
        auto workerLoggerCategory = "DirectoryWorker (" + getDirectoryName(child) + ")";
        auto workerLogger = new Logger(workerLoggerCategory);
        auto worker = new DirectoryWorker(workerLogger, child);
        worker->start();
    }

    logger->log(LogLevel::Trace, "Renaming files.");
    renameFiles();
    
    logger->log(LogLevel::Information, "Work completed successfully.");
}

std::string DirectoryWorker::getDirectoryName(std::string path)
{
    return path.substr(path.find_last_of("/\\") + 1);
}

std::vector<std::string> DirectoryWorker::getChildren() const
{
    std::vector<std::string> subdirectories;

    fs::path path(directory);
    if (!exists(path))
    {
        logger->log(LogLevel::Error, "Directory does not exist.");
        return subdirectories;
    }

    if (!is_directory(path))
    {
        logger->log(LogLevel::Error, "Directory path is not associated with a directory.");
        return subdirectories;
    }

    for (const auto& entry : fs::directory_iterator(path))
    {
        if (is_directory(entry.path()))
        {
            auto subDirectory = entry.path().string();
            subdirectories.push_back(subDirectory);
        }
    }

    return subdirectories;
}

void DirectoryWorker::renameFiles()
{
    fs::path path(directory);
    if (!exists(path))
    {
        logger->log(LogLevel::Error, "Directory does not exist.");
        return;
    }

    if (!is_directory(path))
    {
        logger->log(LogLevel::Error, "Directory path is not associated with a directory.");
        return;
    }

    auto fileCount = 1;
    for (const auto& entry : fs::directory_iterator(path))
        renameFile(entry, fileCount);

    logger->log(LogLevel::Information, "Renamed " + std::to_string(fileCount - 1) + " files.");
}

void DirectoryWorker::renameFile(const std::filesystem::directory_entry& entry, int& fileCount)
{
    try
    {
        if (is_directory(entry.path()))
            return;
        
        auto fileDirectory = entry.path().parent_path().string();
        auto fileName = entry.path().filename().string();
        auto fileExtension = entry.path().extension().string();
        std::string newFileName;
        std::string newFilePath;
        
        do
        {
            newFileName = getDirectoryName(directory) + "-" + std::to_string(fileCount++);
            newFilePath = fileDirectory + "\\" + newFileName + fileExtension;
        } while (fs::exists(newFilePath));
        
        rename(entry.path(), newFilePath);
        logger->log(LogLevel::Trace, "Renamed file " + fileName + " to " + newFileName + ".");
    } catch (const std::exception& e)
    {
        logger->log(LogLevel::Error, "Failed to rename file.");
        logger->log(LogLevel::Error, e.what());
    }
}