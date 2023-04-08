#include <sstream>
#include <string>
#include <iostream>//
#include <fstream>//ifstream 用
#include <stdio.h>
#include <stdlib.h> /* malloc用 */
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TCut.h"
#include "TTree.h"
#include "TDirectory.h"
#include "TEventList.h"
#include "TGraph.h"
#include "TTreeIndex.h"
#include "TBranch.h"
#include "TVectorD.h"
#include "TVector.h"
#include "TString.h"

//ローカルディレクトリのcsv_read_test2_nc2_2_forwaveをgit用にコピーしたものです。
//お気持ちtest２_nocomentでかなり良くなったけどもう少しフレキシブルにしつつコードの気持ち悪さを改善していこうという段階
//1,if文の順番が気持ち悪いので改善ついでにfillのタイミングが気持ち悪いので改善



//2,waveみたいにイベントごとにタイムと波形データがつまる仕組みにしていきたい。

const Int_t number_of_time = 10000; //１万とか

Int_t max_event_number = 2;


void csv_read_test(){
  ifstream ifs("/Users/gotoyu/Desktop/practice1/short_oscillo_sample.txt");
    
    
    Int_t event_number = 0;
    int tmpint = 20;
    
  Int_t n=0;
  //Double_t vol3[30000]={};
  //Double_t vol4[30000]={};//
  Double_t tmpdouble = 0;// とりあえず０
  //string score[40000][5]; //
  string str = "";
  int j = 0;
  int i= 0;
  //Score[][j]のカウンタ。
  double temporaly[5] ={0,0,0,0,0};
  TFile *file = new TFile("file3.root","recreate"); //新規rootファイルを生成
  TTree *tree = new TTree("tree","tree");
  Int_t a = 0;
  Double_t b = 0;
  Double_t c = 0;
  
  
  tree->Branch("val1", &a);
  tree->Branch("val2", &b);
  tree->Branch("val3", &c);//a = 1; b = 2.4;c=1.33;tree->Fill();tree->Write();
  tree->Branch("val4", &temporaly[3]);
  tree->Branch("val5", &temporaly[4]);
    
    
    while(getline(ifs, str) ) // ファイルの中身を一行ずつ読み取る
    {
      std::string tmp = "";
      istringstream stream(str);// 区切り文字がなくなるまで文字を区切っていく
      while (getline(stream, tmp, ',') )
	{
	  
        
            
            
          if(j==0||j==1||j==2)
	      {
		tmpdouble = 0;
		cout <<"else now" <<"\t"<<tmpdouble<<endl;//123
		
	      }else if(j==3)
           
	      {
		i=3;
		double tmpdouble = stod(tmp);//ここで何列目がほしいか定義する。４列目を取ってきたいので３とかいた。
		cout <<"if now    " <<"\t"<<tmpdouble<<endl;
		a = n;
		b = tmpdouble;
		temporaly[j]=tmpdouble;
		// vol3[n]=tmpdouble;
		
	      }
	    else if(j==4)
	      {
		i=4;
		double tmpdouble = stod(tmp);
		cout <<"else if now" <<"\t"<<tmpdouble<<endl;
		c = tmpdouble;
		temporaly[j]=tmpdouble;
		//vol4[n]=tmpdouble;
		//cout <<"a,b,c =" <<a<<","<<b<<","<<c<<"vol3:"<<vol3[n]<<"vol4:"<<vol4[n]<<endl;
		
		
	      }
        cout <<"a,b,c =" <<a<<","<<b<<","<<c<<endl;
         
            
	  
	  
        
       // temporaly[0] =0;
        //temporaly[1] =0;
        //temporaly[2] =0;
        //temporaly[3] =0;
        //temporaly[4] =0;
	  j++;
	}
        tree->Fill();
      cout << endl;
      cout << "n"<< n << endl;
        
        
     
        
        if(n==9999){
            
            n = 0;
            //i = 300;//0以外ならなんでもいい　かなりダサい
        }else{
            n++;}
    //  n++;  // 次の人の配列に移る
        
        
        
      j = 0;
      
    }
  
  for(Int_t i=0;i<n;i++)
    {                     //フィッティングを繰り返しているのは　ルートの特性上繰り返すと精度が上がるから
      
    }
  
  tree->Write();
  
}

