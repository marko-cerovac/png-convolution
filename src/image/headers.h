#pragma once

#include <cstdint>

namespace image {

#pragma pack(push, 1)

    // Structure for BMP file header
    struct BMPHeader {
        uint8_t signature[2];    // File type signature (BM)
        uint32_t file_size;      // Size of file in bytes
        uint16_t reserved1;      // Reserved; must be 0
        uint16_t reserved2;      // Reserved; must be 0
        uint32_t bitmap_offset;  // Offset to image data in bytes

        inline bool check_signature() const { return signature[0] == 'B' && signature[1] == 'M'; }
    };

    // Structure for BMP info header
    struct BMPInfoHeader {
        uint32_t header_size;       // Size of info header in bytes
        int32_t bitmap_width;       // Width of image in pixels
        int32_t bitmap_height;      // Height of image in pixels
        uint16_t bitmap_planes;     // Number of color planes (must be 1)
        uint16_t bits_per_pix;      // Bits per pixel (24 for this example)
        uint32_t compression_type;  // Compression type (0 for none)
        uint32_t bitmap_size;       // Size of image data in bytes
        int32_t x_pix_per_meter;    // X pixels per meter (resolution)
        int32_t y_pix_per_meter;    // Y pixels per meter (resolution)
        uint32_t num_colors;        // Number of colors used
        uint32_t num_importaint;    // Number of important colors
    };

#pragma pack(pop)
}  // namespace image
