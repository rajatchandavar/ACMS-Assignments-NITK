set font "Helvetica,20"
set title "Variation of Temperature with distance at Time = 9 s"
set xrange [0.01095:0.0114]
set yrange [58.3:59]
set xlabel "x (m)"
set ylabel "Temperature (degree C)"
plot "Plot2.txt" using 1:2 with lines title "Explicit scheme","Plot2.txt" using 1:3 with lines title "Implicit scheme","Plot2.txt" using 1:4 with lines title "Crank-Nicholson scheme"
