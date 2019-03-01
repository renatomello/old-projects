reset
set term gif
set out 'img1.gif'
set grid
set xl 'r/rc'
set yl 'v(r)/a'
set xr [0.2:5]
set yr [0:4]
plot 'arq1.dat' u 1:2
