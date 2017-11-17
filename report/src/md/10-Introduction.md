# Introduction

## Hierarchical Memory

_Hierarchical memory_ utilizes a sequence of memory devices and heuristics to
improve performance of memory operations. This sequence exists to balance
performance and cost, allowing machines to take advantage of more expensive,
but faster, memory devices. The machine can then leverage these devices for
recurring or frequently used data to reduce latency.

### Locality

In order to best utilize this hierarchy of devices, engineers employ two
similar, but distinct heuristics based on _locality_. _Temporal locality_
states that data used recently is likely to be used again soon. Without
temporal locality, cache hits would rarely occur as new data from memory would
always be needed. _Spatial locality_ is the principle that data near recently
used data is likely to be needed soon. This principle drives engineers to copy
surrounding data to cache when a cache miss occurs for a memory address.
