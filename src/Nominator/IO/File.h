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
