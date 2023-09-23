#include<stdio.h>
int count(int a, int b); //定义距离计算函数
int nextfloor(int efloor,int closestfloor); //定义电梯下一个前往楼层函数

int main()
{
	int time = 0;
	int people = 0;
	int	beginsave[100],aimsave[100],ti[100];	//储存数据
	int elevatorfloor;
	int total = 0;		//用于记录一共输入了多少个数据
	int beginfloor[100],aimfloor[100];			//到达间隔时间后录入数据
	int jilu = 0;		//用于记录目前录入到哪个数据
	int distance1 = 0, distance2 = 0;	
	int mindistance1 = 10, mindistance2 = 10;	//最短距离
	int closestfloor,closestfloor1,closestfloor2; 	//接下来要前往的楼层
	int a=0,b=0;				//判断变量，无实际意义
	int cnt = 0;				//程序处于真空期时使用
	
	
	//数组录入
	printf("界面出现elevator后开始输入数据。输入结束后按回车键输入-1 -1 -1再按回车键退出程序\n");
	printf("第一个输入的数据间隔时间处应为0\n");
	printf("elevator:");
	scanf("%d\n",&elevatorfloor);
	int i;
	for( i=0; i<100; i++){	
		scanf("%d %d %d", &beginsave[i], &aimsave[i], &ti[i]);
		total++;
		if (beginsave[i] == -1 &&aimsave[i] == -1 && ti[i] == -1){ //手动输入-1 -1 -1结束输入 或输满10个数
			total--;
			break;
		}
	}

	//将间隔时间转化为实际时间
	for (i=0; i<total-1; i++){
		ti[i+1] +=ti[i];	
	}

	//将所有aimfloor初始值转为-20，避免影响之后的比对
	for( i=0; i<total; i++){
		aimfloor[i] = -20;
		beginfloor[i] = -20;
	}
	//初始化：仅对beginfloor进行比对
st:	for (i=jilu; i< jilu + 10; i++){		//到达请求时间就录入数据
		if (time == ti[jilu]){
			jilu++;
			beginfloor[i] = beginsave[i];
		}
		if (time != ti[jilu])
			break;
	}
	for ( i=0; i<jilu; i++){ 	//对beginfloor[i]进行比对
		distance1 = count(elevatorfloor,beginfloor[i]);
		if (distance1 < mindistance1){
			mindistance1 = distance1;
			closestfloor = beginfloor[i];	//记录最近的楼层
		}
		if (mindistance1 == 0){			//正好处于请求楼层的特殊情况
			people ++;
			printf("%d %d %d\n", elevatorfloor, time, people);
			beginfloor[i] = -20;			//删除数据
			aimfloor[i] = aimsave[i];		//录入目的楼层
			closestfloor = aimfloor[i];		//前往目的楼层
			mindistance1 = 10;				//避免接下来出现死循环
			time++;
			break;							
		}
	}
	if (mindistance1 != 0){
		time++;
	}	
//正式进入循环
	while(people> -1 ){
		mindistance1 = 10,mindistance2 = 10;	//避免出现死循环
		//开始录入数据
		for (i=jilu; i< jilu + 10; i++){
			if (time == ti[jilu]){
				jilu++;
				beginfloor[i] = beginsave[i];
			}
			if (time != ti[jilu])
				break;
		}
		//前进一楼，比对是否到达任何初始楼层或目的楼层
		elevatorfloor = nextfloor(elevatorfloor, closestfloor);	//前进一层
		for ( i= 0; i<jilu; i++){
			if (people < 4){				//未超载时比对是否到达了初始楼层
				if ( beginfloor[i] == elevatorfloor){
					people ++;
					beginfloor[i] = -20;
					aimfloor[i] = aimsave[i];
					a = 1;
				}
			}
			if (aimfloor[i] == elevatorfloor){
				people--;
				aimfloor[i] = -20;
				b = 1;
			}
		}
		if (a == 1 || b == 1){			//满足其中一个条件，输出数据
			printf("%d %d %d\n", elevatorfloor, time, people);
			a = 0;
			b = 0;
		}
		
		//如果运输完毕，结束程序
		for (i=0; i<jilu; i++){
			if (ti[jilu-1] < ti[total-1] || beginfloor[i] != -20 || aimfloor[i] != -20 )
				break;
			cnt++;
		}	
		if (cnt == total)
			break;
		cnt = 0;
		//如果此时恰好出现真空期（所有乘客运输完毕但还有乘客将要呼叫，时间直接变为那个乘客的时间，goto函数前往初始化）
		for (i=0; i<jilu; i++){
			if (ti[jilu-1] != ti[total-1] || beginfloor[i] != -20 || aimfloor[i] != -20 ){
				break;
			}
			cnt++;
		}
		if (cnt == jilu){
			jilu++;
			time = ti[jilu];
			goto st;				//st为start的缩写,返回初始化
		}
		cnt = 0;
	//进行下一轮的楼层搜索
		//未超载时对初始楼层进行遍历
		if (people < 4){
			for ( i=0; i<jilu; i++){ 	//对beginfloor[i]进行比对
				distance1 = count(elevatorfloor,beginfloor[i]);
				if (distance1 < mindistance1){
					mindistance1 = distance1;
					closestfloor1 = beginfloor[i];	//记录最近的楼层
				}
			}
		}
		//无论是否超载对目的楼层进行遍历
		for (i=0; i<jilu; i++){		//对aimfloor[i]进行比对
			distance2 = count(elevatorfloor,aimfloor[i]);
			if (distance2 < mindistance2){
				mindistance2 = distance2;
				closestfloor2 = aimfloor[i];	//记录最近的楼层
			}
		}
		if (mindistance1 < mindistance2){		//判断接下来前往哪个楼层
			closestfloor = closestfloor1;
		}else{
			closestfloor = closestfloor2;
		}
	time++;
	}
//调试
//	printf("i\tti[i]\tjilu\ttotal\tbegin[i]\taimfloor\n");
//	for( i=0; i<total; i++){
//		printf("%d\t%d\t%d\t%d\t%d\t%d\n",i,ti[i],jilu,total,beginfloor[i],aimfloor[i]);
//	}
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

int nextfloor(int efloor,int closestfloor)
{
	if(efloor < closestfloor){
		efloor++;
	}
	else if(efloor > closestfloor){
		efloor--;
	}
	return efloor;
}