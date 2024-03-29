﻿/*
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

#include <string>
#include "LogLevel.h"

/*
 * Represents a logger.
 * @tparam T The type of the logger.
 */
class Logger
{

public:
    /*
     * Creates a new logger.
     * @param category The category of the logger.
     */
    Logger(std::string category)
    {
        this->category = category;
    }
    
    /*
     * Logs a message with the specified level.
     * @param level The level of the message.
     * @param message The message to log.
     */
    void log(LogLevel level, std::string message);

private:
    /* The category of the logger. */
    std::string category;
    
    /*
     * Gets the string representation of the specified level.
     * @param level The level to get the string representation of.
     * @return The string representation of the specified level.
     */
    static std::string getLevelAsString(LogLevel level);

    /*
     * Gets the current timestamp.
     * @return The current timestamp.
     */
    static std::string getCurrentTimestamp();
};
