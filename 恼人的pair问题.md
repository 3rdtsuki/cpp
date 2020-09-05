众所周知，想对一个数组排序同时保留序号有多种方法。

最直接的是建立一个结构体，属性1是value，属性2是num

另外就是用pair or map

也可以用哈希表unordered_map，形成一个二维数组，第一维是value，第二维是num

例：leetcode1282用户分组

https://leetcode-cn.com/problems/group-the-people-given-the-group-size-they-belong-to/submissions/

```cpp
#include <unordered_map>
class Solution {
public:
    vector<vector<int>> groupThePeople(vector<int>& groupSizes) {
        unordered_map<int, vector<int>> groups;
        for (int i = 0; i < groupSizes.size(); ++i) {
            groups[groupSizes[i]].push_back(i);
			//形成一个二维数组，第一维是groupsize，第二维是num
        }
        vector<vector<int>> ans;
        //遍历，group是每个地址（指针）
        for (auto group = groups.begin(); group != groups.end(); ++group) {
            const int& gsize = group->first;
            vector<int>& users = group->second;
            for (auto iter = users.begin(); iter != users.end(); iter = next(iter, gsize)) {
                vector<int> dummy(iter, next(iter, gsize));
                ans.push_back(dummy);
            }
        }
        return ans;
    }
};
```

这启发我们一种遍历方法——指针遍历

```cpp
for (auto group = groups.begin(); group != groups.end(); ++group) {
    const int& gsize = group->first;
    vector<int>& users = group->second;
    for (auto iter = users.begin(); iter != users.end(); iter = next(iter, gsize)) {
        vector<int> dummy(iter, next(iter, gsize));
        ans.push_back(dummy);
    }
}
```

