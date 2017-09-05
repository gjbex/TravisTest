#include <armadillo>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_roots.h>
#include <ostream>

double current_i5(double R4, void *params);

int main(int argc, char *argv[]) {
    const int max_iters {100};
    const double R4_min {20.0};
    const double R4_max {100.0};
    gsl_function curr_func {
        .function = &current_i5,
        .params = nullptr
    };
    auto solver = gsl_root_fsolver_alloc(gsl_root_fsolver_brent);
    gsl_root_fsolver_set(solver, &curr_func, R4_min, R4_max);
    std::cout.precision(6);
    int status;
    double R4, i5;
    for (int iter = 1; iter <= max_iters; iter++) {
        gsl_root_fsolver_iterate(solver);
        R4 = gsl_root_fsolver_root(solver);
        auto R4_lower {gsl_root_fsolver_x_lower(solver)};
        auto R4_upper {gsl_root_fsolver_x_upper(solver)};
        status = gsl_root_test_interval(R4_lower, R4_upper, 1e-8, 0.0);
        i5 = current_i5(R4, nullptr);
        std::cout << iter
                  << ": R4 = " << std::defaultfloat << R4
                  << ", i5 = " << std::defaultfloat << i5
                  << std::endl;
        if (status != GSL_CONTINUE)
            break;
    }
    if (status == GSL_SUCCESS) {
        std::cout << "R4 = " << std::defaultfloat << R4
                  << ", i5 = " << std::defaultfloat << i5
                  << std::endl;
        return 0;
    } else {
        std::cerr << "no convergence" << std::endl;
        return 1;
    }
}

using namespace arma;

double current_i5(double R4, void *params) {
    const double E {5.0};
    const double R1 {10.0};
    const double R2 {20.0};
    const double R3 {30.0};
    const double R5 {1000.0};
    mat A {
    /*    i0,   i1,   i2,    i3,    i4,   i5   */
        {1.0,  1.0, -1.0,   0.0,   0.0,  0.0},
        {0.0,  0.0,  1.0,   0.0,  -1.0, -1.0},
        {0.0, -1.0,  0.0,   1.0,   0.0,  1.0},
        {0.0,   R1,  0.0,    R3,   0.0,  0.0},
        {0.0,   R1,   R2,   0.0,   0.0,   R5},
        {0.0,  0.0,  0.0,    R3,    R4,  -R5}
    };
    vec b {0.0, 0.0, 0.0, E, 0.0, 0.0};
    vec x = solve(A, b);
    double i5 {x(5)};
    return i5;
}
