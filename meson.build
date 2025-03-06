project(
  'ar-multimedia-convolution',
  'cpp',
  default_options: ['cpp_std=c++23']
)

# Declare Boost as a dependency, specifically the program_options module
boost_dep = dependency('boost', modules : ['program_options'])

# Define the source files
src_dir = 'src'
sources = files(
  src_dir + '/main.cpp',
  src_dir + '/args.cpp',
  src_dir + '/utils/utils.cpp',
  src_dir + '/image/BMPImage.cpp'
)

if get_option('buildtype') == 'debug'
    add_project_arguments('-ggdb', language : 'cpp')
elif get_option('buildtype') == 'release'
    add_project_arguments('-O3', language : 'cpp')
endif

# Define the executable target with the Boost dependency
executable('convolution', sources, dependencies : boost_dep)
