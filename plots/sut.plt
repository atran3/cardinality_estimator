set title "Relative Error vs. Stream Size/Universe Size"
set key top right
set grid
set xlabel "(Stream Size)/(Universe Size)"
set ylabel "Relative Error"
set logscale xy
set terminal png size 1000, 800
set output 'sut.png'
plot   "sut_pcsa.tab" using 1:2 title "PCSA" with lines, \
   "sut_ll.tab" using 1:2 title "Log Log" with lines, \
   "sut_hll.tab" using 1:2 title "Hyper Log Log" with lines
