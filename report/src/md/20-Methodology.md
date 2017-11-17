# Methodology

## Matrices

Matrices in C are stored in memory in row-major order. As such, they flatten
out in memory as a sequential vector of rows. The most efficient way of
_iteratively_ traversing this matrix is sequentially iterating over each cell
in each row in the vector. This is know as _row-wise_ traversal. By properly
utilizing spatial locality, it performs better than _column-wise_ traversal.
With large matrices, column-wise traversal will generate more cache misses as
the algorithm wont portray the same degree of spatial locality. This is because
each cell in a different row is a full matrix length of data types away from
that cell in memory.

<!-- TODO: Figures with initilization and discussion -->

## Transpose

The transpose operator, $M^T$, flips each value in a 2D matrix $M$ by its $i$
and $j$ values.

<!-- ## Baseline Metrics -->

<!-- ## Recursive Tranpose -->
