# Sharp determination of small cases for the Erdős, Pach, Pollack and Tuza problem

This repository contains code related to the paper "Sharp determination of small cases for the Erdős, Pach, Pollack and Tuza problem}". This code implements the algorithm discussed in the appendix to determine $c(\delta)$ (for $\delta=6$) and $c'(\delta)$ (for $\delta \in \{7,8,16\}$). Please note that the total time for the paper amounts to 1 CPU-year, so running these programs on a Desktop computer for a few hours will only show a tiny fraction of its output. Below we give some illustrative examples.

The code "omega3Delta6.cpp" can be used to compute $c(6)$, whereas the other programs can be used to compute $c'(7),c'(8)$ and $c'(16)$ (the latter additionally makes the assumptions mentioned the paper.

## CODE


### omega3Delta6.cpp

The program can be compiled by executing:
```bash
g++ -g -std=c++11 -O3 omega3Delta6.cpp -o omega3Delta6Executable
```

The program expects as input two integers $a$ and $b$, where $0 \leq a \leq b-1$. Roughly speaking, the program splits it work into $b$ chunks and the integer $a$ indicates which chunk out of the $b$ chunks should be executed (this allows the program to be easily parallelized on a supercomputer). The program will iterate over all repetition lengths and every time it finds a better repeatable graph, it will output the ratio between repetition length and the relevant order, together with the repeatable graph that achieves this. The repeatable graph is output in a layer by layer fashion.

For example, if we execute the following
```bash
./omega3Delta6Executable 5 53
```

The program will output after a while:
```bash
dist and nbVertices:  14 37
Current graph: 
n=4
Edges follow:
0 1
0 3
1 0
1 2
2 1
2 3
3 2
3 0
Edges between current graph and previous graph: 
0 0
0 1
0 2
0 3
Current graph: 
n=1
Edges follow:
Edges between current graph and previous graph: 
0 0
1 0
Current graph: 
n=2
Edges follow:
Edges between current graph and previous graph: 
0 0
0 1
1 0
1 1
2 0
2 1
3 0
3 1
4 0
4 1
Current graph: 
n=5
Edges follow:
0 2
0 3
0 4
1 2
1 3
1 4
2 0
2 1
3 0
3 1
4 0
4 1
Edges between current graph and previous graph: 
0 0
0 1
0 2
0 3
0 4
1 0
1 1
1 2
1 3
1 4
Current graph: 
n=2
Edges follow:
Edges between current graph and previous graph: 
0 0
0 1
Current graph: 
n=1
Edges follow:
Edges between current graph and previous graph: 
0 0
1 0
2 0
3 0
Current graph: 
n=4
Edges follow:
0 1
0 3
1 0
1 2
2 1
2 3
3 2
3 0
Edges between current graph and previous graph: 
0 0
0 1
0 2
0 3
1 0
1 1
1 2
1 3
2 0
2 1
2 2
2 3
Current graph: 
n=3
Edges follow:
Edges between current graph and previous graph: 
0 0
0 1
0 2
1 0
1 1
1 2
Current graph: 
n=2
Edges follow:
0 1
1 0
Edges between current graph and previous graph: 
0 0
0 1
1 0
1 1
Current graph: 
n=2
Edges follow:
Edges between current graph and previous graph: 
0 0
0 1
1 0
1 1
2 0
2 1
3 0
3 1
Current graph: 
n=4
Edges follow:
0 1
0 3
1 0
1 2
2 1
2 3
3 2
3 0
Edges between current graph and previous graph: 
0 0
0 1
0 2
0 3
1 0
1 1
1 2
1 3
Current graph: 
n=2
Edges follow:
Edges between current graph and previous graph: 
0 0
0 1
1 0
1 1
Current graph: 
n=2
Edges follow:
0 1
1 0
Edges between current graph and previous graph: 
0 0
0 1
1 0
1 1
2 0
2 1
Current graph: 
n=3
Edges follow:
Edges between current graph and previous graph: 
0 0
0 1
0 2
1 0
1 1
1 2
2 0
2 1
2 2
3 0
3 1
3 2
Current graph: 
n=4
Edges follow:
0 1
0 3
1 0
1 2
2 1
2 3
3 2
3 0
Edges between current graph and previous graph: 
0 0
0 1
0 2
0 3
Current graph: 
n=1
Edges follow:
Edges between current graph and previous graph: 
```

This indicates that the program found a repeatable graph, resulting in the ratio $14/37$ and it outputs the graph that is also described in the paper.

### chi3Delta7.cpp, chi3Delta8.cpp and chi3Delta16Only2ColorsAssumption.cpp

The program(s) can be compiled by executing:
```bash
g++ -g -std=c++11 -O3 chi3Delta7.cpp -o chi3Delta7Executable
```

The program(s) again expect as input two parameters $a$ and $b$, only this time $c'(\delta)$ will be calculated instead of $c(\delta)$.
