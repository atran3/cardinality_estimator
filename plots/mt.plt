set title "Relative Error vs. Memory Used for Different Cardinalities"
set key top right
set grid
set xlabel "Memory Used (Bytes)
set ylabel "Relative Error
set logscale x 2
set terminal png size 1000, 800
set output 'mt.png'
plot "mt_pcsa_e4.tab" using 1:2 title "PCSA (10e4)" with lines, \
     "mt_pcsa_e7.tab" using 1:2 title "PCSA (10e7)" with lines, \
     "mt_ll_e4.tab" using 1:2 title "Log Log (10e4)" with lines, \
     "mt_ll_e7.tab" using 1:2 title "Log Log (10e7)" with lines, \
     "mt_hll_e4.tab" using 1:2 title "Hyper Log Log (10e4)" with lines, \
     "mt_hll_e7.tab" using 1:2 title "Hyper Log Log (10e7)" with lines, \