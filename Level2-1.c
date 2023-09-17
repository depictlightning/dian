#include<stdio.h>
int count(int a, int b); //定义距离计算函数

// 输入格式：1 2 3表示初始楼层、目标楼层 和时间	
//	输入-1 -1 -1表示输入结束 
//	eg. 5
//		8 5 0
//		7 4 6
//		-1 -1 -1

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

	
//电梯初始化（前往beginfloor(可能有多个人在0s呼叫）
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

//原间隔时间（ti[])与起始终止时间（mindistance)的比较，是否前往原楼层(beginfloor)
	//大于的情况:正常前往原楼层，删除begin2floor[],录入aim2floor[],people +=1,time +=mindistance
	if (ti[jilu] > mindistance ){
		begin2floor[save] = -20;			//删除初始楼层
		aim2floor[save] = aimfloor[save];	//录入目标楼层
		elevatorfloor = closestfloor;		//计算楼层
		people +=1;
		time += mindistance;
		printf("%d %d %d\n", elevatorfloor, time, people);		
	}	
	//等于的情况：同大于，但同时录入begin2floor[]
	else if(ti[jilu] == mindistance ){
		begin2floor[save] = -20;			//删除初始楼层
		aim2floor[save] = aimfloor[save];	//录入目标楼层
		elevatorfloor = closestfloor;	//计算楼层
		people +=1;
		time += mindistance;
		printf("%d %d %d\n", elevatorfloor, time, people);
		save = jilu;						//录入begin2floor
		jilu ++;
		begin2floor[save] = beginfloor[save];	
	}
	//小于的情况
	else if (ti[jilu] < mindistance){
	//基于间隔时间引入testfloor用于判断间隔时间到达后是否需要更改目的楼层
	int testfloor = 0;
	//计算testfloor
	if ( elevatorfloor > closestfloor){	
		testfloor = elevatorfloor - ti[jilu];
	}
	else if( elevatorfloor < closestfloor){
		testfloor = elevatorfloor + ti[jilu];	
	}		
// 比较testlfoor和closestfloor之间距离与mindistance的大小，即引入testdistance
	int testdistance = 0;
	testdistance = count(testfloor,closestfloor);
	mindistance -=ti[jilu];
		//分三种情况 大于等于时，同ti[jilu] > mindistance的情况：前往begin2floor
		if (testdistance >= mindistance){
			begin2floor[save] = -20;			//删除初始楼层
			aim2floor[save] = aimfloor[save];	//录入目标楼层
			elevatorfloor = closestfloor;	//计算楼层
			people += 1;
			time += mindistance;				//注意time对ti[jilu]的影响
			ti[jilu] -= testdistance;
			printf("%d %d %d\n", elevatorfloor, time, people);	
			save = jilu;						//录入begin2floor
			jilu ++;
			begin2floor[save] = beginfloor[save];
		}	
		//小于时：前往下一个乘客的初始楼层（
		else if ( testdistance < mindistance){
			elevatorfloor = testfloor;
			time += testdistance;
			people += 1;
			begin2floor[save] = beginfloor[save];

		}
	
	
	}		

//// 基于间隔时间引入testfloor用于判断间隔时间到达后是否需要更改目的楼层
//	int testfloor = 0;
//	//计算testfloor
//	if ( elevatorfloor > closestfloor){	
//		testfloor = elevatorfloor - ti[jilu];
//	}
//	else if( elevatorfloor < closestfloor){
//		testfloor = elevatorfloor + ti[jilu];	
//	}		
//// 比较testlfoor和closestfloor之间距离与mindistance的大小，即引入testdistance
//	int testdistance = 0;
//	testdistance = count(testfloor,closestfloor);
//	mindistance -=ti[jilu];
////分为三种情况：大于，等于，小于
//
//	if (testdistance > mindistance){
//		
//	}
//	
//
//	
//
//

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
