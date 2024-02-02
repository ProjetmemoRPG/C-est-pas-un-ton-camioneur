set term png
set terminal pngcairo enhanced font "arial,12" size 1000,1000
set output 'histogramme.png'
set title ' ' offset -15,-15 rotate by 55
set ylabel "Top 10 Conducteurs par Nombre de Trajets \n\n\n\nNombre de Trajets}" offset -3,-2
set xlabel 'Conducteurs'
set style data histogram
set style fill solid
set boxwidth 1.5
set xlabel rotate by 180
set xtics offset 0,-6
set xlabel offset 0,-5
set xtics rotate by 90
set ytics rotate by 90
set bmargin at screen 0.2
set lmargin at screen 0.2
set yrange [0:*]

plot 'CPS.txt' using 1:xtic(sprintf("%s\n%s", strcol(2), strcol(3))) title ''
