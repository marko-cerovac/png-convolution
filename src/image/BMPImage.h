#pragma once

#include <memory>
#include <string>

#include "Pixel.h"

namespace image {

    class BMPImage {
      public:

        BMPImage(size_t width, size_t height);
        BMPImage(const std::string& file_path);
        BMPImage(const BMPImage& other);
        BMPImage(BMPImage&& other) noexcept;

        BMPImage& operator=(const BMPImage& other);
        BMPImage& operator=(BMPImage&& other) noexcept;

        void load(const std::string& file_path);
        void save(const std::string& file_path);

        inline size_t get_width() const noexcept { return width; }
        inline size_t get_height() const noexcept { return height; }

        PixelNorm& operator[](size_t width, size_t height);
        const PixelNorm& operator[](size_t width, size_t height) const;

      private:

        void allocate_bitmap(size_t width, size_t height);

      private:

        size_t width;
        size_t height;
        std::unique_ptr<PixelNorm[]> bitmap;
    };
}  // namespace image
