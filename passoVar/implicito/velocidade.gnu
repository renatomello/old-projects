reset
set grid
set xr [0.2:5]
set yr [0:4]
set xl 'r/rc'
set yl 'v(r)/a'
set term gif
set out 'velocidade.gif'
plot 'arq1.dat' u 1:2 w lines lt 1
