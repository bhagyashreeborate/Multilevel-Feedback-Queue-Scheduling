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
        void create_book(int n,int awt,int atat);     //function to create new excel file

};
int column = 1;
int row = 2;
int flag = 1;
Book* book = xlCreateBook();
Sheet* sheet = book->addSheet("MyRR");
//***************************************************************
//    	NEW EXCEL BOOK CREATE FUNCTION DEFINATION
//****************************************************************

void myExcel::create_book(int n,int aw,int atat)
{

    //cout<<"flag = "<<flag;
    //cout<<"aw="<<avgw;
    if (flag == 1){
        if(book)
        {
            sheet->writeStr(1,1,"Processes");
            //sheet->writeStr(1,2,"Total Wait");
            sheet->writeStr(1,3,"Average Waiting Time");
           // sheet->writeStr(1,4,"Average Running Time");
            sheet->writeStr(1,5,"Avg Turnaround Time");
            //sheet->writeStr(1,6,"Throughput");
            if(sheet)
            {

                sheet->writeNum(row, column++, n);
                //sheet->writeNum(row, column++, avgw);
                sheet->writeNum(row, column++, aw);
               // sheet->writeNum(row, column++, avgrt);
                sheet->writeNum(row, column++, atat);
                //sheet->writeNum(row, column++, throughpt);


            }

        if(book->save("MyRR.xls")) std::cout << "\nFile example.xls has been created." << std::endl;
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

		//write string value
sheet->writeNum(row, column++, n);
                //sheet->writeNum(row, column++, avgw);
                sheet->writeNum(row, column++, aw);
               // sheet->writeNum(row, column++, avgrt);
                sheet->writeNum(row, column++, atat);
               // sheet->writeNum(row, column++, throughpt);
                cout<<"\n\nrow = "<<row;
                cout<<"\n\ncolumn = "<<column;
            }
            row++;
            column = 1;


        if(book->save("MyRR.xls")) std::cout << "\nFile example.xls has been created." << std::endl;
        //book->release();
        //flag++;
        }

    }
    //std::cout<<flag;
   // book->release();
    //std::cout << "\nPress any key to exit...";
}


int main()
{

          clock_t t;
    t=clock();

    int ts,n,i,j,pid[100],burst[100],rt[100],arrival[100],wt[100],s[100],e[100],q=0,te[100],temp,tp=0,throughput;
    int awt,atat=0,art=0;
    char avgw[10], avgwt[10], avgrt[10],avgat[10],throughpt[10];
    myExcel me;
    int aw,tat=0;

   // cout<<"enter time slice for process execution:";
    //cin>>ts;
    int k=0;
    while(k<75)
    {


    ts=30;
    cout<<"time slice is:"<<ts<<"\n";
    //cout<<"enter number of processes";
   //cin>>n;
   n=rand() % 50 + 2;
    cout<<"enter number of processes "<<n;

    throughput=1000;
    for(i=0;i<=n;i++)
    {
          pid[i]=i;
    //cout<<"\t"<<"process id for process"<<i<<"is"<<"\t"<<pid[i]<<"\n";

    }
    //cout<<"enter burst times for process";
    //burst[i]=rand() % 10 + 1;
    for(i=0;i<=n;i++)
    {
        //cin>>burst[i];
        burst[i]=rand() % 20 + 9;
        rt[i]=burst[i];
    }
    //cout<<"enter arrival for process";
    for(i=0;i<=n;i++)
    {
        //cin>>arrival[i];
arrival[i]=rand() % 8 + 1;
    }
    for(i=0;i<=n;i++){

	   pid[i]=i+1;

	 }

	 for(i=0;i<n;i++)

	   {

	     te[i]=0;

	     wt[i]=0;

	     s[i]=0;

	     e[i]=0;

	   }

	 for(i=0;i<n;i++)

	   {

	     for(j=i+1;j<n;j++)

	   {

	     if(arrival[i]>arrival[j])

	       {

	         temp=arrival[i];            //sorting according to arrival time

	         arrival[i]=arrival[j];

	         arrival[j]=temp;

	         temp=burst[i];

	         burst[i]=burst[j];

	         burst[j]=temp;

	         temp=pid[i];

	         pid[i]=pid[j];

	         pid[j]=temp;

	       }

	   }

	   }
//cout <<  "\n Gantt chart \n";
j=0;

	   while(j<=n)

	     {

	   j++;

	   for(i=0;i<n;i++)

	     {

	       if(rt[i]==0)  continue;

	       if(rt[i]>ts)
	           {

	               if(arrival[i]>q)
                    q=arrival[i];



	           //cout << q << "\t" << "P" << pid[i] << endl;

	           q=q+ts;

	           rt[i]=rt[i]-ts;

	           te[i]=te[i]+1;

	           }

	       else

	           {



	           //cout << q << "\t" << "P" << pid[i] << endl;

	           wt[i]=q-te[i]*ts;

	           q=q+rt[i];
            rt[i]=rt[i]-rt[i];

	           }
	           if(burst[i]==rt[i]+ts)

	         s[i]=q-ts;
	       else if(burst[i]<=rt[i]+ts)

	         s[i]=q-ts+burst[i];

	       //throughput calculations

	       if(rt[i]==0)

	         if(throughput>=q)

	           tp++;

	     }

	     }

	   awt=0;

	   cout <<  " Process Waiting Time";

	   //waiting time calculation

	   for(i=0;i<n;i++)

	     {

	   wt[i]=wt[i]-arrival[i];
       tat+=burst[i]+wt[i];
       art+=s[i]-arrival[i];
	   awt=awt+wt[i];

	     }


	   aw=awt/n;
cout<<"average waiting time"<<aw<<"\n";
	   atat=tat/n;
cout<<"average turn around time"<<atat<<"\n";

        me.create_book(n,aw,atat);
        aw=0;
        atat=0;
        tat=0;
        awt=0;
        q=0;
        i=0;
        k++;
	}
	  t=clock()-t;
printf("processor time consumption %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
}
