#include<stdio.h>
int count(int a, int b); //定义距离计算函数
/*等待出现elevator后开始输入
输入格式：1 2 3表示初始楼层、目标楼层 和时间	
	输入-1 -1 -1表示输入结束 
	eg. elevator(系统自带）:5
		8 5 0
		7 4 6
		-1 -1 -1 
*/
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
	
	int jilu = 0;	//用于记录还有哪些ti[]的时间没有录入
	int save = 0;
	int testtime = 0;	//到达时间后和目前的ti[jilu]进行比较
	int testfloor;	//用于testtime > ti[jilu]的情况,判断是否前往新呼叫乘客的初始楼层
	int testdistance;		//比较testdistance 和mindistance的区别判断优先前往哪个楼层
	int distance =10;
//电梯初始化（初始化与后面的代码高度重复但又有细微差别)前往beginfloor(可能有多个人在0s呼叫）
	while (people == 0){		
		for( i=jilu; i<10; i++){
			if (ti[i] == 0){
				begin2floor[i] = beginfloor[i];		//录入初始楼层
				jilu = i + 1;
			}
			if (ti[i+1] != 0)
			break;
		}
		for ( i=0; i<10; i++){ 	//第一次只对begin2floor[i]进行比对
			distance = count(elevatorfloor,begin2floor[i]);
			if (distance < mindistance){
				mindistance = distance;
				closestfloor = begin2floor[i];	//记录最近的楼层
				save = i;
			}
		}
		testtime = time + mindistance;		
		if( testtime <= ti[jilu] ){	//正常前往楼层（小于的情况）且是唯一进行printf的	
			time = testtime;
			people += 1;
			begin2floor[save] = -20;			//删除初始楼层
			aim2floor[save] = aimfloor[save];	//录入目标楼层
			elevatorfloor = closestfloor;		//计算楼层
			printf("%d %d %d\n", elevatorfloor, time, people);
			if( testtime == ti[jilu] ){
				begin2floor[jilu] = begin2floor[jilu];	//与小于相比增加了ti[]楼层录入
				jilu++;									//转到下一个ti[]
			}	
		}
			
		else if( testtime > ti[jilu] )		//大于的情况，判断是否前往beginfloor
		{
			if ( elevatorfloor > closestfloor){	
				testfloor = elevatorfloor - (ti[jilu]-time);
			}
			else if( elevatorfloor < closestfloor){
				testfloor = elevatorfloor + (ti[jilu]-time);	
			}		
			time = time + (ti[jilu] - time);		//时间的增加
			elevatorfloor = testfloor;			//电梯处于新的楼层
			testdistance = count(elevatorfloor,beginfloor[jilu]);
			mindistance = count(elevatorfloor,closestfloor);
		
			if (testdistance >= mindistance){	//前往原楼层(但不输出数据）
				begin2floor[jilu] = beginfloor[jilu];		//录入begin2floor的数据
				jilu++;									//前往下一个ti[i]								
			}
			else if(testdistance < mindistance){	//前往新的楼层
				mindistance = testdistance;					//新的最短距离
				begin2floor[jilu] = beginfloor[jilu];		//录入begin2floor的数据
				closestfloor = begin2floor[jilu];			//新的目标楼层
				jilu++;										//前往下一个时间
				save++;										//save++录入新的初始楼层数据
			}
		}
	}

//完成初始化后回归Level1-3的逻辑
	int distance2 =0;
	int save2 = 0;
	int mindistance2 = 10;
	int	closestfloor2 = 10;			//所有2下标表示和beginfloor[i]时的比对作区分
	int memory[10];				//用于接下来n个乘客目的楼层一致时数据删除
	int number = 0;						//用于接下来n个乘客目的楼层一致时people-n
	mindistance = 10;
	while(people > -1){
		if (ti[jilu] == -20)				//即所有begin2floor都已经被录入，直接break.之后和Level1-3程序完全一致
			break;	
		while (people < 4 ){
			if (ti[jilu] == -20)				//即所有begin2floor都已经被录入，直接break.之后和Level1-3程序完全一致
				break;
//调试
//		printf("\tbegin\tbegin2\taim\taim2\tti\ttime\tti[jilu]\n");
//		for( i=0; i<10; i++){
//			printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i,beginfloor[i],begin2floor[i],aimfloor[i],aim2floor[i], ti[i],time,ti[jilu]);
//		}	
			mindistance = 10;
			mindistance2 = 10;
			for ( i=0; i<10; i++){			//未超载时对begin2floor[i]比对
				distance =count(elevatorfloor,begin2floor[i]);
				if (distance < mindistance){
					mindistance = distance;
					closestfloor = begin2floor[i];
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
			
			if (mindistance > mindistance2){	//重新修改testtime的计算方式
				testtime = time + mindistance2;
			}
			else{
				testtime = time + mindistance;
			}
			
	//将初始化代码和Level1-3代码结合
			if (testtime <= ti[jilu]){		
				//distance和distance2进行比较
				//如果前往起始楼层
				if( mindistance < mindistance2){			
					aim2floor[save] = aimfloor[save];		//录入目标楼层
					begin2floor[save] = -20;			//删除数据
					elevatorfloor = closestfloor;	//计算楼层
					people +=1;						//计算人数
					time += mindistance;			//计算时间
					printf("%d %d %d\n", elevatorfloor, time, people);	
				}
				//如果前往目标楼层
				else if(mindistance > mindistance2){
				for (i=0; i<10; i++){				//专用于解决目的楼层相同时的人数bug
					if (aim2floor[save2] == aim2floor[i] ){	
						number ++;						//通过number和memory[i]实现人数统计和数据删除
						memory[i] = i;
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
					begin2floor[save] = -20;	
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
				if (testtime == ti[jilu]){				
					begin2floor[jilu] = beginfloor[jilu];	//与小于相比增加了ti[]楼层录入
					jilu++;	
				}	
			} 
			else if(testtime > ti[jilu]){
				if ( elevatorfloor > closestfloor){		//计算testfloor
					testfloor = elevatorfloor - (ti[jilu]-time);
				}
				else if( elevatorfloor < closestfloor){
					testfloor = elevatorfloor + (ti[jilu]-time);	
				}
				time = time + (ti[jilu] - time);		//时间的增加
				elevatorfloor = testfloor;			//电梯处于新的楼层	
			//同Level1-3逻辑，继续mindistance和mindistance2的判断	
				if( mindistance > mindistance2){		//把所有下标换为2，其他不变
					testdistance = count(elevatorfloor,beginfloor[jilu]);
					mindistance2 = (elevatorfloor,closestfloor2);
					if (testdistance >= mindistance2){	//前往原楼层(但不输出数据）
						begin2floor[jilu] = beginfloor[jilu];		//录入begin2floor的数据
						jilu++;									//前往下一个ti[i]								
					}
					else if(testdistance < mindistance2){
						mindistance2 = testdistance;					//新的最短距离
						begin2floor[jilu] = beginfloor[jilu];		//录入begin2floor的数据
						closestfloor2 = begin2floor[jilu];			//新的目标楼层
						jilu++;										//前往下一个时间
						save++;	
					}
				}
				else if( mindistance <= mindistance2){
					testdistance = count(elevatorfloor,beginfloor[jilu]);
					mindistance2 = (elevatorfloor,closestfloor2);
					if (testdistance >= mindistance){	//前往原楼层(但不输出数据）
						begin2floor[jilu] = beginfloor[jilu];		//录入begin2floor的数据
						jilu++;									//前往下一个ti[i]								
					}
					else if( testdistance < mindistance ){
						mindistance2 = testdistance;					//新的最短距离
						begin2floor[jilu] = beginfloor[jilu];		//录入begin2floor的数据
						closestfloor2 = begin2floor[jilu];			//新的目标楼层
						jilu++;										//前往下一个时间
						save++;		
					}
				}		
			}
		}
	}
		while(people > 3){
			if (ti[jilu] == -20)				//即所有begin2floor都已经被录入，直接break.之后和Level1-3程序完全一致
				break;
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
			if ( time >= ti[jilu]){		//录入按下按键的乘客的初始楼层
				begin2floor[jilu] = beginfloor[jilu];
				if (time == ti[jilu]){	//如果等于的情况,people+1;
					people++;
					begin2floor[jilu] = -20;
				}
			jilu++;
			printf("%d %d %d\n", elevatorfloor, time, people);	 
			}	
		}
				
//之后完全模拟Level1-3
	while(people > -1){
		
		while (people < 4 ){
//调试
		// printf("\tbegin\tbegin2\taim\taim2\tti\ttime\tti[jilu]\n");
		// for( i=0; i<10; i++){
		// 	printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i,beginfloor[i],begin2floor[i],aimfloor[i],aim2floor[i], ti[i],time,ti[jilu]);
		// }
			mindistance = 10;
			mindistance2 =10;	
			for ( i=0; i<10; i++){			//未超载时对beginfloor[i]比对
				distance =count(elevatorfloor,begin2floor[i]);
				if (distance < mindistance){
					mindistance = distance;
					closestfloor = begin2floor[i];
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
				begin2floor[save] = -20;			//删除数据
				elevatorfloor = closestfloor;	//计算楼层
				people +=1;						//计算人数
				time += mindistance;			//计算时间
				printf("%d %d %d\n", elevatorfloor, time, people);	
			}
			//如果前往目标楼层
			else if(mindistance > mindistance2){
			for (i=0; i<10; i++){				//专用于解决目的楼层相同时的人数bug
				if (aim2floor[save2] == aim2floor[i] ){	
					number ++;
					memory[i] = i;						//通过number和memory[i]实现人数统计和数据删除
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
			

//调试				for( i=0; i<10; i++){
//	printf("从这行开始%d %d %d %d\n",i,beginfloor[i], aimfloor[i],aim2floor[i]);
//	}	
		//让程序终止
			int count;
			i = 0;
			for ( i=0;i<10;i++){
				count++;
				if (begin2floor[i]!=-20 || aim2floor[i]!= -20)
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
				if (begin2floor[i]!=-20 || aim2floor[i]!= -20)
				break;
			}
			if (cnt == 10)
			break;			
			cnt = 0;	
		}
//	调试
//	printf("\tbegin\tbegin2\taim\taim2\tti\n");
//	for( i=0; i<10; i++){
//			printf("%d\t%d\t%d\t%d\t%d\t%d\n",i,beginfloor[i],begin2floor[i],aimfloor[i],aim2floor[i], ti[i]);
//	}	
//	// printf("jilu的值为：%d",jilu);
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
