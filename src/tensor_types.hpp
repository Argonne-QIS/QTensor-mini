#ifndef TENSOR_TYPES_H
#define TENSOR_TYPES_H

#include <complex>
#include <vector>
#include <tuple>

using data = std::vector<std::complex<double>>;
using indices = std::vector<int>;
using tensor = std::tuple<data, indices>;

#endif // TENSOR_TYPES_H

