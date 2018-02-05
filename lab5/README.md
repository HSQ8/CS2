Caltech CS2 Assignment 5: Graphs

See [assignment5.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/graphs/blob/master/assignment5.html)


Here's a code snippet. Is there anything wrong with the depth-first search algorithm implemented in dfs()? If so, how would you fix it? If not, how do you know?

 Quite frankly, we are given too little information about what kinds of edges this graph should have. We don't keep a list of visited nodes, so theres a potential that we get stuck depth first searching a cycle, in which case we would just loop forever since we don't keep a list of visited nodes.



 