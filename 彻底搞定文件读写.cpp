#include<fstream>
#include<iostream>
using namespace std;

//读文件
//c version
FILE *fin=fopen(path,"rb");
fseek(fin,1,0);//从0处开始算，偏移1字节处开始读取
fread(buffer,1,20,fin);//以1个字节为单位，读取20个单位，存入buffer
cout<<buffer; 
	

//c++ version
char path[]="./test.txt";//路径用正斜杠
ifstream infile;
infile.open(path);
infile.seekg(1);//从0处开始算，偏移1字节处开始读取
while(infile.eof()==false){//每次读1个字节
  infile>>buffer;
  cout<<buffer<<' ';
}


//写文件
//c version
FILE *fout=fopen(path,"wb");
fwrite(buffer,1,sizeof(buffer),fout);
