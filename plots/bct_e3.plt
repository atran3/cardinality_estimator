set title "Relative Error versus Number of Buckets (Cardinality = 10e3)
set key top right
set xlabel "Number of Buckets"
set ylabel "Relative Error"
set logscale x 2
set terminal png size 1000,800
set output 'bct_e3.png'
plot "bct_pcsa_e3.tab" using 2:3 title "PCSA" with lines, \
 "bct_ll_e3.tab" using 2:3 title "Log Log" with lines, \
 "bct_hll_e3.tab" using 2:3 title "Hyper Log Log" with lines