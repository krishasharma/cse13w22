#!/bin/bash

# collatz sequence lengths for loop
rm -f /tmp/length.dat
for n in {1..10000}; do  
	echo -n $n \ >> /tmp/length.dat     
	./collatz -n $n | wc -l >> /tmp/length.dat
done 


# maximum collatz sequence value for loop 
rm -f /tmp/maximum.dat
for n in {1..10000}; do
	echo -n $n \ >> /tmp/maximum.dat 
	./collatz -n $n | sort -n | tail -n 1 >> /tmp/maximum.dat
done


# collatz sequence lengths histogram 
rm -f /tmp/length.dat 
for n in {1:10000}; do 
	./collatz -n $n | wc -l >> /tmp/length.dat
done 
cat /tmp/length.dat | uniq -c | less >> /tmp/histogram.dat 

# make clean && make sincos   # Rebuild the sincos executable.
# ./sincos > /tmp/sin.dat     # Place the data points into a file.

# This is the heredoc that is sent to gnuplot.


# collatz sequence lengths 
gnuplot <<END
   set terminal pdf 
   set output "length.pdf"
   set title "Collatz Sequence Lengths"
   set xlabel "x"
   set ylabel "y"
   set zeroaxis
   plot "/tmp/length.dat" with dots title ""
END


# maximum collatz sequence value
gnuplot <<END
   set terminal pdf 
   set output "maximum.pdf"
   set title "Maximum Collatz Sequence Value"
   set xlabel "n"
   set ylabel "value"
   set yrange [0:100000] 
   plot "/tmp/maximum.dat" with dots title ""
END

# collatz sequence length histogram 
gnuplot <<END
   set terminal pdf 
   set output "histogram.pdf"
   set title "Collatz Sequence Length Histogram" 
   set xlabel "length"
   set ylabel "frequency" 
   plot "/tmp/histogram.dat" using 2:1 with impulse title ""
END
