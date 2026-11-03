#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_3420213646125504328) {
   out_3420213646125504328[0] = delta_x[0] + nom_x[0];
   out_3420213646125504328[1] = delta_x[1] + nom_x[1];
   out_3420213646125504328[2] = delta_x[2] + nom_x[2];
   out_3420213646125504328[3] = delta_x[3] + nom_x[3];
   out_3420213646125504328[4] = delta_x[4] + nom_x[4];
   out_3420213646125504328[5] = delta_x[5] + nom_x[5];
   out_3420213646125504328[6] = delta_x[6] + nom_x[6];
   out_3420213646125504328[7] = delta_x[7] + nom_x[7];
   out_3420213646125504328[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6607816804594994165) {
   out_6607816804594994165[0] = -nom_x[0] + true_x[0];
   out_6607816804594994165[1] = -nom_x[1] + true_x[1];
   out_6607816804594994165[2] = -nom_x[2] + true_x[2];
   out_6607816804594994165[3] = -nom_x[3] + true_x[3];
   out_6607816804594994165[4] = -nom_x[4] + true_x[4];
   out_6607816804594994165[5] = -nom_x[5] + true_x[5];
   out_6607816804594994165[6] = -nom_x[6] + true_x[6];
   out_6607816804594994165[7] = -nom_x[7] + true_x[7];
   out_6607816804594994165[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_2211673236678016334) {
   out_2211673236678016334[0] = 1.0;
   out_2211673236678016334[1] = 0.0;
   out_2211673236678016334[2] = 0.0;
   out_2211673236678016334[3] = 0.0;
   out_2211673236678016334[4] = 0.0;
   out_2211673236678016334[5] = 0.0;
   out_2211673236678016334[6] = 0.0;
   out_2211673236678016334[7] = 0.0;
   out_2211673236678016334[8] = 0.0;
   out_2211673236678016334[9] = 0.0;
   out_2211673236678016334[10] = 1.0;
   out_2211673236678016334[11] = 0.0;
   out_2211673236678016334[12] = 0.0;
   out_2211673236678016334[13] = 0.0;
   out_2211673236678016334[14] = 0.0;
   out_2211673236678016334[15] = 0.0;
   out_2211673236678016334[16] = 0.0;
   out_2211673236678016334[17] = 0.0;
   out_2211673236678016334[18] = 0.0;
   out_2211673236678016334[19] = 0.0;
   out_2211673236678016334[20] = 1.0;
   out_2211673236678016334[21] = 0.0;
   out_2211673236678016334[22] = 0.0;
   out_2211673236678016334[23] = 0.0;
   out_2211673236678016334[24] = 0.0;
   out_2211673236678016334[25] = 0.0;
   out_2211673236678016334[26] = 0.0;
   out_2211673236678016334[27] = 0.0;
   out_2211673236678016334[28] = 0.0;
   out_2211673236678016334[29] = 0.0;
   out_2211673236678016334[30] = 1.0;
   out_2211673236678016334[31] = 0.0;
   out_2211673236678016334[32] = 0.0;
   out_2211673236678016334[33] = 0.0;
   out_2211673236678016334[34] = 0.0;
   out_2211673236678016334[35] = 0.0;
   out_2211673236678016334[36] = 0.0;
   out_2211673236678016334[37] = 0.0;
   out_2211673236678016334[38] = 0.0;
   out_2211673236678016334[39] = 0.0;
   out_2211673236678016334[40] = 1.0;
   out_2211673236678016334[41] = 0.0;
   out_2211673236678016334[42] = 0.0;
   out_2211673236678016334[43] = 0.0;
   out_2211673236678016334[44] = 0.0;
   out_2211673236678016334[45] = 0.0;
   out_2211673236678016334[46] = 0.0;
   out_2211673236678016334[47] = 0.0;
   out_2211673236678016334[48] = 0.0;
   out_2211673236678016334[49] = 0.0;
   out_2211673236678016334[50] = 1.0;
   out_2211673236678016334[51] = 0.0;
   out_2211673236678016334[52] = 0.0;
   out_2211673236678016334[53] = 0.0;
   out_2211673236678016334[54] = 0.0;
   out_2211673236678016334[55] = 0.0;
   out_2211673236678016334[56] = 0.0;
   out_2211673236678016334[57] = 0.0;
   out_2211673236678016334[58] = 0.0;
   out_2211673236678016334[59] = 0.0;
   out_2211673236678016334[60] = 1.0;
   out_2211673236678016334[61] = 0.0;
   out_2211673236678016334[62] = 0.0;
   out_2211673236678016334[63] = 0.0;
   out_2211673236678016334[64] = 0.0;
   out_2211673236678016334[65] = 0.0;
   out_2211673236678016334[66] = 0.0;
   out_2211673236678016334[67] = 0.0;
   out_2211673236678016334[68] = 0.0;
   out_2211673236678016334[69] = 0.0;
   out_2211673236678016334[70] = 1.0;
   out_2211673236678016334[71] = 0.0;
   out_2211673236678016334[72] = 0.0;
   out_2211673236678016334[73] = 0.0;
   out_2211673236678016334[74] = 0.0;
   out_2211673236678016334[75] = 0.0;
   out_2211673236678016334[76] = 0.0;
   out_2211673236678016334[77] = 0.0;
   out_2211673236678016334[78] = 0.0;
   out_2211673236678016334[79] = 0.0;
   out_2211673236678016334[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_2365991361996157334) {
   out_2365991361996157334[0] = state[0];
   out_2365991361996157334[1] = state[1];
   out_2365991361996157334[2] = state[2];
   out_2365991361996157334[3] = state[3];
   out_2365991361996157334[4] = state[4];
   out_2365991361996157334[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_2365991361996157334[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_2365991361996157334[7] = state[7];
   out_2365991361996157334[8] = state[8];
}
void F_fun(double *state, double dt, double *out_6252851061315761534) {
   out_6252851061315761534[0] = 1;
   out_6252851061315761534[1] = 0;
   out_6252851061315761534[2] = 0;
   out_6252851061315761534[3] = 0;
   out_6252851061315761534[4] = 0;
   out_6252851061315761534[5] = 0;
   out_6252851061315761534[6] = 0;
   out_6252851061315761534[7] = 0;
   out_6252851061315761534[8] = 0;
   out_6252851061315761534[9] = 0;
   out_6252851061315761534[10] = 1;
   out_6252851061315761534[11] = 0;
   out_6252851061315761534[12] = 0;
   out_6252851061315761534[13] = 0;
   out_6252851061315761534[14] = 0;
   out_6252851061315761534[15] = 0;
   out_6252851061315761534[16] = 0;
   out_6252851061315761534[17] = 0;
   out_6252851061315761534[18] = 0;
   out_6252851061315761534[19] = 0;
   out_6252851061315761534[20] = 1;
   out_6252851061315761534[21] = 0;
   out_6252851061315761534[22] = 0;
   out_6252851061315761534[23] = 0;
   out_6252851061315761534[24] = 0;
   out_6252851061315761534[25] = 0;
   out_6252851061315761534[26] = 0;
   out_6252851061315761534[27] = 0;
   out_6252851061315761534[28] = 0;
   out_6252851061315761534[29] = 0;
   out_6252851061315761534[30] = 1;
   out_6252851061315761534[31] = 0;
   out_6252851061315761534[32] = 0;
   out_6252851061315761534[33] = 0;
   out_6252851061315761534[34] = 0;
   out_6252851061315761534[35] = 0;
   out_6252851061315761534[36] = 0;
   out_6252851061315761534[37] = 0;
   out_6252851061315761534[38] = 0;
   out_6252851061315761534[39] = 0;
   out_6252851061315761534[40] = 1;
   out_6252851061315761534[41] = 0;
   out_6252851061315761534[42] = 0;
   out_6252851061315761534[43] = 0;
   out_6252851061315761534[44] = 0;
   out_6252851061315761534[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_6252851061315761534[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_6252851061315761534[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6252851061315761534[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_6252851061315761534[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_6252851061315761534[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_6252851061315761534[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_6252851061315761534[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_6252851061315761534[53] = -9.8100000000000005*dt;
   out_6252851061315761534[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_6252851061315761534[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_6252851061315761534[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6252851061315761534[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6252851061315761534[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_6252851061315761534[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_6252851061315761534[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_6252851061315761534[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_6252851061315761534[62] = 0;
   out_6252851061315761534[63] = 0;
   out_6252851061315761534[64] = 0;
   out_6252851061315761534[65] = 0;
   out_6252851061315761534[66] = 0;
   out_6252851061315761534[67] = 0;
   out_6252851061315761534[68] = 0;
   out_6252851061315761534[69] = 0;
   out_6252851061315761534[70] = 1;
   out_6252851061315761534[71] = 0;
   out_6252851061315761534[72] = 0;
   out_6252851061315761534[73] = 0;
   out_6252851061315761534[74] = 0;
   out_6252851061315761534[75] = 0;
   out_6252851061315761534[76] = 0;
   out_6252851061315761534[77] = 0;
   out_6252851061315761534[78] = 0;
   out_6252851061315761534[79] = 0;
   out_6252851061315761534[80] = 1;
}
void h_25(double *state, double *unused, double *out_6379103624132056279) {
   out_6379103624132056279[0] = state[6];
}
void H_25(double *state, double *unused, double *out_6552484623381252263) {
   out_6552484623381252263[0] = 0;
   out_6552484623381252263[1] = 0;
   out_6552484623381252263[2] = 0;
   out_6552484623381252263[3] = 0;
   out_6552484623381252263[4] = 0;
   out_6552484623381252263[5] = 0;
   out_6552484623381252263[6] = 1;
   out_6552484623381252263[7] = 0;
   out_6552484623381252263[8] = 0;
}
void h_24(double *state, double *unused, double *out_9111435113421266369) {
   out_9111435113421266369[0] = state[4];
   out_9111435113421266369[1] = state[5];
}
void H_24(double *state, double *unused, double *out_8729699046988402236) {
   out_8729699046988402236[0] = 0;
   out_8729699046988402236[1] = 0;
   out_8729699046988402236[2] = 0;
   out_8729699046988402236[3] = 0;
   out_8729699046988402236[4] = 1;
   out_8729699046988402236[5] = 0;
   out_8729699046988402236[6] = 0;
   out_8729699046988402236[7] = 0;
   out_8729699046988402236[8] = 0;
   out_8729699046988402236[9] = 0;
   out_8729699046988402236[10] = 0;
   out_8729699046988402236[11] = 0;
   out_8729699046988402236[12] = 0;
   out_8729699046988402236[13] = 0;
   out_8729699046988402236[14] = 1;
   out_8729699046988402236[15] = 0;
   out_8729699046988402236[16] = 0;
   out_8729699046988402236[17] = 0;
}
void h_30(double *state, double *unused, double *out_1502169026621992906) {
   out_1502169026621992906[0] = state[4];
}
void H_30(double *state, double *unused, double *out_9070817581888500890) {
   out_9070817581888500890[0] = 0;
   out_9070817581888500890[1] = 0;
   out_9070817581888500890[2] = 0;
   out_9070817581888500890[3] = 0;
   out_9070817581888500890[4] = 1;
   out_9070817581888500890[5] = 0;
   out_9070817581888500890[6] = 0;
   out_9070817581888500890[7] = 0;
   out_9070817581888500890[8] = 0;
}
void h_26(double *state, double *unused, double *out_4413461727111869430) {
   out_4413461727111869430[0] = state[7];
}
void H_26(double *state, double *unused, double *out_8589733480567498752) {
   out_8589733480567498752[0] = 0;
   out_8589733480567498752[1] = 0;
   out_8589733480567498752[2] = 0;
   out_8589733480567498752[3] = 0;
   out_8589733480567498752[4] = 0;
   out_8589733480567498752[5] = 0;
   out_8589733480567498752[6] = 0;
   out_8589733480567498752[7] = 1;
   out_8589733480567498752[8] = 0;
}
void h_27(double *state, double *unused, double *out_5668598932163646191) {
   out_5668598932163646191[0] = state[3];
}
void H_27(double *state, double *unused, double *out_6896054270088075979) {
   out_6896054270088075979[0] = 0;
   out_6896054270088075979[1] = 0;
   out_6896054270088075979[2] = 0;
   out_6896054270088075979[3] = 1;
   out_6896054270088075979[4] = 0;
   out_6896054270088075979[5] = 0;
   out_6896054270088075979[6] = 0;
   out_6896054270088075979[7] = 0;
   out_6896054270088075979[8] = 0;
}
void h_29(double *state, double *unused, double *out_9140695613291883075) {
   out_9140695613291883075[0] = state[1];
}
void H_29(double *state, double *unused, double *out_8865695147506658542) {
   out_8865695147506658542[0] = 0;
   out_8865695147506658542[1] = 1;
   out_8865695147506658542[2] = 0;
   out_8865695147506658542[3] = 0;
   out_8865695147506658542[4] = 0;
   out_8865695147506658542[5] = 0;
   out_8865695147506658542[6] = 0;
   out_8865695147506658542[7] = 0;
   out_8865695147506658542[8] = 0;
}
void h_28(double *state, double *unused, double *out_326731696277615628) {
   out_326731696277615628[0] = state[0];
}
void H_28(double *state, double *unused, double *out_4498649909133362500) {
   out_4498649909133362500[0] = 1;
   out_4498649909133362500[1] = 0;
   out_4498649909133362500[2] = 0;
   out_4498649909133362500[3] = 0;
   out_4498649909133362500[4] = 0;
   out_4498649909133362500[5] = 0;
   out_4498649909133362500[6] = 0;
   out_4498649909133362500[7] = 0;
   out_4498649909133362500[8] = 0;
}
void h_31(double *state, double *unused, double *out_2280800325852684415) {
   out_2280800325852684415[0] = state[8];
}
void H_31(double *state, double *unused, double *out_9215941582800850228) {
   out_9215941582800850228[0] = 0;
   out_9215941582800850228[1] = 0;
   out_9215941582800850228[2] = 0;
   out_9215941582800850228[3] = 0;
   out_9215941582800850228[4] = 0;
   out_9215941582800850228[5] = 0;
   out_9215941582800850228[6] = 0;
   out_9215941582800850228[7] = 0;
   out_9215941582800850228[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_3420213646125504328) {
  err_fun(nom_x, delta_x, out_3420213646125504328);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6607816804594994165) {
  inv_err_fun(nom_x, true_x, out_6607816804594994165);
}
void car_H_mod_fun(double *state, double *out_2211673236678016334) {
  H_mod_fun(state, out_2211673236678016334);
}
void car_f_fun(double *state, double dt, double *out_2365991361996157334) {
  f_fun(state,  dt, out_2365991361996157334);
}
void car_F_fun(double *state, double dt, double *out_6252851061315761534) {
  F_fun(state,  dt, out_6252851061315761534);
}
void car_h_25(double *state, double *unused, double *out_6379103624132056279) {
  h_25(state, unused, out_6379103624132056279);
}
void car_H_25(double *state, double *unused, double *out_6552484623381252263) {
  H_25(state, unused, out_6552484623381252263);
}
void car_h_24(double *state, double *unused, double *out_9111435113421266369) {
  h_24(state, unused, out_9111435113421266369);
}
void car_H_24(double *state, double *unused, double *out_8729699046988402236) {
  H_24(state, unused, out_8729699046988402236);
}
void car_h_30(double *state, double *unused, double *out_1502169026621992906) {
  h_30(state, unused, out_1502169026621992906);
}
void car_H_30(double *state, double *unused, double *out_9070817581888500890) {
  H_30(state, unused, out_9070817581888500890);
}
void car_h_26(double *state, double *unused, double *out_4413461727111869430) {
  h_26(state, unused, out_4413461727111869430);
}
void car_H_26(double *state, double *unused, double *out_8589733480567498752) {
  H_26(state, unused, out_8589733480567498752);
}
void car_h_27(double *state, double *unused, double *out_5668598932163646191) {
  h_27(state, unused, out_5668598932163646191);
}
void car_H_27(double *state, double *unused, double *out_6896054270088075979) {
  H_27(state, unused, out_6896054270088075979);
}
void car_h_29(double *state, double *unused, double *out_9140695613291883075) {
  h_29(state, unused, out_9140695613291883075);
}
void car_H_29(double *state, double *unused, double *out_8865695147506658542) {
  H_29(state, unused, out_8865695147506658542);
}
void car_h_28(double *state, double *unused, double *out_326731696277615628) {
  h_28(state, unused, out_326731696277615628);
}
void car_H_28(double *state, double *unused, double *out_4498649909133362500) {
  H_28(state, unused, out_4498649909133362500);
}
void car_h_31(double *state, double *unused, double *out_2280800325852684415) {
  h_31(state, unused, out_2280800325852684415);
}
void car_H_31(double *state, double *unused, double *out_9215941582800850228) {
  H_31(state, unused, out_9215941582800850228);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
