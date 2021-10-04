
#include "tensor_literals.hpp"
#include "tensor_types.hpp"
#include <complex>
#include <tuple>

#define _USE_MATH_DEFINES
#include <cmath>


namespace tensor_literals {
    using namespace std::complex_literals;

    const std::complex<double> csqrt1o2 = M_SQRT1_2 + 0.0i; 
    const std::complex<double> cpio4 = M_PI_4 + 0.0i;
    const std::complex<double> c0 = 0.0i;
    const std::complex<double> c1 = 1.0 + 0.0i;

    tensor make1(int idx) {
        indices ind = { idx };
        data dat = { c1, c0 };
        return std::make_tuple(dat, ind);
    }

    tensor make0(int idx) {
        indices ind = { idx };
        data dat = { c0, c1 };
        return std::make_tuple(dat, ind);
    }

    tensor makeX(int idx_in, int idx_out) {
        indices idx = { idx_in, idx_out };
        data dat = { 
            c0, c1, 
            c1, c0
        };
        return std::make_tuple(dat, idx);
    }

    tensor makeY(int idx_in, int idx_out) {
        indices idx = { idx_in, idx_out };
        data dat = { 
            c0, -1.0if, 
            1.0if, c0
        };
        return std::make_tuple(dat, idx);
    }

    tensor makeZ(int idx_in, int idx_out) {
        indices idx = { idx_in, idx_out };
        data dat = { 
            c1, c0, 
            c0, -c1
        };
        return std::make_tuple(dat, idx);
    }

    tensor makeH(int idx_in, int idx_out) {
        indices idx = { idx_in, idx_out }; 
        
        data dat = { 
            csqrt1o2, csqrt1o2, 
            csqrt1o2, -csqrt1o2 
        };
        return std::make_tuple(dat, idx);
    }

    tensor makeS(int idx_in, int idx_out) {
        indices idx = { idx_in, idx_out };
        data dat = { 
            c1, c0, 
            c0, 1.0if
        };
        return std::make_tuple(dat, idx);
    }
    
    tensor makeT(int idx_in, int idx_out) {
        indices idx = { idx_in, idx_out };
        data dat = { 
            c1, c0, 
            c0, std::cos(cpio4) + std::sin(cpio4) 
        };
        return std::make_tuple(dat, idx);
    }

    tensor makeCX(int idx_in1, int idx_in2, int idx_out1, int idx_out2) {
        indices idx = { idx_in1, idx_in2, idx_out1, idx_out2 };
        data dat = {
            c1, c0, c0, c0,
            c0, c1, c0, c0,
            c0, c0, c0, c1,
            c0, c0, c1, c0
        };
        return std::make_tuple(dat, idx);
    }

    tensor makeCZ(int idx_in1, int idx_in2, int idx_out1, int idx_out2) {
        indices idx = { idx_in1, idx_in2, idx_out1, idx_out2 };
        data dat = { 
            c1, c0, c0, c0,
            c0, c1, c0, c0,
            c0, c0, c1, c0,
            c0, c0, c0, -c1
        };
        return std::make_tuple(dat, idx);
    }

    tensor makeSWAP(int idx_in1, int idx_in2, int idx_out1, int idx_out2) {
        indices idx = { idx_in1, idx_in2, idx_out1, idx_out2 };
        data dat = {
            c1, c0, c0, c0,
            c0, c0, c1, c0,
            c0, c1, c0, c0,
            c0, c0, c0, c1
        };
        return std::make_tuple(dat, idx);
    }

    tensor makeTOFF(int idx_in1, int idx_in2, int idx_in3, int idx_out1, int idx_out2, int idx_out3) {
        indices idx = { idx_in1, idx_in2, idx_in3, idx_out1, idx_out2, idx_out3 };
        data dat = {
            c1, c0, c0, c0, c0, c0, c0, c0,
            c0, c1, c0, c0, c0, c0, c0, c0,
            c0, c0, c1, c0, c0, c0, c0, c0,
            c0, c0, c0, c1, c0, c0, c0, c0,
            c0, c0, c0, c0, c1, c0, c0, c0,
            c0, c0, c0, c0, c0, c1, c0, c0,
            c0, c0, c0, c0, c0, c0, c0, c1,
            c0, c0, c0, c0, c0, c0, c1, c0
        };
        return std::make_tuple(dat, idx);
    }
}
