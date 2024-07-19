#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#include<unistd.h>
void ballss(int o, char r[10],int wr)
{
	int k;
				for(k=0;k<o;k++)
				if(r[k]=='o')
				printf("(W)");
				else if(r[k]=='w')
				printf("(WD%d)",wr);
				else if(r[k]=='n')
				printf("(NB%d)",wr);
				else
				printf("(%c)",r[k]);
}
int toss(char team1[10],char team2[10])
{
	char tosswin[10],tc;
	printf("Who won the toss?");
	scanf("%s",&tosswin);
	printf("Enter B for batting and F for fielding");
	scanf(" %c",&tc);
	
	if(strcmp(team1,tosswin)==0)
		if(tc=='b'|| tc=='B')
		{
			printf("%s chose to bat\n",team1);
			sleep(1);
			return 1;
		}
		else
			{
				printf("%s chose to field\n",team1);
				sleep(1);
				return 2;
			}
	else
		if(tc=='b'|| tc=='B')
		{
			printf("%s chose to bat\n",team2);
			sleep(1);
			return 2;
		}
		else
		{
			printf("%s chose to field\n",team2);
			sleep(1);
			return 1;
		}
			
}
main()
{
	int runst1=0,runst2=0, overt1=0,overcon, balls, wicketst1=0,wicketst2=0, boundaries,k,o=0,b,choice;
	int i,j,runs,wr,t;
	FILE *fp1,*fp2,*fp3;
	char c,team1[10],team2[10],r[10],filename[20],teamname[10],content[100];
	printf("Enter Team 1");
	scanf("%s",&team1);
	printf("Enter Team 2");
	scanf("%s",&team2);
	printf("Enter number of overs");
	scanf("%d",&overcon);
	t=toss(team1,team2);
	if(t==2)
	{
		team2[strcspn(team2,"\n")]=0;
		sprintf(filename,"%s.txt",team2);
		fp1=fopen(filename,"w");
	}
	else
	{
		team1[strcspn(team1,"\n")]=0;
		sprintf(filename,"%s.txt",team1);
		fp1=fopen(filename,"w");
	}
	if(fp1==NULL)
	printf("Error in creating team file");
	system("cls");
	sleep(1);
	printf("\t\t\t\t-----------------------------\n");
	sleep(1);
    printf("\t\t\t\t|       Cricket Match       |\n");
    sleep(1);
    printf("\t\t\t\t|        %s VS %s         |\n",team1,team2);
    printf("\t\t\t\t-----------------------------\n");
    sleep(2);
	printf("Are ");
	sleep(1);
	printf("You ");
	sleep(1);
	printf("Ready?\n");
    sleep(2);
    printf("Press any key to continue");
    getch();
	for(i=0;i<=overcon;i++)
	{
		o=0;
		for(j=0;j<6;j++)
		{
			hello:
			b=j+1;
			if(i<overcon)
			fprintf(fp1,"%d.%d\t",i,b);
			system("cls");	
			printf("\t\t\t ---------------------------------------------------------------------------------------");
			if(t==1)
			{
			printf("\n\t\t\t|  %s  Batting  |\t\t\t%d-%d\t\t\t|\tovers %d.%d\t|\n",team1,runst1,wicketst1,i,j);
			
			}
			else
			{
			printf("\n\t\t\t|  %s  Batting  |\t\t\t%d-%d\t\t\t|\tovers %d.%d\t|\n",team2,runst1,wicketst1,i,j);
			t=2;
			
			}
			printf("\t\t\t|---------------------------------------------------------------------------------------|\n");
			printf("\t\t\t   ");
			ballss(o,r,wr);
			printf("\n\t\t\t|---------------------------------------------------------------------------------------|\n");
			if(k==5)
			k=0;
			if(i==overcon || wicketst1==10)
			goto out1;
			printf("\nRuns:0 1 2 3 4 6 Wicket:o Wide:w No Ball:n\n");
			printf("Enter case");
			scanf(" %c",&c);
			r[o]=c;
			o++;
			switch(c)
			{
				case '0':
					fprintf(fp1,"0\t");
					break;
				case '1':
					fprintf(fp1,"1\t");
					runst1=runst1+1;
					break;
				case '2':
					fprintf(fp1,"2\t");
					runst1=runst1+2;
					break;
				case '3':
					fprintf(fp1,"3\t");
					runst1=runst1+3;
					break;
				case '4':
					fprintf(fp1,"4\t");
					runst1=runst1+4;
					break;
				case '6':
					fprintf(fp1,"6\t");
					runst1=runst1+6;
					break;
				case 'w':
					printf("Enter wide runs");
					scanf("%d",&wr);
					runst1=runst1+wr;
					fprintf(fp1,"Wide %d\t",wr);
					if(j==0)
					j=0;
					else
					j--;
					break;
				case 'o':
					wicketst1++;
					printf("Enter runs if runout");
					scanf("%d",&runs);
					runst1=runst1+runs;
					fprintf(fp1,"Wicket %d\t",runs);
					break;
				case 'n':
					printf("Enter no ball runs");
					scanf("%d",&wr);
					runst1=runst1+wr;
					fprintf(fp1,"No Ball %d\t",wr);
					if(j==0)
					j=0;
					else
					j--;
					break;
				default:
					printf("Choose a valid option");
					goto hello;
			}
			fprintf(fp1,"%d-%d\n",runst1,wicketst1);
		}
	}
	out1:
		fclose(fp1);
	printf("Ready for the next half? Press any key to continue");
	getch();
		if(t==1)
	{
		team2[strcspn(team2,"\n")]=0;
		sprintf(filename,"%s.txt",team2);
		fp2=fopen(filename,"w");
	}
	else
	{
		team1[strcspn(team1,"\n")]=0;
		sprintf(filename,"%s.txt",team1);
		fp2=fopen(filename,"w");
	}
	for(i=0;i<=overcon;i++)
	{
		o=0;
		for(j=0;j<6;j++)
		{
			hello1:
			b=j+1;
			if(i<overcon)
			fprintf(fp2,"%d.%d\t",i,b);
			system("cls");	
			printf("\t\t\t ---------------------------------------------------------------------------------------");
			if(t==1)
			printf("\n\t\t\t|  %s  Batting  |\t\t\t%d-%d\t\t\t|\tovers %d.%d\t|\n",team2,runst2,wicketst2,i,j);
			else
			{
			printf("\n\t\t\t|  %s  Batting  |\t\t\t%d-%d\t\t\t|\tovers %d.%d\t|\n",team1,runst2,wicketst2,i,j);
			t=2;
			}
			printf("\t\t\t|---------------------------------------------------------------------------------------|\n");
			printf("\t\t\t   ");
			ballss(o,r,wr);
			printf("\n\t\t\t|---------------------------------------------------------------------------------------|\n");
			if(k==5)
			k=0;
			if(i==overcon || wicketst2==10 || runst2>runst1)
			goto out2;
			printf("\nRuns:0 1 2 3 4 6 Wicket:o Wide:w No Ball:n\n");
			printf("Enter case");
			scanf(" %c",&c);
			r[o]=c;
			o++;
			switch(c)
			{
				case '0':
					fprintf(fp2,"0\t");
					break;
				case '1':
					fprintf(fp2,"1\t");
					runst2=runst2+1;
					break;
				case '2':
					fprintf(fp2,"2\t");
					runst2=runst2+2;
					break;
				case '3':
					fprintf(fp2,"3\t");
					runst2=runst2+3;
					break;
				case '4':
					fprintf(fp2,"4\t");
					runst2=runst2+4;
					break;
				case '6':
					fprintf(fp2,"6\t");
					runst2=runst2+6;
					break;
				case 'w':
					printf("Enter wide runs");
					scanf("%d",&wr);
					runst2=runst2+wr;
					fprintf(fp2,"Wide %d\t",wr);
					if(j==0)
					j=0;
					else
					j--;
					break;
				case 'o':
					wicketst2++;
					printf("Enter runs if runout");
					scanf("%d",&runs);
					runst2=runst2+runs;
					fprintf(fp2,"Wicket %d\t",runs);
					break;
				case 'n':
					printf("Enter no ball runs");
					scanf("%d",&wr);
					runst2=runst2+wr;
					fprintf(fp2,"No Ball %d\t",wr);
					if(j==0)
					j=0;
					else
					j--;
					break;
				default:
					printf("Choose a valid option");
					goto hello1;
			}
			fprintf(fp2,"%d-%d\n",runst2,wicketst2);
		}
	}
	out2:
	fclose(fp2);
	system("cls");
	if(runst1==runst2)
	printf("Draw, move to the super overs");
	if(t==2)
		if(runst1>runst2)
		printf("%s won by %d runs",team2,runst1-runst2);
		else
		printf("%s won by %d wickets",team1,10-wicketst2);
	else
		if(runst1>runst2)
		printf("%s won by %d runs",team1,runst1-runst2);
		else
		printf("%s won by %d wickets",team2,10-wicketst2);
	nice:
	printf("\n1. See stats\n2. Exit\n");
	scanf("%d",&choice);
	if(choice==1)
	{
		printf("Enter name of team");
		scanf("%s",teamname);
		teamname[strcspn(teamname,"\n")]=0;
		sprintf(filename,"%s.txt",teamname);
		fp3=fopen(filename,"r");
		while(fgets(content,sizeof(content),fp3)!=NULL)
		{
			printf("%s\n",content);
		}
		
		goto nice;
	}		 
	else
	{
		exit(0);
	}
}
