#pragma once

// Structure for RGB pixel
#include <cstdint>

namespace image {
    struct PixelNorm;

    // pixel that uses hex values 0 - 0xFF
    struct PixelHex {
        uint8_t blue;   // Blue component
        uint8_t green;  // Green component
        uint8_t red;    // Red component

        operator PixelNorm() const;
    };

    // normalized pixel that uses values 0.0 - 1.0
    struct PixelNorm {
        float blue;   // Blue component
        float green;  // Green component
        float red;    // Red component

        PixelNorm operator+(PixelNorm other) const;
        PixelNorm& operator*=(float scalar);
        PixelNorm& operator+=(PixelNorm other);
        operator PixelHex() const;
    };

    PixelNorm operator*(float lhs, const PixelNorm& rhs);
    PixelNorm operator*(const PixelNorm& lhs, float rhs);

}  // namespace image
