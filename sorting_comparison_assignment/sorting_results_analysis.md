# Sorting Algorithm Comparison Analysis

## Results Summary

The following analysis is based on testing three sorting algorithms (Insertion Sort, Bucket Sort, and Radix Sort) on random vectors of sizes N ∈ {10, 100, 1000, 10000} with each test repeated 10 times. All vectors contained random integers from 0 to 999.

### Average Wall Clock Times (in milliseconds)

| Size  | Insertion Sort | Bucket Sort | Radix Sort |
|-------|----------------|-------------|------------|
| 10    | 0.0000         | 0.0021      | 0.0074     |
| 100   | 0.0128         | 0.0182      | 0.0239     |
| 1000  | 0.9976         | 0.1558      | 0.1190     |
| 10000 | 67.5071        | 0.8401      | 0.7006     |

## Analysis and Answers

### Which algorithm is faster for small N?

**For small N (N = 10, 100):** **Insertion Sort** is faster.

- At N = 10: Insertion Sort averages 0.0000ms, significantly faster than Bucket Sort (0.0021ms) and Radix Sort (0.0074ms)
- At N = 100: Insertion Sort averages 0.0128ms, still faster than Bucket Sort (0.0182ms) and Radix Sort (0.0239ms)

This makes sense because Insertion Sort has a simple implementation with minimal overhead, while Bucket Sort and Radix Sort have additional setup costs (bucket creation, digit extraction) that become significant relative to the actual sorting time for small datasets.

### Which algorithm is faster for large N?

**For large N (N = 1000, 10000):** **Radix Sort** is fastest, followed by **Bucket Sort**.

- At N = 1000: Radix Sort (0.1190ms) > Bucket Sort (0.1558ms) > Insertion Sort (0.9976ms)
- At N = 10000: Radix Sort (0.7006ms) > Bucket Sort (0.8401ms) > Insertion Sort (67.5071ms)

The performance gap becomes dramatic at N = 10000, where Insertion Sort takes 67.5ms while Radix Sort takes only 0.7ms - nearly 100 times faster!

### How do the wall clock times and growth rates compare to the big O average time complexities?

#### Theoretical Time Complexities:
- **Insertion Sort**: O(n²) average case
- **Bucket Sort**: O(n + k) where k is the number of buckets
- **Radix Sort**: O(d × n) where d is the number of digits

#### Observed Growth Rates:

1. **Insertion Sort**: Shows clear quadratic growth
   - N = 10: 0.0000ms
   - N = 100: 0.0128ms (100x increase → 100x growth)
   - N = 1000: 0.9976ms (10x increase → 78x growth)
   - N = 10000: 67.5071ms (10x increase → 68x growth)
   
   The growth is approximately quadratic, confirming O(n²) behavior.

2. **Bucket Sort**: Shows approximately linear growth
   - N = 10: 0.0021ms
   - N = 100: 0.0182ms (10x increase → 8.7x growth)
   - N = 1000: 0.1558ms (10x increase → 8.6x growth)
   - N = 10000: 0.8401ms (10x increase → 5.4x growth)
   
   Growth is much closer to linear, confirming O(n + k) behavior.

3. **Radix Sort**: Shows approximately linear growth
   - N = 10: 0.0074ms
   - N = 100: 0.0239ms (10x increase → 3.2x growth)
   - N = 1000: 0.1190ms (10x increase → 5.0x growth)
   - N = 10000: 0.7006ms (10x increase → 5.9x growth)
   
   Growth is close to linear, confirming O(d × n) behavior where d is constant for our range.

### Key Observations:

1. **Crossover Point**: The crossover from Insertion Sort being fastest to Radix/Bucket Sort being fastest occurs between N = 100 and N = 1000.

2. **Scalability**: Radix Sort and Bucket Sort maintain excellent performance scaling, while Insertion Sort becomes impractical for larger datasets.

3. **Overhead vs. Efficiency Trade-off**: For very small datasets, the overhead of more complex algorithms outweighs their theoretical efficiency. For larger datasets, the O(n²) complexity of Insertion Sort becomes the dominant factor.

4. **Practical Implications**: 
   - Use Insertion Sort for very small arrays (N < 100)
   - Use Radix Sort for larger arrays where performance is critical
   - Bucket Sort provides a good middle ground with reasonable performance across all sizes

The experimental results strongly support the theoretical time complexity analysis, with the measured growth rates closely matching the expected Big O behaviors.
