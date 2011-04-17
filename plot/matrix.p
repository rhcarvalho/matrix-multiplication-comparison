# Gnuplot script file for plotting data in file "matrix.dat"
set   autoscale                        # scale axes automatically
unset log                              # remove any log-scaling
unset label                            # remove any previous labels
set xtic auto                          # set xtics automatically
set ytic auto                          # set ytics automatically
set title "Comparison of matrix multiplication"
set xlabel "N"
set ylabel "t(s)"
set key left top box
set xr [0:18000]
set yr [0.0:14.0]

f1(x) = a1*x**2 + b1*x + c1
fit f1(x) "matrix.dat" using 1:2 via a1, b1, c1

f2(x) = a2*x**2 + b2*x + c2
fit f2(x) "matrix.dat" using 1:3 via a2, b2, c2

f3(x) = a3*x**2 + b3*x + c3
fit f3(x) "matrix.dat" using 1:4 via a3, b3, c3

f4(x) = a4*x**2 + b4*x + c4
fit f4(x) "matrix.dat" using 1:5 via a4, b4, c4

plot "matrix.dat" using 1:2 title 'C i,j', \
     "matrix.dat" using 1:3 title 'C j,i', \
     "matrix.dat" using 1:4 title 'Fortran i,j', \
     "matrix.dat" using 1:5 title 'Fortran j,i', \
     a1*x**2 + b1*x + c1 notitle, \
     a2*x**2 + b2*x + c2 notitle, \
     a3*x**2 + b3*x + c3 notitle, \
     a4*x**2 + b4*x + c4 notitle
