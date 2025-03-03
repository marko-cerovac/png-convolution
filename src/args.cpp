#include "args.h"

#include <cstdlib>
#include <filesystem>
#include <iostream>

namespace po = boost::program_options;
namespace fs = std::filesystem;

namespace ar {

    po::variables_map parse_cmdline_args(int argc, char** argv) {
        po::variables_map args;
        po::options_description args_group("Program arguments");

        std::string kernel_arg;

        // clang-format off
        args_group.add_options()
            (
                "help",
                "produce help message"
            )
            (
                "input,i",
                po::value<fs::path>()->default_value("./input.png"),
                "infput file (PNG)"
            )
            (
                "output,o",
                po::value<fs::path>()->default_value("./output.png"),
                "output file (PNG)"
            )
            (
                "cores,c",
                po::value<unsigned int>()->default_value(1),
                "number of CPU cores to use"
            )
            (
                "kernel,k",
                po::value<std::string>(&kernel_arg)->default_value("0,0,0,0,1,0,0,0,0"),
                "convolution kernel parameters as a list (eg. 0,0,1,0,0,1,0,0,1)"
            );
        // clang-format on

        po::store(po::parse_command_line(argc, argv, args_group), args);
        po::notify(args);


        if (args.count("help")) {
            std::cout << args_group << std::endl;
            std::exit(0);
        }

        return args;
    }

}  // namespace ar
