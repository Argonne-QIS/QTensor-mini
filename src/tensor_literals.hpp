#ifndef TENSOR_LITERAL_H
#define TENSOR_LITERAL_H

#include "tensor_types.hpp"

namespace tensor_literals {
    tensor make0(int idx);
    tensor make1(int idx);
    tensor makeX(int idx_in, int idx_out);
    tensor makeY(int idx_in, int idx_out);
    tensor makeZ(int idx_in, int idx_out);
    tensor makeH(int idx_in, int idx_out);
    tensor makeS(int idx_in, int idx_out);
    tensor makeT(int idx_in, int idx_out);
    tensor makeCX(int idx_in1, int idx_in2, int idx_out1, int idx_out2);
    tensor makeCZ(int idx_in1, int idx_in2, int idx_out1, int idx_out2);
    tensor makeSWAP(int idx_in1, int idx_in2, int idx_out1, int idx_out2);
    tensor makeTOFF(int idx_in1, int idx_in2, int idx_in3, int idx_out1, int idx_out2, int idx_out3);
}

#endif
