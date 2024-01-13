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

#ifndef LOGLEVEL_H
#define LOGLEVEL_H

/* Represents the level of a log message. */
enum class LogLevel
{
    /* Represents a trace message. */
    Trace = 0,

    /* Represents a debug message. */
    Debug = 1,

    /* Represents an informational message. */
    Information = 2,

    /* Represents a warning that has occurred. */
    Warning = 3,

    /* Represents an error that has occurred. */
    Error = 4,

    /* Represents a fatal error that has occurred. */
    Critical = 5
};

#endif // LOGLEVEL_H
