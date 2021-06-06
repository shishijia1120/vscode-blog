## 第三章 n维向量

### 二、基本内容与重要结论

#### 基础知识

向量加法：$\alpha+ \beta$
数乘向量：$k\alpha$
向量内积：$(\alpha,\beta)=\alpha^T\beta=\beta^T\alpha=a_1b_1+a_2b_2+\cdots+a_nb_n.$

**定义3.1** 设$\alpha_1,\alpha_2,\cdots,\alpha_s$是n维向量，$k_1,k_2,\cdots,k_s$是一组实数，称
$$k_1\alpha_1+k_2\alpha_2+\cdots+k_s\alpha_s,$$

是$a_1,a_2,\cdots,a_s$的线性组合.


**定义3.2** 对n维向量$\alpha_1,\alpha_2,\cdots,\alpha_s和\beta$，若存在实数$k_1,k_2,\cdots,k_s，$使得
$$k_1\alpha_1+k_2\alpha_2+\cdots+k_s\alpha_s=\beta,$$

则称$\beta是a_1,a_2,\cdots,a_s$的线性组合，或者说$\beta可由a_1,a_2,\cdots,a_s$线性表出(示).


**定义3.3** 对n维向量$\alpha_1,\alpha_2,\cdots,\alpha_s，$如果存在不全为零的数使得
$$k_1\alpha_1+k_2\alpha_2+\cdots+k_s\alpha_s=0,$$

则称向量组$a_1,a_2,\cdots,a_s$线性相关.否则，称向量组$a_1,a_2,\cdots,a_s$线性无关.

**定义3.4**设有两个n维向量组 (I)$\alpha_1,\alpha_2,\cdots,\alpha_s;$ ($\Pi$)$\beta_1,\beta_2,\cdots,\beta_t;$ 
如果(I)中每个向量$\alpha_i(i=1,2,\cdots,s)都可由(\Pi)中的向量\beta_1,\beta_2,\cdots,\beta_t$线性表出，则称向量组(I)可由向量组$(\Pi)$线性表出.

如果(I)、$(\Pi)$这两个向量组都可以互相线性表出，则称这两个向量组等价.



**定义3.5** 在向量组$a_1,a_2,\cdots,a_s$中，若存在r个向量$a_{i_1},a_{i_r},\cdots,a_{i_r}$线性无关，再加进任一个向量$a_j(j=1,2,\cdots,s)，$向量组$a_{i_1},a_{i_r},\cdots,a_{i_r},a_j$就线性相关，则称$a_{i_1},a_{i_r},\cdots,a_{i_r}$是向量组$a_{i_1},a_{i_r},\cdots,a_{i_r}$的一个极大线性无关组。

**定义3.6** 向量组$a_1,a_2,\cdots,a_s$的极大线性无关组中所含向量的个数r称为这个向量组的秩.

----

#### 重要定理

**定理3.1** 向量$\beta$ 可由向量组$a_1,a_2,\cdots,a_s$线性表出
$$\Leftrightarrow非齐次线性方程组\begin{bmatrix}
    a_1,a_2,\cdots,a_s
\end{bmatrix} \begin{bmatrix}
    x_1 \\ x_2 \\ \vdots \\ x_s
\end{bmatrix}=\beta 有解$$

$$\Leftrightarrow 秩r\begin{bmatrix}
    a_1,a_2，\cdots,a_s
\end{bmatrix}=r\begin{bmatrix}
    a_1,a_2，\cdots,a_s,\beta
\end{bmatrix}$$


**定理3.2** 向量组$a_1,a_2，\cdots,a_s$线性相关
$$\qquad \qquad \Leftrightarrow 齐次线性方程组\begin{bmatrix}
    a_1,a_2,\cdots,a_s
\end{bmatrix} \begin{bmatrix}
    x_1 \\ x_2 \\ \vdots \\ x_s
\end{bmatrix}=0 有非零解$$

$$\Leftrightarrow 向量组r(a_1,a_2,\cdots,a_s)<s.$$

**推论1** n个n维向量$a_1,a_2,\cdots,a_n$线性相关的充分必要条件是行列式
$$|a_1,a_2,\cdots,a_n|=0.$$

**推论2** n+1个n维向量一定线性相关.

**推论3** 任何部分组$a_1,a_2,\cdots,a_r$相关 $\Rightarrow$整体组$a_1,a_2,\cdots,a_s$相关，
整体组$a_1,a_2,\cdots,a_r,\cdots,a_s$无关 $\Rightarrow$任何部分组$a_1,a_2,\cdots,a_r$无关，反之都不成立.


**推论4**$a_1,a_2,\cdots,a_m$线性无关 $\Rightarrow$延伸组$\tilde{a_1},\tilde{a_2},\cdots,\tilde{a_m}$线性无关;

$\tilde{a_1},\tilde{a_2},\cdots,\tilde{a_m}$线性相关 $\Rightarrow$缩短组$a_1,a_2,\cdots,a_m$线性相关，反之均不成立.

**定理3.3** 如果$a_1,a_2,\cdots,a_s(s\geq 2)$线性相关，则其中必有一个向量可用其余的向量线性表出；反之，若有一个向量可用其余的s-1个向量线性表出，则这s个向量必线性相关.

**定理3.4** 如果$a_1,a_2,\cdots,a_s$线性无关，$a_1,a_2,\cdots,a_s,\beta$线性相关，则$\beta$可由$a_1,a_2,\cdots,a_s$线性表出，且表示法唯一.

**定理3.5**如果向量组$a_1,a_2,\cdots,a_s$可由向量组$\beta_1,\beta_2,\cdots,\beta_t$线性表出。而且s>t，那么$a_1,a_2,\cdots,a_s$线性相关.即如果多数向量能用少数向量线性表出，那么多数向量一定线性相关.
**推论** 如果$a_1,a_2,\cdots,a_s$线性无关，且它由$\beta_1,\beta_2,\cdots,\beta_t$线性表出，则$s \leq t.$

**定理3.6**设$a_1,a_2,\cdots,a_s$可由$\beta_1,\beta_2,\cdots,\beta_t$线性表出，则$r(a_1,a_2,\cdots,a_s) \leq r(\beta_1,\beta_2,\cdots,\beta_t).$

**推论**如果是两个等价的向量组，则r(I)=r($\Pi$).

**定理3.7**如果r(A)=r,则A中有r个线性无关的列向量，而其他列向量都是这r个线性无关向量的线性组合，也就是r(A)=A的列秩.

----
### 三、典型例题分析选讲

#### 1 线性相关

**例子3.5** $\quad已知n维向量\alpha_1,\alpha_2,\alpha_3线性无关，证明3\alpha_1+2\alpha_2,\alpha_2-\alpha_3，4\alpha_3-5\alpha_1线性无关.$

【证】(用定义重组)



【证法二】(用秩)

$$\begin{bmatrix}
    \beta_1,\beta_2,\beta_3
\end{bmatrix}=\begin{bmatrix}
    \alpha_1,\alpha_2,\alpha_3
\end{bmatrix} \begin{bmatrix}
    3 \quad  0 \quad -5 \\
    2 \qquad 1 \quad 0 \\
    0 \quad -1 \quad 4 \\
\end{bmatrix}$$



----

**例3.10** $\quad 已知n维向量\alpha_1,\alpha_2,\alpha_3线性无关，若\beta_1,\beta_2,\beta_3可用\alpha_1,\alpha_2,\alpha_3线性表出，设$

$$\begin{bmatrix}
    \beta_1,\beta_2,\beta_3
\end{bmatrix}=\begin{bmatrix}
    \alpha_1,\alpha_2,\alpha_3
\end{bmatrix}C,$$

$证明\beta_1,\beta_2,\beta_3线性无关的充分必要条件是|C| \neq 0.$

【证】 

----
**例3.11** $已知向量组\alpha_1,\alpha_2,\alpha_3线性无关，向量组\alpha_1+a\alpha_2，\alpha_1+2\alpha_2+\alpha_3，a\alpha_1-\alpha_3线性相关，则a=$__


----

**例3.13** (定理3.5特例)证明: 如果$\beta_1,\beta_2,\beta_3可由\alpha_1,\alpha_2,\alpha_3线性表出，则\beta_1,\beta_2,\beta_3线性相关.$

【证】




----


#### 2 线性表出
**例3.14** $已知\alpha_1=\begin{bmatrix}
    1,2,-3,1
\end{bmatrix}^T,\alpha_2=\begin{bmatrix}
    5,-5,a,11
\end{bmatrix}^T,\alpha_3=\begin{bmatrix}
    1,-3,6,3
\end{bmatrix}^T,\beta=\begin{bmatrix}
    2,-1,3,b
\end{bmatrix}^T,$
$\qquad 试问当a,b取何值是\beta可以由\alpha_1,\alpha_2,\alpha_3线性表示，并写出其表达式.$


----

**例3.15** $确定常数a使向量组\alpha_1=(1,1,a)^T,\alpha_2=(1,a,1)^T,\alpha_3=(a,1,1)^可由向量组\beta_1=(1,1,a)^T$
$\qquad\beta_2=(-2,a,4)^T,\beta_3=(-2,a,a)^T线性表示，但由向量组\beta_1,\beta_2,\beta_3不能由向量组\alpha_1,\alpha_2,\alpha_3线性表示.$

----
**例3.16** $设有向量组(I):\alpha_1=\begin{bmatrix}
    1,0,2
\end{bmatrix}^T,\alpha_2=\begin{bmatrix}
    1,1,3
\end{bmatrix}^T,\alpha_3=\begin{bmatrix}
    1,-1,a+2
\end{bmatrix}^T$
$\qquad (\Pi):\beta_1=\begin{bmatrix}
    1,2,a+3
\end{bmatrix}^T,\beta_2=\begin{bmatrix}
    2,1,a+6
\end{bmatrix}^T,\beta_3=\begin{bmatrix}
    2,1,a+4
\end{bmatrix}^T$
$试问：当a为何值时，向量组(I)与(\Pi)等价?当a为何值时，向量组(I)与(\Pi)不等价?$


----
**例3.17** $设向量组\alpha_1,\alpha_2,\alpha_3线性相关，向量组\alpha_2,\alpha_3,\alpha_4线性无关，问$

$\quad$ (1) $\alpha_1能否由\alpha_2,\alpha_3线性表出？证明你的结论.$ 
$\quad$ (2) $\alpha_4能否由\alpha_1,\alpha_2,\alpha_3线性表出？证明你的结论.$ 



----


#### 3 向量组的秩

#### 4 矩阵的秩

#### 5 Schmidt正交化
。。。。。。








#### 6 向量空间 *

**定义3.7** 全体n维向量空间连同向量的加法和乘法运算合称为n维向量空间.

**定义3.8** 设W是n维向量的非空集合，如果满足
$\quad$(1) $\forall \alpha,\beta \in W,$必要$\alpha+\beta \in W,$
$\quad$(2) $\forall \alpha \in W$及任一实数k，必有$k\alpha \in W,$
则称$W$是n维向量空间的子空间.

**定义3.9** 如果向量空间V中的m个向量$a_1,a_2,\cdots,a_m$满足
$\quad$(1) $a_1,a_2,\cdots,a_m$线性无关；
$\quad$(2) V中任意向量$\beta$均可由向量组$a_1,a_2,\cdots,a_m$线性表出，即
$$x_1a_1+x_2a_2+\cdots+x_ma_m=\beta,$$

则称$a_1,a_2,\cdots,a_m$为向量空间V的一个基底(或基).基中所含向量的个数m称为向量空间V的维数，记作dimV=m，并称V是m维向量空间.向量$\beta$的表示系数$x_1,x_2,\cdots,x_m$称为向量$\beta$在基底$a_1,a_2,\cdots,a_m$下的坐标.

**定义3.10**设$e_1,e_2,\cdot,e_n$是向量空间的一组基，如果它们满足
$$(e_i,e_j)=\begin{cases}
    1, i=j, \\
    0, i \neq j,
\end{cases}$$

则称$e_1,e_2,\cdot,e_n$为规范正交基.


设齐次方程组Ax=0的解向量的集合为W，由解的性质知：
若$\alpha,\beta$是Ax=0的解，则$\alpha+\beta，k\alpha$仍是Ax=0的解，所以W是n维向量空间的子空间，通常称为解空间.


例如，A=$$\begin{bmatrix}
    1 \quad 1 \quad  0 \quad -1 \\
    0 \quad 1 \quad  0 \quad  1  \\
\end{bmatrix}$$，则齐次方程组Ax=0的基础解系

$$\eta_1=\begin{bmatrix}
    0,0,1,0
\end{bmatrix}^T,\eta_2=\begin{bmatrix}
    2,-1,0,1
\end{bmatrix}^T$$
是解空间的基，解空间的维数n-r(A)=4-2=2.


**定义3.11** 在n维向量空间给定两组基
(1) $a_1,a_2,\cdots,a_n$ (2) $\beta_1,\beta_2,\cdots,\beta_n$

若
$$\beta_1=c_{11}a_1+c_{21}a_2+\cdots+c_{n1}a_n,$$

$$\beta_2=c_{12}a_1+c_{22}a_2+\cdots+c_{n2}a_n,$$

$$\cdots$$

$$\beta_n=c_{1n}a_1+c_{2n}a_2+\cdots+c_{nn}a_n,$$

即 $\begin{bmatrix}
    \beta_1,\beta_2,\cdots,\beta_n
\end{bmatrix}$=$\begin{bmatrix}
    a_1,a_2,\cdots,a_{n-1}
\end{bmatrix}C,$

其中$C=\begin{bmatrix}
    c_{11} \quad c_{12} \quad \cdots \quad c_{1n} \\
    c_{21} \quad c_{22} \quad \cdots \quad c_{2n} \\
    \vdots \qquad \vdots \qquad \vdots \\
    c_{n1} \quad c_{n2} \quad \cdots \quad c_{nn} \\
\end{bmatrix},$
则称矩阵C为由基$a_1,a_2,\cdots,a_n$到基$\beta_1,\beta_2,\cdots,\beta_n$的过渡矩阵.

**定理3.8** 如果$a_1,a_2,\cdots,a_n$与$\beta_1,\beta_2,\cdots,\beta_n$的过渡矩阵.

**定理3.9** 如果向量r在基底$a_1,a_2,\cdots,a_n$的坐标为$x_1,x_2,\cdots,x_n$，向量r在基底$\beta_1,\beta_2,\cdots,\beta_n$的坐标为$y_1,y_2,\cdots,y_n$，则坐标变换公式为
$$\begin{bmatrix}
    x_1 \\ x_2 \\ \vdots \\ x_n
\end{bmatrix}=C \begin{bmatrix}
    y_1 \\ y_2 \\ \vdots \\ y_n
\end{bmatrix} 或 x=Cy,$$

其中n阶矩阵C是由基底$a_1,a_2,\cdots,a_n$到基底$\beta_1,\beta_2,\cdots,\beta_n$的过渡矩阵.

**定理3.10** 若n维向量$a_1,a_2,\cdots,a_s$非零且两两正交，则$a_1,a_2,\cdots,a_s$线性无关.

**定理3.11** 若$e_1,e_2,\cdots,e_n$是规范正交基，设
$$\begin{bmatrix}
    \varepsilon_1,\varepsilon_2,\cdots,\varepsilon_n
\end{bmatrix}=\begin{bmatrix}
    e_1,e_2,\cdots,e_n
\end{bmatrix}C,$$

则$\varepsilon_1,\varepsilon_2,\cdots,\varepsilon_n$是规范正交基的充分必要条件是C为正交矩阵.

----

例3.30 
$\quad 从R^2的基\alpha_1=\begin{bmatrix}
    1 \\ 0
\end{bmatrix},\alpha_2=\begin{bmatrix}
    1 \\ -1
\end{bmatrix}到基\beta_1=\begin{bmatrix}
    1 \\ 1
\end{bmatrix},\beta_2=\begin{bmatrix}
    1 \\ 2
\end{bmatrix}的过渡矩阵为$__________

例3.31
$\quad 已知三维向量空间的一组基底为\alpha_1=\begin{bmatrix}
    1,1,0
\end{bmatrix},\alpha_2=\begin{bmatrix}
    1,0,1
\end{bmatrix},\alpha_3=\begin{bmatrix}
    0,1,1
\end{bmatrix},$
$\quad则向量u=\begin{bmatrix}
    2,0,0
\end{bmatrix}在上述基底的坐标是$________

例3.33
$\quad设\alpha_1=\begin{bmatrix}
    1,2,-1,0
\end{bmatrix}^T,\alpha_2=\begin{bmatrix}
    1,1,0,2
\end{bmatrix}^T,\alpha_3=\begin{bmatrix}
    2,1,1,a
\end{bmatrix}^T,若由\alpha_1,\alpha_2,\alpha_3生成的向量空间维数是2，$
$\quad 则a=$________