#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void live_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_9(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_12(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_35(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_32(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_update_33(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void live_H(double *in_vec, double *out_4218059836680828385);
void live_err_fun(double *nom_x, double *delta_x, double *out_294640909843783208);
void live_inv_err_fun(double *nom_x, double *true_x, double *out_4618383641559422893);
void live_H_mod_fun(double *state, double *out_7344566730267608152);
void live_f_fun(double *state, double dt, double *out_8532623406350496766);
void live_F_fun(double *state, double dt, double *out_3755265022923058459);
void live_h_4(double *state, double *unused, double *out_2987905403392131589);
void live_H_4(double *state, double *unused, double *out_2435896361703206297);
void live_h_9(double *state, double *unused, double *out_6773299318607157650);
void live_H_9(double *state, double *unused, double *out_2194706715073615652);
void live_h_10(double *state, double *unused, double *out_1420332384323817174);
void live_H_10(double *state, double *unused, double *out_4848346649582249394);
void live_h_12(double *state, double *unused, double *out_5143132994098362002);
void live_H_12(double *state, double *unused, double *out_1814797336655612630);
void live_h_35(double *state, double *unused, double *out_3285278372981607879);
void live_H_35(double *state, double *unused, double *out_930765695669401079);
void live_h_32(double *state, double *unused, double *out_3019470633368722771);
void live_H_32(double *state, double *unused, double *out_3635790208571151016);
void live_h_13(double *state, double *unused, double *out_7262597744708232008);
void live_H_13(double *state, double *unused, double *out_2846074722916545658);
void live_h_14(double *state, double *unused, double *out_6773299318607157650);
void live_H_14(double *state, double *unused, double *out_2194706715073615652);
void live_h_33(double *state, double *unused, double *out_306067103489919054);
void live_H_33(double *state, double *unused, double *out_4081322700308258683);
void live_predict(double *in_x, double *in_P, double *in_Q, double dt);
}