#include <boost/program_options.hpp>
#include <iostream>

#include "args.h"
#include "Kernel.h"

boost::program_options::variables_map args;

int main(int argc, char* argv[]) {
    args = ar::parse_cmdline_args(argc, argv);

    ar::Kernel<double, 3> kernel({1, 2, 3, 4, 5, 6, 7, 8, 9});

    for (const auto element : kernel) {
        std::cout << element << ", ";
    }

    std::cout << std::endl;

    std::cout << "The first element is: " << kernel.at<0, 0>() << std::endl;

    return 0;
}
