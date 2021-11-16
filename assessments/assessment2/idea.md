# Lannister

## Problem Setup
We are given a set of $N + M$ house locations.
This set $S$ of locations is divided into $N$ *nobles* houses and $M$ *common* houses.
Each house location is represented by a data point lying on the $\mathbb{R}^2$ plane.

The objective of the problem is to find the coefficients of $L1$ and $L2$, two non-horizontal and orthogonal lines lying in the $\mathbb{R}^2$ plane satisfying and maximizing the following conditions:
- `Constraint 1:` $L1$ must seperate the two classes of houses, having the nobles houses on its left and the commons ones on its right.
- `Constraint 2:` The sum of every horizontal distance $x$ between any house and its intercepting point at same $y$ height on $L1$ must be less or equal than a given threshold $s$.
- `Constraint 3:` $L2$ position has to minimize the greatest distance $y$ between any house and its intercepting point at same $x$ coordinate on $L2$.

## Problem Modeling
We are seeking the line coefficients of $L1$ and $L2$. Because we know that they are orthognal, we can reduce the problem to that of finding the following correlated coefficients. We can even check that $m_1m_2 = -\frac{b}{a}\frac{a}{b} = -1$ which is indeed the orthogonality criterion.

$$ L1: ax + by + c_S $$
$$ L2: -bx + ay + c_W $$

### `Constraint 1:`
The first constraint is a linear separation problem given $L1$. This can be easily optimized with CGAL Linear Program solver. To be more explicit, we are optimizing $ax + by + c_S$ in such a way that the $N$ noble houses are on the left of the line and the $M$ common houses are on the right of it. This is translate to the following set of constraints:

$$ \forall (x_n, y_n): ax_n + by_n \leq c_S$$
$$ \forall (x_c, y_c): ax_c + by_c \geq c_S \Leftrightarrow -ax_c - by_c \leq - c_S$$

### `Constraint 2:`
More formally, we require $\sum_{i \in h} |x_i - x_{L_1} | \leq s$ where $h$ denote the set of all houses combined. The situation looks a bit tricky but we now that if the first constraint succeeded, all the noble houses are on $L1$'s left and common ones on its right. We can therefore define $|x_h - x_{L_1}|$ distance according to its class. We can further simplify the calculation knowing that $y_h = y_{L_1}$ namely with $x_{L_1} = \frac{by_{L_1} - c_S}{a} = \frac{by_{h} - c_S}{a} $ 

$$ d_n = x_{L_1} - x_n = \frac{by_{h} - c_S - ax_n}{a}$$
$$ d_c = x_c - x_{L_1} = \frac{ax_c - by_{h} + c_S}{a} $$ 

Now the problem is to formulate a CGAL constraint that enforces $\sum_{i \in h} d_i \leq s$. For that purpose, we can unfold the inequation and see that what comes out is a valid CGAL constraint because we know every coefficient:

$$
\begin{split}
\sum_{i \in h} d_i \\

& = \quad \sum_{i \in h_n} d_n \quad + \quad \sum_{i \in h_c} d_c \\

& = \quad \sum_{i \in h_n} \frac{by_{n} - c_S - ax_n}{a} \quad + \quad \sum_{i \in h_c} \frac{ax_c - by_{c} + c_S}{a} \\

& = \quad \sum_{i \in h_c} x_c -  \sum_{i \in h_n} x_n \quad + \quad \sum_{i \in h_n} \frac{b}{a}y_n  -  \sum_{i \in h_c} \frac{b}{a}y_c  \quad + \quad \frac{1}{a}c_S(M - N) \quad  \leq s \\

& \Leftrightarrow \\

& = \quad a\Big(\sum_{i \in h_c} x_c -  \sum_{i \in h_n} x_n \Big)\quad + \quad b \Big(\sum_{i \in h_n} y_n  -  \sum_{i \in h_c} y_c \Big) \quad + \quad c_S(M - N) \quad \leq as \\

& \Leftrightarrow \\

& = \quad a\Big(\sum_{i \in h_c} x_c -  \sum_{i \in h_n} x_n - s\Big)\quad + \quad b \Big(\sum_{i \in h_n} y_n  -  \sum_{i \in h_c} y_c \Big) \quad + \quad c_S(M - N) \quad \leq 0 \\
\end{split}
$$

### `Constraint 3:`
Below is the formal description of the problem we are facing with this last constraint optimization. Note that we are forced to introduce the absolute value as we have no clue of whether a data point is on the left or on the right of $L_2$.

$$\min_{} \big(\max_{i \in h} \quad | y_i - y_{L_2} | \; \big)$$

Because CGAL doesn't allow us to deal with a maximization probllem, we have to figure out a little trick. Here it is: we introduce a new variable $l$ which represents the maximal length we are searching for. The inner problem then simply reduces to $ \forall i \in h: | y_i - y_{L_2} | \leq l$. We can again unfold $| y_i - y_{L_2} |$ and see that it gives us $2(M+N)$ valid CGAL constraint to add to our LP solver:

$$
\begin{split}
| y_i - y_{L_2} | \leq l 
\quad \Leftrightarrow \quad 
-l \leq y_i - y_{L_2} \leq l
\quad \Leftrightarrow \quad 
-l \leq y_i + \frac{c_W - bx_i}{a} \leq l
\end{split}
$$

If we unfold only one of the 2 side of the inequation for the sake of completeness, we find a last and extra subtelty. Here is what happens:

$$
\begin{split}
y_i + \frac{c_W  - bx_i}{a} \leq l
\quad \Leftrightarrow \quad 
ay_i - bx_i + c_W   \leq al
\end{split}
$$

But notice that this is not anymore a linear problem. Indeed, because we have introduced $l$ as a new *variable* the product $al$ bring our equation to a quadratic form. To get around this concern, we can set $a = 1$. Notice that this simplify the equation of constraint 2. But it also enforce $L1$ and $L2$ not to be horizontal, which was required initially in the problem setup.

## Algorithm Design
To wrap up what we discussed above. We can finally implement a simple CPP routine using CGAL library. We therefore have $5$ variables ($a,b,c_S,c_W, l$) to give to the LP optimizer under the following final contraints:

$$
\begin{equation}
\forall (x_n, y_n): ax_n + by_n \leq c_S
\end{equation}
$$

$$
\begin{equation}
\forall (x_n, y_n): -ax_c - by_c \leq - c_S
\end{equation}
$$

$$
\begin{equation}
b \Big(\sum_{i \in h_n} y_n  -  \sum_{i \in h_c} y_c \Big)  + c_S(M - N) \leq s - \Big(\sum_{i \in h_c} x_c -  \sum_{i \in h_n} x_n \Big)
\end{equation}
$$

$$
\begin{equation}
\forall (x_n, y_n): - bx_n + c_W  -l \leq -y_n
\end{equation}
$$

$$
\begin{equation}
\forall (x_n, y_n): bx_n - c_W  -l \leq y_n
\end{equation}
$$

## Code submission

```CPP
int main() {
    
}
```