#include<windows.h>
#include<iostream> 
#include<ctime>
using namespace std;
char map[20][20];
int n=3;
void initialize(){
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			map[i][j]=' ';
		}
	}
}
void show(){
	for(int i=0;i<n;++i){
		cout<<' '; 
		for(int j=0;j<n;++j){
			cout<<map[i][j]<<" | ";
		}
		cout<<endl;
		cout<<"-----------";
		cout<<endl;
	}
	Sleep(1000);
}
void ai(){
	int operate=0;
	//横 
	for(int i=0;i<n;++i){
		if(map[i][0]==map[i][2]&&map[i][0]=='X'&&map[i][1]==' '){
			map[i][1]='O';
			operate=1;
			return;
		}
		if(map[i][0]==map[i][1]&&map[i][0]=='X'&&map[i][2]==' '){
			map[i][2]='O';
			operate=1;
			return;
		}
		if(map[i][1]==map[i][2]&&map[i][1]=='X'&&map[i][0]==' '){
			map[i][0]='O';
			operate=1;
			return;
		}
	}
	//竖 
	for(int i=0;i<n;++i){
		if(map[0][i]==map[2][i]&&map[0][i]=='X'&&map[1][i]==' '){
			map[1][i]='O';
			operate=1;
			return;
		}
		if(map[0][i]==map[1][i]&&map[0][i]=='X'&&map[2][i]==' '){
			map[2][i]='O';
			operate=1;
			return;
		}
		if(map[1][i]==map[2][i]&&map[1][i]=='X'&&map[0][i]==' '){
			map[0][i]='O';
			operate=1;
			return;
		}
	}	
	// 捺
		if(map[0][0]==map[2][2]&&map[0][0]=='X'&&map[1][1]==' '){
			map[1][1]='O';
			operate=1;
			return;
		}
		else if(map[0][0]==map[1][1]&&map[0][0]=='X'&&map[2][2]==' '){
			map[2][2]='O';
			operate=1;
			return;
		}
		else if(map[1][1]==map[2][2]&&map[2][2]=='X'&&map[0][0]==' '){
			map[0][0]='O';
			operate=1;
			return;
		}
	

	// 撇 

		else if(map[0][2]==map[2][0]&&map[0][2]=='X'&&map[1][1]==' '){
			map[1][1]='O';
			operate=1;
		}
		else if(map[0][2]==map[1][1]&&map[0][2]=='X'&&map[2][0]==' '){
			map[2][0]='O';
			operate=1;
		}
		else if(map[1][1]==map[2][0]&&map[2][0]=='X'&&map[0][2]==' '){
			map[0][2]='O';
			operate=1;
		}    

	

	if(operate==0){
		srand((int)time(0));
		while(1){
			int i=rand()%3,j=rand()%3;
			if(map[i][j]!=' ')continue;
			else{
				map[i][j]='O';
				return;
			}
		}
	}
}
int main(){
	initialize();
	show();
	int x,y; 
	int cnt=0;
	while(1){
		cout<<"please input coordinate:"<<endl; 
		cin>>x>>y;
		cnt++;
		Sleep(1000);
		system("cls");
		if(x>=n){
			break;
		}
		map[x][y]='X';
		show();
		if(cnt==5)break;
		ai();
		system("cls");
		show();
	}
}
