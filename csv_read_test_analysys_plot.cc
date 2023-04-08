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

//csv_read_test3_保存用＿ファイルの取り込みかたやブランチの名前をかえた.ccをコピー


//お気持ちtest２_nocomentでかなり良くなったけどもう少しフレキシブルにしつつコードの気持ち悪さを改善していこうという段階
//1,if文の順番が気持ち悪いので改善ついでにfillのタイミングが気持ち悪いので改善



//2,waveみたいにイベントごとにタイムと波形データがつまる仕組みにしていきたい。
//と思ったけど、これはあまりいい方法ではない気がする。
//なぜならば、藤家さんのAPVのデータに関しては　元データがそもそもそんな構造になっていて、こちらはそうではないから、
//ただし１万ごとに分けたい(一つのイベントのポイント数)
//stoiがif文を連続させると回らないのか、値が入ってないのかわからないけど６番の１にしたらエントリー数を拾ってくれた。
//なんか無理だこれ、くぎれがエントリー数の切れ目と合わない。入力が少ない。
//色々if文で条件を変えて切れ目を変えてみたけど無理だったので、解決方法をもさく、一つは、一個前のに戻ってやり直していく方法、
//もう一個はエントリー数をうまいことプリントして変な箇所見つけること
//i での条件分けを無くしたらうまく行った、多分ワイル文から一回でるのがよろしくない。
//ここまできたらどうするか、一旦APVのものと同じ形式にしてみよう！ブランチの名前とか、形式
//APVのものに何があるかというと、row,instanse,ch,wave,tdc.tdc
//ぶっちゃけchとtdcに対応するものはない
//一旦ロングサンプルコンパイルしてみるか
//できた、後ファイルの名前をええ感じに取り込めるようにしたいのと、chをつめられるようにする？まあそれはやらなくてよい







const Int_t number_of_time = 10000; //１万とか
//const TString TIMEtoCH = "philist";
const TString RAWFILE_PATH = "/Users/gotoyu/Desktop/practice1/";
const TString FILE_HEADER_DATE = "220619_";
Int_t max_event_number = 2;//仮の数字、あとで書き換える、1以外の自然数入れとけば良い


TString Getrawfilename(Int_t ID)
{
  stringstream name;
    name<<FILE_HEADER_DATE<<setw(6)<<setfill('0')<<ID<<".csv";
  //name<<FILE_HEADER_NAME<<setw(6)<<setfill('0')<<ID<<".csv";
  return (TString)name.str();
}

TString Gettreefilename(Int_t ID)//file tukuru toki
{
  stringstream name;
    
    name<<FILE_HEADER_DATE<<setw(6)<<setfill('0')<<ID<<".root";
  //name<<FILE_HEADER_NAME<<setw(6)<<setfill('0')<<ID<<".root";
  return (TString)name.str();
}








void csv_read_test(Int_t ID){
 // ifstream ifs("/Users/gotoyu/Desktop/practice1/long_oscillo_sample.csv");
   
    
    TString rawfile_name = RAWFILE_PATH + Getrawfilename(ID);
    cerr<<"raw file; "<<rawfile_name<<endl;
    
   // ifstream fin(rawfile_name, ios::binary);//ifsかfin は好みの違い
    ifstream ifs(rawfile_name);
    if(ifs.fail()){cerr<<"error by file open!"<<endl; return ;}
    
    
    Int_t event_number = 0;
    int tmpint = 20; //最初こいつには適当に7以上の数字が詰まっていますが、後から書き換えられます。
    

    TFile *file = new TFile("file_test3.root","recreate"); //新規rootファイルを生成
    TTree *tree = new TTree("tree","tree");
    
    
    int n =0;//まじでここ０にしとくの大事
    double temporaly[5] ={0,0,0,0,0};
 //   int real_event_number = 0;
    tree->Branch("event_number", &event_number);//
    //tree->Branch("n", &n);// 意味不
    //tree->Branch("val3", &real_event_number);
      tree->Branch("time", &temporaly[3]);
      tree->Branch("wave", &temporaly[4]);
    
    
    
    
   
    
  
  
  Double_t tmpdouble = 0;// とりあえず０
  
  string str = "";
  int j = 0;
  int i= 0;
 
  while(getline(ifs, str) ) // ファイルの中身を一行ずつ読み取る///・・以下やめてbreakで対応するのはやめた
    {
        
       
        
      
      std::string tmp = "";
      istringstream stream(str);// 区切り文字がなくなるまで文字を区切っていく
      while (getline(stream, tmp, ',') )
	{
	 
        
        
        
        
       if((event_number==0 && n==6) && j==1 ){
          int tmpint = stoi(tmp);
          
             
             max_event_number = tmpint; }
            
             
              
              
              
		
        
       
        if(j==3)
           {
		i=0;
		double tmpdouble = stod(tmp);//ここで何列目がほしいか定義する。４列目を取ってきたいので３とかいた。
		//cout <<"if now    " <<"\t"<<tmpdouble<<endl;
		
		temporaly[j]=tmpdouble;//timeというかinstanceというか
		
		}
	    else if(j==4)
	      {
		i=0;
		double tmpdouble = stod(tmp);
		//cout <<"else if now" <<"\t"<<tmpdouble<<tmp<<endl;
		
		temporaly[j]=tmpdouble;//wave
	
              
	      }
       
        
     
	  j++;
	}
        tree->Fill();
      //cout << endl;
     // cout << "n"<< n << endl;
     
       
        if(n==number_of_time-1){
            
            n = 0;
            cout << "now event_number:"<< event_number <<"/"<<max_event_number<< endl;
            event_number++;
            
            
        }else{
            n++;}
      j = 0;
      
 
    }

    

    
    cout << "check!!! that the last event number equals max event number "<< event_number << "=?"<< max_event_number << endl;
  tree->Write();
   
    
    
  
}

