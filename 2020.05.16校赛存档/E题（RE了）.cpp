#include"pch.h"
#include<iostream>
#include<queue>
#include<cstring>
#include<algorithm>
#include<cstdio>
#define ll long long
#define M 200005
#define N 2147483647
using namespace std;
int n, m, s, ss, endd;
int dis[M],
head[M],//head[i]代表顶点i所连其中一条边的编号 
flag[M],
pre[M],
value[M];

struct edge {
	int l, r, v,
		next;//e[i].next代表第i条边前面的一条边 
	void ini(int lll, int rr, int vv, int nex) {
		l = lll, r = rr, v = vv, next = nex;
	}
	edge() {
	}
}e[M];
struct node {
	int d,//node和集合的距离
		now;//node编号 
	node(int dd, int noww) :d(dd), now(noww) {}
	node() {}
	bool operator<(const node &x)const {
		return d > x.d;
	}
}p;
void bfs() {
	priority_queue<node>q;
	node startnode(0, s);
	q.push(startnode);
	while (!q.empty()) {
		p = q.top();//得到最近的点 
		q.pop();
		int t = p.now;
		if (flag[t] == 1)continue;
		flag[t] = 1;
		for (int i = head[t]; i; i = e[i].next) {
			int x = e[i].r;
			if (dis[x] > dis[t] + e[i].v) {
				dis[x] = dis[t] + e[i].v;
				pre[x] = t;
				node newnode(dis[x], x);
				q.push(newnode);
			}
		}
	}
}
struct pairing {
	int x, y;

}pa[M];
bool cmp(pairing a, pairing b) {
	if (a.x != b.x)return a.x < b.x;
	else return a.y < b.y;
}

int main() {
	int nn;
	cin >> nn;
	while (nn--)
	{
		for (int i = 0; i < M; ++i) {
			e[i].ini(0, 0, 0, 0);
			pa[i].x = pa[i].y = 0;
			dis[i] = head[i] = flag[i] = pre[i] = value[i] = 0;
		}
		cin >> n >> m >> s >> ss >> endd;
		for (int i = 0; i < m; ++i) {
			cin >> value[i];
		}
		sort(value, value + m);
		for (int i = 1; i <= n; i++) {
			dis[i] = N;
		}
		dis[s] = 0;
		int cnt = 0;
		for (int i = 1; i <= m; i++) {
			int l, r, v;
			cin >> l >> r;
			e[++cnt].r = r;//给边编号 
			e[cnt].v = 1;
			e[cnt].next = head[l];//一旦新来一条边，把原来l在head中保存的边挪到e.next中 
			head[l] = cnt;//用新的边来代替挪走的head，最终head就是节点l链表的表头 

			e[++cnt].r = l;//给边编号 
			e[cnt].v = 1;
			e[cnt].next = head[r];//一旦新来一条边，把原来l在head中保存的边挪到e.next中 
			head[r] = cnt;//用新的边来代替挪走的head，最终head就是节点l链表的表头
		}
		bfs();
		/*
		for (int i = 1; i <= n; i++)cout << dis[i] << ' ';
		cout << endl << "path:" << endl; //输出路径，因为dijkstra是贪心算法，所以每一步都是最优解
		for (int i = 1; i <= n; i++)cout << pre[i] << ' ';
		cout << endl << "from a to b:";
		*/
		int sstemp = ss;
		int paircnt = 0;
		while (pre[sstemp]) {
			//printf("(%d,%d)", sstemp, pre[sstemp]);
			int maxm, minm;
			if (sstemp >= pre[sstemp])maxm = sstemp, minm = pre[sstemp];
			else minm = sstemp, maxm = pre[sstemp];
			pa[paircnt].x = maxm;
			pa[paircnt++].y = minm;
			sstemp = pre[sstemp];
		}
		//cout << endl << endl;

		for (int i = 0; i < M; ++i) {
			dis[i] = N;
			flag[i] = pre[i] = 0;
		}
		dis[ss] = 0;
		s = ss;
		bfs();
		/*
		for (int i = 1; i <= n; i++)cout << dis[i] << ' ';
		cout << endl << "path:" << endl; //输出路径，因为dijkstra是贪心算法，所以每一步都是最优解
		for (int i = 1; i <= n; i++)cout << pre[i] << ' ';
		cout << endl << "from b to c:";
		*/
		while (pre[endd]) {
			//printf("(%d,%d)", endd, pre[endd]);
			int maxm, minm;
			if (endd >= pre[endd])maxm = endd, minm = pre[endd];
			else minm = endd, maxm = pre[endd];
			pa[paircnt].x = maxm;
			pa[paircnt++].y = minm;
			endd = pre[endd];
		}

		sort(pa, pa + paircnt, cmp);
		cnt = 1;
		int i;
		priority_queue<int>pq;
		for (i = 0; i <= paircnt - 2; ++i) {
			if ((pa[i].x == pa[i + 1].x&&pa[i].y == pa[i + 1].y) || (pa[i].x == pa[i + 1].y&&pa[i].y == pa[i + 1].x)) {
				cnt++;
			}
			else {
				pq.push(cnt);
				cnt = 1;
			}
		}
		if ((pa[i].x != pa[i + 1].x || pa[i].y != pa[i + 1].y) && (pa[i].x != pa[i + 1].y || pa[i].y != pa[i + 1].x))pq.push(1);
		//cout << endl;
		ll sum = 0;
		cnt = 0;
		while (!pq.empty()) {
			//cout << pq.top() << ' ';
			sum += pq.top()*value[cnt++];
			pq.pop();
		}
		//cout<<endl;
		cout << sum << endl;
	}
}
/*
7 9 1 5 7
2 10 4 8 5 6 7 3 3
1 2
1 3
1 4
3 2
3 5
4 2
5 6
1 7
6 7
*/
/*
4 3 2 3 4
1 2 3
1 2
1 3
1 4
*/
