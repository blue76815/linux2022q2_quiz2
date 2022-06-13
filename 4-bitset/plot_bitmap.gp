reset                                                                           
set xlabel 'bit-density'
set ylabel 'total time (ns)'
set title 'perfomance comparison'
set term png enhanced font 'Times_New_Roman, 10'
set output 'bitmap.png'
set xtics 1,4
set datafile separator ","
set key left

plot \
"data.csv" using 1:2 with linespoints linewidth 1 title "naive", \
"data.csv" using 1:3 with linespoints linewidth 1 title "improved"