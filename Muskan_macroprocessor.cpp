#include<stdio.h>
#include<string.h>

int n,p,m,g;

struct MDT
{
	char opcode[10];
	char operand[50];
}mdt[50];

struct MNT
{
	char name[10];
	int start;
	int end;
}mnt[5];

struct ALA1
{
	char arg[10];
}ala[5];

struct ALA2
{
	char parameter[10];
	char val[4];
}pt[5];

int check_macro(char x[20])
{
	int i;
	for(i=0;i<m;i++)
	{
		if(strcmp(mnt[i].name,x)==0)
		return i;
	}
	return -1;
}

int check_parameter(char x[50])
{
	int i;
	for(i=0;i<p;i++)
	{
		if(strcmp(pt[i].parameter,x)==0)
		return i;
	}
	return -1;
}

void store()
{
	FILE *f,*fp;
	int k,i,j;
	char a[20],b[20],c[40],temp[20],lab[20];
	n=0; p=0; m=0; g=0;
	f=fopen("input.txt","r");
	fp=fopen("output.txt","w");
	while(!feof(f))
	{
		fscanf(f,"%s%s%s",a,b,c);
		if(strcmp(b,"MACRO")==0)
		{
			strcpy(mnt[m].name,a);
			mnt[m].start=0;
			k=1;
			j=0;
			i=0;
			while(c[i]!='\0')
			{
				if(c[i]!=',')
				{
					temp[j]=c[i];
					j++;
				}
				else
				{
					temp[j]='\0';
					j=0;
					strcpy(pt[p].parameter,temp);
					pt[p].val[0]='#';
					pt[p].val[1]=p+49;
					pt[p].val[2]='\0';
					p++;
				}
				i++;
			}
			temp[j]='\0';
			strcpy(pt[p].parameter,temp);
			pt[p].val[0]='#';
			pt[p].val[1]=p+49;
			pt[p].val[2]='\0';
			p++;
			strcpy(mdt[n].opcode,b);
			strcpy(mdt[n].operand,c);
			n++;
		}
		else if(k==1)
		{
			i=check_parameter(c);
			strcpy(mdt[n].opcode,b);
			if(i==-1)
			 strcpy(mdt[n].operand,c);
			else 
				strcpy(mdt[n].operand,pt[i].val);
			n++;
			if(strcmp(b,"MEND")==0)
			{
				k=0;
				mnt[m].end=n-1;
				m++;
			}
		}
		else if((check_macro(b))!=-1)
		{
			i=0;
			g=0;
			j=0;
			while(c[i]!='\0')
			{
				if(c[i]!=',')
				{
					temp[j]=c[i];
					j++;
				}
				else
				{
					temp[j]='\0';
					j=0;
					strcpy(ala[g].arg,temp);
					
					g++;
					
				}
				i++;
			}
			temp[j]='\0';
			strcpy(ala[g].arg,temp);
			g++;
			strcpy(a,"NULL");
			for(i=1;i<n-1;i++)
			{
				if(mdt[i].operand[0]=='?')
				{
					j=mdt[i].operand[1]-49;
					strcpy(temp,ala[j].arg);
				}
				else
					strcpy(temp,mdt[i].operand);
				fprintf(fp,"%s\t%s\t%s\n",a,mdt[i].opcode,temp);
			}
		}
		else
		{
			fprintf(fp,"%s\t%s\t%s\n",a,b,c);
		}
	}
		fclose(f);
		fclose(fp);
}
 main()
{
	int i;
	store();
	printf("\n MDT:\n");
	for(i=0;i<n;i++)
	{
		printf("%s\t%s\n",mdt[i].opcode,mdt[i].operand);
	}
	printf("\n MNT:\nNAME\t START\t END\n");
	for(i=0;i<m;i++)
	{
		printf("%s\t%d\t%d\n",mnt[i].name,mnt[i].start,mnt[i].end);
	}
	printf("\n ALA: \nPosition\t Argument\n");
	for(i=0;i<g;i++)
	{
		printf("%d\t\t%s\n",i+1,ala[i].arg);
	}
}
