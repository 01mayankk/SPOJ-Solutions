# SPOJ - EKO (Eko)

## Topic

* Binary Search
* Binary Search on Answer

---

# Approach

## Intuition

We need to determine the **maximum possible height** at which the sawblade can be placed while still collecting **at least M units of wood**.

Suppose we choose a cutting height **H**.

* Every tree taller than **H** contributes `(treeHeight - H)` units of wood.
* Trees with height less than or equal to **H** contribute nothing.

If the collected wood is **greater than or equal to M**, then this cutting height is valid.

Our goal is to find the **highest valid cutting height**.

---

## Key Observation

The amount of collected wood changes monotonically with the cutting height.

* Increasing the cutting height decreases the collected wood.
* Decreasing the cutting height increases the collected wood.

This creates a monotonic search space.

```
Cut Height

0      ✔
1      ✔
2      ✔
...
15     ✔
16     ✖
17     ✖
18     ✖
```

There is a single transition from **Valid** to **Invalid**, making **Binary Search on Answer** the optimal approach.

---

# Algorithm

1. Set the search range:

   * **Low = 0**
   * **High = Maximum tree height**

2. While `low <= high`:

   * Calculate the middle cutting height.
   * Compute the total wood collected at this height.

3. If collected wood is at least **M**:

   * Store the current height as a possible answer.
   * Search the right half to maximize the cutting height.

4. Otherwise:

   * Search the left half because the blade is too high.

5. Return the last valid height.

---

# Dry Run

### Input

```
4 7

20 15 10 17
```

Required wood = **7**

Maximum tree height = **20**

### Iteration 1

```
Low = 0
High = 20

Mid = 10
```

Collected wood

```
20 -> 10
15 -> 5
10 -> 0
17 -> 7

Total = 22
```

Enough wood is collected.

```
Answer = 10
Move Right
```

---

### Iteration 2

```
Low = 11
High = 20

Mid = 15
```

Collected wood

```
20 -> 5
15 -> 0
10 -> 0
17 -> 2

Total = 7
```

Still valid.

```
Answer = 15
Move Right
```

---

### Iteration 3

```
Low = 16
High = 20

Mid = 18
```

Collected wood

```
20 -> 2
17 -> 0
15 -> 0
10 -> 0

Total = 2
```

Not enough wood.

```
Move Left
```

---

### Iteration 4

```
Low = 16
High = 17

Mid = 16
```

Collected wood

```
20 -> 4
17 -> 1

Total = 5
```

Still insufficient.

```
Move Left
```

Binary Search ends.

## Final Answer

```
15
```

---

# Correctness

At every iteration:

* If a cutting height is valid, every smaller height is also valid.
* If a cutting height is invalid, every larger height is also invalid.

Binary Search exploits this property to efficiently locate the **largest valid cutting height**.

---

# Complexity Analysis

### Time Complexity

Let:

* **N** = Number of trees
* **H** = Maximum tree height

Each Binary Search iteration scans all trees.

```
Time Complexity = O(N × log H)
```

---

### Space Complexity

```
O(1)
```

Only a few extra variables are used.

---

# Key Learning

* Binary Search is not limited to searching elements in a sorted array.
* Whenever the answer space exhibits a **monotonic property**, Binary Search on Answer can significantly reduce the search time.
* Always identify whether the problem asks for the **minimum valid** or the **maximum valid** answer before designing the Binary Search.
