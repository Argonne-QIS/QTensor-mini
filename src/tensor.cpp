#include "tensor.hpp"
#include <complex>
#include <string>
#include <iostream>
#include <tuple>
#include <algorithm>
#include "tensor_types.hpp"
#include "tensor_literals.hpp"
#include "cblas.h"
#include <cassert>

int getbit(int n, int i) {
    return (n & ( 1 << i )) >> i;
}

int swapbits(int x, int i, int j) {
    int same = (getbit(x, i) ^ getbit(x, j));
    int mask = same << i | same << j;
    return x ^ mask;
}

std::string intidxtostring(int n, int k) {
    std::string ret = "";
    for (int i = k - 1; i >= 0; i--) 
        ret += std::to_string(getbit(n, i)) + " ";
    return ret;
}

std::string ctostring(std::complex<double> c) {
    std::string realstr = std::to_string(std::real(c));
    std::string imagstr = std::to_string(std::imag(c));
    return realstr + " + " + imagstr + "i";
}

void print_tensor(tensor t) {
    data dat;
    indices idx;
    std::tie(dat, idx) = t;

    std::cout << "Indices: ";
    std::for_each(idx.begin(), idx.end(), [](int i) {
            std::cout << i << ' '; 
            });
    std::cout << "\nData:\n";
    for (int i = 0; i < dat.size(); i++) 
        std::cout << intidxtostring(i, idx.size()) << " | " <<  ctostring(dat[i]) << "\n"; 
    std::cout << "\n";
}

tensor transpose_tensor(tensor t, int src, int dst) {
    data dat;
    indices idx;
    std::tie(dat, idx) = t;
    std::swap(idx[src], idx[dst]); 
    for (int i = 0; i < dat.size(); i++) {
        int swapped = swapbits(i, src, dst);
        if (i < swapped) {
            std::cout << std::to_string(i) << " " << std::to_string(swapped) << "\n";
            std::swap(dat[i], dat[swapped]);
        }
    }
    return std::make_tuple(dat, idx);
}

tensor _contract_tensor(tensor t, tensor s) {
    data datt, dats;
    indices idxt, idxs;
    std::tie(datt, idxt) = t;   
    std::tie(dats, idxs) = s;

    blasint Nt = datt.size();
    auto At = datt.data();
    blasint inct = 1;
    blasint Ns = dats.size();
    auto As = dats.data();
    blasint incs = 1;

    std::cout << "GOODBYE WORLD\n";
    abort();
    // std::complex<double> out;
    //zdotc(out, Nt, At, inct, At, inct);

    // std::cout << "TEST " << std::to_string(std::real(out));
}

template<class T>
int indexof(std::vector<T> vec, T x) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == x)
            return i;
    }
    return -1;
}

tensor contract_tensor(tensor t, tensor s, int idx) {
    data datt, dats;
    indices idxt, idxs;
    std::tie(datt, idxt) = t;   
    std::tie(dats, idxs) = s;

    int swapt = indexof<int>(idxt, idx);
    int swaps = indexof<int>(idxs, idx);

    if (swapt == -1 || swaps == -1) {
        std::cout << "CANNOT PROCEED\n";
        abort();
    }
    tensor newt = transpose_tensor(t, swapt, idxt.size()-1);
    tensor news = transpose_tensor(s, 0, swaps);


    return _contract_tensor(newt, news);
}



