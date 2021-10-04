# QTensor-Mini

QTensor-mini is a proxy app for the QTensor Quantum Circuit Simulation library. QTensor is meant to demonstrate and test paradigms used in quantum circuit simulation, in particular Tensor Network Contraction. The primary functionality of QTensor is the contraction of simple input tensor network.

QTensor is buing developed to be part of the ECP Proxy app suite. Link to the rest of the project below.
https://proxyapps.exascaleproject.org/


## Key Implementation Details

The tensor network contractions employed by QTensor-mini are written using the BLAS interface, and uses the LibBlasTrampoline package in order to be agnostic to the specific varient of BLAS used. QTensor-mini in particular benefits from using a package with explicit optimizations for tall, skinny matrices, such as BLIS.

An alternative mode making use of the cuTensor library for tensor support on GPUs is in dvelopment.

 
## Building QTensor-mini

Perform the following steps:
1. Build the program using the following `make` commands. 
``` 
$ export perf_num=1     *optional, will enable performance tabulation mode
$ make
```

2. Run the program:
    ```
    make run
    ```

3. Clean the program using:
    ```
    make clean
    ```


## Running the Sample

### Example Input

### Example Output
