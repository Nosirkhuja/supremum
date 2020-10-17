#include<iostream>
#include <vector>
#include <stdio.h>
template <int D> class Ind {
	int p[D];

	void set_x() {}
	template <typename T2, typename ... Args>
	void set_x(const T2& x, const Args&... xxx) { p[D - 1 - sizeof...(Args)] = x; set_x(xxx...); }

public:
	template <typename ... Args> explicit Ind(const Args&... xxx) {
		//static_assert(sizeof...(Args) == D, "illegal parametrs count!");
		set_x(xxx...);
	}

	int& operator [](int i) { return p[i]; }
	const int& operator [](int i) const { return p[i]; }
	int operator * (const Ind &b) const { int res = 0; for (int i = 0; i < D; i++) res += p[i] * b[i]; return res; }
	int prod() const { int res = p[0]; for (int i = 1; i < D; i++) res *= p[i]; return res; }
};

template<typename ... Args> inline Ind<sizeof...(Args)> ind(Args ... args) { return Ind<sizeof...(Args)>(args...); }


template <typename T, int D> class ArrD {
	std::vector<T> data;
	Ind<D> N, mul;
public:
	const Ind<D>& size() const { return N; }

	void init(const Ind<D> &N_) {
		N = N_; mul[0] = 1;
		for (int i = 1; i < D; i++) mul[i] = mul[i - 1] * N[i - 1];
		data.resize(N.prod());
	}
	T& operator [](const Ind<D> &pos) { return data[pos*mul]; }
	const T& operator [](const Ind<D> &pos) const { return data[pos*mul]; }
};

int main() {
	int size; std::cin>>size;
	double a,h,tau; std::cin>>a>>h;
	tau=h*h/(4*a*a);
	double coef=a*tau/(h*h);
	ArrD<double, 2> u, v;
	u.init(ind(size, size));
	v.init(ind(size, size));
	for (int j = 0; j < size; j++){ 
		for (int i = 0; i < size; i++){ 
			u[ind(i, j)] = 0;
		}
	}
	u[ind(size/2, size/2)] = 1.0;
	
	for (int t = 0; t < 100; t++) {
		for (int j = 1; j < size; j++){
			for (int i = 1; i < size; i++){
				v[ind(i,j)] = coef*(u[ind(i+1,j)]+u[ind(i,j+1)]+u[ind(i-1,j)]+u[ind(i,j-1)]-4*u[ind(i,j)])+u[ind(i,j)];
			}
		}
		 u = v;
	}
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			std::printf("%lf %lf %lf \n",(i-1)*h,(j-1)*h,u[ind(i,j)]);
		}
	}
		return 0;
	};
