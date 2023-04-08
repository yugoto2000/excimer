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

//自分のローカルディレクトリの、csv_read_test2_nocomment.ccをコピーした
void csv_read_test(){
  ifstream ifs("/Users/gotoyu/Desktop/practice1/short_oscillo_sample.txt");
  Int_t n=0;
  //Double_t vol3[30000]={};
  //Double_t vol4[30000]={};//
  Double_t tmpdouble = 0;// とりあえず０
  //string score[40000][5]; //
  string str = "";
  int j = 0;  // Score[ ][j]のカウンタ。一人分の名前、国語、英語、数学を入れていく。（０～３）
  TFile *file = new TFile("file.root","recreate"); //新規rootファイルを生成
  TTree *tree = new TTree("tree","tree");
  Int_t a;
  Double_t b;
  Double_t c;
  tree->Branch("val1", &a);
  tree->Branch("val2", &b);
  tree->Branch("val3", &c);//a = 1; b = 2.4; c=1.33;tree->Fill();tree->Write();
  while(getline(ifs, str))  // ファイルの中身を一行ずつ読み取る
    {
      std::string tmp = "";
      istringstream stream(str);// 区切り文字がなくなるまで文字を区切っていく
      while (getline(stream, tmp, ',') )
	{
	  //  score[m][j] = tmp;
	  if(j==3)
	    {
	      double tmpdouble = stod(tmp);//ここで何列目がほしいか定義する。４列目を取ってきたいので３とかいた。
	      cout <<"if now    " <<"\t"<<tmpdouble<<endl;
	      a = n;
	      b = tmpdouble;
	     // vol3[n]=tmpdouble;
              
	    }
	  else if(j==4)
	    {
	      double tmpdouble = stod(tmp);
	      cout <<"else if now" <<"\t"<<tmpdouble<<endl;
	      c = tmpdouble;
	      //vol4[n]=tmpdouble;
	      //cout <<"a,b,c =" <<a<<","<<b<<","<<c<<"vol3:"<<vol3[n]<<"vol4:"<<vol4[n]<<endl;
            cout <<"a,b,c =" <<a<<","<<b<<","<<c<<endl;
	      tree->Fill();
	    }
	  else
	    {
	      tmpdouble = 0;
	      cout <<"else now" <<"\t"<<tmpdouble<<endl;//123
              
	    }
	  
          
	  j++;
	}
      cout << endl;
      cout << "n"<< n << endl;
      n++;  // 次の人の配列に移る
      j = 0;
      
    }
  
  for(Int_t i=0;i<n;i++)
    {                     //フィッティングを繰り返しているのは　ルートの特性上繰り返すと精度が上がるから
      
    }//ここではなにもしてない
  
  tree->Write();
    
}

