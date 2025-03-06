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

        Pixel& operator[](size_t width, size_t height);
        const Pixel& operator[](size_t width, size_t height) const;

      private:

        void allocate_bitmap(size_t width, size_t height);

      private:

        size_t width;
        size_t height;
        std::unique_ptr<std::unique_ptr<Pixel[]>[]> bitmap;
    };
}  // namespace image
