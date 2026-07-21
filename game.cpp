#include<bits/stdc++.h>
#include<windows.h>
#include<conio.h>
using namespace std;
char ch[17][17];
char name[1005];
random_device rd;
bool def,dsp=true;
mt19937 rnd(rd());
long long cnt,tk;
set<pair<int,int> >mp;
double d;
stack<char>stk;
char cr[]="ABCDEF";
struct box{
	int _x,_y;
	int k;
	box()
	{
		_x=_y=0;
	}
};
struct plnt{
	int hx,hy,k;
	char c;
	plnt()
	{
		hx=1;
		hy=16;
		k=0;
		c='O';
		ch[hx][hy]=c;
	}
	void mvpl()
	{
    	ch[hx][hy]=' ';
    	hy--;
		if(hy<0) hy=16;
    	ch[hx][hy]=c;
	}
}; 
vector<int>star;
box x;
int e,g,_dec,cb=1,cbtm;
bool mv;
void disp()
{
	system("cls");
	for(int i=1;i<=15;++i)
	{
		for(int j=1;j<=15;++j) printf("%c",ch[i][j]);
		printf("\n");
	}
	printf("\n");
	if(dsp)
	{
		printf("Current score: %lld/%d\n",cnt,e);
		printf("Current used time: %.2lf s\n",(clock()-d)/CLOCKS_PER_SEC);
		printf("Current ticks: %lld\n",tk);
		if(cb==2) printf("Remain combo time: %d\n",cbtm);
		if(cbtm>=25) printf("Combo time!\n");
	}
}
inline void pr(string str)
{
	for(auto k:str) printf("%c",k),Sleep(50);
}
void wrg()
{
	printf("Your input is invalid.Try again.\n");
	Sleep(1000);
}
int rg;
int hx,hy;
char lft,rgt,hp,qt,ds;
bool w,gr=true;
int main()
{
	for(int i=1;i<=15;++i) ch[1][i]=' ';
	plnt plt;
	SetConsoleTitleA("Box Hiter");
	system("color 79");
	char read=' ';
	do{
		system("cls");
		printf("Welcome to Box Hiter!\n");
		printf("press s to start the game");
		for(int i=1;i<=rnd()%3+1;++i) printf("."),Sleep(500);
		printf("\n");
	}while(!_kbhit());
	read=_getch();
	if(read!='s'&&read!='S') return 0;
	system("cls");
	system("color B9");
	FILE* rd=fopen("player.dat","r");
	if(rd!=nullptr)
	{
		int m=MessageBox(NULL,"Do you want to use your last username?","Username",MB_YESNO);
		if(m==IDYES)
		{
			fseek(rd,0,SEEK_END);
    		int sz=ftell(rd);
    		fseek(rd,0,SEEK_SET);
    		fread(name,1,sz,rd);
    		name[sz]='\0';
    		goto Ann;
		}
	}
	{
		string qw("Do you want to use default name?press d for default\n");
		pr(qw);
		char qn=_getch();
		if(qn=='d')
		{
			name[0]='G';
			name[1]='u';
			name[2]='e';
			name[3]='s';
			name[4]='t';
			int gx=rnd()%9+1;
			char r=gx+'0';
			name[5]=r;
			name[6]='\0';
			goto Nm;		
		}
		{
			string q("Input your name:");
			pr(q);
			scanf("%s",name);		
		}
		Nm:
		;
	}
	Ann:
	string r("Decide the mode: 1 for difficult,and 0 for easy\n");
	pr(r);
	char y=_getch();
	if(y=='1') e=5,g=5;
	else if(y=='0') e=3,g=8;
	else
	{
		printf("Invalid input.Try again\n");
		Sleep(1000);
		goto Ann;
	}
	int qry=MessageBox(NULL,"Do You Want To Use Default Keys?\n(a for left,d for right,q for quit and f for jump,s for display set,range is 20)","Settings",MB_YESNO);
	if(qry==IDYES)
	{
		def=true;
		goto Next;
	}
	{
		A:
		string okf("Input left key:\n");
		pr(okf);
		lft=_getch();
		if(lft<'a'||lft>'z')
		{
			wrg();
			goto A;
		}
		Again:
		string e2("Input right key:\n");
		pr(e2);
		rgt=_getch();
		if(lft==rgt||rgt<'a'||rgt>'z')
		{
			wrg();
			goto Again;
		}
		Ag:
		string e3("Input jump key:\n");
		pr(e3);
		hp=_getch();
		if(hp==lft||hp==rgt||hp<'a'||hp>'z')
		{
			wrg();
			goto Ag;		
		}
		Rp:
		string e4("Input quit key:\n");
		pr(e4);
		qt=_getch();
		if(qt==lft||qt==rgt||qt==hp||qt<'a'||qt>'z')
		{
			wrg();
			goto Rp;		
		}
		Rpt:
		string e5("Input display set key:\n");
		pr(e5);
		ds=_getch();
		if(ds==lft||ds==rgt||ds==hp||ds==qt||ds<'a'||ds>'z')
		{
			wrg();
			goto Rpt;
		}
		Af:
		if(e==5)
		{
			string e6("Input the decrease time(the less is 10,the most is 30)\n");
			pr(e6);
			cin>>rg;
			if(rg<10||rg>30)
			{
				printf("Invalid input.Try again\n");
				Sleep(1000);
				goto Af;		
			}
		}
	}	
	Next:
	if(def)
	{
		rg=20;
		lft='a';
		rgt='d';
		hp='f';
		qt='q';
		ds='s';
	}
	srand(time(0));
	system("color A9");
	for(int i=1;i<=15;++i) ch[14][i]=ch[15][i]='#';
	x._x=10;
	x._y=rand()%14+2;
	ch[x._x][x._y]='H';
	hx=10;
	hy=1;
	ch[12][1]=ch[13][1]='#';
	ch[hx][hy]='@';
	ch[hx+1][hy]='/';
	ch[14][rnd()%14+2]=' ';
	if(e==5)
	{
	int kg=rnd()%14+2;
	while(ch[14][kg-1]!='#'||ch[14][kg]!='#'||ch[14][kg+1]!='#') kg=rnd()%14+2;
	ch[14][kg]=' ';
	}
	d=clock();
	while(true)
	{
		if(e==5)
		{
			if(_dec==rg)
			{
				--cnt;
				_dec=0;
				if(cnt<0)
				{
					system("cls");
					system("color C9");
					printf("You Lose...\n");
					Sleep(1500);
					return 0;
				}
			}
		}
		++plt.k;
		if(plt.k==8)
		{
			plt.k=0;
			plt.mvpl();
		}
		++tk;
		for(int i=1;i<=15;++i) ch[3][i]=' ';
		for(int i=1;i<=5;++i)
		{
			int gh=rnd()%15+1;
			while(ch[3][gh]=='#') gh=rnd()%15+1;
			ch[3][gh]='_';
		}
		for(int i=1;i<=15;++i) ch[2][i]=' ';
		if(plt.hy!=16&&plt.hy!=0) star.clear();
		if(plt.hy==16||plt.hy==0)
		{
			if(star.size())
			{
				if(tk&1)
				{
					for(auto s:star) ch[2][s]='*';
				}
				else
				for(auto s:star) ch[2][s]=' ';
			}
			else
			{
				int tt=rnd()%10+1;
				for(int i=1;i<=tt;++i) star.push_back(rnd()%15+1);
				for(auto s:star) ch[2][s]='*';
			}
		}
		disp();
		if(!gr&&!mv)
		{
			Sleep(100);
			ch[hx+2][hy]=ch[hx+1][hy];
			ch[hx+1][hy]='@';
			ch[hx][hy]=' ';
			++hx;
			if(ch[hx+2][hy]!=' ') gr=true;
		}
		if(mv==true) mv=false;
		if(_kbhit())
		{
			char c=_getch();
			c=tolower(c);
			if(c==lft&&hy>1&&ch[hx+1][hy-1]==' ')
			{
				w=true;
				ch[hx+1][hy-1]='\\';
				ch[hx][hy-1]='@';
				ch[hx][hy]=ch[hx+1][hy]=' ';
				--hy;
			}
			else if(c==rgt&&hy<15&&(hx==10||hx==11||hx==12||ch[hx+1][hy+1]==' '))
			{
				w=false;
				ch[hx+1][hy+1]='/';
				ch[hx][hy+1]='@';
				ch[hx][hy]=ch[hx+1][hy]=' ';
				++hy;
			}
			else if(c==qt)
			{
				FILE* wp=fopen("world.dat","w");
				for(int i=1;i<=15;++i)
				{
					for(int j=1;j<=15;++j) fprintf(wp,"%c",ch[i][j]);
					fprintf(wp,"\n");
				}
				fclose(wp);
				return 0;
			}
			else if(c==hp&&hx>1&&gr)
			{
				mv=true;
				ch[hx-1][hy]='@';
				ch[hx][hy]=ch[hx+1][hy];
				ch[hx+1][hy]=' ';
				--hx;
				gr=false;
				if(ch[hx-1][hy]=='H')
				{
					if(!mp.count({hx-1,hy}))
					{
						mp.insert({hx-1,hy});
						cnt+=cb;
						_dec=0;
						if(cb==1&&!cbtm)
						{
							cb=2;
							cbtm=30;							
						}
					}
					printf("\a");
				}
			}
			else if(c==ds) dsp=!dsp;
		}
		if(ch[hx+2][hy]!='#') gr=false;
		if(ch[hx+2][hy]=='#') gr=true;
		if(cnt>=e)
		{
			printf("\a");
			system("cls");
			system("color E9");
			printf("You Win!\n");
			Sleep(500);
			printf("Used time:%.2lf s\n",(clock()-d)/CLOCKS_PER_SEC);
			FILE* fp=fopen("Box_hiter.dat","a");
			for(int o=1;o<=20;++o) fprintf(fp,"-");
			fprintf(fp,"\n");
			fprintf(fp,"Username: %s\n",name);
			fprintf(fp,"Used time: %.2lf s\n",(clock()-d)/CLOCKS_PER_SEC);
			if(e==5) fprintf(fp,"Difficulty: difficult\n");
			else
			fprintf(fp,"Difficulty: easy\n");
			unsigned int rn=rnd();
			while(rn)
			{
				int rem=rn%16;
				if(rem<=9&&rem>=0) stk.push(rem+'0');
				else
				stk.push(cr[rem-10]);
				rn/=16;
			}
			fprintf(fp,"Code: ");
			while(stk.size())
			{
				fprintf(fp,"%c",stk.top());
				stk.pop();
			}
			fprintf(fp,"\n");
			time_t tm;
			time(&tm);
			string y(ctime(&tm));
			fprintf(fp,y.c_str());
			fprintf(fp,"Used ticks: %lld ticks\n",tk);
			for(int o=1;o<=20;++o) fprintf(fp,"-");
			fprintf(fp,"\n");
			FILE* f2=fopen("player.dat","w");
			fprintf(f2,name);
			fclose(f2);
			fclose(fp);
			Sleep(2000);
			return 0;
		}
		if(x.k==g)
		{
			ch[x._x][x._y]=' ';
			x._y=rand()%14+2;
			x.k=0;
			ch[x._x][x._y]='H';
		}
		++x.k;
		++_dec;
		--cbtm;
		if(cbtm<=0)
		{
			cbtm=0;
			cb=1;
		}
		if(tk>=3020)
		{
			system("cls");
			system("color C9");
			printf("You Lose...\n");
			Sleep(1500);
			return 0;
		}
	}
	return 0;
}
