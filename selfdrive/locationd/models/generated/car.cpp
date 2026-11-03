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
void err_fun(double *nom_x, double *delta_x, double *out_4138135767309589644) {
   out_4138135767309589644[0] = delta_x[0] + nom_x[0];
   out_4138135767309589644[1] = delta_x[1] + nom_x[1];
   out_4138135767309589644[2] = delta_x[2] + nom_x[2];
   out_4138135767309589644[3] = delta_x[3] + nom_x[3];
   out_4138135767309589644[4] = delta_x[4] + nom_x[4];
   out_4138135767309589644[5] = delta_x[5] + nom_x[5];
   out_4138135767309589644[6] = delta_x[6] + nom_x[6];
   out_4138135767309589644[7] = delta_x[7] + nom_x[7];
   out_4138135767309589644[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6613330720144618071) {
   out_6613330720144618071[0] = -nom_x[0] + true_x[0];
   out_6613330720144618071[1] = -nom_x[1] + true_x[1];
   out_6613330720144618071[2] = -nom_x[2] + true_x[2];
   out_6613330720144618071[3] = -nom_x[3] + true_x[3];
   out_6613330720144618071[4] = -nom_x[4] + true_x[4];
   out_6613330720144618071[5] = -nom_x[5] + true_x[5];
   out_6613330720144618071[6] = -nom_x[6] + true_x[6];
   out_6613330720144618071[7] = -nom_x[7] + true_x[7];
   out_6613330720144618071[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_354580675015194462) {
   out_354580675015194462[0] = 1.0;
   out_354580675015194462[1] = 0.0;
   out_354580675015194462[2] = 0.0;
   out_354580675015194462[3] = 0.0;
   out_354580675015194462[4] = 0.0;
   out_354580675015194462[5] = 0.0;
   out_354580675015194462[6] = 0.0;
   out_354580675015194462[7] = 0.0;
   out_354580675015194462[8] = 0.0;
   out_354580675015194462[9] = 0.0;
   out_354580675015194462[10] = 1.0;
   out_354580675015194462[11] = 0.0;
   out_354580675015194462[12] = 0.0;
   out_354580675015194462[13] = 0.0;
   out_354580675015194462[14] = 0.0;
   out_354580675015194462[15] = 0.0;
   out_354580675015194462[16] = 0.0;
   out_354580675015194462[17] = 0.0;
   out_354580675015194462[18] = 0.0;
   out_354580675015194462[19] = 0.0;
   out_354580675015194462[20] = 1.0;
   out_354580675015194462[21] = 0.0;
   out_354580675015194462[22] = 0.0;
   out_354580675015194462[23] = 0.0;
   out_354580675015194462[24] = 0.0;
   out_354580675015194462[25] = 0.0;
   out_354580675015194462[26] = 0.0;
   out_354580675015194462[27] = 0.0;
   out_354580675015194462[28] = 0.0;
   out_354580675015194462[29] = 0.0;
   out_354580675015194462[30] = 1.0;
   out_354580675015194462[31] = 0.0;
   out_354580675015194462[32] = 0.0;
   out_354580675015194462[33] = 0.0;
   out_354580675015194462[34] = 0.0;
   out_354580675015194462[35] = 0.0;
   out_354580675015194462[36] = 0.0;
   out_354580675015194462[37] = 0.0;
   out_354580675015194462[38] = 0.0;
   out_354580675015194462[39] = 0.0;
   out_354580675015194462[40] = 1.0;
   out_354580675015194462[41] = 0.0;
   out_354580675015194462[42] = 0.0;
   out_354580675015194462[43] = 0.0;
   out_354580675015194462[44] = 0.0;
   out_354580675015194462[45] = 0.0;
   out_354580675015194462[46] = 0.0;
   out_354580675015194462[47] = 0.0;
   out_354580675015194462[48] = 0.0;
   out_354580675015194462[49] = 0.0;
   out_354580675015194462[50] = 1.0;
   out_354580675015194462[51] = 0.0;
   out_354580675015194462[52] = 0.0;
   out_354580675015194462[53] = 0.0;
   out_354580675015194462[54] = 0.0;
   out_354580675015194462[55] = 0.0;
   out_354580675015194462[56] = 0.0;
   out_354580675015194462[57] = 0.0;
   out_354580675015194462[58] = 0.0;
   out_354580675015194462[59] = 0.0;
   out_354580675015194462[60] = 1.0;
   out_354580675015194462[61] = 0.0;
   out_354580675015194462[62] = 0.0;
   out_354580675015194462[63] = 0.0;
   out_354580675015194462[64] = 0.0;
   out_354580675015194462[65] = 0.0;
   out_354580675015194462[66] = 0.0;
   out_354580675015194462[67] = 0.0;
   out_354580675015194462[68] = 0.0;
   out_354580675015194462[69] = 0.0;
   out_354580675015194462[70] = 1.0;
   out_354580675015194462[71] = 0.0;
   out_354580675015194462[72] = 0.0;
   out_354580675015194462[73] = 0.0;
   out_354580675015194462[74] = 0.0;
   out_354580675015194462[75] = 0.0;
   out_354580675015194462[76] = 0.0;
   out_354580675015194462[77] = 0.0;
   out_354580675015194462[78] = 0.0;
   out_354580675015194462[79] = 0.0;
   out_354580675015194462[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_1493648855176978168) {
   out_1493648855176978168[0] = state[0];
   out_1493648855176978168[1] = state[1];
   out_1493648855176978168[2] = state[2];
   out_1493648855176978168[3] = state[3];
   out_1493648855176978168[4] = state[4];
   out_1493648855176978168[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_1493648855176978168[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_1493648855176978168[7] = state[7];
   out_1493648855176978168[8] = state[8];
}
void F_fun(double *state, double dt, double *out_8483252687186148757) {
   out_8483252687186148757[0] = 1;
   out_8483252687186148757[1] = 0;
   out_8483252687186148757[2] = 0;
   out_8483252687186148757[3] = 0;
   out_8483252687186148757[4] = 0;
   out_8483252687186148757[5] = 0;
   out_8483252687186148757[6] = 0;
   out_8483252687186148757[7] = 0;
   out_8483252687186148757[8] = 0;
   out_8483252687186148757[9] = 0;
   out_8483252687186148757[10] = 1;
   out_8483252687186148757[11] = 0;
   out_8483252687186148757[12] = 0;
   out_8483252687186148757[13] = 0;
   out_8483252687186148757[14] = 0;
   out_8483252687186148757[15] = 0;
   out_8483252687186148757[16] = 0;
   out_8483252687186148757[17] = 0;
   out_8483252687186148757[18] = 0;
   out_8483252687186148757[19] = 0;
   out_8483252687186148757[20] = 1;
   out_8483252687186148757[21] = 0;
   out_8483252687186148757[22] = 0;
   out_8483252687186148757[23] = 0;
   out_8483252687186148757[24] = 0;
   out_8483252687186148757[25] = 0;
   out_8483252687186148757[26] = 0;
   out_8483252687186148757[27] = 0;
   out_8483252687186148757[28] = 0;
   out_8483252687186148757[29] = 0;
   out_8483252687186148757[30] = 1;
   out_8483252687186148757[31] = 0;
   out_8483252687186148757[32] = 0;
   out_8483252687186148757[33] = 0;
   out_8483252687186148757[34] = 0;
   out_8483252687186148757[35] = 0;
   out_8483252687186148757[36] = 0;
   out_8483252687186148757[37] = 0;
   out_8483252687186148757[38] = 0;
   out_8483252687186148757[39] = 0;
   out_8483252687186148757[40] = 1;
   out_8483252687186148757[41] = 0;
   out_8483252687186148757[42] = 0;
   out_8483252687186148757[43] = 0;
   out_8483252687186148757[44] = 0;
   out_8483252687186148757[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_8483252687186148757[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_8483252687186148757[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8483252687186148757[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_8483252687186148757[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_8483252687186148757[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_8483252687186148757[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_8483252687186148757[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_8483252687186148757[53] = -9.8100000000000005*dt;
   out_8483252687186148757[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_8483252687186148757[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_8483252687186148757[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8483252687186148757[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8483252687186148757[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_8483252687186148757[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_8483252687186148757[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_8483252687186148757[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_8483252687186148757[62] = 0;
   out_8483252687186148757[63] = 0;
   out_8483252687186148757[64] = 0;
   out_8483252687186148757[65] = 0;
   out_8483252687186148757[66] = 0;
   out_8483252687186148757[67] = 0;
   out_8483252687186148757[68] = 0;
   out_8483252687186148757[69] = 0;
   out_8483252687186148757[70] = 1;
   out_8483252687186148757[71] = 0;
   out_8483252687186148757[72] = 0;
   out_8483252687186148757[73] = 0;
   out_8483252687186148757[74] = 0;
   out_8483252687186148757[75] = 0;
   out_8483252687186148757[76] = 0;
   out_8483252687186148757[77] = 0;
   out_8483252687186148757[78] = 0;
   out_8483252687186148757[79] = 0;
   out_8483252687186148757[80] = 1;
}
void h_25(double *state, double *unused, double *out_6997408875953035074) {
   out_6997408875953035074[0] = state[6];
}
void H_25(double *state, double *unused, double *out_8838607550897042775) {
   out_8838607550897042775[0] = 0;
   out_8838607550897042775[1] = 0;
   out_8838607550897042775[2] = 0;
   out_8838607550897042775[3] = 0;
   out_8838607550897042775[4] = 0;
   out_8838607550897042775[5] = 0;
   out_8838607550897042775[6] = 1;
   out_8838607550897042775[7] = 0;
   out_8838607550897042775[8] = 0;
}
void h_24(double *state, double *unused, double *out_5294866930390000869) {
   out_5294866930390000869[0] = state[4];
   out_5294866930390000869[1] = state[5];
}
void H_24(double *state, double *unused, double *out_4861627195845999807) {
   out_4861627195845999807[0] = 0;
   out_4861627195845999807[1] = 0;
   out_4861627195845999807[2] = 0;
   out_4861627195845999807[3] = 0;
   out_4861627195845999807[4] = 1;
   out_4861627195845999807[5] = 0;
   out_4861627195845999807[6] = 0;
   out_4861627195845999807[7] = 0;
   out_4861627195845999807[8] = 0;
   out_4861627195845999807[9] = 0;
   out_4861627195845999807[10] = 0;
   out_4861627195845999807[11] = 0;
   out_4861627195845999807[12] = 0;
   out_4861627195845999807[13] = 0;
   out_4861627195845999807[14] = 1;
   out_4861627195845999807[15] = 0;
   out_4861627195845999807[16] = 0;
   out_4861627195845999807[17] = 0;
}
void h_30(double *state, double *unused, double *out_7154595544304164219) {
   out_7154595544304164219[0] = state[4];
}
void H_30(double *state, double *unused, double *out_6320274592389794148) {
   out_6320274592389794148[0] = 0;
   out_6320274592389794148[1] = 0;
   out_6320274592389794148[2] = 0;
   out_6320274592389794148[3] = 0;
   out_6320274592389794148[4] = 1;
   out_6320274592389794148[5] = 0;
   out_6320274592389794148[6] = 0;
   out_6320274592389794148[7] = 0;
   out_6320274592389794148[8] = 0;
}
void h_26(double *state, double *unused, double *out_6368947806141846566) {
   out_6368947806141846566[0] = state[7];
}
void H_26(double *state, double *unused, double *out_5866633203938452617) {
   out_5866633203938452617[0] = 0;
   out_5866633203938452617[1] = 0;
   out_5866633203938452617[2] = 0;
   out_5866633203938452617[3] = 0;
   out_5866633203938452617[4] = 0;
   out_5866633203938452617[5] = 0;
   out_5866633203938452617[6] = 0;
   out_5866633203938452617[7] = 1;
   out_5866633203938452617[8] = 0;
}
void h_27(double *state, double *unused, double *out_6486955200075223310) {
   out_6486955200075223310[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8495037904190219059) {
   out_8495037904190219059[0] = 0;
   out_8495037904190219059[1] = 0;
   out_8495037904190219059[2] = 0;
   out_8495037904190219059[3] = 1;
   out_8495037904190219059[4] = 0;
   out_8495037904190219059[5] = 0;
   out_8495037904190219059[6] = 0;
   out_8495037904190219059[7] = 0;
   out_8495037904190219059[8] = 0;
}
void h_29(double *state, double *unused, double *out_1641713919961832921) {
   out_1641713919961832921[0] = state[1];
}
void H_29(double *state, double *unused, double *out_5810043248075401964) {
   out_5810043248075401964[0] = 0;
   out_5810043248075401964[1] = 1;
   out_5810043248075401964[2] = 0;
   out_5810043248075401964[3] = 0;
   out_5810043248075401964[4] = 0;
   out_5810043248075401964[5] = 0;
   out_5810043248075401964[6] = 0;
   out_5810043248075401964[7] = 0;
   out_5810043248075401964[8] = 0;
}
void h_28(double *state, double *unused, double *out_7469039293410521422) {
   out_7469039293410521422[0] = state[0];
}
void H_28(double *state, double *unused, double *out_7554301808564619078) {
   out_7554301808564619078[0] = 1;
   out_7554301808564619078[1] = 0;
   out_7554301808564619078[2] = 0;
   out_7554301808564619078[3] = 0;
   out_7554301808564619078[4] = 0;
   out_7554301808564619078[5] = 0;
   out_7554301808564619078[6] = 0;
   out_7554301808564619078[7] = 0;
   out_7554301808564619078[8] = 0;
}
void h_31(double *state, double *unused, double *out_1210087870129871776) {
   out_1210087870129871776[0] = state[8];
}
void H_31(double *state, double *unused, double *out_5240425101705101141) {
   out_5240425101705101141[0] = 0;
   out_5240425101705101141[1] = 0;
   out_5240425101705101141[2] = 0;
   out_5240425101705101141[3] = 0;
   out_5240425101705101141[4] = 0;
   out_5240425101705101141[5] = 0;
   out_5240425101705101141[6] = 0;
   out_5240425101705101141[7] = 0;
   out_5240425101705101141[8] = 1;
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
void car_err_fun(double *nom_x, double *delta_x, double *out_4138135767309589644) {
  err_fun(nom_x, delta_x, out_4138135767309589644);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6613330720144618071) {
  inv_err_fun(nom_x, true_x, out_6613330720144618071);
}
void car_H_mod_fun(double *state, double *out_354580675015194462) {
  H_mod_fun(state, out_354580675015194462);
}
void car_f_fun(double *state, double dt, double *out_1493648855176978168) {
  f_fun(state,  dt, out_1493648855176978168);
}
void car_F_fun(double *state, double dt, double *out_8483252687186148757) {
  F_fun(state,  dt, out_8483252687186148757);
}
void car_h_25(double *state, double *unused, double *out_6997408875953035074) {
  h_25(state, unused, out_6997408875953035074);
}
void car_H_25(double *state, double *unused, double *out_8838607550897042775) {
  H_25(state, unused, out_8838607550897042775);
}
void car_h_24(double *state, double *unused, double *out_5294866930390000869) {
  h_24(state, unused, out_5294866930390000869);
}
void car_H_24(double *state, double *unused, double *out_4861627195845999807) {
  H_24(state, unused, out_4861627195845999807);
}
void car_h_30(double *state, double *unused, double *out_7154595544304164219) {
  h_30(state, unused, out_7154595544304164219);
}
void car_H_30(double *state, double *unused, double *out_6320274592389794148) {
  H_30(state, unused, out_6320274592389794148);
}
void car_h_26(double *state, double *unused, double *out_6368947806141846566) {
  h_26(state, unused, out_6368947806141846566);
}
void car_H_26(double *state, double *unused, double *out_5866633203938452617) {
  H_26(state, unused, out_5866633203938452617);
}
void car_h_27(double *state, double *unused, double *out_6486955200075223310) {
  h_27(state, unused, out_6486955200075223310);
}
void car_H_27(double *state, double *unused, double *out_8495037904190219059) {
  H_27(state, unused, out_8495037904190219059);
}
void car_h_29(double *state, double *unused, double *out_1641713919961832921) {
  h_29(state, unused, out_1641713919961832921);
}
void car_H_29(double *state, double *unused, double *out_5810043248075401964) {
  H_29(state, unused, out_5810043248075401964);
}
void car_h_28(double *state, double *unused, double *out_7469039293410521422) {
  h_28(state, unused, out_7469039293410521422);
}
void car_H_28(double *state, double *unused, double *out_7554301808564619078) {
  H_28(state, unused, out_7554301808564619078);
}
void car_h_31(double *state, double *unused, double *out_1210087870129871776) {
  h_31(state, unused, out_1210087870129871776);
}
void car_H_31(double *state, double *unused, double *out_5240425101705101141) {
  H_31(state, unused, out_5240425101705101141);
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
