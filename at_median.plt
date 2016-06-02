set title "Relative Error versus Number of Estimators (Aggregated with Median)"
set key top right
set xlabel "Number of Estimators"
set ylabel "Relative Error"
set logscale x 2
set terminal png size 1000, 800
set output 'at_median.png'
plot "at_pcsa_median.tab" using 1:2 title "PCSA" with lines, \
 "at_ll_median.tab" using 1:2 title "Log Log" with lines, \
 "at_hll_median.tab" using 1:2 title "Hyper Log Log" with lines