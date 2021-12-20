# chapter 0 - 2 Big-$O$ Notation

## 1. Big-$O$ Notation

使用basic computer steps来描述算法耗时确实已经是一个很好的简化了，它排除了处理器、缓存策略等差异造成的影响。我们可以在此基础上继续简化。

假设$T(n)=3n^2+6n+2$，我们干脆直接省略掉表达式中的低阶项($6n+2$)。可以想象，当$n$非常大时，这些低阶项对总体的影响可以忽略不计了。再进一步，$n^2$前面的系数3也直接省略吧(Thanks to Moore Law)，我们直接说：该算法花费的时间为$O(n^3)$ （big oh of $n^3$）

下面给出Big-$O$ Notation的定义，一般用于分析算法的复杂度：

>$f(n)$和$g(n)$分别为两个算法消耗的时间，输入项大小为$n$。
>
>若存在一个常数$c>0$，使$f(n)\leq c\cdot g(n)$，则称$f=O(g)$，即$f$的增长速度不比$g$快。
>
>$f=O(g)$可以当作是$f\leq g$，只不过这里比较的是增长速度。

假设$f_1(n)=n^2$，$f_2(n)=2n+10$，$f_3(n)=n+1$，

则$f_2=O(f_1)$，因为$f_2\leq 12f_1$；$f_1\neq O(f_2)$，因为找不到$c$使$f_1\leq c\cdot f_2$。

同理，$f_2=O(f_3),f_3=O(f_2)$。

按照Big-$O$ Notation的定义，我们可以继续定义Big-$\Omega$ Notation和Big-$\Theta$ Notation：

>$f=\Omega(g)$ <=> $g=O(f)$
>
>$f=\Theta(g)$ <=> $f=O(g)$且$f=\Omega(g)$

上述例子中，$f_2=\Theta(f_3)$，$f_1=\Omega(f_3)$。

化简为Big-$O$ Notation的常用技巧：

1. 省略系数：如$3n^2$ => $n^2$
2. $n^a$增速大于$n^b$（$a>b$）：$n^2+n$ => $O(n^2)$
3. 指数项增速大于多项式：$2^n+n^9$ => $O(2^n)$
4. 多项式增速大于对数项：$n+(\log n)^5$ => $O(n)$

## 2. Revisit Fibonacci

使用Big-$O$ Notation来分析前面的两个算法：

$fib1$的时间复杂度为：$O(2^n)$，若考虑数字的bit数，复杂度为$O(n\cdot 2^n)$

$fib2$的时间复杂度为：$O(n)$，若考虑数字的bit数，复杂度为$O(n^2)$

### 2.1 矩阵快速幂

之前提到过，存在更好的方法来计算$F_n$，原理是利用矩阵(matrix)：
$$
\left[
\begin{array}\\
F_1 \\
F_2
\end{array}
\right]
=
\left[
\begin{array}\\
 0 & 1 \\
 1 & 1
\end{array}
\right]
\left[
\begin{array}\\
F_0 \\
F_1
\end{array}
\right]
$$

$$
\left[
\begin{array}\\
F_2 \\
F_3
\end{array}
\right]
=
\left[
\begin{array}\\
 0 & 1 \\
 1 & 1
\end{array}
\right]
\left[
\begin{array}\\
F_1 \\
F_2
\end{array}
\right]
=
\left[
\begin{array}\\
 0 & 1 \\
 1 & 1
\end{array}
\right]^2
\left[
\begin{array}\\
F_0 \\
F_1
\end{array}
\right]
$$

$$
...
$$

$$
\left[
\begin{array}\\
F_{n} \\
F_{n+1}
\end{array}
\right]
=
\left[
\begin{array}\\
 0 & 1 \\
 1 & 1
\end{array}
\right]^n
\left[
\begin{array}\\
F_0 \\
F_1
\end{array}
\right]
$$

所以只需要计算出一个固定矩阵的$n$次方就可以得出结果。代码如下：

```c++
Matrix<int> matrix_pow(Matrix<int>& m, int n) {
	if (n == 1) return m;
	Matrix<int> res = matrix_pow(m, n / 2);
	if (n % 2 == 1) return m * res * res;
	return res * res;
}

int fib3(int n) {
	if (n == 0) return 0;
	if (n == 1) return 1;
	Matrix<int> m = Matrix<int>(2, 2);
	m(1, 1) = 0;
	m(1, 2) = 1;
	m(2, 1) = 1;
	m(2, 2) = 1;
	m = matrix_pow(m, n);
	return m(1, 2);
}
```

分析$fib3$，每进行一次矩阵乘法需要使用4次实数加法和8次实数乘法，由于实数乘法耗时大于实数加法，下面将只考虑乘法。假设有矩阵$X$，采用代码中`matrix_pow`的分治策略（后面章节会详细分析）：
$$
X^n=\left\{
\begin{aligned}
&(X^{\lfloor \frac{n}{2} \rfloor})^2, & n为偶数 \\
&X \cdot (X^{\lfloor \frac{n}{2} \rfloor})^2, & n为奇数
\end{aligned}
\right.
$$
易得计算出$X^n$将需要至少$\log n$次矩阵乘法，即$O(\log n)$次实数乘法。如果不考虑数字的bit数，那么该算法的复杂度就是$O(\log n)$。

下面分析数字bit位数的变化。每一次矩阵平方，bit位数将翻倍；若只乘以$X$，bit位数最多加一位，可忽略不计。由此可以推算出经过$\log n$次运算后，$F_n$的长度将为$2^{\log n}=O(n)-bits$，那么对于两个$n-bit$的实数，每次乘法所需要的步数$M(n)$是多少呢？大家可以猜测一下，使用一般方法应该是$M(n)=O(n^2)$。

综上所述，该算法的总复杂度似乎是$O(M(n)\log n)$。但是，我们注意到，每分治一次，数字的bit位数其实变为原来的一半，总复杂度应该要比上述式子更小。假设总的steps为$T(n)$，则可以列出下面的式子：
$$
T(n)=T(\frac{n}{2})+O(M(\frac{n}{2}))
$$
我们做出一个乐观的预测：$M(n)=O(n^c),1 < c < 2$。那么上述式子可以化简为：
$$
T(n)=M(\frac{n}{2})+M(\frac{n}{4})+\cdots +M(1)\leq n^c\sum^{i}\frac{1}{2^{ic}}=O(n^c)=O(M(n))
$$
由此可得，该算法的复杂度就是$O(M(n))$。只要两个$n-bit$实数乘法复杂度小于$O(n^2)$，$fib3$就会比$fib2$更快！那么有可能实现吗？再次打住，后面再详细说。

### 2.2 公式法

上一章提过，可以用数学推导出来的公式直接计算$F_n$：
$$
F_n=\frac{1}{\sqrt{5}}(\frac{1+\sqrt{5}}{2})^{n}-\frac{1}{\sqrt{5}}(\frac{1-\sqrt{5}}{2})^{n}
$$
看着简单，但其实行不通，因为所有数字都是无理数，无理数的$n$次方，会丢失精度。

有趣的是，仔细观察$fib3$中的矩阵：
$$
X=
\left[
\begin{array}\\
 0 & 1 \\
 1 & 1
\end{array}
\right]
$$
可以求解出它的特征值为：
$$
\lambda_1=\frac{1+\sqrt{5}}{2}, \lambda_2=\frac{1-\sqrt{5}}{2}
$$
而矩阵的特征值具有如下性质：
$$
X\xi=\lambda \xi
$$

$$
X^2\xi=\lambda^2 \xi
$$

$$
...
$$

$$
X^n\xi=\lambda^n \xi
$$

是不是与$F_n$的公式有千丝万缕的联系？其实，$fib3$本质上就是求解了无理数的$n$次方，只不过是换了一种表达形式罢了。















