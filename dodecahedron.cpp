#include <iostream>
#include <math.h>

struct V {
	double x,y,z;
	V(): x(0),y(0),z(0) {}
	V(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

	V operator - () const { return V(-x,-y,-z);}
	V operator + (const V& b) const { return V(x+b.x, y+b.y, z+b.z);}
	V operator - (const V& b) const { return V(x-b.x, y-b.y, z-b.z);}
	V operator * (double S) const { return V (x*S, y*S, z*S);}
	void operator += (const V&b) { x+= b.x; y+= b.y ; z+= b.z;}
	V operator %( const V &b) const { return V(y*b.z-z*b.y, -x*b.z+z*b.x, x*b.y-y*b.x);}
	double operator * (const V& b) const { return (x*b.x + y*b.y + z*b.z);} 
	double abs () const { return sqrt(x*x+y*y+z*z) ;}
	V rotate (const V& b) const { return V(x,y,z)*cos(b.abs()) - (V(x,y,z)%b)*(sin(b.abs())/b.abs()) + b*(V(x,y,z)*b)*((1-cos(b.abs()))/(b*b)); }

	
};

V operator *( double d, const V &v ) { return v*d; }
std::ostream& operator << (std::ostream& S, const V& a) {S<<a.x <<' ' << a.y << ' ' << a.z<<'\n'; return S;}
  
////////////////////////////

struct G{
	V data[5];
	V& operator [](int i) /*const*/ { return data[i]; }
	const V& operator [](int i) const { return data[i]; }
	G operator - () const {G newG = *this; 
		for(int i=0; i<5;i++) newG.data[i] = -newG.data[i];
		return newG;}
	G rotate(const V& b) const { G newG = *this; for(int i=0; i<5;i++) newG.data[i] = newG.data[i].rotate(b);
		return newG;}
	//G rotate(int i) const {}

};

std::ostream& operator << (std::ostream& S, const G& g){
	for(int i=0; i<6; i++) S<<g[i%5];
	return S<<"\n\n";
}

int main(){
	//1. первая грань 
	G g0; g0[0] = V(0,0.607062,0.79465);
	for(int i=1; i<5; i++) g0[i] = g0[i-1].rotate(V(0, 0, 2*M_PI/5));
	std::cout<<g0<<-g0;

	//2. все остальное
	for(int i=0; i<5; i++){
		G g = g0.rotate(g0[i]*(2*M_PI/3));
		std::cout<<g<<-g;
	}
	
	return 0;
}
//////////////////////////////////нахождение грани 
