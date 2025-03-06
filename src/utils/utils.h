#pragma once

#include <string>
#include <vector>

namespace utils {

    /**
     * Because c++ strings don't have a split method...🤬
     *
     */
    std::vector<std::string> split(std::string s, char delimiter = ',');
}  // namespace utils
