#include<stdio.h>
int count(int a, int b); //���������㺯��
int nextfloor(int efloor,int closestfloor); //���������һ��ǰ��¥�㺯��

int main()
{
	int time = 0;
	int people = 0;
	int	beginsave[100],aimsave[100],ti[100];	//��������
	int elevatorfloor;
	int total = 0;		//���ڼ�¼һ�������˶��ٸ�����
	int beginfloor[100],aimfloor[100];			//������ʱ���¼������
	int jilu = 0;		//���ڼ�¼Ŀǰ¼�뵽�ĸ�����
	int distance1 = 0, distance2 = 0;	
	int mindistance1 = 10, mindistance2 = 10;	//��̾���
	int closestfloor,closestfloor1,closestfloor2; 	//������Ҫǰ����¥��
	int a=0,b=0;				//�жϱ�������ʵ������
	int cnt = 0;				//�����������ʱʹ��
	
	
	//����¼��
	printf("�������elevator��ʼ�������ݡ���������󰴻س�������-1 -1 -1�ٰ��س����˳�����\n");
	printf("��һ����������ݼ��ʱ�䴦ӦΪ0\n");
	printf("elevator:");
	scanf("%d\n",&elevatorfloor);
	int i;
	for( i=0; i<100; i++){	
		scanf("%d %d %d", &beginsave[i], &aimsave[i], &ti[i]);
		total++;
		if (beginsave[i] == -1 &&aimsave[i] == -1 && ti[i] == -1){ //�ֶ�����-1 -1 -1�������� ������10����
			total--;
			break;
		}
	}

	//�����ʱ��ת��Ϊʵ��ʱ��
	for (i=0; i<total-1; i++){
		ti[i+1] +=ti[i];	
	}

	//������aimfloor��ʼֵתΪ-20������Ӱ��֮��ıȶ�
	for( i=0; i<total; i++){
		aimfloor[i] = -20;
		beginfloor[i] = -20;
	}
	//��ʼ��������beginfloor���бȶ�
st:	for (i=jilu; i< jilu + 10; i++){		//��������ʱ���¼������
		if (time == ti[jilu]){
			jilu++;
			beginfloor[i] = beginsave[i];
		}
		if (time != ti[jilu])
			break;
	}
	for ( i=0; i<jilu; i++){ 	//��beginfloor[i]���бȶ�
		distance1 = count(elevatorfloor,beginfloor[i]);
		if (distance1 < mindistance1){
			mindistance1 = distance1;
			closestfloor = beginfloor[i];	//��¼�����¥��
		}
		if (mindistance1 == 0){			//���ô�������¥����������
			people ++;
			printf("%d %d %d\n", elevatorfloor, time, people);
			beginfloor[i] = -20;			//ɾ������
			aimfloor[i] = aimsave[i];		//¼��Ŀ��¥��
			closestfloor = aimfloor[i];		//ǰ��Ŀ��¥��
			mindistance1 = 10;				//���������������ѭ��
			time++;
			break;							
		}
	}
	if (mindistance1 != 0){
		time++;
	}	
//��ʽ����ѭ��
	while(people> -1 ){
		mindistance1 = 10,mindistance2 = 10;	//���������ѭ��
		//��ʼ¼������
		for (i=jilu; i< jilu + 10; i++){
			if (time == ti[jilu]){
				jilu++;
				beginfloor[i] = beginsave[i];
			}
			if (time != ti[jilu])
				break;
		}
		//ǰ��һ¥���ȶ��Ƿ񵽴��κγ�ʼ¥���Ŀ��¥��
		elevatorfloor = nextfloor(elevatorfloor, closestfloor);	//ǰ��һ��
		for ( i= 0; i<jilu; i++){
			if (people < 4){				//δ����ʱ�ȶ��Ƿ񵽴��˳�ʼ¥��
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
		if (a == 1 || b == 1){			//��������һ���������������
			printf("%d %d %d\n", elevatorfloor, time, people);
			a = 0;
			b = 0;
		}
		
		//���������ϣ���������
		for (i=0; i<jilu; i++){
			if (ti[jilu-1] < ti[total-1] || beginfloor[i] != -20 || aimfloor[i] != -20 )
				break;
			cnt++;
		}	
		if (cnt == total)
			break;
		cnt = 0;
		//�����ʱǡ�ó�������ڣ����г˿�������ϵ����г˿ͽ�Ҫ���У�ʱ��ֱ�ӱ�Ϊ�Ǹ��˿͵�ʱ�䣬goto����ǰ����ʼ����
		for (i=0; i<jilu; i++){
			if (ti[jilu-1] != ti[total-1] || beginfloor[i] != -20 || aimfloor[i] != -20 ){
				break;
			}
			cnt++;
		}
		if (cnt == jilu){
			jilu++;
			time = ti[jilu];
			goto st;				//stΪstart����д,���س�ʼ��
		}
		cnt = 0;
	//������һ�ֵ�¥������
		//δ����ʱ�Գ�ʼ¥����б���
		if (people < 4){
			for ( i=0; i<jilu; i++){ 	//��beginfloor[i]���бȶ�
				distance1 = count(elevatorfloor,beginfloor[i]);
				if (distance1 < mindistance1){
					mindistance1 = distance1;
					closestfloor1 = beginfloor[i];	//��¼�����¥��
				}
			}
		}
		//�����Ƿ��ض�Ŀ��¥����б���
		for (i=0; i<jilu; i++){		//��aimfloor[i]���бȶ�
			distance2 = count(elevatorfloor,aimfloor[i]);
			if (distance2 < mindistance2){
				mindistance2 = distance2;
				closestfloor2 = aimfloor[i];	//��¼�����¥��
			}
		}
		if (mindistance1 < mindistance2){		//�жϽ�����ǰ���ĸ�¥��
			closestfloor = closestfloor1;
		}else{
			closestfloor = closestfloor2;
		}
	time++;
	}
//����
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