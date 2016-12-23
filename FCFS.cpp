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
        void create_book(int n,int avwt,int avtat);     //function to create new excel file

};
int column = 1;
int row = 2;
int flag = 1;
Book* book = xlCreateBook();
Sheet* sheet = book->addSheet("MyFCFS");
//***************************************************************
//    	NEW EXCEL BOOK CREATE FUNCTION DEFINATION
//****************************************************************

void myExcel::create_book(int n,int avwt1,int avtat1)
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
                sheet->writeNum(row, column++, avwt1);
               // sheet->writeNum(row, column++, avgrt);
                sheet->writeNum(row, column++, avtat1);
                //sheet->writeNum(row, column++, throughpt);


            }

        if(book->save("MyFCFS.xls")) std::cout << "\nFile example.xls has been created." << std::endl;
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
                sheet->writeNum(row, column++, avwt1);
               // sheet->writeNum(row, column++, avgrt);
                sheet->writeNum(row, column++, avtat1);
               // sheet->writeNum(row, column++, throughpt);
                cout<<"\n\nrow = "<<row;
                cout<<"\n\ncolumn = "<<column;
            }
            row++;
            column = 1;


        if(book->save("MyFCFS.xls")) std::cout << "\nFile example.xls has been created." << std::endl;

        }

    }

}

    int main()
     {
          clock_t t;
    t=clock();
    	int n,bt[100],wt[100],tat[100],avwt=0,avtat=0,i,j;

    	int avwt1=0;
    	int avtat1=0;
    	 myExcel me;
    	//cout<<"Enter total number of processes(maximum 20):";
    	int k=0;
    	while(k<75)
        {

    	n=rand()%50+2;
    	cout<<n<<"\n";
    	//cout<<"nEnter Process Burst Time";
    	for (i=0;i<n;i++) {
    		//cout<<"P["<<i+1<<"]:";
    		bt[i]=rand()%20+9;
    	}
    	wt[0]=0;
    	//waiting time for first process is 0
    	//calculating waiting time
    	for (i=1;i<n;i++) {
    		wt[i]=0;
    		for (j=0;j<i;j++)
    		            wt[i]+=bt[j];
    	}
    	//cout<<"nProcessttBurst TimetWaiting TimetTurnaround Time";
    	//calculating turnaround time
    	for (i=0;i<n;i++) {
    		tat[i]=bt[i]+wt[i];
    		avwt+=wt[i];
    		avtat+=tat[i];
    		//cout<<"nP["<<i+1<<"]"<<"tt"<<bt[i]<<"tt"<<wt[i]<<"tt"<<tat[i];
    	}
    	avwt1=avwt/n;
    	avtat1=avtat/n;
    	cout<<"Average Waiting Time:"<<avwt1<<"\n";
    	cout<<"Average Turnaround Time:"<<avtat1;
    	me.create_book(n,avwt1,avtat1);
    	avwt=0;
    	avtat=0;
    	avwt1=0;
    	avtat1=0;
    	k++;
    	cout<<k;
        }
        t=clock()-t;
printf("processor time consumption %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
    }
