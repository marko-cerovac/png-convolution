const path_env = {
    project_root: "/home/marko/Code/Projects/ar/convolution"
    debug_target_dir: "/home/marko/Code/Projects/ar/convolution/target/debug"
    release_target_dir: "/home/marko/Code/Projects/ar/convolution/target/release"
}

const data_env = {
    input: ($path_env.project_root | path join data/input.bmp)
    output: ($path_env.project_root | path join data/output.bmp)
}

export def setup [] {
    use std/dirs

    dirs add  $path_env.project_root
    mkdir target/debug target/release

    print $"(ansi purple_bold)Setting up the release build directory(ansi reset)"
    meson setup target/release --buildtype=release

    print $"(ansi purple_bold)Setting up the release build directory(ansi reset)"
    meson setup target/debug --buildtype=debug

    dirs drop
}

# Build the project
export def build [
    type?: string # build type, can be debug or release
] {
    use std/dirs

    let build_type = ($type | default 'debug')

    match $build_type {
        'debug' => { dirs add $path_env.debug_target_dir }
        'release' => { dirs add $path_env.release_target_dir }
        _ => {
            print --stderr $"(ansi red)unknown build type(ansi reset)"
            return
        }
    }

    meson compile
    dirs drop
}

# Runs the project
export def run [
    type?: string # build type, can be debug or release
] {
    use std/dirs

    let build_type = ($type | default 'debug')

    build $type

    mut executable = []

    match $build_type {
        'debug' => { $executable = $path_env.debug_target_dir }
        'release' => { $executable = $path_env.release_target_dir }
        _ => {
            print --stderr $"(ansi red)unknown build type(ansi reset)"
            return
        }
    }

    $executable = $executable | path join convolution

    dirs add $path_env.project_root
    run-external $"($executable)" "-i" $"($data_env.input)" "-o" $"($data_env.output)" "-k" "0.0625,0.125,0.0625,0.125,0.25,0.125,0.0625,0.125,0.0625"
    dirs drop
}

export def time [] {
    timeit { run }
}

# Use gwenview to open the output image
export def show [] {
    if ($data_env.output | path exists) {
        gwenview $data_env.output
    } else {
        print --stderr $"(ansi red)Output data not found, run the project to create output data.(ansi reset)"
    }
}

export def clean [] {
    use std/dirs

    print $"(ansi purple_bold)Cleaning debug build artifacts(ansi reset)"
    dirs add $path_env.debug_target_dir
    ninja clean

    print $"(ansi purple_bold)Cleaning release build artifacts(ansi reset)"
    cd $path_env.release_target_dir
    ninja clean

    dirs drop

    if ($data_env.output | path exists) {
        print $"(ansi purple_bold)Cleaning output data(ansi reset)"
        rm $data_env.output
    }
}

export-env {
    load-env $path_env
    load-env $data_env
}
