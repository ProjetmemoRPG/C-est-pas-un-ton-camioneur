set term png
set terminal pngcairo enhanced font "arial,12" size 1000,1000
set output 'histogramme.png'
set title ' Trajet les plus long'
set ylabel "Distance" offset 0,0
set xlabel 'Trajet ID'
set style data histogram
set style fill solid
set boxwidth 1.5
set xlabel rotate by 0
set xtics offset 0,0
set xlabel offset 0,0
set xtics rotate by 0
set ytics rotate by 0
set tmargin at screen 0.9
set lmargin at screen 0.1
set yrange [0:*]

plot 'CPS.txt' using 1:xtic(2) title ''
