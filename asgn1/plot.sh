#!/bin/bash

rm -f /tmp/length.dat

for n in {1..10000}; do  
	echo -n $n \ >> /tmp/length.dat     
	./collatz -n $n | wc -l >> /tmp/length.dat
done 

for n in {1..10000}; do
	echo
	./collatz -n $n | sort -n | tail -n 1 >> /tmp/maximum.dat


# make clean && make sincos   # Rebuild the sincos executable.
# ./sincos > /tmp/sin.dat     # Place the data points into a file.

# This is the heredoc that is sent to gnuplot.

gnuplot <<END
   set terminal pdf 
   set output "length.pdf"
   set title "Collatz Sequence Lengths"
   set xlabel "x"
   set ylabel "y"
   set zeroaxis
   plot "/tmp/length.dat" with dots title ""
END
