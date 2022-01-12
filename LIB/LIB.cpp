#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include "time.h"
#define BOOKFILENAME "C:\\Users\\lenovo\\Documents\\HELLOWORLD\\LIB\\book.txt"//改为自己的文件路径
#define LIBRARIANFILENAME "C:\\Users\\lenovo\\Documents\\HELLOWORLD\\LIB\\librarian.txt"
#define READERFILENAME "C:\\Users\\lenovo\\Documents\\HELLOWORLD\\LIB\\reader.txt"
#define BORROWFILENAME "C:\\Users\\lenovo\\Documents\\HELLOWORLD\\LIB\\borrow.txt"
#define SEPCHAR " "
#define MAXFIELD 20//对象最多数据成员数
#define MAXSIZE 1024//对象最大占用空间
#define MAXINFO 1000//最大单项对象数
using namespace std;

class INFOBASE{
	int id;
	static int idseq;
public:
	INFOBASE(){id=++idseq;}
	INFOBASE(int id1){id=id1;}
	void setID(int id1){id=id1;}
	int getID(){return id;}
	virtual void setInfo(string*)=0;
	virtual void getInfo(string*)=0;
	static void setseq(int seq){idseq=seq;}
	static int getseq(){return idseq;}
	virtual void output(ostream&)=0;
	virtual ~INFOBASE(){}
};
int INFOBASE::idseq=0;
class BKINFO:public INFOBASE{
	string name;
	string writer;
public:
	BKINFO(){}
	BKINFO(int id,string nm,string wt):INFOBASE(id){name=nm;writer=wt;}
	BKINFO(string nm,string wt){name=nm;writer=wt;}
	void setInfo(string *wt){name=wt[0];writer=wt[1];}
	void getInfo(string *wt){wt[0]=name;wt[1]=writer;}
	void output(ostream& ofile){
		ofile<<getID()<<SEPCHAR<<name.data()<<SEPCHAR<<writer.data()<<endl;
	}
};
//
/*class readerinfo:public INFOBASE{
	string name;
	string xinB;
public:
	friend ostream& operator<<(ostream& cout1, readerinfo& p);
	readerinfo(){}
	readerinfo(int n,string x,string a):INFOBASE(n){name = x;xinB = a;}
	readerinfo(string n,string a){name = n;xinB = a;}
	void setInfo(string *s){name = s[0];xinB = s[1];}
	void getInfo(string *s){s[0] = name; s[1] = xinB;}
	void output(ostream& cout1){cout1<<name<<xinB<<endl;}
};
class MANGEINFO: public INFOBASE{
	string name;
	string remark;
public:
	friend ostream& operator<<(ostream& cout2, MANGEINFO& p);
	MANGEINFO(){}
	MANGEINFO(int n,string na,string r):INFOBASE(n){name = na;remark = r;}
	MANGEINFO(string na,string r){name = na;remark = r;}
	void setInfo(string *s){name = s[0];remark = s[1];}
	void getInfo(string *s){s[0] = name;s[1] = remark;}
	void output(ostream& cout2){cout2<<name<<remark;}
};*/
class RDINFO:public INFOBASE{//自
	string name;
	string sex;
public:
	RDINFO(){}
	RDINFO(int id,string nm,string sx):INFOBASE(id){name=nm;sex=sx;}//id,姓名，性别
	RDINFO(string nm,string sx){name=nm;sex=sx;}
	void setInfo(string *sx){name=sx[0];sex=sx[1];}
	void getInfo(string *sx){sx[0]=name;sx[1]=sex;}
	void output(ostream& ofile){
		ofile<<getID()<<SEPCHAR<<name.data()<<SEPCHAR<<sex.data()<<endl;
	}
};
class LBINFO:public INFOBASE{//自
	string name;
	string remark;
public:
	LBINFO(){}
	LBINFO(int id,string nm,string rm):INFOBASE(id){name=nm;remark=rm;}//id,姓名，备注
	LBINFO(string nm,string rm){name=nm;remark=rm;}
	void setInfo(string *rm){name=rm[0];remark=rm[1];}
	void getInfo(string *rm){rm[0]=name;rm[1]=remark;}
	void output(ostream& ofile){
		ofile<<getID()<<SEPCHAR<<name.data()<<SEPCHAR<<remark.data()<<endl;
	}
};
//
class BRINFO:public INFOBASE{	//借阅信息
	string book;
	string reader;
	string librarian;
	string borrowTime;
	string returnTime;
public:
	BRINFO(){}
	BRINFO(int id,string bk,string rd,string lib,string time1,string time2="//"):INFOBASE(id){
		book=bk;reader=rd;librarian=lib;borrowTime=time1,returnTime=time2;
	}
	BRINFO(string bk,string rd,string lib,string time1,string time2="//"){
		book=bk;reader=rd;librarian=lib;borrowTime=time1,returnTime=time2;
	}
	void setInfo(string *wt){
		book=wt[0],reader=wt[1];librarian=wt[2];borrowTime=wt[3],returnTime=wt[4];
	}
	void getInfo(string *wt){wt[0]=book; wt[1]=reader;wt[2]=librarian;
wt[3]=borrowTime,wt[4]=returnTime;}
	void output(ostream& ofile){
		ofile<<getID()<<SEPCHAR<<book.data()<<SEPCHAR<<
reader.data()<<SEPCHAR<<librarian.data()<<SEPCHAR;
		ofile<<borrowTime.data()<<SEPCHAR<<returnTime.data()<<endl;
	}
};
class INFOMANAGE{
protected:
	INFOBASE *info[MAXINFO];
	int infocounter;
public:
	INFOMANAGE():infocounter(0){}
	virtual void CreateObj(string*)=0;
	virtual void NewInfo(string*)=0;
	void Save(char* FileName){
		ofstream outfile(FileName);
		if(!outfile.is_open()) return;
		for(int i=0;i<infocounter;++i) info[i]->output(outfile);
		outfile.close();
	}
	void Load(char* FileName){
		ifstream infile(FileName);
		if(!infile.is_open()) return;
		for(int i=0;i<infocounter;++i) delete info[i];//删除原有信息
		infocounter=0;
		INFOBASE::setseq(0);
		char inl[MAXSIZE+1];
		string field[MAXFIELD];//最大限定数据成员个数
		infile.getline(inl,MAXSIZE);//从文件中读取一行数据
		while(!infile.eof()){
			int j=0;
			char *tokenPtr=strtok(inl,SEPCHAR);//空格分隔
			while(tokenPtr!=NULL){
				field[j++]=tokenPtr;
				tokenPtr=strtok(NULL,SEPCHAR);
			}
			if(atoi(field[0].data())>INFOBASE::getseq())
 INFOBASE::setseq(atoi(field[0].data()));
			CreateObj(field);//构造对象并存储指针
			infile.getline(inl,MAXSIZE);
		}
		infile.close();
	}
	int getSize(){return infocounter;}
	INFOBASE* getInfo(int i){return info[i];}
	int EraseInfo(int id){
		for(int i=0;i<infocounter;++i)
			if(info[i]->getID()==id){
				delete info[i];
//				for(int j=i;j<infocounter-1;++j) info[j]=info[j+1]; infocounter--;
				return 1;
			}
		return 0;
	}
	void BrowsInfo(){
		for(int i=0;i<infocounter;++i) info[i]->output(cout);
	}
	virtual ~INFOMANAGE(){for(int i=0;i<infocounter;++i) delete info[i];}
};
class BORROW:public INFOMANAGE{
public:
	BORROW(){INFOBASE::setseq(0);}
	void CreateObj(string *s){
		info[infocounter++]=new BRINFO(atoi(s[0].data()),s[1],s[2],s[3],s[4],s[5]);}
	void NewInfo(string *s){info[infocounter++]=new BRINFO(s[0],s[1],s[2],s[3],s[4]);}
};
//
class LIBRARIAN:public INFOMANAGE{//自
public:
	LIBRARIAN(){}
	void CreateObj(string *s){
		info[infocounter++]=new LBINFO(atoi(s[0].data()),s[1],s[2]);}
	void NewInfo(string* s){info[infocounter++]=new LBINFO(s[0],s[1]);}
};
class READER:public INFOMANAGE{//自
public:
	READER(){}
	void CreateObj(string *s){
		info[infocounter++]=new RDINFO(atoi(s[0].data()),s[1],s[2]);}
	void NewInfo(string *s){info[infocounter++]=new RDINFO(s[0],s[1]);}
};
class BOOK:public INFOMANAGE{//自
public:
	BOOK(){}
	void CreateObj(string *s){
		info[infocounter++]=new BKINFO(atoi(s[0].data()),s[1],s[2]);}
	void NewInfo(string *s){info[infocounter++]=new BKINFO(s[0],s[1]);}
};
//
class MENUCOMMON{
public:
	static void display(string info){cout<<endl<<info.data()<<endl;}
	static string getinfo(string info,int noblank=1){//默认不允许空输入
		char in[MAXSIZE+1];
		while(1){
			cout<<info.data();
			cin.getline(in,MAXSIZE);
			if(in[0]!=0||noblank==0) break;
		}
		return in;
	}
	static int getid(string info){return atoi(getinfo(info).data());}
	string getTime(){
		time_t tt = time(NULL);
		tm* t=localtime(&tt);
		char h[50];
		sprintf(h,"%d-%02d-%02d",t->tm_year+1900,t->tm_mon+1,t->tm_mday);
		return h;
	}
	virtual void newItem(INFOMANAGE *im)=0;
	virtual void changeItem(INFOMANAGE *im)=0;
	virtual void manageItem(INFOMANAGE *pb,char* fileName){
		pb->Load(fileName);
		while(1){
			display("1.新增；2.删除；3.修改；4.浏览；5.保存修改；6.放弃修改；0.返回");
			switch(getid("请选择：")){
			case 0:return;
			case 1:newItem(pb);break;
			case 2:deleteItem(pb);break;
			case 3:changeItem(pb);break;
			case 4:browseItem(pb);break;
			case 5:pb->Save(fileName);break;
			case 6:pb->Load(fileName);break;
			default:cout<<"选择错误。"<<endl;continue;
			}
		}
	}
	void alterItem(INFOMANAGE *im,string *fieldname,int count){
		int id=getid("请输入需要修改的编号：");
		int i,j=-1,k=0;
		string *str1=new string[count];
		for(i=0;i<im->getSize();++i)
			if(im->getInfo(i)->getID()==id){
				j=i;
				im->getInfo(i)->getInfo(str1);//获取对象数据字段原值
				break;
			}
		if(j<0){display("该编号不存在。");return;}
		for(i=0;i<count;++i){
			string msg1="请输入新";
			msg1=msg1.append(fieldname[i]).append("（不修改请直接回车）：");
			string temp=getinfo(msg1,0);
			if(temp.compare("")!=0) {str1[i]=temp;k=1;}
		}
		if(k) im->getInfo(j)->setInfo(str1);
	}
	void deleteItem(INFOMANAGE *im){
		if(im->EraseInfo(getid("请输入需要删除的编号：")))
display("删除成功。"); else display("删除失败。");
	}
	void browseItem(INFOMANAGE *im){
		int size=im->getSize();
		for(int i=0;i<size;++i) im->getInfo(i)->output(cout);
		if(size==0) display("无信息。");
	}
	virtual ~MENUCOMMON(){}
};
class BORROWMENU:public MENUCOMMON{
public:
	void changeItem(INFOMANAGE *im){
		int id=getid("请输入需要修改的编号：");
		int i,j=-1,k=0;
		string *str1=new string[5];
		for(i=0;i<im->getSize();++i)
			if(im->getInfo(i)->getID()==id){
				j=i;
				im->getInfo(i)->getInfo(str1);//获取对象数据字段原值
				break;
			}
		if(j<0){display("该编号不存在。");return;}
		if(str1[4].compare("//")!=0){display("该编号已还书，不能修改。");return;}
		string temp;
		temp=getinfo("请输入修改后的书籍编号名称（没有变化请直接回车）：",0);
		if(temp.compare("")!=0) {str1[0]=temp;k=1;}
		temp=getinfo("请输入修改后的读者编号姓名（没有变化请直接回车）：",0);
		if(temp.compare("")!=0) {str1[1]=temp;k=1;}
		temp=getinfo("请输入修改后的管理员编号姓名（没有变化直接回车）：",0);
		if(temp.compare("")!=0) {str1[2]=temp;k=1;}
		if(k) im->getInfo(j)->setInfo(str1);
	}
	void newItem(INFOMANAGE *im){
		string str1[5];
		str1[0]=getinfo("请输入书籍编号名称：");
		str1[1]=getinfo("请输入读者编号姓名：");
		str1[2]=getinfo("请输入管理员编号姓名：");
		str1[3]=getTime();
		str1[4]="//";
		im->NewInfo(str1);
	}
	void ReturnBook(INFOMANAGE *im){
		int id=getid("请输入需要还书的编号：");
		int i,j=-1;
		string *str1=new string[5];
		for(i=0;i<im->getSize();++i)
			if(im->getInfo(i)->getID()==id){
				j=i;
				im->getInfo(i)->getInfo(str1);//获取对象数据字段原值
				break;
			}
		if(j<0){display("该编号不存在。");return;}
		if(str1[4].compare("//")!=0){display("该编号已还书");return;}
		str1[4]=getTime();
		im->getInfo(j)->setInfo(str1);
	}
	void manageItem(INFOMANAGE *pb,char* fileName){
		pb->Load(fileName);
		while(1){
			display("1.借书；2.还书；3.修改；4.浏览；5.保存修改；6.放弃修改；0.返回");
			switch(getid("请选择：")){
			case 0:return;
			case 1:newItem(pb);break;
			case 2:ReturnBook(pb);break;
			case 3:changeItem(pb);break;
			case 4:browseItem(pb);break;
			case 5:pb->Save(fileName);break;
			case 6:pb->Load(fileName);break;
			default:cout<<"选择错误。"<<endl;continue;
			}
		}
	}
};
class LIBRARIANMENU:public MENUCOMMON{
public:
	void newItem(INFOMANAGE *im){
		string str1[2];
		str1[0]=getinfo("请输入管理员名：");
str1[1]=getinfo("请输入管理员备注（不能为空）：");
		im->NewInfo(str1);
	}
	void changeItem(INFOMANAGE *im){
		string str1[2];
		str1[0]="管理员名";  str1[1]="管理员备注";
		alterItem(im,str1,2);
	}
};
//
class READERMENU:public MENUCOMMON{//自
public:
	void newItem(INFOMANAGE *im){
		string str1[2];
		str1[0]=getinfo("请输入读者名：");
str1[1]=getinfo("请输入读者性别：");
		im->NewInfo(str1);
	}
	void changeItem(INFOMANAGE *im){
		string str1[2];
		str1[0]="读者名";  str1[1]="读者性别";
		alterItem(im,str1,2);
	}
};
class BOOKMENU:public MENUCOMMON{//自
public:
	void newItem(INFOMANAGE *im){
		string str1[2];
		str1[0]=getinfo("请输入书名：");
str1[1]=getinfo("请输入作者名：");
		im->NewInfo(str1);
	}
	void changeItem(INFOMANAGE *im){
		string str1[2];
		str1[0]="书名";  str1[1]="作者名";
		alterItem(im,str1,2);
	}
};
//
class MAINMENU{
public:
	static void run(MENUCOMMON *p,INFOMANAGE *q,char* FILENAME){
		p->manageItem(q,FILENAME);
		delete p;
		delete q;
	}
	static void Menu(){
		while(1){
			MENUCOMMON::display("1.图书管理\n2.读者管理\n3.管理员管理\n4.借阅管理\n0.返回");
			switch(MENUCOMMON::getid("请选择：")){
				case 0:return;
				case 1:run(new BOOKMENU,new BOOK,(char*) BOOKFILENAME);	break;
				case 2:run(new READERMENU,new READER,(char*)LIBRARIANFILENAME);break;
				case 3:run(new LIBRARIANMENU,new LIBRARIAN,(char*)READERFILENAME);break;
				case 4:run(new BORROWMENU,new BORROW,(char*)BORROWFILENAME);break;
				default:cout<<"选择错误。"<<endl;continue;
				}
			}
	}
};
int main(){ MAINMENU::Menu(); }
