#include <boost/program_options.hpp>
#include <string>

#include "image/BMPImage.h"
#include "args.h"

boost::program_options::variables_map args;

int main(int argc, char* argv[]) {

    auto args = ar::parse_cmdline_args(argc, argv);

    std::string input_file = args.at("input").as<std::string>();
    std::string output_file = args.at("output").as<std::string>();

    image::BMPImage image(input_file);

    image.save(output_file);

    return 0;
}
