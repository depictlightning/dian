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
//将所有间隔时间转化为总时间（方便与elevatorfloor时间进行比较）
	for( i=0; i<10; i++){
		ti[i+1] += ti[i];
		if (ti[i+2] < 0){
		break;	
		}	
	}
	
//电梯初始化（初始化与后面的代码高度重复但又有细微差别)前往beginfloor(可能有多个人在0s呼叫）
	while (people == 0){
		int jilu = 0;			//用于记录还有哪些ti[]的时间没有录入
		for( i=0; i<10; i++){
			if (ti[i] == 0){
				begin2floor[i] = beginfloor[i];		//录入初始楼层
				jilu = i + 1;
			}
			if (ti[i+1] != 0)
			break;
		}
		int distance =10;
		int save = 0;
		for ( i=0; i<10; i++){ 	//第一次只对begin2floor[i]进行比对
			distance = count(elevatorfloor,begin2floor[i]);
			if (distance < mindistance){
				mindistance = distance;
				closestfloor = begin2floor[i];	//记录最近的楼层
				save = i;
			}
		}
		int testtime = elevatorfloor + mindistance;	//到达时间后和目前的ti[jilu]进行比较
		int testfloor;	//用于testtime > ti[jilu]的情况,判断是否前往新呼叫乘客的初始楼层
		int testdistance;		//比较testdistance 和mindistance的区别判断优先前往哪个楼层
		
		if( testtime <= ti[jilu] ){	//正常前往楼层（小于的情况）且是唯一进行printf的	
			time = testtime;
			people += 1;
			begin2floor[save] = -20;			//删除初始楼层
			aim2floor[save] = aimfloor[save];	//录入目标楼层
			elevatorfloor = closestfloor;		//计算楼层
			printf("%d %d %d\n", elevatorfloor, time, people);	
		}else if( testtime > ti[jilu] )		//大于的情况，判断是否前往beginfloor
		{
			if ( elevatorfloor > closestfloor){	
				testfloor = elevatorfloor - (ti[jilu]-time);
			}
			else if( elevatorfloor < closestfloor){
				testfloor = elevatorfloor + (ti[jilu]-time);	
			}		
		}
		
		elevatorfloor = testfloor;			//电梯处于新的楼层
		testdistance = count(elevatorfloor,beginfloor[jilu]);
		mindistance = count(elevatorfloor,closestfloor);
		
		if (testdistance >= mindistance){	//前往原楼层(但不输出数据）
			begin2floor[jilu] = beginfloor[jilu];		//录入begin2floor的数据
			jilu++;									//前往下一个ti[i]								
		}
		else if(testdistance < mindistance){	//前往新的楼层
			mindistance = testdistance;
			jilu++;
			begin2floor[jilu] = beginfloor[jilu];		//录入begin2floor的数据
		}
	}
	
//	//调试
	printf("\tbegin\tbegin2\taim\taim2\tti\n");
	for( i=0; i<10; i++){
			printf("%d\t%d\t%d\t%d\t%d\t%d\n",i,beginfloor[i],begin2floor[i],aimfloor[i],aim2floor[i], ti[i]);
	}	
	// printf("jilu的值为：%d",jilu);
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
