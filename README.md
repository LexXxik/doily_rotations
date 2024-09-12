# doily_rotations
The purpose of the program is to categorize all 6-qubit doilies created by rotations of 2-qubit subdoilies. In particular this document expalins:
- what are doilies
- how are doilies categorized
- the purpose of this project
# Execution
The compiled version of the whole program can be executed in the terminal
```bash
./main.out
```
# What is doily?
Doily is a generalized quadrangle but for simplicity it is the following geometrical picture...

There are 15 points and 15 lines in each doily where each line has 3-points. Looking at the picture lines of the doily are connecting points on the outside of doily, through the center, and with curved lines around the center. Hence, important feature is that the line does not have to be straight!
## Points
There are 15 points in the doily and each point has 6 letters associated with it in the picture... Hence, we say that the picture shows a **6-qubit doily**: 6 letters = 6 qubits. Each point represents an **observable** in a 6-qubit quantum system. Each letter is one qubit.

Hence, in **2-qubit doily** each point has 2 letters. 

In the context of this project I distinguish between: outer, mid-edge, and inner vertices (points). They are highlighted in the picture...

## Lines
Each doily has 15 lines: 5 outer lines creating a hexagonal shape, 5 lines that pass through the center, and 5 curved lines. Recall that each line has 3 points and that the lines do not have to be straight!

Since each point is associated with one 6-qubit observable in the 6-qubit doily (picture...), there is also a rule about when observables lie on the same line. If they lie on the same line the observables commute - meaning that the measurements of the physical 6-qubit system, corresponding to these observables, can occur at the same time without interfering with results.

In addition, one can take a product of all observables lying on the same line to obtain $\pm 1$ up to a complex factor $i$. The **negative line** is a line whose product of observables is $-1$.

# Categorizing doilies
Each doily is unique by the observable it has and the type of lines it contains. However, doilies can be categorized further based on following metrics.

## Based on observable (vertices, points) types
A 6-qubit observable can be categorized into 6 categories: $A$, $B$, $C$, $D$, $E$, $F$. The category is determined by the number of Is in the observable: $A$ means 5 Is, $B$ means 4 Is, $C$ means 3 Is, etc. till $F$ which means 0 Is. 

## Based on configuration of negative lines
I alluded that negative lines are important. Indeed the doily can be categorized by the number of negative lines and configuration. In the table... the number is the number of negative lines and configurations $7$ and $8$ are distinguished between types $A$, and $B$. As two distinct doily' types with $7$ ($8$) lines exist.

If the number of lines in doily is odd, we say that doily is **contextual**. Otherwise it is non-contextual.

# The purpose
The goal of this project is to categorize all 6-qubit doilies that are created by the rotation of its three 2-qubit subdoilies. 

The project start with 4 unique 2-qubit doilies with different type of 2-qubit observables. To create 6-qubit doily from 2-qubit ones, it suffices to create a ``waffle``: stacking three 2-qubit doilies on top of each waffle.

Once such 6-qubit waffle is created, it remains to rotate each of the constituent 2-qubit subdoiles. It is like a combination lock!! After each rotation we check whether the doily is contextual. If it is the doily is categorized based on types of observables and configuration of negative lines. 