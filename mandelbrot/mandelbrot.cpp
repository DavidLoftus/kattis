#include "mandelbrot.hpp"

#include <iostream>
#include <complex>
#include <iterator>
#include <algorithm>
#include <sstream>

namespace mandelbrot {

template<typename T>
bool inSet(std::complex<T> c, size_t niter) {
    std::complex<T> z = 0;
    for(size_t i = 0; i < niter; ++i) {
        z = z*z + c;
        if (std::norm(z) >= 4) {
            return false;
        }
    }
    return true;
}

struct input_t {
    std::complex<float> z;
    int r;
};

std::istream& operator>>(std::istream& is, input_t& input) {
    float a, b;
    is >> a >> b >> input.r; is.ignore();
    input.z = {a, b};
    return is;
}

void solution(std::istream& in, std::ostream& out) {
    std::transform(
            std::istream_iterator<input_t>(in),
            std::istream_iterator<input_t>(),
                    std::ostream_iterator<std::string>(out, "\n"),
            [n = 1](const input_t& input) mutable {
                std::ostringstream ss;
                ss << "Case " << n++ << ": " << (inSet(input.z, input.r) ? "IN" : "OUT");
                return ss.str();
            });
}

} // namespace mandelbrot
