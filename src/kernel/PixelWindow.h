#pragma once

#include "../image/Pixel.h"
#include "StaticMatrix.h"

namespace ar {
    template <size_t N>
    using PixelWindow = StaticMatrix<image::PixelNorm, N>;
}
