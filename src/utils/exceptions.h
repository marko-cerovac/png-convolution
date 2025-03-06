#pragma once

#include <stdexcept>

namespace utils {

    /**
     * Used for parsing command line arguments
     */
    class ParseErrorException : public std::runtime_error {
      public:

        explicit ParseErrorException(const std::string& message) : std::runtime_error(message) {}
    };

    /**
     * Thrown if the input file format is wrong or corrupted
     */
    class WrongInputFormatException : public std::runtime_error {
      public:

        explicit WrongInputFormatException(const std::string& message)
            : std::runtime_error(message) {}
    };

    /**
     * Thrown if the input file is not found
     */
    class FileNotFoundException : public std::runtime_error {
      public:

        explicit FileNotFoundException(const std::string& message) : std::runtime_error(message) {}
    };

}  // namespace utils
