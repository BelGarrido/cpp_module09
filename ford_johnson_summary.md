# Ford-Johnson Algorithm — Study Summary

## Core idea

Ford-Johnson (also called **Merge-Insertion Sort**) sorts a list using the **minimum possible number of comparisons**.  
It does this by controlling very carefully the order in which elements are inserted into a sorted chain.

---

## The 3 phases

### Phase 1 — Pair and compare
- Group all elements into pairs
- Compare each pair → one **winner**, one **loser**
- Cost: `n/2` comparisons

### Phase 2 — Sort the winners
- Recursively sort all winners → this builds the **main chain**
- Each loser stays paired with its winner throughout

### Phase 3 — Insert the losers ← the hard part
- Insert losers into the main chain using **binary search**
- The **order** of insertion is what Jacobsthal controls
- Goal: minimize the total number of comparisons

---

## Why order matters — binary search cost

Binary search cost depends on the size of the search range:

| Search range size | Comparisons needed | Budget (insertions at this cost) |
|---|---|---|
| 1 | 1 | 1 element |
| 2 – 3 | 2 | 2 elements |
| 4 – 7 | 3 | 4 elements |
| 8 – 15 | 4 | 8 elements |

> The cost jumps every time the range crosses a power of 2.  
> Goal: insert as many elements as possible **before** the cost jumps.

---

## The key insight — reduced search range

- Loser `b` is always smaller than its paired winner `a` (known from phase 1)
- So you only binary search the portion of the chain **to the left of `a`** — not the full chain
- Inserting a **far loser** first does **not** grow the search range of closer losers
- So inside each group, insert **from the far end backwards** (e.g. `b3` before `b2`)

---

## Jacobsthal sequence

```
J(0) = 0
J(1) = 1
J(n) = J(n-1) + 2 * J(n-2)
```

The sequence:

```
0, 1, 1, 3, 5, 11, 21, 43, 85, 171...
```

The values used as **group start indexes** in Ford-Johnson:

```
1, 3, 5, 11, 21, 43...
```

This sequence is **fixed** — you precompute it and use it as a lookup table.

---

## Insertion groups

Each Jacobsthal value tells you **where a new group starts**.  
Inside each group, you insert **backwards** to the previous group end.

| Group | Insertion order |
|---|---|
| Group 1 | `b1` |
| Group 2 | `b3`, `b2` |
| Group 3 | `b5`, `b4` |
| Group 4 | `b11`, `b10`, `b9`, `b8`, `b7`, `b6` |
| Group 5 | `b21`, `b20`, ... , `b12` |

---

## One sentence summary

> Ford-Johnson inserts losers in a specific order — given by Jacobsthal — so that every binary search stays just below the next power of 2, minimizing the total number of comparisons.
