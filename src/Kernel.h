#pragma once
#include <array>
#include <cstddef>
#include <initializer_list>
#include <stdexcept>

namespace ar {
    template <typename T, std::size_t N>
    class Kernel {
      public:

        static_assert(N != 0, "Kernel dimension must be a non-zero value.");

        Kernel() = delete;

        Kernel(const std::initializer_list<double>& list) {
            unsigned int i = 0;
            for (const auto& param : list) {
                matrix[i++] = param;
            }
        }

        T operator()(std::size_t n, std::size_t m) const {
            return matrix[n * N + m];
        }

        T& operator()(std::size_t n, std::size_t m) {
            return matrix[n * N + m];
        }

        template <std::size_t n, std::size_t m>
        constexpr T at() const {
            return matrix[n * N + m];
        }

        template <std::size_t n, std::size_t m>
        constexpr T& at() {
            return matrix[n * N + m];
        }

        constexpr auto dim() const { return N; }

        constexpr inline auto begin() { return matrix.begin(); }
        constexpr inline auto cbegin() const { return matrix.cbegin(); }

        constexpr inline auto end() { return matrix.end(); }
        constexpr inline auto cend() const { return matrix.cend(); }

        /* static Kernel<T, N> parse(const std::string& input); */

      private:

        std::array<T, N * N> matrix;
    };
}  // namespace ar
