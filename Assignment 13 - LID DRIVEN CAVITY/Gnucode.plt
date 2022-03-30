set title "Convergence of u-velocity at geometrical centre of cavity w.r.t. time"
set xlabel "time (s)"
set ylabel "Velocity"
plot "Error.txt" using 1:2 with lines title "u-velocity"