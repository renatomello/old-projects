reset
set term gif
set out 'img3.gif'
set grid
set xl 'r/rc'
set yl 'e(r)/e(rc)'
plot 'arq3.dat' u 1:2
