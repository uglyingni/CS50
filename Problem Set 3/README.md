# Problem Set 3

## Plurality
Program which runs a pluarlity election. Accepts a list of candidates as a command line argument. User then inputs how many voters there will be. Each voter will be promted to cast their vote and the program will determine the winner.

[Detail](https://cs50.harvard.edu/x/2023/psets/3/plurality/)

## Tideman
A program that runs a Tideman election. Accepts a list of candidates as command line arguments. User enters number of voters when prompted. Each voter casts their vote by ranking the candidates. The program will determine the winner using [The Tideman Method](#The-Tideman-ethod)

### The Tideman method
The Tideman voting method consists of three parts:

* Tally: Once all of the voters have indicated all of their preferences, determine, for each pair of candidates, who the preferred candidate is and by what margin they are preferred.
* Sort: Sort the pairs of candidates in decreasing order of strength of victory, where strength of victory is defined to be the number of voters who prefer the preferred candidate.
* Lock: Starting with the strongest pair, go through the pairs of candidates in order and “lock in” each pair to the candidate graph, so long as locking in that pair does not create a cycle in the graph.
* Once the graph is complete, the source of the graph (the one with no edges pointing towards it) is the winner.

[Detail](https://cs50.harvard.edu/x/2023/psets/3/tideman/)
