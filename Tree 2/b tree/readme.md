# B-Tree

B-Tree is a special type of self-balancing search tree in which each node can contain more than one key and more than two children.

![b-tree](./b-tree.jpg)

## Properties

- All leaves have the same depth (all leaves on the same level like in a perfect tree)

In a B-Tree, every node has a lower and upper bound on the number of keys they can contains. Let $t \geq 2$ be the minimum degree of the tree. We have the following properties :

1. Lower bound (except root) :
    - Every node has at least $t-1$ keys
    - Every node has at least $t$ children
2. Upper bound :
    - Every node has at most $2t-1$ keys
    - Every node has at most $2t$ children

Thus, a node with $n$ keys has $n+1$ children.
