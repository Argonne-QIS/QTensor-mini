import sys, os
import timeit
import argparse
import numpy as np

from .libargs import add_args

def get_tensors(miniargs):
    pass

def generate_tensors(miniargs):
    pass

def get_network(miniargs):
    pass

def main():

    clock = timeit.default_time()

    parser = argparse.ArgumentParser(description='QTensor-mini')
    add_args(parser)
    miniargs = parser.parse_args()

    np.random.seed(miniargs.seed)

if __name__ == '__main__':
    main()
