Caltech CS2 Assignment 6: Multithreading and Concurrency

See [assignment6.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/concurrency/blob/master/assignment6.html)


In a file named README in the philosophers directory, describe in a few sentences the algorithm that is governing the philosophers' behavior and why this "solution" will always deadlock.

/**
 * the philosophers always picks up one fork first and never lets go of the fork until he is done eating, in which case it will just hog the fork without using it, and if the neighboring 
 * philosopher also does the same, then everyone hogs one fork and never lets go, which causes everyone to not be able to  eat and noone is willing to give up a fork.
 */
Determine the maximum number of philosophers that can sit at the table at any one time such that we can guarantee no deadlock will occur. In the same README file, give this number and describe how you arrived at it. This can be a logical argument — there is no need for a formal proof.
/**
 * the maximum number of philosophers, p, that can sit down given n forks is p = n-1. this means that for every p philosophers at the table, we will have p+1 forks, which, by pigeon hole 
 * principle, implies that at least one philosopher has 2 forks, who is then able to eat and then release the two forks for others to use. 
 */
This solution will only prevent deadlock when the system begins in an asymmetric state; the philosopher numbering requirement implicitly breaks the symmetry. In your README file, explain what would happen if we began this solution from a state where all philosophers begin with dirty, left forks.
/**
 * we reach a deadlock as if all the forks are dirty, then all the philosophers have eaten, and thus all the
 * philosophers are now trying to give up a fork. We persist in this state until one of the philosophers decides
 * to eat again, at which point, he will request a fork and get one readily available since all other philosophers
 * at which point the process will start normally. 
 */
Suppose that it it is more computationally demanding to trace some rays than others (for example, if most rays go into space while a few rays bounce off of a huge number of objects). Why might an approach similar to a producer-consumer queue provide a performance improvement over an approach that assigns an equal number of rays to each thread? Answer in a README file. Our reference answer is three sentences.
/**
 * an approach that assigns equal numbers of rays to each thread assumes that each ray takes the same amount of time, which is false. If one thread finishes early, then we have wasted 
 * computation.  Thus it is better to use a producer consumer queue to distribute work as it is being finished or consumed so that each thread is working full time and no thread is idle.
 */
