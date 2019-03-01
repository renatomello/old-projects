reset
set term gif
set out 'img4.gif'
set grid
set xr [0:1.5]
set yr [-10:0]
set xl 'log(r/rc)'
set yl 'log(p(r)/p0)'
plot 'arq4.dat' u 1:2,'arq5.dat' u 1:2
