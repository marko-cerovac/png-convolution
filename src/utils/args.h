#pragma once

#include <boost/program_options.hpp>

namespace ar {

    boost::program_options::variables_map parse_cmdline_args(int argc, char** argv);

}
