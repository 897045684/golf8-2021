#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_8873621528686367328);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6845093829299839856);
void pose_H_mod_fun(double *state, double *out_5272508026350459838);
void pose_f_fun(double *state, double dt, double *out_5613529983893470632);
void pose_F_fun(double *state, double dt, double *out_5878277159556682250);
void pose_h_4(double *state, double *unused, double *out_5305905984689579201);
void pose_H_4(double *state, double *unused, double *out_575573780401498883);
void pose_h_10(double *state, double *unused, double *out_2835732852621838097);
void pose_H_10(double *state, double *unused, double *out_3794534418366600876);
void pose_h_13(double *state, double *unused, double *out_5662511839388362108);
void pose_H_13(double *state, double *unused, double *out_2636700044930833918);
void pose_h_14(double *state, double *unused, double *out_556794040786755953);
void pose_H_14(double *state, double *unused, double *out_3387667075937985646);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}