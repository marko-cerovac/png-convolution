project( 'ar-multimedia-convolution', 'cpp')

add_global_arguments(
  '-std=c++23',
  '-Wpedantic',
  '-fopenmp',
  '-march=native',
  '-mavx2',
  '-ftree-vectorize',
  '-fopt-info-vec-all', # let me know which loops are being vectorized
  # '-ftree-vectorizer-verbose', # let me know which loops are being vectorized
  language : 'cpp'
)

# Declare Boost as a dependency, specifically the program_options module
boost_dep = dependency('boost', modules : ['program_options'])
openmp_dep = dependency('openmp')

# Define the source files
src_dir = 'src'
sources = files(
  src_dir + '/main.cpp',
  src_dir + '/utils/args.cpp',
  src_dir + '/utils/utils.cpp',
  src_dir + '/image/Pixel.cpp',
  src_dir + '/image/BMPImage.cpp'
)

if get_option('buildtype') == 'debug'
    add_project_arguments('-ggdb', language : 'cpp')
elif get_option('buildtype') == 'release'
    add_project_arguments('-O3', language : 'cpp')
endif

# Define the executable target with the Boost dependency
executable('convolution', sources, dependencies : [boost_dep, openmp_dep])
