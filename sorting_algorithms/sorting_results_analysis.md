# Sorting Algorithm Performance Analysis
## Homework Assignment 5 - O(n²) and O(n log n) Sorting Algorithms

### Experimental Results

The following table shows the average wall clock times (in milliseconds) for 10 trials of each sorting algorithm:

| N (Array Size) | Insertion Sort (ms) | Merge Sort (ms) | Ratio (I/M) |
|----------------|---------------------|-----------------|-------------|
| 10             | 0.0000              | 0.0006          | 0.00        |
| 100            | 0.0020              | 0.0115          | 0.17        |
| 1000           | 0.0938              | 0.0938          | 1.00        |
| 10000          | 6.9487              | 0.9006          | 7.72        |

### Analysis and Answers

#### Which algorithm is faster for small N?
For small values of N (10, 100), **Insertion Sort is faster** than Merge Sort. This is evident from the results:
- N=10: Insertion Sort is essentially instantaneous (0.0000 ms) vs Merge Sort (0.0006 ms)
- N=100: Insertion Sort (0.0020 ms) is about 5.75 times faster than Merge Sort (0.0115 ms)

#### Which algorithm is faster for large N?
For large values of N (1000, 10000), **Merge Sort becomes significantly faster**:
- N=1000: Both algorithms perform similarly (0.0938 ms each)
- N=10000: Merge Sort (0.9006 ms) is about 7.72 times faster than Insertion Sort (6.9487 ms)

#### How do the wall clock times and growth rates compare to the big O average time complexities?

The experimental results align well with the theoretical time complexities:

**Insertion Sort - O(n²):**
- Small N: Very fast due to minimal overhead and few comparisons
- Large N: Performance degrades quadratically as predicted by O(n²)
- At N=10000, the time increases dramatically compared to smaller sizes

**Merge Sort - O(n log n):**
- Small N: Slightly slower due to recursive overhead and array copying
- Large N: Maintains relatively good performance due to the logarithmic factor
- At N=10000, it significantly outperforms Insertion Sort

### Key Observations

1. **Crossover Point**: The crossover where Merge Sort becomes more efficient than Insertion Sort occurs around N=1000 in this experiment.

2. **Growth Rate Validation**: 
   - Insertion Sort shows quadratic growth (N=100 to N=1000: ~47x increase in time)
   - Merge Sort shows near-linear growth (N=100 to N=1000: ~8x increase in time)

3. **Practical Implications**: 
   - For small datasets (< 100 elements), Insertion Sort's simplicity and low overhead make it competitive
   - For larger datasets, Merge Sort's O(n log n) complexity provides substantial performance benefits

### Conclusion

The experimental results confirm the theoretical analysis: while Insertion Sort has advantages for very small datasets due to its simplicity and low overhead, Merge Sort's superior asymptotic complexity (O(n log n) vs O(n²)) makes it the clear winner for larger datasets. The crossover point observed in this experiment aligns with expectations from algorithmic analysis.
