#pragma once
#include <array>
#include <cstddef>
#include <initializer_list>
#include <string>

#include "utils/exceptions.h"
#include "utils/utils.h"

namespace ar {
    template <typename T, size_t N>
    class Kernel {
      public:

        static_assert(N != 0, "Kernel dimension must be a non-zero value.");

        Kernel() = default;

        Kernel(const std::initializer_list<T>& list) {
            unsigned int i = 0;
            for (const auto& param : list) {
                matrix[i++] = param;
            }
        }

        T operator()(size_t n, size_t m) const { return matrix[n * N + m]; }

        T& operator()(size_t n, size_t m) { return matrix[n * N + m]; }

        template <size_t n, size_t m>
        constexpr T at() const {
            return matrix[n * N + m];
        }

        template <size_t n, size_t m>
        constexpr T& at() {
            return matrix[n * N + m];
        }

        constexpr auto dim() const { return N; }

        constexpr inline auto begin() { return matrix.begin(); }
        constexpr inline auto cbegin() const { return matrix.cbegin(); }

        constexpr inline auto end() { return matrix.end(); }
        constexpr inline auto cend() const { return matrix.cend(); }

      private:

        std::array<T, N * N> matrix;
    };

    template <size_t N>
    class Kernel<float, N> {
      public:

        static_assert(N != 0, "Kernel dimension must be a non-zero value.");

        Kernel() = default;

        Kernel(const std::initializer_list<float>& list) {
            unsigned int i = 0;
            for (const auto& param : list) {
                matrix[i++] = param;
            }
        }

        float operator()(size_t n, size_t m) const { return matrix[n * N + m]; }

        float& operator()(size_t n, size_t m) { return matrix[n * N + m]; }

        template <size_t n, size_t m>
        constexpr float at() const {
            return matrix[n * N + m];
        }

        template <size_t n, size_t m>
        constexpr float& at() {
            return matrix[n * N + m];
        }

        constexpr auto dim() const { return N; }

        constexpr inline auto begin() { return matrix.begin(); }
        constexpr inline auto cbegin() const { return matrix.cbegin(); }

        constexpr inline auto end() { return matrix.end(); }
        constexpr inline auto cend() const { return matrix.cend(); }

        static Kernel<float, N> parse(const std::string& input) {
            auto params = utils::split(input);

            if (params.size() != N * N) {
                throw utils::ParseErrorException(
                    "Parsing error: number of parameters doesn't match kernel dimentions");
            }

            Kernel<float, N> result;

            size_t i = 0;
            for (const auto& param : params) {
                try {
                    float temp         = std::stod(param);
                    result.matrix[i++] = temp;
                } catch (const std::exception& err) {
                    throw utils::ParseErrorException(
                        "Parsing error: could not resolve parameter to a float");
                }
            }

            return result;
        }

      private:

        std::array<float, N * N> matrix;
    };
}  // namespace ar
