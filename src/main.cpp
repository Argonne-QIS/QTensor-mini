#include <emmintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <cmath>
#include <complex>

#include "tensor.hpp"
#include "graph.hpp"
#include <boost/program_options.hpp>

namespace opts=boost::program_options;

int main(int argc, char* argv[]) {
    // Define broad command line arguments
    opts::options_description general("General Options");
    general.add_options()
        ("help", "produce help message")
        ("seed", opts::value<int>(), "set random seed")
        ("report", "print a information on completion")
        ("numthreads", opts::value<int>(), "set number of OMP threads")
        ;

    // Command line arguments for working with tensors and tensor network contractions
    opts::options_description tensoropts("Tensor Contraction Options");
    tensoropts.add_options()
        ("supported-gates", "print list of supported gates")
        ("input-order", opts::value<std::string>(),
         "path to input linear contraction order")
        ("input-tensors", opts::value<std::string>(), 
         "path to input list of tensors")
        ("output-tensor", opts::value<std::string>(), 
         "contract network and write output to this location");

    // Command line arguments for working with hypergraphs
    opts::options_description hypergraph("Hypergraph Options (In Development)");
    hypergraph.add_options()
        ("input-graph", opts::value<std::string>(), 
         "path to input hypergraph")
        ("ouput-graph", opts::value<std::string>(), 
         "generate and write hypergraph to this location")
        ("order-algorithm", opts::value<int>(), 
         "algorithm used for contraction ordering\n (1) Greedy\n (2) Tamaki\n(3) Partitioning")
        ("partition-library", opts::value<int>(), 
         "Libary used for graph partitions\n (1) KaHyPar")
        ; 

    // Aggregate command line argument descriptions
    opts::options_description desc("Allowed Options");
    desc.add(general).add(hypergraph).add(tensoropts);

    // Construct map containing command line arguments
    opts::variables_map vm;
    opts::store(opts::parse_command_line(argc, argv, desc), vm);
    opts::notify(vm);

    // Generate help message and exit
    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 1;
    }

    // Set random seed for pseudorandom number generation.
    if (vm.count("seed")) {
        srand(vm["seed"].as<int>());
    }

    int order_algorithm = 0;
    if (vm.count("order-algorithm")) {
        order_algorithm = vm["order-algorithm"].as<int>();
    }
    
    // select and initialize partition algorithm
    int partition_algorithm = 1;
    if (vm.count("partition-algorithm")) {
        partition_algorithm = vm["partition-algorithm"].as<int>();
    }
    switch (partition_algorithm) {
        case 1:
            break;
        default:
            std::cout << "Not a supported algorithm" << std::endl;
    }

    // initialize sparse incidence matrix
    // sparse_matrix_t incidence;

    if (vm.count("input-graph")) {
        // TODO Load graph from input file
    } 

    /*
    std::cout << "TESTING\n";

    tensor tX = tensor_literals::makeY(1, 2);
    print_tensor(tX);
    tensor tY = tensor_literals::makeX(2, 3);
    print_tensor(tY);
    contract_tensor(tX, tY, 2);
    */
    return 0;
}
