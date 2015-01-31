#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

/////Analisi preliminare
double media(int N, double * misure)
{
	double sum=0;
	for (int i=0; i<N; i++){
		sum+=misure[i];
	}
	double media=sum/N;
	return media;
}

double scarto1(int N, double * misure)
{
	double med = media(N, misure);
	double sums=0;
	for(int i=0; i<N; i++){
		sums+=(med-misure[i])*(med-misure[i]);
	}
	double sqm=sqrt(sums/N);
	return sqm;
}


double scarto2(int N, double * misure)
{
	double eqm=sqrt((N/(N-1)))*scarto1(N, misure);
	return eqm;
}

double err_media(int N, double * misure)
{
	double em=scarto2(N, misure)/sqrt(N);
	return em;
}
/////


/////Sommatorie
double sum(int N, double * x)
{
	double sum=0;
	for(int i=0; i<N; i++){
		sum+=x[i];
	}
	return sum;
}

double sumquad(int N, double * x)
{
	double sum=0;
	for(int i=0; i<N; i++){
		sum+=(x[i]*x[i]);
	}
	return sum;
}

double sumprod(int N, double * x, double * y)
{
	double sum=0;
	for(int i=0; i<N; i++){
		sum+=(x[i]*y[i]);
	}
	return sum;
}
/////

/////Funzioni interpolazione: y=a+bx
double interp_delta(int N, double * x, double * y)
{
	double delta=N*sumquad(N, x)-((sum(N, x))*(sum(N, x)));
	return delta;
}

double interp_a(int N, double * x, double * y)
{
	double a=(1/interp_delta(N, x, y))*((sumquad(N, x))*(sum(N, y))-(sum(N, x))*(sumprod (N, x, y)));
	return a;
}

double interp_b(int N, double * x, double * y)
{
	double b=(1/interp_delta(N, x, y))*(N*(sumprod(N, x, y))-((sum(N, x))*(sum(N, y))));
	return b;
}
	
double sigmay_post(int N, double * x, double * y)
{
	double sy=0;
	for (int i=0; i<N; i++){
		sy+=((interp_a(N, x, y))+((interp_b(N, x, y))*x[i])-(y[i]))*((interp_a(N, x, y))+((interp_b(N, x, y))*x[i])-(y[i]));
	}
	sy=sy/(N-2);
	sy=sqrt(sy);
	return sy;
}

double interp_sigmaa(int N, double * x, double * y)
{
	double sa=(sigmay_post(N, x, y))*sqrt((sumquad(N, x))/(interp_delta(N, x, y)));
	return sa;
}

double interp_sigmab(int N, double * x, double * y)
{
	double sb=(sigmay_post(N, x, y))*sqrt(N/(interp_delta(N, x, y)));
	return sb;
}

double cov_mq(int N, double * x, double * y)
{
	return (-(sum(N, x)*sigmay_post(N, x, y)*sigmay_post(N, x, y)/interp_delta(N, x, y)));
}


/*
//##strutture
struct lineare_sigmadato
{
	double a, b, sa, sb;
};
//##


double max(double * dati, int N)
{
	double max;
	for(int i=0; i<N; i++){
		if(dati[i]>max) max=dati[i];
	}
	return max;
}


double min(double * dati, int N)
{
	double min;
	for(int i=0; i<N; i++){
		if(dati[i]<min) min=dati[i];
	}
	return min;
}



double lambda(double stima_1, double err_1, double stima_2, double err_2)
{
	double numer=sqrt((stima_1-stima_2)*(stima_1-stima_2));
	double denom=sqrt((err_1*err_1)+(err_2*err_2));
	double lambda=numer/denom;
	return lambda;
}


//INTERPOLAZIONE LINEARE
//##sommatorie utili e simili



double sum_normsquad(int N, double *x, double *s)
{
	double sum=0;
	for(int i=0; i<N; i++){
		sum+=(x[i])/(s[i]*s[i]);
	}
	return sum;
}

double sumquad_normsquad(int N, double *x, double *s)
{
	double sum=0;
	for(int i=0; i<N; i++){
		sum+=(x[i]*x[i])/(s[i]*s[i]);
	}
	return sum;
}

double sumprod_normsquad(int N, double *x, double *y, double *s)
{
	double sum=0;
	for(int i=0; i<N; i++){
		sum+=(x[i]*y[i])/(s[i]*s[i]);
	}
	return sum;
}

double sumone_normsquad(int N, double *s)
{
	double sum=0;
	for(int i=0; i<N; i++){
		sum+=1/(s[i]*s[i]);
	}
	return sum;
}

//##

//##sigma noto costante



	
	


double interp_sigmaa_dato(int N, double * x, double * y, double sigmay)
{
	double sa=(sigmay)*sqrt((sumquad(N, x))/(interp_delta(N, x, y)));
	return sa;
}

double interp_sigmab_dato(int N, double * x, double * y, double sigmay)
{
	double sb=(sigmay)*sqrt(N/(interp_delta(N, x, y)));
	return sb;
}
	
	

	
double interp_m(int N, double *x, double *y)
{
	double m=sumprod(N, x, y)/sumquad(N, x);
	return m;
}

double interp_sigmam_dato(int N, double *x, double sigma)
{
	double sm=sqrt((sigma*sigma)/((sumquad(N, x))));
	return sm;
}


//##

//##sigma variabile
double interp_delta_svar(int N, double *x, double *s)
{
	double delta=(sumone_normsquad(N, s)*sumquad_normsquad(N, x, s))-(sum_normsquad(N, x, s)*sum_normsquad(N, x, s));
	return delta;
}

double interp_a_svar(int N, double *x, double *y, double *s)
{
	double a=(1/interp_delta_svar(N,x,s))*(sumquad_normsquad(N,x,s)*sum_normsquad(N,y,s))-(sum_normsquad(N,x,s)*sumprod_normsquad(N,x,y,s));
	return a;
}

double interp_b_svar(int N, double *x, double *y, double*s)
{
	double b=(1/interp_delta_svar(N,x,s))*((sumone_normsquad(N,s)*sumprod_normsquad(N,x,y,s))-(sum_normsquad(N,x,s)*sum_normsquad(N,y,s)));
	return b;
}
	
double interp_sigmaa_svar(int N, double *x, double *s)
{
	double sa=sqrt((1/interp_delta_svar(N,x,s))*sumquad_normsquad(N,x,s));
	return sa;
}

double interp_sigmab_svar(int N, double *x, double *s)
{
	double sa=sqrt((1/interp_delta_svar(N,x,s))*sumone_normsquad(N,s));
	return sa;
}
//##

//##default
void print_an_default(double * misure, int N)
{
	cout << "media: "<< media(N, misure)
		 << "\nscarto quadratico medio: " << scarto1(N, misure) 
		 << "\nerrore quadratico medio: " << scarto2(N, misure) 
		 << "\nerrore sulla media: " << err_media(N, misure) 
	   	 << endl;
}

void interp_lineare_default (int N, double * x, double * y, char * nomefile)
{
	fstream dati;
	dati.open(nomefile, fstream::out);
	dati << "Retta y=" << interp_a(N, x, y) << "+" << interp_b(N, x, y) 
	<< "x. \nErrore su a=" << interp_sigmaa(N, x, y) 
	<< "; errore su b=" << interp_sigmab(N, x, y) << "." << endl;
	dati.close();
}

void interp_lineare_sigmadato(int N, double * x, double * y, double sy, char * nomefile)
{
	fstream dati;
	//cout<<N<<x<<y; ////
	double a=interp_a(N, x, y);
	double b=interp_b(N, x, y);
	double sa=interp_sigmaa_dato(N, x, y, sy);
	double sb=interp_sigmab_dato(N, x, y, sy);
	dati.open(nomefile, fstream::out);
	dati << "Retta y=" << a << "+" <<  b << "x. \nErrore su a=" << sa << "; errore su b=" << sb 
	<< ". Compatibilita' di 'a' con lo zero=" << lambda(a, sa, 0, 0) << endl;
	dati.close();
}
void interp_lin_perzero_dato(int N, double *x, double *y, double sigma, char *nomefile)
{
	fstream dati;
	dati.open(nomefile, fstream::out);
	dati << "Retta y=" << interp_m(N, x, y) << "x. \nErrore su m=" 
	<< interp_sigmam_dato(N, x, sigma) << "." << endl;
	dati.close();
}


void acq_nomefile(char * nomefile)
{
	cout << "Inserire il nome del file." << endl;
	cin >> nomefile;
}

void legg_file(double * mis_vuoto, int N, char * nomefile)
{
	fstream filedati;
	filedati.open(nomefile, fstream::in);
	for (int i=0; i<N; i++){
		filedati>>mis_vuoto[i];
	}
	filedati.close();
}


void scrivisufile (char * nomefile, char * stringa)
{
	fstream file;
	file.open(nomefile, fstream::out);
	file << stringa;
	file.close();
}
//#*/
