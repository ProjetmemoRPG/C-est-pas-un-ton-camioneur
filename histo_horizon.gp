set title "Diagramme à Barres Horizontales"
set ylabel "Distances (km)"
set xlabel "Noms"
set style histogram clustered
set style fill solid border -14
set boxwidth 0.5
set yrange [0:*]  
set xrange [0:10]  
set term png 

datafile = "resultats.txt"

plot datafile using 0:1:xtic(2) with boxes title "Distances"
