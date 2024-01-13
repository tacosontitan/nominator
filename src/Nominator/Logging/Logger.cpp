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

#include "Logger.h"

#include <iostream>
#include <chrono>
#include <format>


void Logger::log(LogLevel level, std::string message)
{
    auto timestamp = getCurrentTimestamp();
    auto logLevel = getLevelAsString(level);
    std::cout << timestamp << " - " << category << " " << logLevel << ": " << message << "\n";
}

std::string Logger::getCurrentTimestamp()
{
    const auto now = std::chrono::system_clock::now();
    return std::format("{:%m-%d-%Y %H:%M:%OS}", now);
}

std::string Logger::getLevelAsString(LogLevel level)
{
    switch (level)
    {
        case LogLevel::Trace: return "(trace)";
        case LogLevel::Debug: return "(debug)";
        case LogLevel::Information: return "(info)";
        case LogLevel::Warning: return "(warn)";
        case LogLevel::Error: return "(error)";
        case LogLevel::Critical: return "(critical)";
    }

    throw std::invalid_argument("Invalid log level.");
}