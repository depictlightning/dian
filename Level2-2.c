#include<stdio.h>
int nextfloor(int state, int efloor); //nextfloor函数通过当前电梯状态判断接下来前往的楼层
int count(int a, int b);			//距离计算函数
int main()
{
//所有1,2下标表示电梯1，电梯2
    int beginfloor[10];	//乘客初始楼层
	int begin2floor[10];//time到达后录入初始楼层
	int aimfloor[10];	//乘客目标楼层
	int aim2floor[10]; //乘客进入后录入目标楼层
	int ti[10];			//乘客时间
	int updown[10];		//录入数据判断乘客是上行还是下行
	int i = 0;
	int elevator1floor,elevator2floor = 0 ;	//电梯现处楼层
	int closest1floor,closest2floor = 0;	//最近楼层（即电梯即将前往楼层）                      
	int distance1,distance2 = 10;	//电梯现处楼层和目标楼层的距离	
	int mindistance1,mindistance2 = 10;	//电梯和最近目标楼层最短距离
	int people = 0;	
	int time = 0;	
	int state1,state2 = 0;		//电梯停运时状态为0		
	int save1,save2  = 0;		//save用于删除电梯初始楼层	
	int cnt = 0;				//专用于各种记数

	
//将所有数组的值初始化为-20（避免对后续数据造成影响）	
	for( i=0; i<10; i++){	
		beginfloor[i] = -20;
		begin2floor[i] = -20;
		aimfloor[i] = -20;
		aim2floor[i] = -20;
		ti[i] = -20;
		updown[i] = -20;
	}
	

//数组录入
	printf("elevator1:");
	scanf("%d",&elevator1floor);
	printf("elevator2:");
	scanf("%d\n,",&elevator2floor);
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

//引入updown[]数组(如果上行则数组值为1，下行数组值为-1)
	for ( i=0; i<10; i++){
		if (beginfloor[i] != -20){
			if (aimfloor[i] > beginfloor[i]){
				updown[i] = 1;
			}
			else if(aimfloor[i] < beginfloor[i]){
				updown[i] = -1;
			}
		}
	}

//分为电梯两停，一停一动，两动
	for ( i=0;i<10;i++ ){
		if (ti[i] == time){
			begin2floor[i] == beginfloor[i];
		}
	}
	//两停
	if (state1 == 0 && state2 == 0 ){
		for ( i=0; i<10; i++){		//对电梯1的最近初始楼层检索
			distance1 =count(elevator1floor,begin2floor[i]);	
			if (distance1 < mindistance1){
				mindistance1 = distance1;
				closest1floor = begin2floor[i];
				save1 = i;
			}
		}
		for ( i=0; i<10; i++){		//对电梯1的最近初始楼层检索
			distance2 =count(elevator2floor,begin2floor[i]);	
			if (distance2 < mindistance2){
				mindistance1 = distance2;
				closest2floor = begin2floor[i];
				save2 = i;	
			}
		}
//判断电梯两辆全启动还是只一辆（前提存在begin2floor请求)
			if ( closest1floor == closest2floor){	//如果最近楼层一致(仅有一个请求)，谁近谁去
			//(存在一个特例，即有两个及以上请求，但closestfloor都指向同一楼，此时让另一部电梯等待1个单位时间（非最优解，但程序编写相对简单）
				if( mindistance1 <= mindistance2){
					state1 = updown[save1];	
				}else{
					state2 = updown[save2];
				}
			}
			else{										//存在多个请求
				state1 = updown[save1];
				state2 = updown[save2];									
			}			
		}
	}
	
	
	
	
	
	
	
//	调试
	printf("\tbegin\tbegin2\taim\taim2\tti\tupdown[i]\n");
	for( i=0; i<10; i++){
			printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i,beginfloor[i],begin2floor[i],aimfloor[i],aim2floor[i], ti[i],updown[i]);
	}	
	return 0;
}

int nextfloor(int state, int efloor)	//通过当前电梯状态判断接下来前往的楼层
{	
	if (state == 1)
		if (efloor != 10){
			efloor++;	
		}
	if (state == -1 )
		if (efloor != 1)
			efloor--;
	}
	return efloor;
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