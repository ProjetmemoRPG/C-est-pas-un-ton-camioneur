set term png
set terminal pngcairo enhanced font "arial,12" size 1000,1000

set output 'histogramme.png'
set style data lines
set style fill transparent solid 0.35 noborder
set title 'Graf min-max des trajet avec le plus grand ecart-type'
set ylabel "Distance (Km)" offset 0,0
set xlabel 'Route ID'
set xtics rotate 90

plot 'CPS.txt' using 4:xtic(1) with lines, '' using 3:xtic(1) with line, '' using 2:xtic(1) with line
