#include "TestUtils.h"
#include "MatlabUtilsTest.h"
#include "Position.h"
#include "Mjday.h"
#include "MeanObliquity.h"
#include "NutAngles.h"
#include "timediff.h"
#include "Frac.h"
#include "R_x.h"
#include "R_y.h"
#include "R_z.h"
#include "unit.h"
#include "EqnEquinox.h"
#include <stdlib.h>

void test_Position()
{
    double lon = -2.11796961366573;
    double lat = 0.683053277790977;
    double h = 99.81638;

    double *expected = (double*)(double[3]) {-2577383.6395731382, -4230610.2467987221, 4004108.3320587045};
    double *actual = Position(lon, lat, h);
    array_test_delta("Position() 1", expected, actual, 3, 10e-7);
    free(actual);

    lon = -1.50472339730215;
    lat = 0.533589040236714;
    h = 0.;

    expected = (double*)(double[3]) {362889.51475075335,-5484262.3610134749,3225167.7284776145};
    actual = Position(lon, lat, h);
    array_test_delta("Position() 2", expected, actual, 3, 10e-7);
    free(actual);

    lon = -1.91986217719376;
    lat = 0.698131700797732;
    h = 2000.;

    expected = (double*)(double[3]) {-1673928.5598879098,-4599080.9200722268,4079271.1474197493};
    actual = Position(lon, lat, h);
    array_test_delta("Position() 7", expected, actual, 3, 10e-7);
    free(actual);
}

void test_Mjday()
{
    int year, month, day, hour, min;
    double sec;
    double expected, actual;

    year = 2009;
    month = 5;
    day = 26;
    hour = 16;
    min = 0;
    sec = 20.475;
    expected = 54977.666903645732;
    actual = Mjday(year, month, day, hour, min, sec);
    double_test("Mjday() 1", expected, actual);

    year = 2011;
    month = 1;
    day = 4;
    hour = 13;
    min = 0;
    sec = 46.5;
    expected = 55565.542204861064;
    actual = Mjday(year, month, day, hour, min, sec);
    double_test("Mjday() 2", expected, actual);

    year = 2006;
    month = 9;
    day = 11;
    hour = 4;
    min = 45;
    sec = 44.073;
    expected = 53989.198426770978;
    actual = Mjday(year, month, day, hour, min, sec);
    double_test("Mjday() 3", expected, actual);
}

void test_MeanObliquity()
{
    double Mjd_TT;
    double expected;
    double actual;

    Mjd_TT = 54977.667669664253;
    expected = 0.409071470559;
    actual = MeanObliquity(Mjd_TT);

    double_test("MeanObliquity() 1", expected, actual);

    Mjd_TT = 55565.542970879585;
    expected = 0.409067817510;
    actual = MeanObliquity(Mjd_TT);

    double_test("MeanObliquity() 2", expected, actual);

    Mjd_TT = 53989.199181215423;
    expected = 0.409077612887;
    actual = MeanObliquity(Mjd_TT);

    double_test("MeanObliquity() 3", expected, actual);
}

void test_NutAngles()
{
    double Mjd_TT;
    double exp_dpsi, exp_deps;
    double dpsi = 0;
    double deps = 0;

    Mjd_TT = 54977.667669664253;
    exp_dpsi = 0.000064869339;
    exp_deps = 0.000022305134;

    NutAngles(Mjd_TT, &dpsi, &deps);

    double_test("NutAngles() 1, dpsi", exp_dpsi, dpsi);
    double_test("NutAngles() 1, deps", exp_deps, deps);

    Mjd_TT = 55565.542970879585;
    exp_dpsi = 0.000087228574;
    exp_deps = -0.000000813487;

    NutAngles(Mjd_TT, &dpsi, &deps);

    double_test("NutAngles() 2, dpsi", exp_dpsi, dpsi);
    double_test("NutAngles() 2, deps", exp_deps, deps);

    Mjd_TT = 53989.199181215423;
    exp_dpsi = 0.000007098336;
    exp_deps = 0.000046734356;

    NutAngles(Mjd_TT, &dpsi, &deps);

    double_test("NutAngles() 2, dpsi", exp_dpsi, dpsi);
    double_test("NutAngles() 2, deps", exp_deps, deps);
}

void test_timediff()
{
    double UT1_UTC = 0.258022690875596;
    double TAI_UTC = 34;

    double UT1_TAI_e = 0.;
    double UTC_GPS_e = 0.;
    double UT1_GPS_e = 0.;
    double TT_UTC_e = 0.;
    double GPS_UTC_e = 0.;

    double UT1_TAI = 0.;
    double UTC_GPS = 0.;
    double UT1_GPS = 0.;
    double TT_UTC = 0.;
    double GPS_UTC = 0.;

    UT1_UTC = 0.258022690875596;
    TAI_UTC = 34;

    UT1_TAI_e = -33.7419773091244;
    UTC_GPS_e = -15;
    UT1_GPS_e = -14.7419773091244;
    TT_UTC_e = 66.184;
    GPS_UTC_e = 15;

    timediff(UT1_UTC, TAI_UTC, &UT1_TAI, &UTC_GPS, &UT1_GPS, &TT_UTC, &GPS_UTC);
    double_test("timediff(), UT1_TAI", UT1_TAI_e, UT1_TAI);
    double_test("timediff(), UTC_GPS", UTC_GPS_e, UTC_GPS);
    double_test("timediff(), UT1_GPS", UT1_GPS_e, UT1_GPS);
    double_test("timediff(), TT_UTC", TT_UTC_e, TT_UTC);
    double_test("timediff(), GPS_UTC", GPS_UTC_e, GPS_UTC);

}

void test_Frac()
{
    double in;
    double expected;
    double actual;

    in = 10.3456636914056;
    expected = 0.3456636914056;
    actual = Frac(in);
    double_test("Frac() 1", expected, actual);

    in = 10.352627149095715;
    expected = 0.352627149095715;
    actual = Frac(in);
    double_test("Frac() 2", expected, actual);
}

void test_R_x()
{
    double in;
    double **expected = malloc(3 * sizeof(double*));
    double **actual;

    in = -0.409093775692299;
    expected[0] = (double*)(double[3]) {1., 0., 0.};
    expected[1] = (double*)(double[3]) {0., 0.917481675640187, -0.397778047237997};
    expected[2] = (double*)(double[3]) {0., 0.397778047237997, 0.917481675640187};

    actual = R_x(in);

    matrix_test("R_x() 1", expected, actual, 3, 3);

    free(actual);

    in = 0.409071470558628;
    expected[0] = (double*)(double[3]) {1., 0., 0.};
    expected[1] = (double*)(double[3]) {0., 0.917490547904469, 0.397757582587632};
    expected[2] = (double*)(double[3]) {0., -0.397757582587632, 0.917490547904469};

    actual = R_x(in);

    matrix_test("R_x() 2", expected, actual, 3, 3);

    free(actual);

    in = -2.56777193042581e-6;
    expected[0] = (double*)(double[3]) {1., 0., 0.};
    expected[1] = (double*)(double[3]) {0., 0.999999999996703, -2.56777193042298e-6};
    expected[2] = (double*)(double[3]) {0., 2.56777193042298e-6, 0.999999999996703};

    actual = R_x(in);

    matrix_test("R_x() 3", expected, actual, 3, 3);

    free(actual);
    free(expected);
}

void test_R_y()
{
    double in;
    double **expected = malloc(3 * sizeof(double*));
    double **actual;

    in = 0.000913347353936069;
    expected[0] = (double*)(double[3]) {0.999999582898335, 0., -0.000913347226949831};
    expected[1] = (double*)(double[3]) {0., 1., 0.};
    expected[2] = (double*)(double[3]) {0.000913347226949831, 0. , 0.999999582898335};

    actual = R_y(in);

    matrix_test("R_y() 1", expected, actual, 3, 3);

    free(actual);

    in = -7.57892008067929e-8;
    expected[0] = (double*)(double[3]) {0.999999999999997, 0., 7.57892008067929e-8};
    expected[1] = (double*)(double[3]) {0., 1., 0.};
    expected[2] = (double*)(double[3]) {-7.57892008067929e-8, 0., 0.999999999999997};

    actual = R_y(in);

    matrix_test("R_y() 2", expected, actual, 3, 3);

    free(actual);

    in = 0.000913349201373003;
    expected[0] = (double*)(double[3]) {0.999999582896647, 0., -0.000913349074385995};
    expected[1] = (double*)(double[3]) {0., 1., 0.};
    expected[2] = (double*)(double[3]) {0.000913349074385995, 0., 0.999999582896647};

    actual = R_y(in);

    matrix_test("R_y() 3", expected, actual, 3, 3);

    free(actual);
    free(expected);
}

void test_R_z()
{
    double in;
    double **expected = malloc(3 * sizeof(double*));
    double **actual;

    in = -0.001050992069582;
    expected[0] = (double*)(double[3]) {0.999999447707886, -0.00105099187608332, 0.};
    expected[1] = (double*)(double[3]) {0.00105099187608332, 0.999999447707886, 0.};
    expected[2] = (double*)(double[3]) {0., 0., 1.};

    actual = R_z(in);

    matrix_test("R_z() 1", expected, actual, 3, 3);

    free(actual);

    in = 2.17192854407046;
    expected[0] = (double*)(double[3]) {-0.565576570524664, 0.824695788077977, 0.};
    expected[1] = (double*)(double[3]) {-0.824695788077977, -0.565576570524664, 0.};
    expected[2] = (double*)(double[3]) {0., 0., 1.};

    actual = R_z(in);

    matrix_test("R_z() 2", expected, actual, 3, 3);

    free(actual);

    in = 2.50337730618796;
    expected[0] = (double*)(double[3]) {-0.803160266383483, 0.595763028814992, 0.};
    expected[1] = (double*)(double[3]) {-0.595763028814992, -0.803160266383483, 0.};
    expected[2] = (double*)(double[3]) {0., 0., 1.};

    actual = R_z(in);

    matrix_test("R_z() 3", expected, actual, 3, 3);

    free(actual);
    free(expected);
}

void test_unit()
{
    double *vec = (double*)(double[3]){-9341115904217.03, 16158801718408.7, 29720729511155.2};
    double *actual = unit(vec);
    double *expected = (double*)(double[3]){-0.266163758239956, 0.460425439329396, 0.846856108567397};

    array_test("unit() 1", expected, actual, 3);

    vec = (double*)(double[3]){2644218480744.88, -9104674845836.32, 19019299944092.7};
    actual = unit(vec);
    expected = (double*)(double[3]) {0.124425783694902, -0.428427647423945, 0.894968142044561};

    array_test("unit() 2", expected, actual, 3);

    vec = (double*)(double[3]){218961962953.224, 11038749223.2812, 38367764388851.1};
    actual = unit(vec);
    expected = (double*)(double[3]) {0.00570683207063089, 0.000287704227394504, 0.999983674513737};

    array_test_delta("unit() 3", expected, actual, 3, 1e-10);
    // La norma sale chunga, perdemos precision
}

void test_EqnEquinox()
{
    double in;
    double expected;
    double actual;

    in = 54977.6676696643;
    expected = 5.95170051422054e-5;
    actual = EqnEquinox(in);

    double_test("EqnEquinox() 1", expected, actual);

    in = 55565.9051733796;
    expected = 8.02104092023363e-5;
    actual = EqnEquinox(in);

    double_test("EqnEquinox() 2", expected, actual);

    in = 54332.4868655555;
    expected = 3.23022519949022e-5;
    actual = EqnEquinox(in);

    double_test("EqnEquinox() 3", expected, actual);
}

int main()
{
    MatlabUtilsTest();
    test_Position();
    test_Mjday();
    test_MeanObliquity();
    test_NutAngles();
    test_timediff();
    test_Frac();
    test_R_x();
    test_R_y();
    test_R_z();
    test_unit();
    test_EqnEquinox();
    return 0;
}
