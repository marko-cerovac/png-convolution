#include "utils.h"

#include <string>
#include <vector>

namespace utils {
    std::vector<std::string> split(std::string s, char delimiter) {
        size_t pos_start = 0, pos_end;
        std::string token;
        std::vector<std::string> res;

        while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
            token = s.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + 1;
            res.push_back(token);
        }

        res.push_back(s.substr(pos_start));
        return res;
    }

}  // namespace utils
