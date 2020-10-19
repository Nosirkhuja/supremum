#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <errno.h>


int main(int argc, char **argv) {
	double Gamma, Omega, A, h, t_min, t_max, x=0.0, v=0.0;
	char *eptr;
	if (argc <= 2) {
		perror("Error in argc: argc<=3 (wait Gamma, Omega) \n");
		exit(1);
	}
	errno = 0;
	Gamma = std::strtod(argv[1], &eptr);
	Omega = std::strtod(argv[2], &eptr);
	A = 1;
	h = std::min(2.0*M_PI/200, 2.0*M_PI/(Omega*200));
	t_min = 50/Gamma;
	t_max = t_min + 100.0*M_PI/Omega;

	for (double t = 0; t < t_max; t += h) {
		x += v*h*0.5;
		v += h*(-x - 2.0*Gamma*v + A*std::sin(Omega * (t+h/2)));
		x += h*v*0.5;
		std::printf("%lf %lf %lf\n", t, x, v);
	}
	return 0;
}