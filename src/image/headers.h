#pragma once

#include <sys/types.h>
namespace image {

    // Structure for BMP file header
    struct BMPHeader {
        u_int8_t signature[2];    // File type signature (BM)
        u_int32_t file_size;      // Size of file in bytes
        u_int16_t reserved1;      // Reserved; must be 0
        u_int16_t reserved2;      // Reserved; must be 0
        u_int32_t bitmap_offset;  // Offset to image data in bytes

        inline bool check_signature() const { return signature[0] == 'B' && signature[1] == 'M'; }
    };

    // Structure for BMP info header
    struct BMPInfoHeader {
        u_int32_t header_size;       // Size of info header in bytes
        int32_t bitmap_width;        // Width of image in pixels
        int32_t bitmap_height;       // Height of image in pixels
        u_int16_t bits_per_pix;      // Bits per pixel (24 for this example)
        u_int16_t bitmap_planes;     // Number of color planes (must be 1)
        u_int32_t compression_type;  // Compression type (0 for none)
        u_int32_t bitmap_size;       // Size of image data in bytes
        int32_t x_pix_per_meter;     // X pixels per meter (resolution)
        int32_t y_pix_per_meter;     // Y pixels per meter (resolution)
        u_int32_t num_colors;        // Number of colors used
        u_int32_t num_importaint;    // Number of important colors
    };
}  // namespace image
