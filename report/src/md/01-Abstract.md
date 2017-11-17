\begin{abstract}

Modern computers use clever tricks to increase performance without incurring
massive financial costs. One such performance improvement is seen in hierarchical memory
where a series of progressively slower memory devices work together to reduce
the latency induced by memory operations. Although these systems work well when
used effectively, naive code can break the system, resulting in bad performance.
These issues become highly apparent when looping over large matrices.
Depending on the architecture of the cache, the ordering of the matrix in
memory, and the code itself, initializing and performing actions on matrices
could take a large amount of time. This paper explores the effects of cache
on matrix operations using C-code. The results show that programmers need pay
close attention to the design of their code to ensure proper utilization of
the underlying hardware through novel means.

\end{abstract}
