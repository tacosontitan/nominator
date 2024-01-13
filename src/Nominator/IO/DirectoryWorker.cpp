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

#include "File.h"

namespace fs = std::filesystem;

std::future<void> DirectoryWorker::start()
{
    auto future = std::async(std::launch::async, [this]()
    {
        logger->log(LogLevel::Debug, "Identifying children.");
        auto children = getChildren();

        logger->log(LogLevel::Trace, "Creating workers for children.");
        std::vector<std::future<void>> futures;
        for (const auto& child : children)
        {
            auto workerLoggerCategory = "DirectoryWorker (" + getDirectoryName() + ")";
            auto workerLogger = new Logger(workerLoggerCategory);
            auto worker = new DirectoryWorker(workerLogger, child);
            auto workerFuture = worker->start();
            futures.push_back(std::move(workerFuture));
        }

        logger->log(LogLevel::Trace, "Renaming files.");
        auto workload = renameFiles();
        workload.wait();

        logger->log(LogLevel::Trace, "Waiting for workers to finish.");
        for (const auto& future : futures)
            future.wait();

        logger->log(LogLevel::Information, "Work completed successfully.");
    });

    return future;
}

std::string DirectoryWorker::getDirectoryName() const
{
    return directory.substr(directory.find_last_of("/\\") + 1);
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

std::future<void> DirectoryWorker::renameFiles()
{
    auto future = std::async(std::launch::async, [this]()
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
        {
            if (is_directory(entry.path()))
                continue;

            auto filePath = entry.path().string();
            auto fileName = entry.path().filename().string();
            auto fileExtension = entry.path().extension().string();
            auto file = new File(filePath, fileName, fileExtension);
            auto newFileName = getDirectoryName() + "-" + std::to_string(fileCount++);
            auto renameSuccessful = file->rename(newFileName).get();
            if (!renameSuccessful)
                logger->log(LogLevel::Error, "Failed to rename file " + fileName + ".");
        }

        logger->log(LogLevel::Information, "Renamed " + std::to_string(fileCount - 1) + " files.");
    });

    return future;
}