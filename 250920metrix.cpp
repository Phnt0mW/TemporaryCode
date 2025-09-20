#include <bits/stdc++.h>
using namespace std;

/*# 7-1 关系闭包算法练习
## 题目描述
掌握关系的三种闭包（自反闭包、对称闭包、传递闭包）构造算法，以及 Warshall 传递闭包算法。编程实现输入任意 \( n \times n \) 的关系矩阵，根据选择的算法构造对应的闭包，并打印输出结果。

## 输入格式
1. 第一行输入两个整数：\( n \)（矩阵阶数，满足 \( 1 < n \leq 10 \)）和 **算法选择**（取值区间为 [1,4]），两个值之间用空格分隔。  
- 算法选择 = 1：执行自反闭包 \( r(R) \) 计算；  
- 算法选择 = 2：执行对称闭包 \( s(R) \) 计算；  
- 算法选择 = 3：执行传递闭包 \( t(R) \) 计算；  
- 算法选择 = 4：执行 Warshall 传递闭包算法 \( w(R) \) 计算。  
2. 接下来 \( n \) 行，每行输入 \( n \) 个 0 或 1（关系矩阵元素），元素之间用空格分隔。

## 输出格式
1. 首先输出一行 **结果说明**，根据算法选择对应不同的说明文本：  
- 自反闭包：`The reflexive closure of the given matrix is`  
- 对称闭包：`The symmetric closure of the given matrix is`  
- 传递闭包：`The transitive closure of the given matrix is`  
- Warshall 传递闭包：`The Warshall algorithm of the given matrix is`  
2. 随后输出 \( n \) 行，每行 \( n \) 个 0 或 1（构造后的闭包矩阵），元素之间用空格分隔，每行末尾需打印换行符。

## 输入样例
```
3 1
0 1 1
1 0 1
0 1 0
```

## 输出样例
```
The reflexive closure of the given matrix is
1 1 1
1 1 1
0 1 1
```

## 约束条件
- 代码长度限制：16 KB  
- 时间限制：400 ms  
- 内存限制：64 MB  
- 栈限制：8192 KB  

## 核心算法说明
1. **自反闭包 \( r(R) \)**：在原关系矩阵基础上，将主对角线元素（即 \( (i,i) \) 位置，\( 0 \leq i < n \)）全部置为 1，确保每个元素与自身存在关系。  
2. **对称闭包 \( s(R) \)**：在原关系矩阵基础上，对任意 \( i \neq j \)，若 \( matrix[i][j] = 1 \)，则令 \( matrix[j][i] = 1 \)（即矩阵与自身转置取“或”运算），确保关系的双向性。  
3. **传递闭包 \( t(R) \)**：通过迭代计算矩阵的幂集并集（\( R \cup R^2 \cup R^3 \cup \dots \cup R^n \)），若存在从 \( i \) 到 \( k \)、\( k \) 到 \( j \) 的路径，则令 \( (i,j) = 1 \)，确保关系的传递性。  
4. **Warshall 算法**：高效计算传递闭包的方法，通过三重循环迭代考虑每个节点作为“中间节点”，若 \( i \) 到 \( k \) 且 \( k \) 到 \( j \) 可达，则更新 \( i \) 到 \( j \) 为可达，时间复杂度优化为 \( O(n^3) \)。*/

bool a[105][105], b[105][105], c[105][105];
int main()
{
	int n, op;
	cin >> n >> op;

	if ( op == 1 ) {
		for ( int i = 1; i <= n; i++ ) {
			for ( int k = 1; k <= n; k++ ) {
				cin >> a[i][k];
			}
		}

		for ( int i = 1; i <= n; i++ ) {
			a[i][i] = 1;
		}

		cout << "The reflexive closure of the given matrix is" << endl;

		for ( int i = 1; i <= n; i++ ) {
			for ( int k = 1; k <= n; k++ ) {
				cout << a[i][k] << ( k == n ? '\n' : ' ' ) ;
			}
		}

	} else
		if ( op == 2 ) {
			for ( int i = 1; i <= n; i++ ) {
				for ( int k = 1; k <= n; k++ ) {
					cin >> a[i][k];
				}
			}

			for ( int i = 1; i <= n; i++ ) {
				for ( int k = 1; k <= n; k++ ) {
					if ( a[i][k] ) {
						a[k][i] = 1;
					}
				}
			}

			cout << "The symmetric closure of the given matrix is" << endl;

			for ( int i = 1; i <= n; i++ ) {
				for ( int k = 1; k <= n; k++ ) {
					cout << a[i][k] << ( k == n ? '\n' : ' ' ) ;
				}
			}

		} else
			if ( op == 3 || op == 4 ) {
				for ( int i = 1; i <= n; i++ ) {
					for ( int k = 1; k <= n; k++ ) {
						cin >> a[i][k];
					}
				}

				for ( int k = 1; k <= n; k++ ) {
					for ( int i = 1; i <= n; i++ ) {
						for ( int j = 1; j <= n; j++ ) {
							a[i][j] = a[i][j] || ( a[i][k] && a[k][j] );
						}
					}
				}

				if ( op == 3 )
				{ cout << "The transitive closure of the given matrix is" << endl; }

				else {
					cout << "The Warshall algorithm of the given matrix is" << endl;
				}

				for ( int i = 1; i <= n; i++ ) {
					for ( int k = 1; k <= n; k++ ) {
						cout << a[i][k] << ( k == n ? '\n' : ' ' ) ;
					}
				}
			}
}
