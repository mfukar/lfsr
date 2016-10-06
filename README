An implementation of a Galois LFSR, along with some helpful utilities.

## What is it?

A linear feedback shift register (LFSR) is a shift register whose input is a linear
function of its state.

There are two variations, the Fibonacci LFSR and the Galois LFSR.

The Fibonacci LFSR determines the input bit by the exclusive-or of the output bit and the
'tap' bits, or taps.

The Galois LFSR, bits are shifted right unchanged unless they are taps, in which case they
are XORd with the output bit.

Their equivalence is better illustrated [here](http://www.cs.miami.edu/home/burt/learning/Csc599.092/docs/galois.pdf).

Along with the implementation of a Galois LFSR, in this repository you will find:

+ A pseudo random number generator using said LFSR, in prng.c
+ A table of taps for constructing maximum length GLFSRs, in lfsr_table.txt
+ A Python implementation of a GLFSR, in lfsr.py
+ A Python implementation of the Berlekamp-Massey algorithm, for finding the
  minimal LFSR that generates a given sequence, in lfsr.py

## How to use

You can use the Galois LFSR implementation anywhere where you would need a LFSR
implementation. If performance is critical, I suggest you find more efficient, parallel
implementations. Or, hire me to write one for you. Use cases for LFSRs are simple PRNGs,
weak stream ciphers, white noise generators, signature analysis, signal scrambling, and
test pattern generation.

The Python module can be used without any dependencies other than the standard library in
all similar use cases.

## How to build

`lfsr.c` and `prng.c` contain C89, C99, and C11-compatible code. Compile with:

`$(CC lfsr.c prng.c)`

`lfsr.py` is compatible with both Python 2 and Python 3, but has only been tested against Python 3.5.

