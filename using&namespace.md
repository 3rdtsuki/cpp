namespace不能在主函数里面  	
想要使用某个namespace中的元素有三种方法：  
1.直接ns::a  
2.using namespace ns; 接下来都不用写空间名了  
3.using ns::a; 接下来该元素不用写空间名了  
想换的时候再写一遍新空间名即可  
```cpp
#include<iostream> 
using namespace std;
namespace fa{
	int a=39;
}
namespace son{
	int a=23;
}
int main(){

	cout<<fa::a;
  
	using namespace son;
	cout<<a;
  
	using fa::a;
	cout<<a;
}
```
