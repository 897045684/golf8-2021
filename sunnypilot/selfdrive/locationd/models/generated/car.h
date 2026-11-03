#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_3420213646125504328);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_6607816804594994165);
void car_H_mod_fun(double *state, double *out_2211673236678016334);
void car_f_fun(double *state, double dt, double *out_2365991361996157334);
void car_F_fun(double *state, double dt, double *out_6252851061315761534);
void car_h_25(double *state, double *unused, double *out_6379103624132056279);
void car_H_25(double *state, double *unused, double *out_6552484623381252263);
void car_h_24(double *state, double *unused, double *out_9111435113421266369);
void car_H_24(double *state, double *unused, double *out_8729699046988402236);
void car_h_30(double *state, double *unused, double *out_1502169026621992906);
void car_H_30(double *state, double *unused, double *out_9070817581888500890);
void car_h_26(double *state, double *unused, double *out_4413461727111869430);
void car_H_26(double *state, double *unused, double *out_8589733480567498752);
void car_h_27(double *state, double *unused, double *out_5668598932163646191);
void car_H_27(double *state, double *unused, double *out_6896054270088075979);
void car_h_29(double *state, double *unused, double *out_9140695613291883075);
void car_H_29(double *state, double *unused, double *out_8865695147506658542);
void car_h_28(double *state, double *unused, double *out_326731696277615628);
void car_H_28(double *state, double *unused, double *out_4498649909133362500);
void car_h_31(double *state, double *unused, double *out_2280800325852684415);
void car_H_31(double *state, double *unused, double *out_9215941582800850228);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}