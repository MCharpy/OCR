#include <stdio.h>
#include <stdlib.h>

float rtab[16];

void _Save(int a,int b,float tab[],char p[])
{
	FILE *fp;
	fp = fopen(p,"w");
	fprintf(fp,"%i%s%i%s",a,"\n",b,"\n");
	for(int i = 0 ; i < a*b;i++)
	{
		fprintf(fp,"%f%s",tab[i],"\n");
	}
	fclose(fp);
}

void _Load(char p[])
{
	char e[1];
	char b[1];
	float tab[16];
	char a[1];
	FILE *fp;
	fp = fopen(p,"r");
	fgets(a,5,fp);
	int c = atoi(a);
	fgets(b,5,fp);
	int d = atoi(b);
	char s[10] = "";
	for(int i = 0; i < c*d;i++)
	{
		fgets(e,15,fp);
		rtab[i] = atof(e);
	}
	fclose(fp);	
}


int main () {
	char fp[] = "file.txt";
	int a = 2;
	int b = 2;
	float tab[] = {1,2,3,4};
	_Save(a,b,tab,fp);
	_Load(fp);
	return(0);
}
