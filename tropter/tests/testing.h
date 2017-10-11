#ifndef TROPTER_TESTING_H
#define TROPTER_TESTING_H

#include <catch.hpp>

/// Compare any two Eigen matrices (their dimensions and each element)
/// using Catch, with a given relative error tolerance.
// Extra parentheses are to avoid a warning from GCC 5.4.
#define TROPTER_REQUIRE_EIGEN(actual, expected, rel_error_tolerance)         \
do {                                                                         \
    REQUIRE((actual.rows() == expected.rows()));                             \
    REQUIRE((actual.cols() == expected.cols()));                             \
    for (int ir = 0; ir < actual.rows(); ++ir) {                             \
        for (int ic = 0; ic < actual.cols(); ++ic) {                         \
            INFO("(" << ir << "," << ic << "): " <<                          \
                    actual(ir, ic) << " vs " << expected(ir, ic));           \
            REQUIRE((Approx(actual(ir, ic)).epsilon(rel_error_tolerance)     \
                    == expected(ir, ic)));                                   \
        }                                                                    \
    }                                                                        \
} while (0)

/// Similar to TROPTER_REQUIRE_EIGEN, but using an absolute error tolerance.
#define TROPTER_REQUIRE_EIGEN_ABS(actual, expected, abs_error_tolerance)     \
do {                                                                         \
    REQUIRE((actual.rows() == expected.rows()));                             \
    REQUIRE((actual.cols() == expected.cols()));                             \
    for (int ir = 0; ir < actual.rows(); ++ir) {                             \
        for (int ic = 0; ic < actual.cols(); ++ic) {                         \
            INFO("(" << ir << "," << ic << "): " <<                          \
                    actual(ir, ic) << " vs " << expected(ir, ic));           \
            REQUIRE((Approx(actual(ir, ic)).margin(abs_error_tolerance)      \
                    == expected(ir, ic)));                                   \
        }                                                                    \
    }                                                                        \
} while (0)

#endif // TROPTER_TESTING_H