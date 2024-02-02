set term png
set terminal pngcairo enhanced font "arial,12" size 1500,1000

set output 'histogramme.png'
set style data line
set style fill transparent solid 0.35 noborder
set title 'Graf min-max des trajet avec le plus grand ecart-type'
set ylabel "Distance (Km)" offset 0,0
set xlabel 'Route ID'
set xtics rotate 90

plot 'CPS.txt' using 2:xtic(4) with filledcurves x1 lt rgb "#00FF00" notitle, '' using 3:xtic(4) with line ti 'moyenne' lt rgb "#FF00FF", '' using 2:xtic(4) with line ti 'max' lt rgb "#0000FF", '' using 1:xtic(4) with filledcurves x1 lt rgb "#FFFFFF" notitle,  '' using 1:xtic(4) with filledcurves x1 lt rgb "#FFFFFF" notitle, '' using 1:xtic(4) with filledcurves x1 lt rgb "#FFFFFF" notitle,'' using 1:xtic(4) with filledcurves x1 lt rgb "#FFFFFF" notitle,'' using 1:xtic(4) with filledcurves x1 lt rgb "#FFFFFF" notitle,'' using 1:xtic(4) with filledcurves x1 lt rgb "#FFFFFF" notitle,'' using 1:xtic(4) with filledcurves x1 lt rgb "#FFFFFF" notitle,'' using 1:xtic(4) with filledcurves x1 lt rgb "#FFFFFF" notitle,  '' using 1:xtic(4) with lines ti 'min' lt rgb "#FF0000"
