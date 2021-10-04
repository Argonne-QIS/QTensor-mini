#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>
#include <iostream>
#include <tuple>
#include "tensor.hpp"
#include "contraction.hpp"

using edge_inc = std::tuple<int, int>;
using HG = std::vector<edge_inc>;
using tvert = std::tuple<int, tensor>;
using TN = std::tuple<HG, std::vector<tvert>>;

TN parseTN(std::string filename);
void printTN(TN network);

tensor contractTN(TN network);

#endif  // GRAPH_H
