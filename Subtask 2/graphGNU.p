# Gnuplot script file for plotting data from file "data.txt"

set autoscale
set title "Measure mean and standard deviation of latencies of the different implementations"
set xlabel "Matrix Size"
set ylabel "Time in milliseconds"

set boxwidth 0.25
plot 'Data.txt' using ($0-.05):2:3:xtic(1) with boxerrorbars title col, \
     '' using ($0+0.25):4:5 with boxerrorbars title col, \
	'' using ($0+0.55):6:7 with boxerrorbars title col, \
'' using ($0+0.85):8:9 with boxerrorbars title col

