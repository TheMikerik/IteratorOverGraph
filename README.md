# Iterator Over Graph
This code starts [iterating](https://en.wikipedia.org/wiki/Iterator) over a graph from the smallest number in each component of it.

## How To Use It
There is no need to select graphs manually. Currently, it automatically loads 7 graphs from Graphs folder.
So just type
```bash
g++ ./main.cpp -o iterator -Wall -Wextra -g -fsanitize=address -lm -lstdc++
```
Then just run it by
```bash
./iterator
```
## Graph Visualization
I also added graph visualization for each graph thats tested in this program. You can find it in the Graphs Visual folder.