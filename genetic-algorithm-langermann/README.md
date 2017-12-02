# Genetic Algorithm
[Langerman's Fitness Function](https://www.cs.cmu.edu/afs/cs/project/jair/pub/volume24/ortizboyer05a-html/node6.html)

A Genetic Algorithm can be described using the pseudocode below.
```Initialize a population of S individuals;
 Evaluate the fitness of every individual;
 While NOT(termination_criteria()) {
     Form the parent pool using tournament selection;
      While (size of offspring pool < 10S) {
            Pick 2 parents at random;
            Crossover the 2 parents to produce 2 offspring;
            Mutate the 2 offspring to produce 2 mutated offspring;
            Evaluate the fitness of the 2 mutated offspring;
            Add the mutated offspring to the offspring pool;
      }
  Form a joint pool from the union of the parent pool and the offspring pool;
  Sort the joint pool by fitness;
  The next population = the fittest S individuals in the joint pool;
  }```