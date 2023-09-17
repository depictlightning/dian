#include<stdio.h>
int count(int a, int b); //定义距离计算函数
// 输入格式：1 2 3表示初始楼层、目标楼层 和时间	
//	输入-1 -1 -1表示输入结束 
//	eg. 5
//		8 5 0
//		7 4 6
//		-1 -1 -1

//
int main()
{
	int beginfloor[10];	//乘客初始楼层
	int begin2floor[10];//time到达后录入初始楼层
	int aimfloor[10];	//乘客目标楼层
	int aim2floor[10]; //乘客进入后录入目标楼层
	int ti[10];			//乘客时间
	int i = 0;
	int elevatorfloor = 0;	//电梯现处楼层
	int closestfloor = 0;	//最近楼层（即电梯即将前往楼层）
	int mindistance = 10;	//最短距离（用于时间统计）
	int people = 0;	
	int time = 0;		

	
//将所有数组的值初始化为-20（避免对后续数据造成影响）	
	for( i=0; i<10; i++){	
		beginfloor[i] = -20;
		begin2floor[i] = -20;
		aimfloor[i] = -20;
		aim2floor[i] = -20;
		ti[i] = -20;
	}

//数组录入
	printf("elevator:");
	scanf("%d\n",&elevatorfloor);
	for( i=0; i<10; i++){	
	scanf("%d %d %d", &beginfloor[i], &aimfloor[i], &ti[i]);
	if (beginfloor[i] == -1 &&aimfloor[i] == -1 && ti[i] == -1){ //手动输入-1 -1 -1结束输入 或输满10个数
		beginfloor[i] = -20;									//-1输入值删除
		aimfloor[i] = -20;
		ti[i] = -20;
		break;
		}
	}


//	//调试
	printf("\tbegin\tbegin2\taim\taim2\tti\n");
	for( i=0; i<10; i++){
			printf("%d\t%d\t%d\t%d\t%d\t%d\n",i,beginfloor[i],begin2floor[i],aimfloor[i],aim2floor[i], ti[i]);
	}	
	printf("jilu的值为：%d",jilu);
	return 0;
}

int count(int a, int b)
{	
	int m;
	if ( a>b ){
		m = a - b;
	}else{
		m = b - a;
	}
	return m;
}
