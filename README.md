Comparing Codon, Pypy, Vanilla Python and C++
=============================================

Comparing the performance of three Python implementations and native C++ at naively computing the number of prime numbers between two numbers.

The implementations being compared:
 + **Vanilla Python 3** - [python.org](https://www.python.org/)
 + **Codon** - [Github](https://github.com/exaloop/codon)
 + **Pypy3** - [pypy3.org](https://www.pypy.org/)
 + **C++**

**Test Bench**: Intel® Core™ i3-7100U CPU @ 2.40GHz (2 Core / 4 Threads)

Results are as follows. Sorted from fastest to slowest: 
|       Command      |     Mean [s]    | Min [s] | Max [s] |  Relative  |
|:-------------------|----------------:|--------:|--------:|-----------:|
| `C++ Parallel`     | 1.971 ± 0.058   | 1.883   | 2.074   |    1.00    |
| `C++ Sequential`   | 4.566 ± 0.029   | 4.530   | 4.612   |    2.32    |
| `Codon Parallel`   | 5.517 ± 0.057   | 5.413   | 5.600   |    2.80    |
| `Codon Sequential` | 14.724 ± 0.049  | 14.663  | 14.839  |    7.47    |
| `Pypy 3`           | 20.124 ± 0.158  | 19.971  | 20.516  |    10.21   |
| `Vanilla Python3`  | 108.218 ± 0.923 | 107.305 | 110.186 |    54.91   |

