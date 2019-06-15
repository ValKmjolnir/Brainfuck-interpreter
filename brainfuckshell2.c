#include<stdio.h>
#include<string.h>
char Command[4096],PaperStripe[4096],*ptr,enterrelease;
int BracketPair[4096],LoopNum[4096];
int Check()
{
	int cntleft=0,cntright=0,flag=0;
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
		if(Command[i]==']'&&cntleft<cntright){printf("Code>> [Error] Command[%d]: ']' <<Lack of enough '[' .\n",i);flag=1;}
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
	if(flag)	return 0;
	else	return 1;
}
void Code()
{
	int runcnt=0;
	if(!Check())	return;
	for(int i=0;Command[i]!='\0';i++)
	{
		if(Command[i]=='[')	BracketPair[i]=65535;
		if(Command[i]==']')
			for(int j=i;j>=0;j--)
				if(Command[j]=='['&&BracketPair[j]==65535){BracketPair[i]=j;BracketPair[j]=i;break;}
	}
	for(int i=0;Command[i]!='\0';i++)
		switch(Command[i])
		{
			case '>':ptr++;break;
			case '<':ptr--;break;
			case '+':(*ptr)++;break;
			case '-':(*ptr)--;break;
			case ',':printf("Input>> ");*ptr=getchar();enterrelease=getchar();break;
			case '.':printf("Output>> %c\n",*ptr);break;
			case '[':LoopNum[BracketPair[i]]=(*ptr)-1;runcnt=0;break;
			case ']':
				if(LoopNum[i]!=0)
				{
					runcnt++;LoopNum[i]--;i=BracketPair[i];//then i++
					if(runcnt>1073741824){printf("Code>> [Failed] << Too much time used to run this programme.\n");return;}
					break;
				}
				break;
		}
	return;
}
int main()
{
	while(1)
	{
		ptr=PaperStripe;
		for(int i=0;i<4096;i++)
		{
			Command[i]=PaperStripe[i]='\0';
			BracketPair[i]=LoopNum[i]=0;
		}
		printf("Code>> ");gets(Command);
		if(Command[0]=='q'&&Command[1]=='u'&&Command[2]=='i'&&Command[3]=='t'&&Command[4]=='('&&Command[5]==')'&&Command[6]=='\0')break;
		Code();
	}
	return 0;
}
