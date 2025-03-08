#include "BMPImage.h"

#include <cassert>
#include <fstream>
#include <stdexcept>
#include <utility>

#include "../utils/exceptions.h"
#include "Pixel.h"
#include "headers.h"

namespace image {
    BMPImage::BMPImage(size_t width, size_t height) : width(width), height(height) {
        assert(height > 0 && width > 0);

        bitmap = std::make_unique<PixelNorm[]>(width * height);
    }

    BMPImage::BMPImage(const std::string& filepath) { load(filepath); }

    BMPImage::BMPImage(const BMPImage& other) : width(other.width), height(other.height) {
        bitmap = std::make_unique<PixelNorm[]>(width * height);

        for (size_t i = 0; i < width * height; i++) {
            bitmap[i] = other.bitmap[i];
        }
    }

    BMPImage::BMPImage(BMPImage&& other) noexcept :
        width(other.width),
        height(other.height),
        bitmap(std::move(other.bitmap)) {}

    BMPImage& BMPImage::operator=(const BMPImage& other) {
        if (this == &other) {
            return *this;
        }

        bitmap.release();

        height = other.height;
        width  = other.width;
        bitmap = std::make_unique<PixelNorm[]>(width * height);

        for (size_t i = 0; i < width * height; i++) {
            bitmap[i] = other.bitmap[i];
        }

        return *this;
    }

    BMPImage& BMPImage::operator=(BMPImage&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        bitmap.release();

        height = other.height;
        width  = other.width;
        bitmap = std::move(other.bitmap);

        return *this;
    }

    void BMPImage::load(const std::string& filepath) {
        std::ifstream file(filepath, std::ios::binary);

        if (!file.is_open()) {
            throw utils::FileNotFoundException("Failed to open input file: " + filepath);
        }

        // read the BMP file header
        BMPHeader header;
        file.read(reinterpret_cast<char*>(&header), sizeof(header));

        if (!header.check_signature()) {
            throw utils::WrongInputFormatException(
                "Input file does not contain a BMP image signature.");
        }

        // read the BMP info header
        BMPInfoHeader info_header;
        file.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));

        if (info_header.bits_per_pix != 24) {
            throw utils::WrongInputFormatException("Only 24-bit BMPs are supported.");
        }

        width  = info_header.bitmap_width;
        height = info_header.bitmap_height;
        bitmap = std::make_unique<PixelNorm[]>(width * height);

        // go to the bitmap in the file
        file.seekg(header.bitmap_offset);

        // calculate the padding
        int padding = ((width * info_header.bits_per_pix + 31) / 32) * 4 - (width * 3);

        PixelHex placeholder;
        for (long int y = height - 1; y >= 0; y--) {
            for (long int x = 0; x < width; x++) {
                file.read(reinterpret_cast<char*>(&placeholder), sizeof(PixelHex));
                bitmap[y * height + x] = static_cast<PixelNorm>(placeholder);
            }
            // skip padding
            file.seekg(static_cast<size_t>(file.tellg()) + padding);
        }

        file.close();
    }

    void BMPImage::save(const std::string& file_path) {
        std::ofstream file(file_path, std::ios::binary);

        if (!file.is_open()) {
            throw utils::FileNotFoundException("Output file can not be opened.");
        }

        BMPHeader file_header;
        file_header.signature[0]  = 'B';
        file_header.signature[1]  = 'M';
        file_header.file_size     = 54 + (width * height * 3);
        file_header.reserved1     = 0;
        file_header.reserved2     = 0;
        file_header.bitmap_offset = 54;

        file.write(reinterpret_cast<char*>(&file_header), sizeof(file_header));

        BMPInfoHeader info_header;
        info_header.header_size      = 40;
        info_header.bitmap_width     = width;
        info_header.bitmap_height    = height;
        info_header.bitmap_planes    = 1;
        info_header.bits_per_pix     = 24;
        info_header.compression_type = 0;
        info_header.bitmap_size      = width * height * 3;
        info_header.x_pix_per_meter  = 0;
        info_header.y_pix_per_meter  = 0;
        info_header.num_colors       = 0;
        info_header.num_importaint   = 0;

        file.write(reinterpret_cast<char*>(&info_header), sizeof(info_header));

        // calculate the padding
        int padding = ((width * info_header.bits_per_pix + 31) / 32) * 4 - (width * 3);

        width  = info_header.bitmap_width;
        height = info_header.bitmap_height;
        PixelHex placeholder;
        // write the pixel data
        for (long int y = height - 1; y >= 0; --y) {
            for (long int x = 0; x < width; x++) {
                placeholder = static_cast<PixelHex>(bitmap[y * height + x]);
                file.write(reinterpret_cast<char*>(&placeholder), sizeof(PixelHex));
            }

            // write padding bites
            for (int i = 0; i < padding; i++) {
                char zero = 0;
                file.write(&zero, sizeof(zero));
            }
        }

        file.close();
    }

    PixelNorm& BMPImage::operator[](size_t width, size_t height) {
        if (width > this->width || height > this->height) {
            throw std::out_of_range("Attempting to index a pixel out of bounds.");
        }

        /* return bitmap[height * this->height + width]; */
        return bitmap[width * this->width + height];
    }

    const PixelNorm& BMPImage::operator[](size_t width, size_t height) const {
        if (width > this->width || height > this->height) {
            throw std::out_of_range("Attempting to index a pixel out of bounds.");
        }

        /* return bitmap[height * this->height + width]; */
        return bitmap[width * this->width + height];
    }
}  // namespace image
