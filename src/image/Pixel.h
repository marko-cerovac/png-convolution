#pragma once

// Structure for RGB pixel
#include <cstdint>

namespace image {
    struct PixelNorm;

    // pixel that uses hex values 0 - 0xFF
    struct PixelHex {
        uint8_t red;      // Red component
        uint8_t green;    // Green component
        uint8_t blue;     // Blue component

        operator PixelNorm () const;
    };

    // normalized pixel that uses values 0.0 - 1.0
    struct PixelNorm {
        float red;
        float green;
        float blue;

        operator PixelHex () const;
    };
}
