
naive_sum problem
because the sum variable float sum is limited in precision, everytime we add (1./((float) HUGE)), it is infact not represented and is lost as the resulting sum is rounded down.
