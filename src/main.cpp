#include <boost/program_options.hpp>
#include <string>

#include "args.h"
#include "image/BMPImage.h"

boost::program_options::variables_map args;

int main(int argc, char* argv[]) {
    auto args = ar::parse_cmdline_args(argc, argv);

    std::string input_file  = args.at("input").as<std::string>();
    std::string output_file = args.at("output").as<std::string>();

    image::BMPImage image(input_file);

    for (int i = 0; i < image.get_height(); i++) {
        for (int j = 0; j < image.get_width(); j++) {
            if (i == j) {
                image[i, j] = {0xFF, 0xFF, 0xFF};
            }
        }
    }

    image[0, 0] = {0xFF, 0x00, 0xFF};
    image[image.get_width() - 1, image.get_height() - 1] = {0x00, 0x00, 0xFF};

    image.save(output_file);

    return 0;
}
