#ifndef TENSOR_H
#define TENSOR_H

#include "tensor_types.hpp"
#include "tensor_literals.hpp"

tensor transpose_tensor(tensor t, int src, int dst);

tensor contract_tensor(tensor t, tensor s, int idx);

void print_tensor(tensor t);

#endif  // TENSOR_H
