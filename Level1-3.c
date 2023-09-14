#include<stdio.h>
int count(int a, int b); //定义距离计算函数

// 输入格式：1 2 表示初始楼层和目标楼层 
//	输入 -1 -1结束输入	eg.  2 3
//							5 9
//							6 8
//							-1 -1
int main()
{
	int beginfloor[10];	//乘客初始楼层
	int aimfloor[10];	//乘客目标楼层
	int aim2floor[10]; //乘客进入后录入目标楼层
	int i = 0;
	int elevatorfloor = 1;	//电梯现处楼层
	int closestfloor = 0;	//最近楼层（即电梯即将前往楼层）
	int mindistance = 10;	//最短距离（用于时间统计）
	int people = 0;	
	int time = 0;		

	
//将所有数组的值初始化为-20（避免对后续数据造成影响）	
	for( i=0; i<10; i++){	
		beginfloor[i] = -20;
		aimfloor[i] = -20;
		aim2floor[i] = -20;
	}

//数组录入
	for( i=0; i<10; i++){	
	scanf("%d %d", &beginfloor[i], &aimfloor[i]);
	if (beginfloor[i] == -1 &&aimfloor[i] == -1){ //手动输入-1 -1结束输入 或输满10个数
		beginfloor[i] = -20;
		aimfloor[i] = -20;
		break;
		}
	}

//	打印电梯初始楼层(如果一楼没人上电梯的情况下)
	int cal = 0;
	for( i=0; i<10; i++){	
		if (beginfloor[i] == 1)
		cal +=1;		//cal用来判断是否一楼有人上梯，即是否需要打印出 1 0 0
	} 
	if( cal == 0){
		printf("%d %d %d\n", elevatorfloor, time, people);
	}
//进行最短距离测算(初始化楼层寻找）
	int distance =10;
	int save;
	for ( i=0; i<10; i++){ 	//第一次只对beginfloor[i]进行比对
			distance = count(elevatorfloor,beginfloor[i]);
			if (distance < mindistance){
				mindistance = distance;
				closestfloor = beginfloor[i];
				save = i;						//记录i的值
			}
		}
	aim2floor[save] = aimfloor[save];		//录入目标楼层
	beginfloor[save] = -20;			//删除数据
	elevatorfloor = closestfloor;	//计算楼层
	people +=1;						//计算人数
	time += mindistance;			//计算时间
	printf("%d %d %d\n", elevatorfloor, time, people);

	int distance2 =0;
	int save2 = 0;
	int mindistance2 = 10;
	int	closestfloor2 = 10;			//所有2下标表示和beginfloor[i]时的比对作区分
	int memory[10];				//用于接下来n个乘客目的楼层一致时数据删除
	int number = 0;						//用于接下来n个乘客目的楼层一致时people-n
	
	while(people > -1){
		while (people < 4 ){	
			mindistance = 10;
			mindistance2 =10;	
			for ( i=0; i<10; i++){			//未超载时对beginfloor[i]比对
				distance =count(elevatorfloor,beginfloor[i]);
				if (distance < mindistance){
					mindistance = distance;
					closestfloor = beginfloor[i];
					save = i;						//记录i的值
				}
			}
			
			for ( i=0; i<10; i++){			//未超载时和aim2floor[i]进行
				distance2 =count(elevatorfloor,aim2floor[i]);
				if (distance2 < mindistance2){
					mindistance2 = distance2;
					closestfloor2 = aimfloor[i];
					save2 = i;					//记录i的值（便于录入目标楼层）
				}				
				
			}
			//distance和distance2进行比较
			//如果前往起始楼层
			if( mindistance < mindistance2){			
				aim2floor[save] = aimfloor[save];		//录入目标楼层
				beginfloor[save] = -20;			//删除数据
				elevatorfloor = closestfloor;	//计算楼层
				people +=1;						//计算人数
				time += mindistance;			//计算时间
				printf("%d %d %d\n", elevatorfloor, time, people);	
			}
			//如果前往目标楼层
			else if(mindistance > mindistance2){
			for (i=0; i<10; i++){				//专用于解决目的楼层相同时的人数bug
				if (aim2floor[save2] == aim2floor[i] ){
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
				elevatorfloor = closestfloor2;
				people -= number;
				number = 0;
				time += mindistance2;
				printf("%d %d %d\n", elevatorfloor, time, people);
			}
			//distance一致情况下放弃前往起始楼层。前往目的楼层，people-n
			else if(mindistance == mindistance2 && closestfloor2 != closestfloor){
				for (i=0; i<10; i++){				//专用于解决目的楼层相同时的人数bug
					if (aim2floor[save2] == aim2floor[i] ){
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
				elevatorfloor = closestfloor2;
				people -= number;
				number = 0;
				time += mindistance2;
				printf("%d %d %d\n", elevatorfloor, time, people);
			
			}
			//目的楼层与起始楼层一致同时前往
			else if(mindistance == mindistance2 && closestfloor2 == closestfloor){
				for (i=0; i<10; i++){				//专用于解决目的楼层相同时的人数bug
					if (aim2floor[save2] == aim2floor[i] ){
						memory[i] = i;
						number ++;
					}else{
						memory[i] = -1;
					}
				}
				aim2floor[save] = aimfloor[save];
				beginfloor[save] = -20;	
				for (i=0; i<10; i++){
					if(memory[i] != -1){
						aim2floor[memory[i]] = -20;
				    }
				}
				elevatorfloor = closestfloor;
				time += mindistance;
				people -=number;
				number = 0;
				people +=1;
				printf("%d %d %d\n", elevatorfloor, time, people);	
			}
			//让程序终止

//调试				for( i=0; i<10; i++){
//	printf("从这行开始%d %d %d %d\n",i,beginfloor[i], aimfloor[i],aim2floor[i]);
//	}
			int count;
			i = 0;
			for ( i=0;i<10;i++){
				count++;
				if (beginfloor[i]!=-20 || aim2floor[i]!= -20)
				break;
			}
//调试			printf("count的值是%d\n",count);
			if (count == 10)
			break;			
			count = 0;
		}
	//超载时
		while(people > 3){
			for ( i=0; i<10; i++){			//超载时和aim2floor[i]进行比对
				distance2 =count(elevatorfloor,aim2floor[i]);
				if (distance2 < mindistance2){
					mindistance2 = distance2;
					closestfloor2 = aimfloor[i];
					save2 = i;					//记录i的值
				}
			}
			for (i=0; i<10; i++){				//专用于解决目的楼层相同时的人数bug
				if (aim2floor[save2] == aim2floor[i] ){
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
			elevatorfloor = closestfloor2;
			people -= number;
			number = 0;
			time += mindistance2;
			printf("%d %d %d\n", elevatorfloor, time, people);
		}
	//在大的while循环中再让count停止
		int cnt =0;
			i = 0;
			for ( i=0;i<10;i++){
				cnt++;
				if (beginfloor[i]!=-20 || aim2floor[i]!= -20)
				break;
			}
			if (cnt == 10)
			break;			
			cnt = 0;	
	}
//	//调试
//	for( i=0; i<10; i++){
//	printf("从这行开始%d %d %d %d\n",i,beginfloor[i], aimfloor[i],aim2floor[i]);
//	}

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
