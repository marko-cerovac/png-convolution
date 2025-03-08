#include "Pixel.h"

namespace image {
    PixelHex::operator PixelNorm() const {
        return {
            static_cast<float>(blue) / 0xFF,
            static_cast<float>(green) / 0xFF,
            static_cast<float>(red) / 0xFF,
        };
    }

    PixelNorm::operator PixelHex() const {
        return {
            static_cast<uint8_t>(blue * 0xFF),
            static_cast<uint8_t>(green * 0xFF),
            static_cast<uint8_t>(red * 0xFF),
        };
    }

    PixelNorm PixelNorm::operator+(PixelNorm other) const {
        return {blue + other.blue, green + other.green, red + other.red};
    }

    PixelNorm& PixelNorm::operator*=(float scalar) {
        blue *= scalar;
        green *= scalar;
        red *= scalar;

        return *this;
    }

    PixelNorm& PixelNorm::operator+=(PixelNorm other) {
        blue += other.blue;
        green += other.green;
        red += other.red;

        return *this;

    }

    PixelNorm operator*(float lhs, const PixelNorm& rhs) {
        return {
            rhs.blue * lhs,
            rhs.green * lhs,
            rhs.red * lhs,
        };

    }

    PixelNorm operator*(const PixelNorm& lhs, float rhs) {
        return {
            lhs.blue * rhs,
            lhs.green * rhs,
            lhs.red * rhs,
        };
    }
}  // namespace image
