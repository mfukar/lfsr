#!/usr/bin/env python
# -*- coding: utf-8 -*-
# @file         /home/mfukar/src/lfsr/lfsr.py
# @author       Michael Foukarakis
# @version      1.0
# @date         Created:     Thu Feb 03, 2011 08:19 GTB Standard Time
#               Last Update: Thu Oct 06, 2016 14:40 CEST
#------------------------------------------------------------------------
# Description:  Implementation of a Galois LFSR
#               The bitstream is provided by the generator function
#               GLFSR.states(). The 'repeat' flag controls whether the
#               generator stops once the LFSR overflows or whether it
#               continues perpetually.
#------------------------------------------------------------------------
# History:      None yet
# TODO:         Nothing yet
#------------------------------------------------------------------------
class GLFSR:
    def __init__(self, polynomial, seed):
        self.polynomial = polynomial | 1
        self.seed = seed
        self.data = seed
        self.mask = 1

        temp_mask = polynomial
        while temp_mask != 0:
            if temp_mask & self.mask != 0:
                temp_mask = temp_mask ^ self.mask
            if temp_mask == 0: break
            self.mask = self.mask << 1

    def states(self, repeat=False):
        while True:
            self.data = self.data << 1
            if self.data & self.mask != 0:
                self.data = self.data ^ self.polynomial
                yield 1
            else:
                yield 0
            if repeat == False and self.data == self.seed:
                return


# Polynomials needed below this point
from polynomial import Polynomial
X   = Polynomial([1, 0])
One = Polynomial([1])

def bm(seq):
    """Implementation of the Berlekamp-Massey algorithm, the purpose
       of which is to find a LFSR with the smallest possible length
       that generates a given sequence.

       A generator is returned  that yields the current LFSR at
       each call. At the k-th call the yielded LFSR is guaranteed
       to generate the first k bits of SEQ.

       Input :
       Output: A list of coefficients [c0, c1,..., c{m-1}]

       Internally, if the state of the LFSR is (x0,x1,...,x{m-1})
       then the output bit is x0, the register contents are shifted
       to the left, and the new
       x{m-1} = c0 * x0 + c1 * x1 +...+c{m-1} * x{m-1}

       The generating function G(x) = s_0 + s_1 * x^1 + s_2 * x^2 + ...
       of a LFSR is rational and (when written in lowest terms) the
       denominator f(x) is called the characteristic polynomial of the
       LFSR. Here we have f(x) = c0 * x^m + c1 * x^{m-1} +...+ c{m-1} * x + 1.
       """
    # Allow for an input string along with a list or tuple
    if type(seq) == type('string'):
        seq = map(int, tuple(seq))

    m = 0

    # N is the index of the current element of the sequence SEQ under consideration
    # f is the characteristic polynomial of the current LFSR
    N,f = 0,One

    # N0 and f0 are the values of N and f when m was last changed
    # N0 starts out as -1
    N0,f0 = -1,One

    n = len(seq)
    while N < n:
        # Does the current LFSR compute the next entry in the
        # sequence correctly? If not we need to update the LFSR
        if seq[N] != f.dot(seq[:N]):
            # If N is small enough we can get away with just
            # updating the coefficients in the LFSR. Note that
            # the 'X' occuring below is a global variable and
            # is the indeterminant in the polynomials defined
            # by the class 'Polynomial'. That is, X=Polynomial([1,0])
            if 2*m>N:
                f = f + f0 * X**(N-N0)

            # Otherwise we'll have to update everything
            else:
                f0, f = f, f + f0 * X**(N-N0)
                N0 = N
                m = N+1-m

        # Next element..
        N += 1

        # yield the coefficients [c0, ... , c{m-1}] of the
        # current LFSR's feedback function
        yield f[:-1]
    # yield the final LFSR coefficients once again
    yield f[:-1]
