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

//csv_read_test2_nc2_forwave保存用nがうまくプリントできないし入力数が減る.ccをコピー
//お気持ちtest２_nocomentでかなり良くなったけどもう少しフレキシブルにしつつコードの気持ち悪さを改善していこうという段階
//1,if文の順番が気持ち悪いので改善ついでにfillのタイミングが気持ち悪いので改善



//2,waveみたいにイベントごとにタイムと波形データがつまる仕組みにしていきたい。
//と思ったけど、これはあまりいい方法ではない気がする。
//なぜならば、藤家さんのAPVのデータに関しては　元データがそもそもそんな構造になっていて、こちらはそうではないから、
//ただし１マンごとに分けたい
//stoiがif文を連続させると回らないのか、値が入ってないのかわからないけど６番の１にしたらエントリー数を拾ってくれた。
//なんか無理だこれ、くぎれがエントリー数の切れ目と合わない。入力が少ない。
//色々if文で条件を変えて切れ目を変えてみたけど無理だったので、解決方法をもさく、一つは、一個前のに戻ってやり直していく方法、
//もう一個はエントリー数をうまいことプリントして変な箇所見つけること

const Int_t number_of_time = 10000; //１万とか

Int_t max_event_number = 2;

void csv_read_test(){
  ifstream ifs("/Users/gotoyu/Desktop/practice1/short_oscillo_sample.txt");
    
    
    
    Int_t event_number = 0;
    int tmpint = 20; //最初こいつには適当に7以上の数字が詰まっていますが、後から書き換えられます。
    double temporaly[5] ={0,0,0,0,0}; //Score[][j]のカウンタ。一人分の名前、国語、英語、数学を入れていく。（０～３）
   
int n ;
    TFile *file = new TFile("file4.root","recreate"); //新規rootファイルを生成
    TTree *tree = new TTree("tree","tree");
    int real_event_number = 0;
    tree->Branch("event_number", &event_number);//
    //tree->Branch("n", &n);// 意味不
    tree->Branch("val3", &real_event_number);
      tree->Branch("val4", &temporaly[3]);
      tree->Branch("val5", &temporaly[4]);
    
    
    
    
   
    
  //Int_t n=0;
  
  Double_t tmpdouble = 0;// とりあえず０
  
  string str = "";
  int j = 0;
  int i= 0;
  //Score[][j]のカウンタ。一人分の名前、国語、英語、数学を入れていく。（０～３）
  
 
    
    for(event_number=0;event_number<max_event_number;event_number++){
    
    Int_t n=0;
        i=0;
  while((getline(ifs, str) )&& i ==0)  // ファイルの中身を一行ずつ読み取る/・・以下やめてbreakで対応
    {
        
       
        
      
      std::string tmp = "";
      istringstream stream(str);// 区切り文字がなくなるまで文字を区切っていく
      while (getline(stream, tmp, ',') )
	{
	 
        
        
        
        
      //  if((event_number==0 && n==6) && j==1 ){
        //   int tmpint = stoi(tmp);
          // cout <<"if now    " <<"\t"<<tmp<<endl;
            //cout <<"\t " <<"all event count:"<<tmpint<<endl;
            //temporaly[j]=tmpdouble;
           
             
             //max_event_number = tmpint; }
            //max_event_number = 0; }
        
        
            
         // if(((j==0||j==1)||j==2))
	    //  {
		//cout <<"else now" <<"\t"<<tmpdouble<<endl;//123
            //  double tmpdouble = stod(tmp);
              
             
              
              
              
		//}
        
       
        if(j==3)
           {
		i=0;
		double tmpdouble = stod(tmp);//ここで何列目がほしいか定義する。４列目を取ってきたいので３とかいた。
		cout <<"if now    " <<"\t"<<tmpdouble<<endl;
		//a = n;
		//b = tmpdouble;
		temporaly[j]=tmpdouble;
		// vol3[n]=tmpdouble;
		}
	    else if(j==4)
	      {
		i=0;
		double tmpdouble = stod(tmp);
		cout <<"else if now" <<"\t"<<tmpdouble<<tmp<<endl;
		//c = tmpdouble;
		temporaly[j]=tmpdouble;
		//vol4[n]=tmpdouble;
		//cout <<"a,b,c =" <<a<<","<<b<<","<<c<<"vol3:"<<vol3[n]<<"vol4:"<<vol4[n]<<endl;
             
              
	      }
       // cout <<"a,b,c =" <<a<<","<<b<<","<<c<<endl;
        
        /*  else if(j==1)
         {
     
      double tmpdouble = stod(tmp);//ここで何列目がほしいか定義する。４列目を取ってきたいので３とかいた。
      cout <<"if now    " <<"\t"<<tmpdouble<<endl;
      //a = n;
      //b = tmpdouble;
      temporaly[j]=tmpdouble;
      // vol3[n]=tmpdouble;
      }
    */
	  
	  
        
     
	  j++;
	}
        tree->Fill();
      cout << endl;
      cout << "n"<< n << endl;
       // 次の人の配列に移る
        if(n==number_of_time){real_event_number = real_event_number + 1;}//これも気持ち悪いけど-2でいいと思う。,+1でOK最後まで回った数をカウントする。イベント数と同じかどうか確かめて//fillの後にこれ入れないとダメよ
       
        if(n==number_of_time){
            
            n = 0;
            i = 300;//0以外ならなんでもいい　かなりダサい
        }else{
            n++;}
      j = 0;
      
    }
    }

    

    
    cout << "countlasteventnumber"<< event_number << endl;
  tree->Write();
    cout << "real ni tumeta ibennto suu "<< real_event_number << endl;
    cout << "=max_event_number?"<< max_event_number << endl;
    
  
}

