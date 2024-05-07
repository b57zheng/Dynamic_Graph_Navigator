Class UMLs:

![image](https://github.com/b57zheng/Graphs_for_Navigation/assets/98293562/1f38f3b3-724a-44b3-b3df-a4f320a22fab)

Runtime Analysis: Dijkstra’s algorithm 
- The algorithm initializes the first note in the path array with weight 0. This operation is O(1).
- In each iteration, the algorithm extracts the node with min weight from the path array. In the worst case, every node is extracted once. Hence, the operation is O(|V|).
- For each min weight path’s end node, expand all edges. In the worst case, this operation repeats for every edge in the graph. Hence, the operation is O(|E|).
- Total runtime for extraction is O(|log(V)|)
- Total runtime for edge expansion is O(|E))
- Hence, the total runtime is O(|E|log|V|).

