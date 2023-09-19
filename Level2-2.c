#include<stdio.h>

int main()
{
    int beginfloor[10];	//乘客初始楼层
	int begin2floor[10];//time到达后录入初始楼层
	int aimfloor[10];	//乘客目标楼层
	int aim2floor[10]; //乘客进入后录入目标楼层
	int ti[10];			//乘客时间
	int updown[10];		//录入数据判断乘客是上行还是下行
	int i = 0;
	int elevator1floor = 0;	//电梯1现处楼层
	int elevator2floor = 0;	//电梯2现处楼层
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
	
//	调试
	printf("\tbegin\tbegin2\taim\taim2\tti\tupdown[i]\n");
	for( i=0; i<10; i++){
			printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i,beginfloor[i],begin2floor[i],aimfloor[i],aim2floor[i], ti[i],updown[i]);
	}	
	return 0;
}