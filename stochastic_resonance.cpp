#include <iostream>
#include <vector>
#include <stdio.h>
#include <cmath>
#include <cstdlib>

template <int D, typename T=double> class Vec{
		T p[D];
		
		void set_x(){}
		template <typename T2, typename ... Args>
		void set_x(const T2& x, const Args&... xxx){	p[D-1-sizeof...(Args)] = x; set_x(xxx...); }
	public:
		static int size(){ return D; }
		
        explicit Vec(T val=0) { for(int i=0; i<D; i++) p[i] = val; }    
		Vec(const Vec<1, T> &v){ for(int i=0; i<D; i++) p[i] = v[0]; }

		template <typename ... Args> explicit Vec(const Args&... xxx){ 
			static_assert(sizeof...(Args)==D, "illegal parametrs count!"); 
			set_x(xxx...); 
		}

		
		T  operator [] (int i) const { 
			return p[i]; 
		} 
		T& operator [] (int i) { 
			return p[i]; 
		} 

		template <typename ... Args> 
		Vec<sizeof ...(Args), T> operator ()(Args ... xxx) const { 
			return Vec<sizeof ...(Args), T>((*this)[xxx]...);
		}
		template <int D2> Vec<D2, T> operator ()(const Vec<D2, int> &I) const { 
			Vec<D2, T> res; for(int i=0; i<D2; i++) res[i] = (*this)[I[i]]; 
			return res;
		}
	};
double randd() {
  const double rand_alpha=1./(1.+RAND_MAX);
  double rand_alpha2PI=2*M_PI/(1.+RAND_MAX);
  return sqrt(-2.*log(rand_alpha*(random()+1)))*cos(rand_alpha2PI*random());
}

int main(int argc, char const *argv[])
{
	if (argc <= 4) {
		perror("Error in argc: argc<=3 (wait size >=1000, 0.01<=tau<=0.05), tmax, tpc \n");
		exit(1);
	}

	char *eptr;
	errno = 0;

	int size; 
	double tau,gamma,tpc,tmax;

	size = int(std::strtod(argv[1], &eptr));
	tau = std::strtod(argv[2], &eptr);
	tmax = std::strtod(argv[3], &eptr);
	tpc = std::strtod(argv[4], &eptr);
	gamma=0.1;

	std::vector<Vec<2> > data;
	data.resize(size);

	double a=-1; double b=1; double Tm=0.1;
	double tgT =  sqrt(2*tau*gamma*Tm);

	for(Vec<2> &p: data){
		p[0]=0;
		p[1]=0;
	}
	for(double t=0; t<tmax; t=t+tau){
	for(Vec<2> &p: data){
		p[0] += p[1]*tau*.5; 
		p[1] += tau*(-a*p[0]-b*p[0]*p[0]*p[0]);
		p[0] += p[1]*tau*.5;
		p[1] += (-gamma*p[1]*tau+tgT*randd());

	}
	if (fabs(t-tpc) <= 1e-7) for(Vec<2> &d: data){
		printf("%lf %lf\n", d[0],d[1]);
	}
	}

	

}
