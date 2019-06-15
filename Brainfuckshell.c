#include<stdio.h>
#include<string.h>
char Command[1024]={'\0'},Paperstripe[1024]={'\0'},*ptr;
int Loop[1024]={0};
void Domain(int depth)
{
	char enterrelease;
	if(Command[depth]=='\0')
		return;
	switch(Command[depth])
	{
		case '>':ptr++;Domain(depth+1);break;
		case '<':ptr--;Domain(depth+1);break;
		case '+':(*ptr)++;Domain(depth+1);break;
		case '-':(*ptr)--;Domain(depth+1);break;
		case ',':printf("Input>> ");*ptr=getchar();enterrelease=getchar();Domain(depth+1);break;
		case '.':printf("Output>> %c\n",*ptr);Domain(depth+1);break;
		case '[':
				for(int i=0;i<*ptr;i++)
					Domain(depth+1);
			Domain(Loop[depth]+1);break;
		case ']':return;break;
		default:break;
	}
}
int Check()
{
	int cntleft=0,cntright=0;
	int flag=0;
	for(int i=0;Command[i]!='\0';i++)
		if(Command[i]!=','&&Command[i]!='.'&&Command[i]!='+'&&Command[i]!='-'&&Command[i]!='>'&&Command[i]!='<'&&Command[i]!='['&&Command[i]!=']')
		{
			printf("Code>> [Error] Command[%d]: %c <<Not a correct charater.\n",i,Command[i]);
			flag=1;
		}
	for(int i=0;Command[i]!='\0';i++)
	{
		if(Command[i]=='[')
			cntleft++;
		if(Command[i]==']')
			cntright++;
		if(Command[i]==']'&&cntleft<cntright)
		{
			printf("Code>> [Error] Command[%d]: ']' <<Lack of enough '[' .\n",i);
			flag=1;
		}
	}
	if(cntleft==cntright)
	{
		if(!flag)
			printf("Code>> [Complete] 0 error(s),0 warning(s).\n");
	}
	else
	{
		printf("Code>> [Error] Command   <<Lack of %d '%c'(s)\n",cntleft>cntright? cntleft-cntright:cntright-cntleft,cntleft>cntright? ']':'[');
		flag=1;
	}
	if(flag)
		return 0;
	else
		return 1;
}
int main()
{
	while(1)
	{
		printf("Code>> ");gets(Command);
		if(Command[0]=='q'&&Command[1]=='u'&&Command[2]=='i'&&Command[3]=='t'&&Command[4]=='('&&Command[5]==')'&&Command[6]=='\0')
			break;
		if(!Check())
			continue;
		ptr=Paperstripe;
		for(int i=0;Command[i]!='\0';i++)
			if(Command[i]==']')
				for(int j=i;j>=0;j--)
					if(Command[j]=='['&&Loop[j]==0)Loop[j]=i;
		Domain(0);printf("\n");
		for(int i=0;i<1024;i++)	Paperstripe[i]=0;
	}
	return 0;
}
