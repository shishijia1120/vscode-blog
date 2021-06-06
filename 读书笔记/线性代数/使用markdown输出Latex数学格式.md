## 使用Markdown输出Latex数学格式
### 基本
分数：$\frac{1}{3}$
指数：$3^2$
n次方根输出：$\sqrt{3x-1}+\sqrt[5]{2y^5-4}$
求和输出：$\sum_{n=1}^\infty k$
极限输出：$\lim\limits_{x \to \infty} \exp(-x)=0$
阶乘输出：$$\frac{n!}{k!(n-k)!}=\binom{n}{k}$$

### 矩阵
矩阵输出：使用\begin{bmatrix}和\end{bmatrix}围住即可输出矩阵，矩阵之间用\$来空格，用\\来换行。

$$
s=\begin{bmatrix}
1 & 2 & 3 \\
4 & 5 & 6 \\
\end{bmatrix}
$$


$$
s=\begin{bmatrix}
    A & B & \cdots & C \\
    A & B& \cdots &C \\
    \vdots & \vdots & \ddots & \vdots \\
    G & H & \cdots & I \\
\end{bmatrix}
$$


$$
\begin{gathered}
\begin{matrix}
 0 & 1 \\
 1 & 0 \\   
\end{matrix}  
\quad
\begin{bmatrix}
   0 & -i \\
   i & 0 \\ 
\end{bmatrix}
\quad
\begin{pmatrix}
   0 & -i \\
   i & 0 \\ 
\end{pmatrix}
\quad
\begin{Bmatrix}
   0 & -i \\
   i & 0 \\ 
\end{Bmatrix}
\quad
\begin{vmatrix}
   0 & -i \\
   i & 0 \\ 
\end{vmatrix}
\quad
\begin{Vmatrix}
   0 & -i \\
   i & 0 \\ 
\end{Vmatrix}
\quad
\end{gathered}
$$

### 分段函数
分段函数的编写：分段函数是非常复杂的，这时候会用到LaTex的cases语法，用\begin{cases}和\end{cases}围住即可，中间则用\\来分段，具体我们来看下面的例子。

$$
x(m,n)=
\begin{cases}
 x(n),\\
 x(n-1),\\
 x(n+1),\\
\end{cases}
$$
