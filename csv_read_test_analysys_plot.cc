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
//csv_read_test4.ccをコピー

//一旦ロングサンプルコンパイルしてみるか
//できた、後ファイルの名前をええ感じに取り込めるようにしたいのと、chをつめられるようにする？

//IDは例えば165533とか、日付の後に時間が載っていると思うのでそれを記入してください。
//さあここからは解析の方のマクロを作るべきではないだろうか。
//ここを離れようか　何をしよう、ch２、ch３のツリーを両方とりこんで、？？さらに積算？？むずい

//そもそもデータ的にはch２をトリがとしたch３の信号のはずなので、こいつをそのまま範囲指定して積算でいいのでは
//多分それでいい
//積算ていうことは多分回している最中に全部足して時間を掛け算して、さらに今回ディバイドした分の補正とかを入れればいいはずだけど、
//そのくらいならこのコードでもできてしまうのでこのコードでやってしまってもいいのか分けた方がいいのか。
//関数にして呼び出すのはあり？なしかなぁ




const Int_t number_of_time = 10000; //１万とか
const TString RAWFILE_PATH = "/Users/gotoyu/Desktop/practice1/";
const TString TREEFILE_PATH = "/Users/gotoyu/Desktop/practice1/";
//const TString TREEFILE_PATH = "./tree/";
const TString FILE_HEADER_DATE = "220619_";
Int_t max_event_number = 0;//仮置き、後でファイルから読み取ります。


TString Getrawfilename(Int_t ID)
{
  stringstream name;
  name<<FILE_HEADER_DATE<<setw(6)<<setfill('0')<<ID<<".csv";
  
  return (TString)name.str();
}







TString Gettreefilename(Int_t ID)//file tukuru toki
{
  stringstream name;
  name<<FILE_HEADER_DATE<<setw(6)<<setfill('0')<<ID<<".root";
  //name<<FILE_HEADER_NAME<<setw(6)<<setfill('0')<<ID<<".root";
  return (TString)name.str();
}








void csv_read_test(Int_t ID){//int_t は多分符号付きって意味だよ
  // ifstream ifs("/Users/gotoyu/Desktop/practice1/long_oscillo_sample.csv");
  TString rawfile_name = RAWFILE_PATH + Getrawfilename(ID);
  cerr<<"raw file; "<<rawfile_name<<endl;
  // ifstream fin(rawfile_name, ios::binary);//ifsかfin は好みの違い
  ifstream ifs(rawfile_name);
  if(ifs.fail()){cerr<<"error by file open!"<<endl; return ;}
  Int_t event_number = 0;
  int tmpint = 20; //最初こいつには適当に7以上の数字が詰まっていますが、後から書き換えられます。
  TString treefile_name = Gettreefilename(ID);
  TFile *file = new TFile(TREEFILE_PATH + treefile_name, "recreate");//新規rootファイルを生成
  //TFile *file = new TFile("file_test3.root","recreate"); //新規rootファイルを生成
  TTree *tree = new TTree("tree","tree");
  int n =0;//まじでここ０にしとくの大事
  double temporaly[5] ={0,0,0,0,0};
  //   int real_event_number = 0;
  tree->Branch("event_number", &event_number);//
  //tree->Branch("n", &n);// 意味不cout はできるのに
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

