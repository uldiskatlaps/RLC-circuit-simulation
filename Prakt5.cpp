#include <graphics.h>
#include <iostream>
#include <cmath>
using namespace std;

class elektriskais_elements
{
public:
	double Um=230, f=50, R=10, XL=20, XC=8;
	double i[2000], ur[2000], ul[2000], uc[2000], u[2000];
	int n=0;
		
	void modelet(double ts, double tb, double dt)
	{
		double Z, Im, fi, t;
		Z=sqrt(pow(R,2)+pow(XL-XC,2));
		Im=Um/Z;
		fi=asin((XL-XC)/Z);
		
		for(t=ts; t<=tb; t+=dt)
		{
			i[n]=Im*sin(2*M_PI*f*t+fi);
			ur[n]=Im*R*sin(2*M_PI*f*t+fi);
			ul[n]=Im*XL*sin(2*M_PI*f*t+fi+M_PI/2);
			uc[n]=Im*XC*sin(2*M_PI*f*t+fi-M_PI/2);
			u[n]=Um*sin(2*M_PI*f*t);
			n++;
		}
	}
	void zimet(double *i, double *u, int y, int n, double mi, double mu, int ci, int cu);
};

void elektriskais_elements::zimet(double *i, double *u, int y, int n, double mi, double mu, int ci, int cu){
	for(int x=0; x<n-1; x++)
	{
		setcolor(cu);
		line(x,y-u[x]*mu,x+1,y-u[x+1]*mu);
		setcolor(ci);
		line(x,y-i[x]*mi,x+1,y-i[x+1]*mi);
	}
}

class Rezistors: public elektriskais_elements{
public:
	Rezistors(){
	}
};

class Spole: public elektriskais_elements{
public:
	Spole(){	
	}
};

class Kondensators: public elektriskais_elements{
public:
	Kondensators(){
	}
};

class Avots: public elektriskais_elements{
public:
	Avots(){
	}
};

int main()
{
	Rezistors rezistors;
	Spole spole;
	Kondensators kondensators;
	Avots avots;
	
	rezistors.modelet(0, 1, 0.001);
	spole.modelet(0, 1, 0.001);
	kondensators.modelet(0, 1, 0.001);
	avots.modelet(0, 1, 0.001);
	
	initwindow(1024,600,"Grafikas logs");
	rezistors.zimet(rezistors.i, rezistors.ur, 150, 1000, 1.2, 0.2, 14, 11);
	spole.zimet(spole.i, spole.ul, 250, 1000, 1.2, 0.2, 14, 10);
	kondensators.zimet(kondensators.i, kondensators.uc, 350, 1000, 1.2, 0.2, 14, 9);
	avots.zimet(avots.i, avots.u, 50, 1000, 1.2, 0.2, 14, 12);

	while(!kbhit());
	closegraph();
}
