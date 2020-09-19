//基于后缀表达式的整数四则运算计算器（含括号）
//Mika 2020.9.19
#include <iostream>
#include <stack>
using namespace std;
stack<int>stack_num,stack_op;
void cal_add_minus(){	//one step calculate
	char op=stack_op.top();
	stack_op.pop();
	int rt=stack_num.top();
	stack_num.pop();
	int rs=stack_num.top();
	stack_num.pop();
	int temp_ans=0;
	if(op=='*'){
		temp_ans=rs*rt;
	}
	else if(op=='/'){
		temp_ans=rs/rt;
	}
	else if(op=='+'){
		temp_ans=rs+rt;
	}
	else if(op=='-'){
		temp_ans=rs-rt;
	}
	stack_num.push(temp_ans);
}

int main(){
	string exp;
	cin>>exp;
	exp='('+exp+")$";	//把表达式放在括号中，方便exp[0]为负号的情况 
	int len=exp.length();
	int temp=0;
	int ans=0;
	for(int i=0;i<len;++i){
		if(exp[i]>='0'&&exp[i]<='9'){
			temp=temp*10+(int)exp[i]-48;
		}
		else{
			if(temp){
				stack_num.push(temp);
			}
			temp=0;
			if(exp[i]=='$'){
			    break;
			}
			else if(exp[i]==')'){	//遇到右括号，将左括号之后的运算完成 
				while(stack_op.top()!='('){
				    cal_add_minus();
				}
				stack_op.pop();
			}
			else if(exp[i]=='+'||exp[i]=='-'){	//遇到加减号，将前面的运算完成 
				if(!stack_op.empty()){
			        if(stack_op.top()!='('){	//如果不是括号中的第一个运算符，就运算 
			            cal_add_minus();
			        }
			        else{	//如果减号前面一个字符是左括号，说明这是负数的负号不是减号，相当于0-x 
			        	if(exp[i-1]=='('){
			        		stack_num.push(0);
			        	}
					} 
			    }
                stack_op.push(exp[i]);
			}
			else{	//乘号、除号、左括号 
				stack_op.push(exp[i]);
			}
		}
	}
	while(!stack_op.empty()){
        cal_add_minus();
	}
	cout<<stack_num.top()<<' ';
	return 0; 
} 
