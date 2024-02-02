set term png
C = "#99ffff"; Cpp = "#4671d5"
set terminal pngcairo enhanced font "arial,12" size 1000,1000
set output 'histogramme.png'
set title 'Ville les plus traverser'
set ylabel "Nombre de passage" offset -3,-2
set xlabel 'Ville'
set style data histogram
set style histogram cluster gap 1
set style fill solid
set boxwidth 1
set xlabel rotate by 0
set xtics offset 0,-6
set xlabel offset 0,-5
set xtics rotate by 75
set ytics rotate by 0
set bmargin at screen 0.2
set lmargin at screen 0.2

plot 'CPS.txt' using 2:xtic(1) ti 'Traversé', '' u 3 ti 'Depart'
