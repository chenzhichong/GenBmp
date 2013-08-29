#include <stdio.h>
#include <math.h>
#include "learn.h"
#include <time.h>
#define WIDTH 480
#define HEIGH 800
int main()
{
	//ClImage* img = clLoadImage("d:/test.bmp");
	/*struct tm *local;
	char tmpbuf[128];
	char file_name[256];
	time_t t;
	t=time(NULL);
	local=localtime(&t);
	strftime( tmpbuf, 128, "%Y-%m-%d-%H-%M-%S", local);
	//printf(tmpbuf);
	sprintf(file_name,"screen-%s.bmp", tmpbuf);
	ClImage* img = clLoadRaw("fb0", WIDTH, HEIGH, 4);
	if (clSaveImage(file_name, img))
		printf("success!!");*/
	FILE* fp;
	fp = fopen("fb0", "rb");  
	/*int num;
	char file_name[256];
	printf("请输入：");
	scanf("%d", &num);*/
	/*for (num = 0; num < 49; num++)
	{
	ClImage* img = clLoadBlockRaw(fp, 67, 67, 4, 4, 196, num);
	sprintf(file_name, "%d.bmp", num);
	if (img)
		if (clSaveImage(file_name, img))
			printf("success!!");
	}*/
	double simlarval;
	printf("please entry simlarval:");
	scanf("%lf", &simlarval);
	while (1)
	{
	int num;
	/*for(num =0; num<49;num++)
	{*/
	int sum = 0;
	printf("please entry num:");
	scanf("%d", &num);
	ClImage* img = clLoadBlockRaw(fp, 67, 67, 4, 4, 196, num);
	//ClImage* img1 = clLoadBlockRaw(fp, 67, 67, 4, 4, 196, 2);
	//double* hd = getHistogramData(img);
	//double* hd1 = getHistogramData(img1);
	int i = 0;
	double simlar;
	for (i = 0; i<49; i++)
	{
		simlar = modelMatch(getHistogramData(img), getHistogramData(clLoadBlockRaw(fp, 67, 67, 4, 4, 196, i)));
		if (simlar >= simlarval)
		//if (1)
		{
			printf("%d.bmp vs %d.bmp simlar:%f\n", num, i, simlar);
			sum++;
		}
	}
	/*if (img)
		if (clSaveImage("confirm.bmp", img))
			printf("success!!");*/
	printf("toal=%d\n", sum);
	}

	return 0;
}
