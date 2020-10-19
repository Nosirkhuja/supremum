#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <iostream>
#include <errno.h>

int main(int argc, char **argv) {
	double Gamma, Omega, t, x, v, t_prev, x_prev, riemann_re=0.0, riemann_im=0.0, t_min;
	if (argc <= 2) {
		perror("Error in argc: argc<=2 (wait Gamma, Omega)\n");
		exit(1);
	}
	char *eptr;
	errno = 0;
	Gamma = std::strtod(argv[1], &eptr);
	Omega = std::strtod(argv[2], &eptr);
	std::scanf ("%lf %lf %lf", &t_prev, &x_prev, &v);
	t_min = 30/Gamma;
	std::string line;
	std::stringstream myString;
	while (std::getline(std::cin, line)){
		std::stringstream myString(line); myString>>t>>x;
		riemann_re += (std::cos (Omega *(t+t_prev)*0.5)*(x+x_prev)*0.5)* (t-t_prev);
		riemann_im += (std::sin (Omega *(t+t_prev)*0.5)*(x+x_prev)*0.5)* (t-t_prev);
		t_prev = t;
		x_prev = x;
	}
	riemann_re=2*riemann_re/(t - t_min);
	riemann_im=2*riemann_im/(t - t_min);
	std::printf ("%lf \n", sqrt(riemann_re*riemann_re+riemann_im*riemann_im));
	return 0;
}

//for W in $(seq .1 .01 2); do echo -n "$W " >> 1.dat ; ./ody 0.1 $W 1 | ./furie 0.1 $W >> 1.dat ; done
//gnuplot -e 'plot "new2.dat" u ($1):(sqrt(($2)*($2)+($3)*($3))) w l;pause -1'
