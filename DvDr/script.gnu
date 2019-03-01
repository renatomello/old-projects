reset
set term gif
set out 'fig.gif'
set xl 'r/R'
set yl 'v(r/R)/a'
set xr [0:20]
set yr [0:175]
plot 'va.dat' u 1:2 w lines lt 1
