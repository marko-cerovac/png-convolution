#include "args.h"

#include <boost/program_options/options_description.hpp>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <thread>

namespace po = boost::program_options;
namespace fs = std::filesystem;

namespace ar {

    po::options_description create_cmdline_args() {
        po::options_description args_group("Program arguments");
        // clang-format off
        args_group.add_options()
            (
                "help,h",
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
                // get the number of cores on the CPU and use it as the default value
                po::value<unsigned int>()->default_value(std::thread::hardware_concurrency()),
                "number of CPU cores to use (defaults to the max number the CPU has)"
            )
            (
                "kernel,k",
                po::value<std::string>()->default_value("0,0,0,0,1,0,0,0,0"),
                "convolution kernel parameters as a list (eg. 0,0,1,0,0,1,0,0,1)"
            );
        // clang-format on

        return args_group;
    }

    /**
     * A function that parses command line arguments and returns
     * a hash map that contains the values.
     *
     * It also checks if the user passed in the --help flag, in which case
     * it prints out the help info end exits.
     *
     * @param argc Argument count
     * @param argv Argument list
     *
     * */
    po::variables_map parse_cmdline_args(int argc, char** argv) {
        po::variables_map args_map;
        po::options_description args_group = create_cmdline_args();

        std::string kernel_arg;

        po::store(po::parse_command_line(argc, argv, args_group), args_map);
        po::notify(args_map);

        if (args_map.count("help")) {
            std::cout << args_group << std::endl;
            std::exit(0);
        }

        return args_map;
    }

}  // namespace ar
