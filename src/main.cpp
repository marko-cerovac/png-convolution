#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <omp.h>

#include "image/BMPImage.h"
#include "kernel/Kernel.h"
/* #include "kernel/PixelWindow.h" */
/* #include "src/image/Pixel.h" */
#include "utils/args.h"

boost::program_options::variables_map args;

int main(int argc, char* argv[]) {
    /* auto args = ar::parse_cmdline_args(argc, argv); */

    // -------------------------------------------
    //    TESTING KERNEL PARSING AND OPERATIONS
    // -------------------------------------------

    /* auto kernel = ar::Kernel<3>::parse(args.at("kernel").as<std::string>()); */
    /**/
    /* ar::PixelWindow<3> bitmap = { */
    /*     {0.0, 1.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 1.0, 0.0}, */
    /*     {0.5, 0.0, 0.0}, {0.0, 0.0, 5.0}, {0.5, 0.0, 0.0}, */
    /*     {0.0, 1.0, 0.0}, {0.5, 0.0, 0.0}, {0.0, 1.0, 0.0} */
    /* }; */
    /**/
    /* image::PixelNorm result = kernel.convolve(bitmap); */
    /**/
    /* std::cout << result.blue << "\t" << result.green << "\t" << result.red << std::endl; */

    // --------------------------------------------
    //    TESTING IMAGE LOADING AND MANIPULATION
    // --------------------------------------------

    /* std::string input_file  = args.at("input").as<std::string>(); */
    /* std::string output_file = args.at("output").as<std::string>(); */
    /**/
    /* image::BMPImage image(input_file); */

    // darken image by 0.5
    /* for (int i = 0; i < image.get_height(); i++) { */
    /*     for (int j = 0; j < image.get_width(); j++) { */
    /*         image[i,j] *= 0.5; */
    /*     } */
    /* } */
    /**/
    /* image[0, 0] = {1.0, 0.0, 1.0}; */
    /* image[image.get_width() - 1, image.get_height() - 1] = {0.0, 0.0, 1.0}; */
    /**/
    /* image.save(output_file); */

    // --------------------------------------------
    //    TESTING CONVOLUTION
    // --------------------------------------------

    auto args = ar::parse_cmdline_args(argc, argv);

    auto kernel             = ar::Kernel<3>::parse(args.at("kernel").as<std::string>());
    std::string input_file  = args.at("input").as<std::string>();
    std::string output_file = args.at("output").as<std::string>();

    image::BMPImage image(input_file);

    std::cout << "Warming up..." << std::endl;
    for (int i = 0; i < 5; i++) {
        image.apply_convolution(kernel);
    }

    auto start_time = std::chrono::high_resolution_clock::now();
    auto result = image.apply_convolution(kernel);
    std::cout << "Calculating..." << std::endl;

    for (int i = 0; i < 49; i++) {
        result = result.apply_convolution(kernel);
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
    std::cout << "Elapsed time for 50 iterations: " << elapsed.count() << "ms" << std::endl;

    result.save(output_file);

    return 0;
}
