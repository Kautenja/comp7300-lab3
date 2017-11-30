# Conclusions

This paper presents a recursive and parallel method to initialize and transpose
a large square matrix in minimal time. A key feature of this recursive
algorithm is a natural "cache naive" trait that allows it to exploit the cache
line without explicit cache blocking. This coupled with a highly parallel
architecture, like the 16-core Intel Xeon processors in the Tux machines,
allows the algorithm to initialize and transpose a 40000x40000 matrix
($\approx 12.8$GB) in 1.9 seconds ($\approx 6.7GB/s$). Although this time is
fast, faster times are certainly possible. Future research may investigate the
integration of vector architectures like GPUs to speedup the initialization and
transpose of matrices.
