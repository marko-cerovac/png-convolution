#include "Pixel.h"

namespace image {
    PixelHex::operator PixelNorm() const {
        return {
            static_cast<float>(red) / 0xFF,
            static_cast<float>(blue) / 0xFF,
            static_cast<float>(green) / 0xFF,
        };
    }

    PixelNorm::operator PixelHex() const {
        return {
            static_cast<uint8_t>(red * 0xFF),
            static_cast<uint8_t>(blue * 0xFF),
            static_cast<uint8_t>(green * 0xFF),
        };
    }
}  // namespace image
