#include<stdio.h>
int max(int a, int b); //定义比大小函数

int main()
{
	int bf; //人所在的楼层
	int tf;	//人的终点楼层
	int ef;	//电梯现在所在楼层
	
	scanf("%d %d %d", &bf, &tf, &ef);
	
	int time = 0;	//当下运行时间
	int people = 0;	//当下人数
	
	printf("%d %d %d\n", ef, time, people);	//电梯初始楼层时
	
	time = max(bf, ef);						//楼层大减小
	people += 1;
	printf("%d %d %d\n", bf, time, people);	//到达乘客楼层时
	
	time += max(tf, bf);
	people -= 1;	
	printf("%d %d %d\n", tf, time, people);	//到达终点楼层
	
	
	return 0;
}

int max(int a, int b)
{	
	int m;
	if ( a>b ){
		m = a - b;
	}else{
		m = b - a;
	}
	return m;
}