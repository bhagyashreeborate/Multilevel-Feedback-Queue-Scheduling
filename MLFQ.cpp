#include "libxl.h"
#include<stdio.h>
#include<queue>
#include<iostream>
#include<string>
#include<stdlib.h>
#include <sstream>
#include<time.h>

using namespace std;
using namespace libxl;


class myExcel
{
    public:
        void create_book(int n,int awtime,int avtat);     //function to create new excel file

};
int column = 1;
int row = 2;
int flag = 1;
Book* book =  xlCreateBook();
Sheet* sheet = book->addSheet("MLFQE1");
//***************************************************************
//    	NEW EXCEL BOOK CREATE FUNCTION DEFINATION
//****************************************************************

void myExcel::create_book(int n,int awtime,int avtat)
{

    cout<<"flag = "<<flag;

    if (flag == 1){
        if(book)
        {

            sheet->writeStr(1,1,"Number of processes");
            sheet->writeStr(1,3,"Avg waiting Time");
            sheet->writeStr(1,2,"Average turn-around Time");
            //sheet->writeStr(1,4,"Throughput");
            if(sheet)
            {
                sheet->writeNum(row, column++, n);
                sheet->writeNum(row, column++, awtime);
                sheet->writeNum(row, column++, avtat);
                //sheet->writeNum(row, column++, throughpt);


            }

        if(book->save("MLFQE.xls")) std::cout << "\nFile has been created." << std::endl;
        //book->release();
        }
        row++;
        flag++;
        column = 1;

    }

    else{
        if(book)
        {
            if(sheet)
            {
                sheet->writeNum(row, column++, n);
                sheet->writeNum(row, column++, awtime);
                sheet->writeNum(row, column++, avtat);
                //sheet->writeNum(row, column++, throughpt);
                //cout<<"\n\nrow = "<<row;
                //cout<<"\n\ncolumn = "<<column;
            }
            row++;
            column = 1;


        if(book->save("MLFQE.xls")) std::cout << "\nFile has been created." << std::endl;
        //book->release();
        //flag++;
        }

    }
   // std::cout<<flag;
   // book->release();
    //std::cout << "\nPress any key to exit...";
}

struct process
{
	int pid;
	int atime;
	int btime;
	int rtime; //Remaining Time
	int priority;

	//Parameters for predicting output
	int stime;
	int etime;
};


struct mycomp
{
	bool operator()(const process& lhs, const process& rhs) const
	{
		return lhs.priority > rhs.priority;
	}
};

void printproc(process arr[],int n)
{
	printf("\nPROCESS TABLE");
	printf("\n");
	for(int i=0;i<n;i++)
	{
		printf("%d %d %d %d",arr[i].pid,arr[i].atime,arr[i].btime,arr[i].priority);
		printf("\n");
	}
}

int opid,rtime,wtime,n;
int fitime,tat=0,avtat;
int awtime,sum1=0,sum2=0;
int main()
{
    clock_t t;
    t=clock();
    myExcel me;

    int k=0;
    while(k<75)
    {


	int i,j,p=0,tot=0;
	int a[20];
	//scanf("%d",&n);
	n=rand() % 50 + 1;
	cout<<"enter number of processes"<<n;
	//cout<<n;
	int pid,atime,btime,priority;
	int Fprev=0;
	process arr[n+1];
	for( i=0;i<n;i++)
	{
	    //pid=rand() % 9 + 1;
	    //cout<<pid;
        //atime=rand() % 9 + 1;
        pid=i;
        atime=rand()% 8 +1;
        btime=rand() % 20 + 9;
	    priority=rand() % 9+ 0;
//scanf("%d %d %d %d",&pid,&atime,&btime,&priority);
		arr[i].pid = pid;
        arr[0].atime=0;
        arr[i+1].atime=atime;
		arr[i].btime=btime;
		arr[i].priority=priority;
		arr[i].rtime=btime;
		tot = tot + btime;
	}

	//print before sorting
	//printproc(arr,n);

	//Sort The Processes as per arrival time
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(arr[i].atime<arr[j].atime)
			{
				//Swap i and j
				int tpid = arr[i].pid;
				int tatime = arr[i].atime;
				int tbtime = arr[i].btime;
				int tpriority=arr[i].priority;
				int rtime = arr[i].rtime;

				arr[i].pid=arr[j].pid;
				arr[i].atime = arr[j].atime;
				arr[i].btime  = arr[j].btime;
				arr[i].priority = arr[j].priority;
				arr[i].rtime = arr[j].rtime;

				arr[j].pid=tpid;
				arr[j].atime = tatime;
				arr[j].btime  = tbtime;
				arr[j].priority = tpriority;
				arr[j].rtime = rtime;

			}
		}
	}
  int chart[1000];
	//Initialize chart
	for(i=0;i<tot+1;i++)
		chart[i]=0;
	priority_queue<process, vector<process>, mycomp> q1;
	priority_queue<process, vector<process>, mycomp> q2;
	queue<process> q3;
	int time=0;
	int turn = 0;
	int quanta=4,rquanta=4;
	int flag1=0;
	while((!q1.empty())||(!q2.empty())||(!q3.empty())||(flag1==0)||(turn<n))
        {
		//printf("\ntime: %d",time);
		while((turn<n) && (arr[turn].atime==time))
		{


			if(quanta!=4&&(arr[turn].priority<q1.top().priority))
			{
				//printf("\t here pushed %d into q2",q1.top().pid);
				q2.push(q1.top());
				q1.pop();
				quanta=4;
            }
			//if(flag1==0)
			//	printf("\t***flag1 value Changed***");

			flag1=1;
			//printf("\npushed: %d in q1",arr[turn].pid);
			q1.push(arr[turn]);
			turn = turn +1;
		}
		if(!q1.empty())
		{
		    	process cur = q1.top();
			//printf("\nPopped %d",cur.pid);
			chart[time]=cur.pid;
			cur.rtime = cur.rtime-1;
			q1.push(cur);
			q1.pop();
			quanta=quanta-1;
			if(q1.top().rtime==0)
			{
				//printf("\tRemaining Time is 0");
				q1.pop();
				quanta=4;
			}
			else if(quanta==0)
			{
				//printf("\tTime quanta over for %d rtime is %d",cur.pid,cur.rtime);

				if(q1.top().rtime>0)
                {
                Fprev=q1.top().priority;
                 q2.push(q1.top());
                }

				q1.pop();
				quanta=4;
			}
		}
		else if(!q2.empty())
		{
		    if(quanta!=4 && Fprev<q1.top().priority)
            {
               q3.push(q2.top());
				q2.pop();
				quanta=4;
            }
		   else if((rquanta!=4)&&(!q3.empty()))
			{
				//Pop from Queue 2 and push at back
				//printf("\tpushing %d with rtime %d in q2",q2.front().pid,q2.front().rtime);
				q3.push(q3.front());
				q3.pop();
				rquanta=4;
			}

			process cur = q2.top();
			//printf("\nPopped %d",cur.pid);
			chart[time]=cur.pid;
			cur.rtime = cur.rtime-1;
			q2.push(cur);
			q2.pop();
			quanta=quanta-1;
			if(q2.top().rtime==0)
			{
				//printf("\tRemaining Time is 0");
				q2.pop();
				quanta=4;
			}
			else if(quanta==0)
			{
				//printf("\tTime quanta over for %d rtime is %d",cur.pid,cur.rtime);

				if(q2.top().rtime>0)
					q3.push(q2.top());
				q2.pop();
				quanta=4;
			}
		}
		else if(!q3.empty())
		{
			//Process Queue 2 for Round Robin

			q3.front().rtime = q3.front().rtime-1;
			//printf("\nIn RR rtime for %d is : %d",q2.front().pid,q2.front().rtime);
			chart[time]=q3.front().pid;
			rquanta--;
			if(q3.front().rtime==0)
			{
				q3.pop();
				rquanta=4;
			}

			else if(rquanta==0)
			{
				//printf("\trquanta is zero, removing and adding at end %d",q2.front().pid);
				q3.push(q3.front());
				q3.pop();
				rquanta=4;
			}

		}

		time= time+1;
        }
       // printf("\nCurrent Chart: ");
		/*for(i=0;i<=time;i++)
			printf("%d",chart[i]);
		printf("\n");*/

	//Predict output
	for(i=0;i<n;i++)
	{
		int flag=0;
		int curpid = arr[i].pid;
		for(j=0;j<time;j++)
		{
			if(chart[j]==curpid)
			{
				if(flag==0)
				{
					arr[i].stime=j;
					flag=1;
				}
				else
					arr[i].etime=j+1;
			}
		}
	}

	//Sort The Processes as per pid
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(arr[i].pid<arr[j].pid)
			{
				//Swap i and j
				int tpid = arr[i].pid;
				int tatime = arr[i].atime;
				int tbtime = arr[i].btime;
				int tpriority=arr[i].priority;
				int rtime = arr[i].rtime;
				int stime = arr[i].stime;
				int etime = arr[i].etime;

				arr[i].pid=arr[j].pid;
				arr[i].atime = arr[j].atime;
				arr[i].btime  = arr[j].btime;
				arr[i].priority = arr[j].priority;
				arr[i].rtime = arr[j].rtime;
				arr[i].stime = arr[j].stime;
				arr[i].etime = arr[j].etime;

				arr[j].pid=tpid;
				arr[j].atime = tatime;
				arr[j].btime  = tbtime;
				arr[j].priority = tpriority;
				arr[j].rtime = rtime;
				arr[j].stime=stime;
				arr[j].etime=etime;

			}
		}
	}


	//Print Output
	for(i=0;i<n;i++)
	{
		opid = arr[i].pid;
		//wtime = arr[i].stime - arr[i].atime;
		tat=arr[i].etime - arr[i].stime;
		wtime = tat-arr[i].btime;
		//fitime=arr[i].etime;
        //cout<<"process"<<i<<"\t"<<wtime<<"\n";
		//printf("%d %d %d %d\n",opid,rtime,fitime,wtime);

       // tat=arr[i].btime + wtime;
        //avtat+=tat;
        sum1+=wtime;
        sum2+=tat;
        //me.create_book(wtime,rtime,tat,throughpt);

}
awtime=int(sum1/n);
cout<<"average waiting time"<<awtime<<"\n";
avtat=int(sum2/n);
cout<<"average turn around time"<<avtat<<"\n";
me.create_book(n,awtime,avtat);
awtime=0;
avtat=0;
sum1=0;
sum2=0;
k++;
cout<<k;
}

t=clock()-t;
printf("processor time consumption %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);

}


