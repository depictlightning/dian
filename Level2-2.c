#include<stdio.h>
int nextfloor(int state, int efloor); //nextfloor函数通过当前电梯状态判断接下来前往的楼层
int count(int a, int b);			//距离计算函数
int state(int elevatorfloor, int closestfloor);		//判断电梯目前状态


//注意本程序忽略了一种极端情况，即两辆电梯在同一时刻抵达目的楼层，之后需要进行比对判断哪辆电梯前往哪个楼层，由于人数过少，此情况难以出现
int main()
{
//所有1,2下标表示电梯1，电梯2
    int beginfloor[10];	//乘客初始楼层
//	int begin1floor[10],begin2floor[10];	//额外设置这两个数组为了解决People为0时
	int begin3floor[10];
	int aimfloor[10];	//乘客目标楼层
	int aim1floor[10],aim2floor[10]; //乘客进入后录入目标楼层
	int ti[10];			//乘客时间
	int updown[10];		//录入数据判断乘客是上行还是下行
	int i = 0;
	int elevator1floor = 0,elevator2floor = 0 ;	//电梯现处楼层
	int closest1floor = 0,closest2floor = 0;	//最近楼层（即电梯即将前往楼层）                      
	int distance1 = 10,distance2 = 10;	//电梯现处楼层和目标楼层的距离	
	int mindistance1 = 10,mindistance2 = 10;	//电梯和最近目标楼层最短距离
	int people1 = 0,people2 = 0;	
	int time = 0;	
	int state1 = 0,state2 = 0;		//电梯停运时状态为0		
	int save1,save2  = 0;		//save用于删除电梯初始楼层	
	int cnt = 0;				//专用于各种记数、
	int memory[10],number = 0;			//专用于解决目的楼层相同的bug
	int a,b = 0;				//无具体含义一些小地方使用的判断变量
	

	
//将所有数组的值初始化为-20（避免对后续数据造成影响）	
	for( i=0; i<10; i++){	
		beginfloor[i] = -20;
		begin3floor[i] = -20;
		aimfloor[i] = -20;
		aim1floor[i] = -20;
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
	
	int final;			//记录最后一个时间	
//将所有间隔时间转化为总时间（方便与elevatorfloor时间进行比较）
	for( i=0; i<10; i++){
		if (ti[1] == -20){
			final = i;
			break;
		}
		else{
			ti[i+1] += ti[i];
			if (ti[i+2] < 0){
				final  = i+1;
				break;	
			}
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
	
//进入正式程序
	while (people1 > -1 && people2 > -1){
	//程序终止
		for ( i=0;i<10;i++){
			cnt++;
			if (begin3floor[i] != 0 || aim1floor[i] != 0 || aim2floor[i] != 0 || time <= ti[final] )
				break;
		}
		if (cnt == 10)
			break;
		cnt = 0;
			
	//分为电梯两停，一停一动，两动(包含多人同时按下电梯）
		for ( i=0;i<10;i++ ){					//到达间隔时间录入数据
			if (ti[i] == time){
				begin3floor[i] = beginfloor[i];
			}
		}
	//电梯状态：都处于停止时
		if (state1 == 0 && state2 == 0 ){
			for ( i=0; i<10; i++){		//对电梯1的最近初始楼层检索
				distance1 =count(elevator1floor,begin3floor[i]);	
				if (distance1 < mindistance1){
					mindistance1 = distance1;
					closest1floor = begin3floor[i];
				}
			}
			for ( i=0; i<10; i++){		//对电梯2的最近初始楼层检索
				distance2 =count(elevator2floor,begin3floor[i]);	
				if (distance2 < mindistance2){
					mindistance2 = distance2;
					closest2floor = begin3floor[i];	
				}
			}
				//判断电梯两辆全启动还是只一辆（前提存在begin3floor请求)
				if ( closest1floor == closest2floor){	//如果最近楼层一致(仅有一个请求)，谁近谁去
					//(存在一个特例，即有两个及以上请求，但closestfloor都指向同一楼，此时让另一部电梯等待1个单位时间（非最优解，但程序编写相对简单）
					if( mindistance1 <= mindistance2){
						state1 = state(elevator1floor, closest1floor);	
					}else{
						state2 = state(elevator2floor, closest2floor);
					}
				}
				else{										//存在多个请求
					state1 = state(elevator1floor, closest1floor);
					state2 = state(elevator2floor, closest2floor);								
				}			
		}
	//电梯1状态：处于运行中（按state状态向上或向下前进一楼）
		if (state1 != 0){						//对电梯1进行判断
			elevator1floor = nextfloor(state1,elevator1floor);	//前进一楼
			//还未到达目标楼层
			if (elevator1floor != closest1floor){			
				for ( i=0; i<10; i++){
					if (aim1floor[i] == elevator1floor){		//无论是否满载，判断是否有乘客下车,沿用之前逻辑
						a = 1;									//判断变量，无实际意义
						memory[i] = i;
						number++;
					}else{
						memory[i] = -1;
					}
				}
				for(i=0; i<10; i++){
					if(memory[i] != -1){
						aim1floor[memory[i]] = -20;
					}
				}
				people1 -=number;
					if( people1 < 4){						//未满载时,判断是否接受乘客请求(必须满足方向相同）
						if (begin3floor[i] == elevator1floor && updown[i] == state1){
							b = 1;						//判断变量，无实际意义
							people1++;					//人数+1；
							begin3floor[i] = -20;		//删除请求数据
							aim1floor[i] = aimfloor[i];	//录入目标楼层
						}	
					}
				if (a == 1 || b == 1){				//满足其中一个条件打印数据
					printf("elevator1:%d %d %d\n",elevator1floor, time, people1);
				}
				a = 0;
				b = 0;
			}
			//如果到达目的楼层
			else if (elevator1floor == closest1floor ){
				for (i=0; i<10; i++){				//专用于解决目的楼层相同时的人数bug
					if (aim1floor[i] == elevator1floor ){
						memory[i] = i;
						number ++;
					}else{
						memory[i] = -1;
					}
				}
				for (i=0; i<10; i++){
					if(memory[i] != -1){
						aim1floor[memory[i]] = -20;
				    }
				}
				people1 -= number;
				number = 0;												
				//进行新楼层的寻找(同时包含判断是否同时到达了某个请求的初始楼层）
				if (people1 > 0){				//如果电梯上还有乘客，优先前往目的楼层，电梯状态不变
					for (i=0; i<10; i++){
						if ( begin3floor[i] == elevator1floor && updown[i] == state1){	//首先判断是否到达了初始楼层(同方向）
							people1++;
							begin3floor[i] = -20;
							aim1floor[i] = aimfloor[i];
						}
					}
					for ( i=0; i<10; i++){		//对电梯1的最近目标楼层检索
						distance1 =count(elevator1floor,aim1floor[i]);	
						if (distance1 < mindistance1){
							mindistance1 = distance1;
							closest1floor = aim1floor[i];
						}
					}
				}
				else if(people1 == 0 ){				//已经没有乘客(且people2有乘客）
					if( state2 != 0){				//电梯2处于启动状态
						for ( i= 0; i<10; i++){
							if (begin3floor[i] == elevator1floor){			//如果同时到达了初始楼层，直接将初始楼层的目的楼层录入，退出循环
								people1++;
								state1 = state(elevator1floor, closest1floor); 
								begin3floor[i] = -20;
								aim1floor[i] = aimfloor[i];
								break;
							}
							if (state2 == 1){	//检索存在的请求楼层（当然应当不在另一部电梯的范围内）
								if (begin3floor[i] == elevator1floor){			//如果同时到达了初始楼层，直接将初始楼层的目的楼层录入，退出循环
									people1++;
									state1 = state(elevator1floor, closest1floor); 
									begin3floor[i] = -20;
									aim1floor[i] = aimfloor[i];
									break;
								}
								if (begin3floor[i] < closest2floor && begin3floor[i] > elevator2floor + 1 ){	//不在另一部电梯范围内的判断
									distance1 =count(elevator1floor,begin3floor[i]);					//初始楼层搜索
									if (distance1 < mindistance1){
										mindistance1 = distance1;
										closest1floor = begin3floor[i];	
										state1 = state(elevator1floor, closest1floor); 		//更改电梯状态												
									}
								}
							}
							else if(state2 == -1){
								if (begin3floor[i] == elevator1floor){			//如果同时到达了初始楼层，直接将初始楼层的目的楼层录入，退出循环
									people1--;
									state1 = state(elevator1floor, closest1floor); 
									begin3floor[i] = -20;
									aim1floor[i] = aimfloor[i];
									break;
								}
								if (begin3floor[i] > closest2floor && begin3floor[i] < elevator2floor -1 ){	//不在另一部电梯范围内的判断
									distance1 =count(elevator1floor,begin3floor[i]);	
									if (distance1 < mindistance1){
										mindistance1 = distance1;
										closest1floor = begin3floor[i];	
										state1 = state(elevator1floor, closest1floor); 		//更改电梯状态		
									}
								}							
							}													
							if (begin3floor[i] = -20){			//如果没有请求，利用cnt让电梯状态归0
								cnt ++;
							}
						}
					
					if (cnt == 10){
						state1 = 0;
					}	
					cnt = 0;							//回归初始化
					}
					else if (state2 == 0){				//此时另一部电梯停止，此电梯也完成任务）
						state1 = 0;
					}	
				}

			printf("elevator1:%d %d %d\n",elevator1floor, time, people1);
			}
		}
	
															
													
	//电梯2状态：处于运行中（按state状态向上或向下前进一楼）
		if (state2 != 0){						//对电梯2进行判断
//调试
//			printf("begin3floor[0]:%d\n",begin3floor[0]);
			
			elevator2floor = nextfloor(state2,elevator2floor);	//前进一楼
			//还未到达目标楼层
			if (elevator2floor != closest2floor){			
				for ( i=0; i<10; i++){
					if (aim2floor[i] == elevator2floor){		//无论是否满载，判断是否有乘客下车,沿用之前逻辑
						a = 1;									//判断变量，无实际意义
						memory[i] = i;
						number++;
					}else{
						memory[i] = -1;
					}
				}
				for(i=0; i<10; i++){
					if(memory[i] != -1){
						aim2floor[memory[i]] = -20;
					}
				}
				people1 -=number;
					if( people2 < 4){						//未满载时,判断是否接受乘客请求(必须满足方向相同）
						if (begin3floor[i] == elevator1floor && updown[i] == state1){
							b = 1;						//判断变量，无实际意义
							people2++;					//人数+1；
							begin3floor[i] = -20;		//删除请求数据
							aim2floor[i] = aimfloor[i];	//录入目标楼层
						}	
					}
				if (a == 1 || b == 1){				//满足其中一个条件打印数据
					printf("elevator2:%d %d %d\n",elevator1floor, time, people2);
				}
				a = 0;
				b = 0;
			}
			//如果到达目的楼层
			else if (elevator2floor == closest2floor ){
				for (i=0; i<10; i++){				//专用于解决目的楼层相同时的人数bug
					if (aim2floor[i] == elevator2floor ){
						memory[i] = i;
						number ++;
					}else{
						memory[i] = -1;
					}
				}
				for (i=0; i<10; i++){
					if(memory[i] != -1){
						aim2floor[memory[i]] = -20;
				    }
				}
				people2 -= number;
				number = 0;												
				//进行新楼层的寻找(同时包含判断是否同时到达了某个请求的初始楼层）
				if (people2 > 0){				//如果电梯上还有乘客，优先前往目的楼层，电梯状态不变
					for (i=0; i<10; i++){
						if ( begin3floor[i] == elevator1floor && updown[i] == state1){	//首先判断是否到达了初始楼层(同方向）
							people2++;
							begin3floor[i] = -20;
							aim2floor[i] = aimfloor[i];
						}
					}
					for ( i=0; i<10; i++){		//对电梯1的最近目标楼层检索
						distance2 =count(elevator2floor,aim2floor[i]);	
						if (distance2 < mindistance2){
							mindistance2 = distance2;
							closest2floor = aim1floor[i];
						}
					}
				}
				else if(people2 == 0){				//已经没有乘客
					if (state1 != 0){
						for ( i= 0; i<10; i++){
							if (begin3floor[i] == elevator2floor){			//如果同时到达了初始楼层，直接将初始楼层的目的楼层录入，退出循环
								people2++;
								state2 = state(elevator2floor, closest2floor); 
								begin3floor[i] = -20;
								aim2floor[i] = aimfloor[i];
								break;
							}
							if (state1 == 1){	//检索存在的请求楼层（当然应当不在另一部电梯的范围内）*
								if (begin3floor[i] == elevator2floor){			//如果同时到达了初始楼层，直接将初始楼层的目的楼层录入，退出循环
									people2++;
									state1 = state(elevator2floor, closest2floor); 
									begin3floor[i] = -20;
									aim2floor[i] = aimfloor[i];
									break;
								}
								if (begin3floor[i] < closest1floor && begin3floor[i] > elevator1floor ){	//不在另一部电梯范围内的判断*
									distance1 =count(elevator2floor,begin3floor[i]);					//初始楼层搜索
									if (distance2 < mindistance2){
										mindistance2 = distance2;
										closest2floor = begin3floor[i];	
										state2 = state(elevator1floor, closest1floor); 		//更改电梯状态												
									}
								}
							}
							else if(state1 == -1){								
								if (begin3floor[i] == elevator1floor){			//如果同时到达了初始楼层，直接将初始楼层的目的楼层录入，退出循环
									people2--;
									state2 = state(elevator2floor, closest2floor); 
									begin3floor[i] = -20;
									aim2floor[i] = aimfloor[i];
									break;
								}
								if (begin3floor[i] > closest1floor && begin3floor[i] < elevator1floor ){	//不在另一部电梯范围内的判断*
									distance2 =count(elevator2floor,begin3floor[i]);	
									if (distance2 < mindistance2){
										mindistance2 = distance2;
										closest2floor = begin3floor[i];	
										state2 = state(elevator1floor, closest2floor); 		//更改电梯状态		
									}
								}							
							}
							
							if (begin3floor[i] = -20){			//如果没有请求，利用cnt让电梯状态归0
								cnt ++;
							}
						}
						if (cnt == 10){
							state2 = 0;
						}	
					cnt = 0;							//回归初始化
					}
					else if (state1 == 0){				//此时另一部电梯停止，此电梯也完成任务）
						state2 = 0;
					}
			printf("elevator2:%d %d %d\n",elevator2floor, time, people2);	
			}	
		}
		time++;				//时间+1(不放在开头因为初始化需要time是0） 
		}
	}
}	
	

//		printf("state1:%d,state2:%d,closest1floor:%d,closest2floor:%d\n",state1,state2);
//	调试
//	printf("\tbegin\tbegin2\taim\taim2\tti\tupdown[i]\n");
//	for( i=0; i<10; i++){
//			printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i,beginfloor[i],begin3floor[i],aimfloor[i],aim2floor[i], ti[i],updown[i]);
//	}	
//	return 0;
//}

int nextfloor(int state, int efloor)	//通过当前电梯状态判断接下来前往的楼层
{	
	if (state == 1)
		if (efloor != 10){
			efloor++;	
		}
	if (state == -1 ){
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

int state(int elevatorfloor, int closestfloor){			//判断电梯目前状态
	int elevatorstate;
	if (elevatorfloor > closestfloor){
		elevatorstate = -1;
	}
	else if (elevatorfloor < closestfloor){
		elevatorstate = 1;
	}
	return elevatorstate;
}