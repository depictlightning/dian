#include<stdio.h>
int count(int a, int b); //���������㺯��

// �����ʽ��1 2 ��ʾ��ʼ¥���Ŀ��¥�� 
//	���� -1 -1��������	eg.  2 3
//							5 9
//							6 8
//							-1 -1
int main()
{
	int beginfloor[10];	//�˿ͳ�ʼ¥��
	int aimfloor[10];	//�˿�Ŀ��¥��
	int aim2floor[10]; //�˿ͽ����¼��Ŀ��¥��
	int i = 0;
	int elevatorfloor = 1;	//�����ִ�¥��
	int closestfloor = 0;	//���¥�㣨�����ݼ���ǰ��¥�㣩
	int mindistance = 10;	//��̾��루����ʱ��ͳ�ƣ�
	int people = 0;	
	int time = 0;		

	printf("��������󰴻س�������-1 -1 -1�ٰ��س����˳�����\n");
	
//�����������ֵ��ʼ��Ϊ-20������Ժ����������Ӱ�죩	
	for( i=0; i<10; i++){	
		beginfloor[i] = -20;
		aimfloor[i] = -20;
		aim2floor[i] = -20;
	}

//����¼��
	for( i=0; i<10; i++){	
	scanf("%d %d", &beginfloor[i], &aimfloor[i]);
	if (beginfloor[i] == -1 &&aimfloor[i] == -1){ //�ֶ�����-1 -1�������� ������10����
		beginfloor[i] = -20;
		aimfloor[i] = -20;
		break;
		}
	}

//	��ӡ���ݳ�ʼ¥��(���һ¥û���ϵ��ݵ������)
	int cal = 0;
	for( i=0; i<10; i++){	
		if (beginfloor[i] == 1)
		cal +=1;		//cal�����ж��Ƿ�һ¥�������ݣ����Ƿ���Ҫ��ӡ�� 1 0 0
	} 
	if( cal == 0){
		printf("%d %d %d\n", elevatorfloor, time, people);
	}
//������̾������(��ʼ��¥��Ѱ�ң�
	int distance =10;
	int save;
	for ( i=0; i<10; i++){ 	//��һ��ֻ��beginfloor[i]���бȶ�
			distance = count(elevatorfloor,beginfloor[i]);
			if (distance < mindistance){
				mindistance = distance;
				closestfloor = beginfloor[i];
				save = i;						//��¼i��ֵ
			}
		}
	aim2floor[save] = aimfloor[save];		//¼��Ŀ��¥��
	beginfloor[save] = -20;			//ɾ������
	elevatorfloor = closestfloor;	//����¥��
	people +=1;						//��������
	time += mindistance;			//����ʱ��
	printf("%d %d %d\n", elevatorfloor, time, people);

	int distance2 =0;
	int save2 = 0;
	int mindistance2 = 10;
	int	closestfloor2 = 10;			//����2�±��ʾ��beginfloor[i]ʱ�ıȶ�������
	int memory[10];				//���ڽ�����n���˿�Ŀ��¥��һ��ʱ����ɾ��
	int number = 0;						//���ڽ�����n���˿�Ŀ��¥��һ��ʱpeople-n
	
	while(people > -1){
		while (people < 4 ){	
			mindistance = 10;
			mindistance2 =10;	
			for ( i=0; i<10; i++){			//δ����ʱ��beginfloor[i]�ȶ�
				distance =count(elevatorfloor,beginfloor[i]);
				if (distance < mindistance){
					mindistance = distance;
					closestfloor = beginfloor[i];
					save = i;						//��¼i��ֵ
				}
			}
			
			for ( i=0; i<10; i++){			//δ����ʱ��aim2floor[i]����
				distance2 =count(elevatorfloor,aim2floor[i]);
				if (distance2 < mindistance2){
					mindistance2 = distance2;
					closestfloor2 = aimfloor[i];
					save2 = i;					//��¼i��ֵ������¼��Ŀ��¥�㣩
				}				
				
			}
			//distance��distance2���бȽ�
			//���ǰ����ʼ¥��
			if( mindistance < mindistance2){			
				aim2floor[save] = aimfloor[save];		//¼��Ŀ��¥��
				beginfloor[save] = -20;			//ɾ������
				elevatorfloor = closestfloor;	//����¥��
				people +=1;						//��������
				time += mindistance;			//����ʱ��
				printf("%d %d %d\n", elevatorfloor, time, people);	
			}
			//���ǰ��Ŀ��¥��
			else if(mindistance > mindistance2){
			for (i=0; i<10; i++){				//ר���ڽ��Ŀ��¥����ͬʱ������bug
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
			//distanceһ������·���ǰ����ʼ¥�㡣ǰ��Ŀ��¥�㣬people-n
			else if(mindistance == mindistance2 && closestfloor2 != closestfloor){
				for (i=0; i<10; i++){				//ר���ڽ��Ŀ��¥����ͬʱ������bug
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
			//Ŀ��¥������ʼ¥��һ��ͬʱǰ��
			else if(mindistance == mindistance2 && closestfloor2 == closestfloor){
				for (i=0; i<10; i++){				//ר���ڽ��Ŀ��¥����ͬʱ������bug
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
			//�ó�����ֹ

//����				for( i=0; i<10; i++){
//	printf("�����п�ʼ%d %d %d %d\n",i,beginfloor[i], aimfloor[i],aim2floor[i]);
//	}
			int count;
			i = 0;
			for ( i=0;i<10;i++){
				count++;
				if (beginfloor[i]!=-20 || aim2floor[i]!= -20)
				break;
			}
//����			printf("count��ֵ��%d\n",count);
			if (count == 10)
			break;			
			count = 0;
		}
	//����ʱ
		while(people > 3){
			for ( i=0; i<10; i++){			//����ʱ��aim2floor[i]���бȶ�
				distance2 =count(elevatorfloor,aim2floor[i]);
				if (distance2 < mindistance2){
					mindistance2 = distance2;
					closestfloor2 = aimfloor[i];
					save2 = i;					//��¼i��ֵ
				}
			}
			for (i=0; i<10; i++){				//ר���ڽ��Ŀ��¥����ͬʱ������bug
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
	//�ڴ��whileѭ��������countֹͣ
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
//	//����
//	for( i=0; i<10; i++){
//	printf("�����п�ʼ%d %d %d %d\n",i,beginfloor[i], aimfloor[i],aim2floor[i]);
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
