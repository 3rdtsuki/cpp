class内部重载小于号，可以用于sort和priority_queue等

```cpp
struct node{
    int d,//node和集合的距离
	now;//node编号 
    bool operator<(const node &x)const {
        return d>x.d;
    }
}p;
```

