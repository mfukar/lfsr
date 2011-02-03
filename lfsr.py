#!/usr/bin/env python
# @file		/home/mfukar/src/lfsr/lfsr.py
# @author	Michael Foukarakis
# @version	1.0
# @date 	Created:     Thu Feb 03, 2011 08:19 GTB Standard Time
# 		Last Update: Thu Feb 03, 2011 16:26 GTB Standard Time
#------------------------------------------------------------------------
# Description:	Implementation of a Galois LFSR 
#               The bitstream is provided by the generator function
#               GLFSR.states(). The 'repeat' flag controls whether the
#               generator stops once the LFSR overflows or whether it
#               continues perpetually.
#------------------------------------------------------------------------
# History:	None yet
# TODO:		Nothing yet
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
