题目：https://www.luogu.com.cn/problem/T133626?contestId=29614

[ 展开](javascript:void 0)

## 题目描述

给定一个含有n(n一定为偶数)个元素的数组a，对\forall{}a_i∀*a**i*保证，a_i{}\le{}k*a**i*≤*k*。

对这个数组a进行最少次替换操作，替换操作定义为用s(s\in[1,k],s\in{}Z)*s*(*s*∈[1,*k*],*s*∈*Z*)替换a中的任意元素，使这个数组经过所有替换操作后满足如下规则：

- 对\forall{}a_i满足0<{}a_i\le{}k对∀*a**i*满足0<*a**i*≤*k*
- \exist x\in\N ,对\forall{}i\in[1,n/2]，均有a_i+a_{n-i+1}=x∃*x*∈N,对∀*i*∈[1,*n*/2]，均有*a**i*+*a**n*−*i*+1=*x*

## 输入格式

第一行为一个整数t(1\le{}t\le{}1e4)*t*(1≤*t*≤1*e*4)，表示测试数据组数

每组测试数据的第一行包括两个整数n和k(2\le{}n\le{}2\times10^5,1\le{}k\le{}2\times10^5)(2≤*n*≤2×105,1≤*k*≤2×105)，表示数组a的长度以及a_i*a**i*的上界值，保证n是偶数。每组测试数据的第二行包括n个整数a_1,a_2,...,a_n(1\le{}a_i\le{}k)*a*1,*a*2,...,*a**n*(1≤*a**i*≤*k*)，分别表示数组a中的n个初始元素。

对所有测试数据的n和k保证满足\sum{}n<2\times10^5∑*n*<2×105和\sum{}k<2\times10^5∑*k*<2×105

## 输出格式

对于每组测试数据，输出进行最少进行替换操作的次数，每个一行

## 输入输出样例

**输入 #1**复制

```
4
4 2
1 2 1 2
4 3
1 2 2 1
8 7
6 1 1 7 6 3 4 6
6 6
5 2 6 1 3 4
```

**输出 #1**复制

```
0
1
4
2
```

```
本题需要明确，尽管修改方法不唯一，但是最佳修改方法是：
通过枚举的方法将x从2到2k都试一遍
（1）如果两数之和=x，不用修改
（2）如果一对数中较大的<x-k，或者较小的>x-1，则两个数都要修改（因为较小的也<x-k||较大的也>x-1）
（3）否则修改一次
优化的方法是先将较大数和较小数分别排序，
用二分找到较大组中第一个>=x-k的位置，那么它之前的组肯定要改一次，记录次数cnt1
用二分找到较小组中第一个<=x-1的位置，那么它之后的组肯定要改一次，记录次数cnt2
而且这两种情况不会同时出现
设改零次的组数为t0,改一次的组数为a，改两次的组数为b
则t0+a+b=n/2,b=cnt1+cnt2
所以总次数=a+2b=cnt1+cnt2+n/2-t0，t0需要事先记录

利用二分在升序数组中查找的函数：
lower_bound(a+start,a+end,value):查找数组a从start到end的元素中第一个值>=value的元素的地址，再减a即为索引
upper_bound(a+start,a+end,value):查找数组a从start到end的元素中第一个值>value的元素的地址，
通过n/2-upper_bound的方式可以求第一个值<=value的元素的地址

map的几个函数：
map<t1,t2>：把类型t1映射到t2
map.clear()：清空map
map.count(x):在map中查找x，没有返回0，有返回1
```

```cpp
#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;
const int maxn = 200005;
int a[maxn];
int bigger[maxn], smaller[maxn];
map<int, int>times;
int main() {
	int nn;
	cin >> nn;
	while (nn--) {
		int n, k;
		cin >> n >> k;
		for (int i = 0; i < n; ++i) {
			cin >> a[i];
		}
		times.clear();
		for (int i = 0; i < n / 2; ++i) {
			if (!times.count(a[i] + a[n - i - 1])) {
				times[a[i] + a[n - i - 1]] = 0;
			}
			times[a[i] + a[n - i - 1]]++;
			bigger[i] = max(a[i], a[n - i - 1]);
			smaller[i] = min(a[i], a[n - i - 1]);
		}
		sort(bigger, bigger + n / 2);
		sort(smaller, smaller + n / 2);
		int cnt1 = 0, cnt2 = 0, ans = n;
		for (int x = 2; x <= 2 * k; ++x) {
			cnt1 = lower_bound(bigger, bigger + n / 2, x - k) - bigger;
			//因为数组从0开始，所以返回的正是前面的元素个数
			cnt2 = upper_bound(smaller, smaller + n / 2, x - 1) - smaller;
			cnt2 = n / 2 - cnt2;
			ans = min(ans, cnt1 + cnt2 + n / 2 - (times.count(x) ? times[x] : 0));
		}
		cout << ans << endl;
	}
}
```

