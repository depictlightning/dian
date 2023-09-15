#include<stdio.h>

int main()
{
	int bf; //人所在的楼层
	int tf;	//人的终点楼层
	int ef;	//电梯现在所在楼层

//请输入文件地址
	FILE *fp = fopen("D:\\dian\\Level1-2.txt","r");
	fscanf(fp,"%d\n", &ef);
	fscanf(fp,"%d %d",&bf, &tf);
	fclose(fp);
	
	int time = 0;	//当下运行时间
	int people = 0;	//当下人数
	
	printf("%d %d %d\n", ef, time, people);	//电梯初始楼层时
	
	if (ef > bf){
		time = ef - bf;
	}else{
		time = bf - ef;
	}
	people += 1;
	printf("%d %d %d\n", bf, time, people);	//到达乘客楼层时
	
	int final = 0;
	if ( tf > bf){
		final = tf - bf;
		time += final;
	}else{
		final = bf - tf;
		time += final;
	}
	people -= 1;	
	printf("%d %d %d\n", tf, time, people);	//到达终点楼层
	
	
	return 0;
}




