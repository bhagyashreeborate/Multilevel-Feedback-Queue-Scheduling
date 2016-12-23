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
        void create_book(int n,int avgwt,int avgat,int avgrt,int throughpt);     //function to create new excel file

};
int column = 1;
int row = 2;
int flag = 1;
Book* book =  xlCreateBook();
Sheet* sheet = book->addSheet("SJF");
//***************************************************************
//    	NEW EXCEL BOOK CREATE FUNCTION DEFINATION
//****************************************************************

void myExcel::create_book(int n,int avgwt,int avgat,int avgrt,int throughpt)
{

    cout<<"flag = "<<flag;

    if (flag == 1){
        if(book)
        {
sheet->writeStr(1,1,"NOP");
            sheet->writeStr(1,2,"Average Waiting Time");
            sheet->writeStr(1,3,"Avg Turnaround Time");
            sheet->writeStr(1,4,"Average Running Time");
            sheet->writeStr(1,5,"Throughput");
            if(sheet)
            {
                sheet->writeNum(row, column++, n);
                sheet->writeNum(row, column++, avgwt);
                sheet->writeNum(row, column++, avgat);
                sheet->writeNum(row, column++, avgrt);
                sheet->writeNum(row, column++, throughpt);


            }

        if(book->save("SJF.xls")) std::cout << "\nFile example.xls has been created." << std::endl;
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
                sheet->writeNum(row, column++, avgwt);
                sheet->writeNum(row, column++, avgat);
                sheet->writeNum(row, column++, avgrt);
                sheet->writeNum(row, column++, throughpt);
                cout<<"\n\nrow = "<<row;
                cout<<"\n\ncolumn = "<<column;
            }
            row++;
            column = 1;


        if(book->save("SJF.xls")) std::cout << "\nFile example.xls has been created." << std::endl;
        //book->release();
        //flag++;
        }

    }
    std::cout<<flag;
   // book->release();
    std::cout << "\nPress any key to exit...";
}




    void SJF_NP(int n, int burst[], int arrival[], int throughput)
    {
          myExcel me;
      cout << "Output for SJF_Non_Preemptive scheduling algorithm" << endl;

      int i, j, temp, temp2;
      double tot, avgwait, avgturnaround, avgresponse, tp;

      //array instantiations
      int start[n], end[n], wait[n];

      //calculations
      for(i=1;i<=n;i++)
        {
          for(j=i+1;j<=n;j++)
            {
              if (i>=2 && burst[i-1]>burst[j-1])
                {
                  temp = burst[i-1];
                  temp2 = arrival[i-1];
                  burst[i-1]=burst[j-1];
                  arrival[i-1]=arrival[j-1];
                  burst[j-1]=temp;
                  arrival[j-1]=temp2;
                }
            }
          if(i==1)
            {
              start[0]=0;
              end[0]=burst[0];
              wait[0]=0;
            }
          else
            {
              start[i-1]=end[i-2];
              end[i-1]=start[i-1]+burst[i-1];
              wait[i-1]=start[i-1]+arrival[i-1];
            }
          //throughput
          if (start[i+1] <= throughput)
            tp = i+1;
        }

      //output
      //cout << "\n\nPROCESS \t BURST TIME\tARRIVAL TIME\tWAIT TIME\tSTART TIME\tEND TIME\n";
     // for (i=0;i<n;i++){
       // cout << "\nP[" << i + 1 << "]" << "\t\t" << burst[i] << "\t\t" << arrival[i] << "\t\t" << wait[i] << "\t\t" << start[i] << "\t\t" << end[i];
    //  }
      //avg wait time
      for(i=1,tot=0;i<n;i++){
        tot+=wait[i-1];
        avgwait=tot/n;
      }
      //avg turnaround time
      for(i=1,tot=0;i<n;i++){
        tot+=end[i-1];
        avgturnaround=tot/n;
      }
      //avg response time
      for(i=1,tot=0;i<n;i++){
        tot+=start[i-1];
        avgresponse=tot/n;
      }
      cout << "\n\nAverage Wait Time: " << avgwait;
      cout << "\nAverage Response Time: " << avgturnaround;
      cout << "\nAverage Turnaround Time: " << avgresponse;
      cout << "\nThroughput for (" << throughput << "): " << tp << endl;
      me.create_book(n,avgwait,avgturnaround,avgresponse,tp);
    }
    int main()
    {
         clock_t t;
    t=clock();
        int k=0;

        while(k<75)
        {

        int throughput=10000;
        int burst[100],arrival[100];
        int n=rand()% 50 + 1;
        cout<<"number of processes"<<n;
        for(int i=0;i<n;i++)
        {
          burst[i]= rand()% 20 + 9;
         arrival[i]= rand()% 8 + 1;
        }

        SJF_NP(n,burst,arrival,10000);
        k++;
            }
             t=clock()-t;
printf("processor time consumption %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);

    }

