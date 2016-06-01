set key top right
set xlabel "True Cardinality"
set ylabel "Number of Buckets"
set zlabel "Relative Error"
set logscale x
set logscale y 2
set terminal png size 1000,800
set output 'bct.png'
splot "bct_ll.tab" using 1:2:3 title "asdf" with points pt 6