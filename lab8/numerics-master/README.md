Caltech CS2 Assignment 8: Numerics

See [assignment8.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/numerics/blob/master/assignment8.html)


naive_sum problem
because the sum variable float sum is limited in precision, every time we add (1./((float) HUGE)), it is in fact not represented and is lost as the resulting sum is rounded down.



DFT
The Fourier transform of a sin function is smooth where as the discrete Fourier transform would have more jagged. As the function becomes more complicated, the resulting function in DTF becomes more smooth.