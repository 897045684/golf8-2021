#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_8873621528686367328) {
   out_8873621528686367328[0] = delta_x[0] + nom_x[0];
   out_8873621528686367328[1] = delta_x[1] + nom_x[1];
   out_8873621528686367328[2] = delta_x[2] + nom_x[2];
   out_8873621528686367328[3] = delta_x[3] + nom_x[3];
   out_8873621528686367328[4] = delta_x[4] + nom_x[4];
   out_8873621528686367328[5] = delta_x[5] + nom_x[5];
   out_8873621528686367328[6] = delta_x[6] + nom_x[6];
   out_8873621528686367328[7] = delta_x[7] + nom_x[7];
   out_8873621528686367328[8] = delta_x[8] + nom_x[8];
   out_8873621528686367328[9] = delta_x[9] + nom_x[9];
   out_8873621528686367328[10] = delta_x[10] + nom_x[10];
   out_8873621528686367328[11] = delta_x[11] + nom_x[11];
   out_8873621528686367328[12] = delta_x[12] + nom_x[12];
   out_8873621528686367328[13] = delta_x[13] + nom_x[13];
   out_8873621528686367328[14] = delta_x[14] + nom_x[14];
   out_8873621528686367328[15] = delta_x[15] + nom_x[15];
   out_8873621528686367328[16] = delta_x[16] + nom_x[16];
   out_8873621528686367328[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_6845093829299839856) {
   out_6845093829299839856[0] = -nom_x[0] + true_x[0];
   out_6845093829299839856[1] = -nom_x[1] + true_x[1];
   out_6845093829299839856[2] = -nom_x[2] + true_x[2];
   out_6845093829299839856[3] = -nom_x[3] + true_x[3];
   out_6845093829299839856[4] = -nom_x[4] + true_x[4];
   out_6845093829299839856[5] = -nom_x[5] + true_x[5];
   out_6845093829299839856[6] = -nom_x[6] + true_x[6];
   out_6845093829299839856[7] = -nom_x[7] + true_x[7];
   out_6845093829299839856[8] = -nom_x[8] + true_x[8];
   out_6845093829299839856[9] = -nom_x[9] + true_x[9];
   out_6845093829299839856[10] = -nom_x[10] + true_x[10];
   out_6845093829299839856[11] = -nom_x[11] + true_x[11];
   out_6845093829299839856[12] = -nom_x[12] + true_x[12];
   out_6845093829299839856[13] = -nom_x[13] + true_x[13];
   out_6845093829299839856[14] = -nom_x[14] + true_x[14];
   out_6845093829299839856[15] = -nom_x[15] + true_x[15];
   out_6845093829299839856[16] = -nom_x[16] + true_x[16];
   out_6845093829299839856[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_5272508026350459838) {
   out_5272508026350459838[0] = 1.0;
   out_5272508026350459838[1] = 0.0;
   out_5272508026350459838[2] = 0.0;
   out_5272508026350459838[3] = 0.0;
   out_5272508026350459838[4] = 0.0;
   out_5272508026350459838[5] = 0.0;
   out_5272508026350459838[6] = 0.0;
   out_5272508026350459838[7] = 0.0;
   out_5272508026350459838[8] = 0.0;
   out_5272508026350459838[9] = 0.0;
   out_5272508026350459838[10] = 0.0;
   out_5272508026350459838[11] = 0.0;
   out_5272508026350459838[12] = 0.0;
   out_5272508026350459838[13] = 0.0;
   out_5272508026350459838[14] = 0.0;
   out_5272508026350459838[15] = 0.0;
   out_5272508026350459838[16] = 0.0;
   out_5272508026350459838[17] = 0.0;
   out_5272508026350459838[18] = 0.0;
   out_5272508026350459838[19] = 1.0;
   out_5272508026350459838[20] = 0.0;
   out_5272508026350459838[21] = 0.0;
   out_5272508026350459838[22] = 0.0;
   out_5272508026350459838[23] = 0.0;
   out_5272508026350459838[24] = 0.0;
   out_5272508026350459838[25] = 0.0;
   out_5272508026350459838[26] = 0.0;
   out_5272508026350459838[27] = 0.0;
   out_5272508026350459838[28] = 0.0;
   out_5272508026350459838[29] = 0.0;
   out_5272508026350459838[30] = 0.0;
   out_5272508026350459838[31] = 0.0;
   out_5272508026350459838[32] = 0.0;
   out_5272508026350459838[33] = 0.0;
   out_5272508026350459838[34] = 0.0;
   out_5272508026350459838[35] = 0.0;
   out_5272508026350459838[36] = 0.0;
   out_5272508026350459838[37] = 0.0;
   out_5272508026350459838[38] = 1.0;
   out_5272508026350459838[39] = 0.0;
   out_5272508026350459838[40] = 0.0;
   out_5272508026350459838[41] = 0.0;
   out_5272508026350459838[42] = 0.0;
   out_5272508026350459838[43] = 0.0;
   out_5272508026350459838[44] = 0.0;
   out_5272508026350459838[45] = 0.0;
   out_5272508026350459838[46] = 0.0;
   out_5272508026350459838[47] = 0.0;
   out_5272508026350459838[48] = 0.0;
   out_5272508026350459838[49] = 0.0;
   out_5272508026350459838[50] = 0.0;
   out_5272508026350459838[51] = 0.0;
   out_5272508026350459838[52] = 0.0;
   out_5272508026350459838[53] = 0.0;
   out_5272508026350459838[54] = 0.0;
   out_5272508026350459838[55] = 0.0;
   out_5272508026350459838[56] = 0.0;
   out_5272508026350459838[57] = 1.0;
   out_5272508026350459838[58] = 0.0;
   out_5272508026350459838[59] = 0.0;
   out_5272508026350459838[60] = 0.0;
   out_5272508026350459838[61] = 0.0;
   out_5272508026350459838[62] = 0.0;
   out_5272508026350459838[63] = 0.0;
   out_5272508026350459838[64] = 0.0;
   out_5272508026350459838[65] = 0.0;
   out_5272508026350459838[66] = 0.0;
   out_5272508026350459838[67] = 0.0;
   out_5272508026350459838[68] = 0.0;
   out_5272508026350459838[69] = 0.0;
   out_5272508026350459838[70] = 0.0;
   out_5272508026350459838[71] = 0.0;
   out_5272508026350459838[72] = 0.0;
   out_5272508026350459838[73] = 0.0;
   out_5272508026350459838[74] = 0.0;
   out_5272508026350459838[75] = 0.0;
   out_5272508026350459838[76] = 1.0;
   out_5272508026350459838[77] = 0.0;
   out_5272508026350459838[78] = 0.0;
   out_5272508026350459838[79] = 0.0;
   out_5272508026350459838[80] = 0.0;
   out_5272508026350459838[81] = 0.0;
   out_5272508026350459838[82] = 0.0;
   out_5272508026350459838[83] = 0.0;
   out_5272508026350459838[84] = 0.0;
   out_5272508026350459838[85] = 0.0;
   out_5272508026350459838[86] = 0.0;
   out_5272508026350459838[87] = 0.0;
   out_5272508026350459838[88] = 0.0;
   out_5272508026350459838[89] = 0.0;
   out_5272508026350459838[90] = 0.0;
   out_5272508026350459838[91] = 0.0;
   out_5272508026350459838[92] = 0.0;
   out_5272508026350459838[93] = 0.0;
   out_5272508026350459838[94] = 0.0;
   out_5272508026350459838[95] = 1.0;
   out_5272508026350459838[96] = 0.0;
   out_5272508026350459838[97] = 0.0;
   out_5272508026350459838[98] = 0.0;
   out_5272508026350459838[99] = 0.0;
   out_5272508026350459838[100] = 0.0;
   out_5272508026350459838[101] = 0.0;
   out_5272508026350459838[102] = 0.0;
   out_5272508026350459838[103] = 0.0;
   out_5272508026350459838[104] = 0.0;
   out_5272508026350459838[105] = 0.0;
   out_5272508026350459838[106] = 0.0;
   out_5272508026350459838[107] = 0.0;
   out_5272508026350459838[108] = 0.0;
   out_5272508026350459838[109] = 0.0;
   out_5272508026350459838[110] = 0.0;
   out_5272508026350459838[111] = 0.0;
   out_5272508026350459838[112] = 0.0;
   out_5272508026350459838[113] = 0.0;
   out_5272508026350459838[114] = 1.0;
   out_5272508026350459838[115] = 0.0;
   out_5272508026350459838[116] = 0.0;
   out_5272508026350459838[117] = 0.0;
   out_5272508026350459838[118] = 0.0;
   out_5272508026350459838[119] = 0.0;
   out_5272508026350459838[120] = 0.0;
   out_5272508026350459838[121] = 0.0;
   out_5272508026350459838[122] = 0.0;
   out_5272508026350459838[123] = 0.0;
   out_5272508026350459838[124] = 0.0;
   out_5272508026350459838[125] = 0.0;
   out_5272508026350459838[126] = 0.0;
   out_5272508026350459838[127] = 0.0;
   out_5272508026350459838[128] = 0.0;
   out_5272508026350459838[129] = 0.0;
   out_5272508026350459838[130] = 0.0;
   out_5272508026350459838[131] = 0.0;
   out_5272508026350459838[132] = 0.0;
   out_5272508026350459838[133] = 1.0;
   out_5272508026350459838[134] = 0.0;
   out_5272508026350459838[135] = 0.0;
   out_5272508026350459838[136] = 0.0;
   out_5272508026350459838[137] = 0.0;
   out_5272508026350459838[138] = 0.0;
   out_5272508026350459838[139] = 0.0;
   out_5272508026350459838[140] = 0.0;
   out_5272508026350459838[141] = 0.0;
   out_5272508026350459838[142] = 0.0;
   out_5272508026350459838[143] = 0.0;
   out_5272508026350459838[144] = 0.0;
   out_5272508026350459838[145] = 0.0;
   out_5272508026350459838[146] = 0.0;
   out_5272508026350459838[147] = 0.0;
   out_5272508026350459838[148] = 0.0;
   out_5272508026350459838[149] = 0.0;
   out_5272508026350459838[150] = 0.0;
   out_5272508026350459838[151] = 0.0;
   out_5272508026350459838[152] = 1.0;
   out_5272508026350459838[153] = 0.0;
   out_5272508026350459838[154] = 0.0;
   out_5272508026350459838[155] = 0.0;
   out_5272508026350459838[156] = 0.0;
   out_5272508026350459838[157] = 0.0;
   out_5272508026350459838[158] = 0.0;
   out_5272508026350459838[159] = 0.0;
   out_5272508026350459838[160] = 0.0;
   out_5272508026350459838[161] = 0.0;
   out_5272508026350459838[162] = 0.0;
   out_5272508026350459838[163] = 0.0;
   out_5272508026350459838[164] = 0.0;
   out_5272508026350459838[165] = 0.0;
   out_5272508026350459838[166] = 0.0;
   out_5272508026350459838[167] = 0.0;
   out_5272508026350459838[168] = 0.0;
   out_5272508026350459838[169] = 0.0;
   out_5272508026350459838[170] = 0.0;
   out_5272508026350459838[171] = 1.0;
   out_5272508026350459838[172] = 0.0;
   out_5272508026350459838[173] = 0.0;
   out_5272508026350459838[174] = 0.0;
   out_5272508026350459838[175] = 0.0;
   out_5272508026350459838[176] = 0.0;
   out_5272508026350459838[177] = 0.0;
   out_5272508026350459838[178] = 0.0;
   out_5272508026350459838[179] = 0.0;
   out_5272508026350459838[180] = 0.0;
   out_5272508026350459838[181] = 0.0;
   out_5272508026350459838[182] = 0.0;
   out_5272508026350459838[183] = 0.0;
   out_5272508026350459838[184] = 0.0;
   out_5272508026350459838[185] = 0.0;
   out_5272508026350459838[186] = 0.0;
   out_5272508026350459838[187] = 0.0;
   out_5272508026350459838[188] = 0.0;
   out_5272508026350459838[189] = 0.0;
   out_5272508026350459838[190] = 1.0;
   out_5272508026350459838[191] = 0.0;
   out_5272508026350459838[192] = 0.0;
   out_5272508026350459838[193] = 0.0;
   out_5272508026350459838[194] = 0.0;
   out_5272508026350459838[195] = 0.0;
   out_5272508026350459838[196] = 0.0;
   out_5272508026350459838[197] = 0.0;
   out_5272508026350459838[198] = 0.0;
   out_5272508026350459838[199] = 0.0;
   out_5272508026350459838[200] = 0.0;
   out_5272508026350459838[201] = 0.0;
   out_5272508026350459838[202] = 0.0;
   out_5272508026350459838[203] = 0.0;
   out_5272508026350459838[204] = 0.0;
   out_5272508026350459838[205] = 0.0;
   out_5272508026350459838[206] = 0.0;
   out_5272508026350459838[207] = 0.0;
   out_5272508026350459838[208] = 0.0;
   out_5272508026350459838[209] = 1.0;
   out_5272508026350459838[210] = 0.0;
   out_5272508026350459838[211] = 0.0;
   out_5272508026350459838[212] = 0.0;
   out_5272508026350459838[213] = 0.0;
   out_5272508026350459838[214] = 0.0;
   out_5272508026350459838[215] = 0.0;
   out_5272508026350459838[216] = 0.0;
   out_5272508026350459838[217] = 0.0;
   out_5272508026350459838[218] = 0.0;
   out_5272508026350459838[219] = 0.0;
   out_5272508026350459838[220] = 0.0;
   out_5272508026350459838[221] = 0.0;
   out_5272508026350459838[222] = 0.0;
   out_5272508026350459838[223] = 0.0;
   out_5272508026350459838[224] = 0.0;
   out_5272508026350459838[225] = 0.0;
   out_5272508026350459838[226] = 0.0;
   out_5272508026350459838[227] = 0.0;
   out_5272508026350459838[228] = 1.0;
   out_5272508026350459838[229] = 0.0;
   out_5272508026350459838[230] = 0.0;
   out_5272508026350459838[231] = 0.0;
   out_5272508026350459838[232] = 0.0;
   out_5272508026350459838[233] = 0.0;
   out_5272508026350459838[234] = 0.0;
   out_5272508026350459838[235] = 0.0;
   out_5272508026350459838[236] = 0.0;
   out_5272508026350459838[237] = 0.0;
   out_5272508026350459838[238] = 0.0;
   out_5272508026350459838[239] = 0.0;
   out_5272508026350459838[240] = 0.0;
   out_5272508026350459838[241] = 0.0;
   out_5272508026350459838[242] = 0.0;
   out_5272508026350459838[243] = 0.0;
   out_5272508026350459838[244] = 0.0;
   out_5272508026350459838[245] = 0.0;
   out_5272508026350459838[246] = 0.0;
   out_5272508026350459838[247] = 1.0;
   out_5272508026350459838[248] = 0.0;
   out_5272508026350459838[249] = 0.0;
   out_5272508026350459838[250] = 0.0;
   out_5272508026350459838[251] = 0.0;
   out_5272508026350459838[252] = 0.0;
   out_5272508026350459838[253] = 0.0;
   out_5272508026350459838[254] = 0.0;
   out_5272508026350459838[255] = 0.0;
   out_5272508026350459838[256] = 0.0;
   out_5272508026350459838[257] = 0.0;
   out_5272508026350459838[258] = 0.0;
   out_5272508026350459838[259] = 0.0;
   out_5272508026350459838[260] = 0.0;
   out_5272508026350459838[261] = 0.0;
   out_5272508026350459838[262] = 0.0;
   out_5272508026350459838[263] = 0.0;
   out_5272508026350459838[264] = 0.0;
   out_5272508026350459838[265] = 0.0;
   out_5272508026350459838[266] = 1.0;
   out_5272508026350459838[267] = 0.0;
   out_5272508026350459838[268] = 0.0;
   out_5272508026350459838[269] = 0.0;
   out_5272508026350459838[270] = 0.0;
   out_5272508026350459838[271] = 0.0;
   out_5272508026350459838[272] = 0.0;
   out_5272508026350459838[273] = 0.0;
   out_5272508026350459838[274] = 0.0;
   out_5272508026350459838[275] = 0.0;
   out_5272508026350459838[276] = 0.0;
   out_5272508026350459838[277] = 0.0;
   out_5272508026350459838[278] = 0.0;
   out_5272508026350459838[279] = 0.0;
   out_5272508026350459838[280] = 0.0;
   out_5272508026350459838[281] = 0.0;
   out_5272508026350459838[282] = 0.0;
   out_5272508026350459838[283] = 0.0;
   out_5272508026350459838[284] = 0.0;
   out_5272508026350459838[285] = 1.0;
   out_5272508026350459838[286] = 0.0;
   out_5272508026350459838[287] = 0.0;
   out_5272508026350459838[288] = 0.0;
   out_5272508026350459838[289] = 0.0;
   out_5272508026350459838[290] = 0.0;
   out_5272508026350459838[291] = 0.0;
   out_5272508026350459838[292] = 0.0;
   out_5272508026350459838[293] = 0.0;
   out_5272508026350459838[294] = 0.0;
   out_5272508026350459838[295] = 0.0;
   out_5272508026350459838[296] = 0.0;
   out_5272508026350459838[297] = 0.0;
   out_5272508026350459838[298] = 0.0;
   out_5272508026350459838[299] = 0.0;
   out_5272508026350459838[300] = 0.0;
   out_5272508026350459838[301] = 0.0;
   out_5272508026350459838[302] = 0.0;
   out_5272508026350459838[303] = 0.0;
   out_5272508026350459838[304] = 1.0;
   out_5272508026350459838[305] = 0.0;
   out_5272508026350459838[306] = 0.0;
   out_5272508026350459838[307] = 0.0;
   out_5272508026350459838[308] = 0.0;
   out_5272508026350459838[309] = 0.0;
   out_5272508026350459838[310] = 0.0;
   out_5272508026350459838[311] = 0.0;
   out_5272508026350459838[312] = 0.0;
   out_5272508026350459838[313] = 0.0;
   out_5272508026350459838[314] = 0.0;
   out_5272508026350459838[315] = 0.0;
   out_5272508026350459838[316] = 0.0;
   out_5272508026350459838[317] = 0.0;
   out_5272508026350459838[318] = 0.0;
   out_5272508026350459838[319] = 0.0;
   out_5272508026350459838[320] = 0.0;
   out_5272508026350459838[321] = 0.0;
   out_5272508026350459838[322] = 0.0;
   out_5272508026350459838[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_5613529983893470632) {
   out_5613529983893470632[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_5613529983893470632[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_5613529983893470632[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_5613529983893470632[3] = dt*state[12] + state[3];
   out_5613529983893470632[4] = dt*state[13] + state[4];
   out_5613529983893470632[5] = dt*state[14] + state[5];
   out_5613529983893470632[6] = state[6];
   out_5613529983893470632[7] = state[7];
   out_5613529983893470632[8] = state[8];
   out_5613529983893470632[9] = state[9];
   out_5613529983893470632[10] = state[10];
   out_5613529983893470632[11] = state[11];
   out_5613529983893470632[12] = state[12];
   out_5613529983893470632[13] = state[13];
   out_5613529983893470632[14] = state[14];
   out_5613529983893470632[15] = state[15];
   out_5613529983893470632[16] = state[16];
   out_5613529983893470632[17] = state[17];
}
void F_fun(double *state, double dt, double *out_5878277159556682250) {
   out_5878277159556682250[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5878277159556682250[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5878277159556682250[2] = 0;
   out_5878277159556682250[3] = 0;
   out_5878277159556682250[4] = 0;
   out_5878277159556682250[5] = 0;
   out_5878277159556682250[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5878277159556682250[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5878277159556682250[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_5878277159556682250[9] = 0;
   out_5878277159556682250[10] = 0;
   out_5878277159556682250[11] = 0;
   out_5878277159556682250[12] = 0;
   out_5878277159556682250[13] = 0;
   out_5878277159556682250[14] = 0;
   out_5878277159556682250[15] = 0;
   out_5878277159556682250[16] = 0;
   out_5878277159556682250[17] = 0;
   out_5878277159556682250[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5878277159556682250[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5878277159556682250[20] = 0;
   out_5878277159556682250[21] = 0;
   out_5878277159556682250[22] = 0;
   out_5878277159556682250[23] = 0;
   out_5878277159556682250[24] = 0;
   out_5878277159556682250[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5878277159556682250[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_5878277159556682250[27] = 0;
   out_5878277159556682250[28] = 0;
   out_5878277159556682250[29] = 0;
   out_5878277159556682250[30] = 0;
   out_5878277159556682250[31] = 0;
   out_5878277159556682250[32] = 0;
   out_5878277159556682250[33] = 0;
   out_5878277159556682250[34] = 0;
   out_5878277159556682250[35] = 0;
   out_5878277159556682250[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5878277159556682250[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5878277159556682250[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5878277159556682250[39] = 0;
   out_5878277159556682250[40] = 0;
   out_5878277159556682250[41] = 0;
   out_5878277159556682250[42] = 0;
   out_5878277159556682250[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5878277159556682250[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_5878277159556682250[45] = 0;
   out_5878277159556682250[46] = 0;
   out_5878277159556682250[47] = 0;
   out_5878277159556682250[48] = 0;
   out_5878277159556682250[49] = 0;
   out_5878277159556682250[50] = 0;
   out_5878277159556682250[51] = 0;
   out_5878277159556682250[52] = 0;
   out_5878277159556682250[53] = 0;
   out_5878277159556682250[54] = 0;
   out_5878277159556682250[55] = 0;
   out_5878277159556682250[56] = 0;
   out_5878277159556682250[57] = 1;
   out_5878277159556682250[58] = 0;
   out_5878277159556682250[59] = 0;
   out_5878277159556682250[60] = 0;
   out_5878277159556682250[61] = 0;
   out_5878277159556682250[62] = 0;
   out_5878277159556682250[63] = 0;
   out_5878277159556682250[64] = 0;
   out_5878277159556682250[65] = 0;
   out_5878277159556682250[66] = dt;
   out_5878277159556682250[67] = 0;
   out_5878277159556682250[68] = 0;
   out_5878277159556682250[69] = 0;
   out_5878277159556682250[70] = 0;
   out_5878277159556682250[71] = 0;
   out_5878277159556682250[72] = 0;
   out_5878277159556682250[73] = 0;
   out_5878277159556682250[74] = 0;
   out_5878277159556682250[75] = 0;
   out_5878277159556682250[76] = 1;
   out_5878277159556682250[77] = 0;
   out_5878277159556682250[78] = 0;
   out_5878277159556682250[79] = 0;
   out_5878277159556682250[80] = 0;
   out_5878277159556682250[81] = 0;
   out_5878277159556682250[82] = 0;
   out_5878277159556682250[83] = 0;
   out_5878277159556682250[84] = 0;
   out_5878277159556682250[85] = dt;
   out_5878277159556682250[86] = 0;
   out_5878277159556682250[87] = 0;
   out_5878277159556682250[88] = 0;
   out_5878277159556682250[89] = 0;
   out_5878277159556682250[90] = 0;
   out_5878277159556682250[91] = 0;
   out_5878277159556682250[92] = 0;
   out_5878277159556682250[93] = 0;
   out_5878277159556682250[94] = 0;
   out_5878277159556682250[95] = 1;
   out_5878277159556682250[96] = 0;
   out_5878277159556682250[97] = 0;
   out_5878277159556682250[98] = 0;
   out_5878277159556682250[99] = 0;
   out_5878277159556682250[100] = 0;
   out_5878277159556682250[101] = 0;
   out_5878277159556682250[102] = 0;
   out_5878277159556682250[103] = 0;
   out_5878277159556682250[104] = dt;
   out_5878277159556682250[105] = 0;
   out_5878277159556682250[106] = 0;
   out_5878277159556682250[107] = 0;
   out_5878277159556682250[108] = 0;
   out_5878277159556682250[109] = 0;
   out_5878277159556682250[110] = 0;
   out_5878277159556682250[111] = 0;
   out_5878277159556682250[112] = 0;
   out_5878277159556682250[113] = 0;
   out_5878277159556682250[114] = 1;
   out_5878277159556682250[115] = 0;
   out_5878277159556682250[116] = 0;
   out_5878277159556682250[117] = 0;
   out_5878277159556682250[118] = 0;
   out_5878277159556682250[119] = 0;
   out_5878277159556682250[120] = 0;
   out_5878277159556682250[121] = 0;
   out_5878277159556682250[122] = 0;
   out_5878277159556682250[123] = 0;
   out_5878277159556682250[124] = 0;
   out_5878277159556682250[125] = 0;
   out_5878277159556682250[126] = 0;
   out_5878277159556682250[127] = 0;
   out_5878277159556682250[128] = 0;
   out_5878277159556682250[129] = 0;
   out_5878277159556682250[130] = 0;
   out_5878277159556682250[131] = 0;
   out_5878277159556682250[132] = 0;
   out_5878277159556682250[133] = 1;
   out_5878277159556682250[134] = 0;
   out_5878277159556682250[135] = 0;
   out_5878277159556682250[136] = 0;
   out_5878277159556682250[137] = 0;
   out_5878277159556682250[138] = 0;
   out_5878277159556682250[139] = 0;
   out_5878277159556682250[140] = 0;
   out_5878277159556682250[141] = 0;
   out_5878277159556682250[142] = 0;
   out_5878277159556682250[143] = 0;
   out_5878277159556682250[144] = 0;
   out_5878277159556682250[145] = 0;
   out_5878277159556682250[146] = 0;
   out_5878277159556682250[147] = 0;
   out_5878277159556682250[148] = 0;
   out_5878277159556682250[149] = 0;
   out_5878277159556682250[150] = 0;
   out_5878277159556682250[151] = 0;
   out_5878277159556682250[152] = 1;
   out_5878277159556682250[153] = 0;
   out_5878277159556682250[154] = 0;
   out_5878277159556682250[155] = 0;
   out_5878277159556682250[156] = 0;
   out_5878277159556682250[157] = 0;
   out_5878277159556682250[158] = 0;
   out_5878277159556682250[159] = 0;
   out_5878277159556682250[160] = 0;
   out_5878277159556682250[161] = 0;
   out_5878277159556682250[162] = 0;
   out_5878277159556682250[163] = 0;
   out_5878277159556682250[164] = 0;
   out_5878277159556682250[165] = 0;
   out_5878277159556682250[166] = 0;
   out_5878277159556682250[167] = 0;
   out_5878277159556682250[168] = 0;
   out_5878277159556682250[169] = 0;
   out_5878277159556682250[170] = 0;
   out_5878277159556682250[171] = 1;
   out_5878277159556682250[172] = 0;
   out_5878277159556682250[173] = 0;
   out_5878277159556682250[174] = 0;
   out_5878277159556682250[175] = 0;
   out_5878277159556682250[176] = 0;
   out_5878277159556682250[177] = 0;
   out_5878277159556682250[178] = 0;
   out_5878277159556682250[179] = 0;
   out_5878277159556682250[180] = 0;
   out_5878277159556682250[181] = 0;
   out_5878277159556682250[182] = 0;
   out_5878277159556682250[183] = 0;
   out_5878277159556682250[184] = 0;
   out_5878277159556682250[185] = 0;
   out_5878277159556682250[186] = 0;
   out_5878277159556682250[187] = 0;
   out_5878277159556682250[188] = 0;
   out_5878277159556682250[189] = 0;
   out_5878277159556682250[190] = 1;
   out_5878277159556682250[191] = 0;
   out_5878277159556682250[192] = 0;
   out_5878277159556682250[193] = 0;
   out_5878277159556682250[194] = 0;
   out_5878277159556682250[195] = 0;
   out_5878277159556682250[196] = 0;
   out_5878277159556682250[197] = 0;
   out_5878277159556682250[198] = 0;
   out_5878277159556682250[199] = 0;
   out_5878277159556682250[200] = 0;
   out_5878277159556682250[201] = 0;
   out_5878277159556682250[202] = 0;
   out_5878277159556682250[203] = 0;
   out_5878277159556682250[204] = 0;
   out_5878277159556682250[205] = 0;
   out_5878277159556682250[206] = 0;
   out_5878277159556682250[207] = 0;
   out_5878277159556682250[208] = 0;
   out_5878277159556682250[209] = 1;
   out_5878277159556682250[210] = 0;
   out_5878277159556682250[211] = 0;
   out_5878277159556682250[212] = 0;
   out_5878277159556682250[213] = 0;
   out_5878277159556682250[214] = 0;
   out_5878277159556682250[215] = 0;
   out_5878277159556682250[216] = 0;
   out_5878277159556682250[217] = 0;
   out_5878277159556682250[218] = 0;
   out_5878277159556682250[219] = 0;
   out_5878277159556682250[220] = 0;
   out_5878277159556682250[221] = 0;
   out_5878277159556682250[222] = 0;
   out_5878277159556682250[223] = 0;
   out_5878277159556682250[224] = 0;
   out_5878277159556682250[225] = 0;
   out_5878277159556682250[226] = 0;
   out_5878277159556682250[227] = 0;
   out_5878277159556682250[228] = 1;
   out_5878277159556682250[229] = 0;
   out_5878277159556682250[230] = 0;
   out_5878277159556682250[231] = 0;
   out_5878277159556682250[232] = 0;
   out_5878277159556682250[233] = 0;
   out_5878277159556682250[234] = 0;
   out_5878277159556682250[235] = 0;
   out_5878277159556682250[236] = 0;
   out_5878277159556682250[237] = 0;
   out_5878277159556682250[238] = 0;
   out_5878277159556682250[239] = 0;
   out_5878277159556682250[240] = 0;
   out_5878277159556682250[241] = 0;
   out_5878277159556682250[242] = 0;
   out_5878277159556682250[243] = 0;
   out_5878277159556682250[244] = 0;
   out_5878277159556682250[245] = 0;
   out_5878277159556682250[246] = 0;
   out_5878277159556682250[247] = 1;
   out_5878277159556682250[248] = 0;
   out_5878277159556682250[249] = 0;
   out_5878277159556682250[250] = 0;
   out_5878277159556682250[251] = 0;
   out_5878277159556682250[252] = 0;
   out_5878277159556682250[253] = 0;
   out_5878277159556682250[254] = 0;
   out_5878277159556682250[255] = 0;
   out_5878277159556682250[256] = 0;
   out_5878277159556682250[257] = 0;
   out_5878277159556682250[258] = 0;
   out_5878277159556682250[259] = 0;
   out_5878277159556682250[260] = 0;
   out_5878277159556682250[261] = 0;
   out_5878277159556682250[262] = 0;
   out_5878277159556682250[263] = 0;
   out_5878277159556682250[264] = 0;
   out_5878277159556682250[265] = 0;
   out_5878277159556682250[266] = 1;
   out_5878277159556682250[267] = 0;
   out_5878277159556682250[268] = 0;
   out_5878277159556682250[269] = 0;
   out_5878277159556682250[270] = 0;
   out_5878277159556682250[271] = 0;
   out_5878277159556682250[272] = 0;
   out_5878277159556682250[273] = 0;
   out_5878277159556682250[274] = 0;
   out_5878277159556682250[275] = 0;
   out_5878277159556682250[276] = 0;
   out_5878277159556682250[277] = 0;
   out_5878277159556682250[278] = 0;
   out_5878277159556682250[279] = 0;
   out_5878277159556682250[280] = 0;
   out_5878277159556682250[281] = 0;
   out_5878277159556682250[282] = 0;
   out_5878277159556682250[283] = 0;
   out_5878277159556682250[284] = 0;
   out_5878277159556682250[285] = 1;
   out_5878277159556682250[286] = 0;
   out_5878277159556682250[287] = 0;
   out_5878277159556682250[288] = 0;
   out_5878277159556682250[289] = 0;
   out_5878277159556682250[290] = 0;
   out_5878277159556682250[291] = 0;
   out_5878277159556682250[292] = 0;
   out_5878277159556682250[293] = 0;
   out_5878277159556682250[294] = 0;
   out_5878277159556682250[295] = 0;
   out_5878277159556682250[296] = 0;
   out_5878277159556682250[297] = 0;
   out_5878277159556682250[298] = 0;
   out_5878277159556682250[299] = 0;
   out_5878277159556682250[300] = 0;
   out_5878277159556682250[301] = 0;
   out_5878277159556682250[302] = 0;
   out_5878277159556682250[303] = 0;
   out_5878277159556682250[304] = 1;
   out_5878277159556682250[305] = 0;
   out_5878277159556682250[306] = 0;
   out_5878277159556682250[307] = 0;
   out_5878277159556682250[308] = 0;
   out_5878277159556682250[309] = 0;
   out_5878277159556682250[310] = 0;
   out_5878277159556682250[311] = 0;
   out_5878277159556682250[312] = 0;
   out_5878277159556682250[313] = 0;
   out_5878277159556682250[314] = 0;
   out_5878277159556682250[315] = 0;
   out_5878277159556682250[316] = 0;
   out_5878277159556682250[317] = 0;
   out_5878277159556682250[318] = 0;
   out_5878277159556682250[319] = 0;
   out_5878277159556682250[320] = 0;
   out_5878277159556682250[321] = 0;
   out_5878277159556682250[322] = 0;
   out_5878277159556682250[323] = 1;
}
void h_4(double *state, double *unused, double *out_5305905984689579201) {
   out_5305905984689579201[0] = state[6] + state[9];
   out_5305905984689579201[1] = state[7] + state[10];
   out_5305905984689579201[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_575573780401498883) {
   out_575573780401498883[0] = 0;
   out_575573780401498883[1] = 0;
   out_575573780401498883[2] = 0;
   out_575573780401498883[3] = 0;
   out_575573780401498883[4] = 0;
   out_575573780401498883[5] = 0;
   out_575573780401498883[6] = 1;
   out_575573780401498883[7] = 0;
   out_575573780401498883[8] = 0;
   out_575573780401498883[9] = 1;
   out_575573780401498883[10] = 0;
   out_575573780401498883[11] = 0;
   out_575573780401498883[12] = 0;
   out_575573780401498883[13] = 0;
   out_575573780401498883[14] = 0;
   out_575573780401498883[15] = 0;
   out_575573780401498883[16] = 0;
   out_575573780401498883[17] = 0;
   out_575573780401498883[18] = 0;
   out_575573780401498883[19] = 0;
   out_575573780401498883[20] = 0;
   out_575573780401498883[21] = 0;
   out_575573780401498883[22] = 0;
   out_575573780401498883[23] = 0;
   out_575573780401498883[24] = 0;
   out_575573780401498883[25] = 1;
   out_575573780401498883[26] = 0;
   out_575573780401498883[27] = 0;
   out_575573780401498883[28] = 1;
   out_575573780401498883[29] = 0;
   out_575573780401498883[30] = 0;
   out_575573780401498883[31] = 0;
   out_575573780401498883[32] = 0;
   out_575573780401498883[33] = 0;
   out_575573780401498883[34] = 0;
   out_575573780401498883[35] = 0;
   out_575573780401498883[36] = 0;
   out_575573780401498883[37] = 0;
   out_575573780401498883[38] = 0;
   out_575573780401498883[39] = 0;
   out_575573780401498883[40] = 0;
   out_575573780401498883[41] = 0;
   out_575573780401498883[42] = 0;
   out_575573780401498883[43] = 0;
   out_575573780401498883[44] = 1;
   out_575573780401498883[45] = 0;
   out_575573780401498883[46] = 0;
   out_575573780401498883[47] = 1;
   out_575573780401498883[48] = 0;
   out_575573780401498883[49] = 0;
   out_575573780401498883[50] = 0;
   out_575573780401498883[51] = 0;
   out_575573780401498883[52] = 0;
   out_575573780401498883[53] = 0;
}
void h_10(double *state, double *unused, double *out_2835732852621838097) {
   out_2835732852621838097[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_2835732852621838097[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_2835732852621838097[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_3794534418366600876) {
   out_3794534418366600876[0] = 0;
   out_3794534418366600876[1] = 9.8100000000000005*cos(state[1]);
   out_3794534418366600876[2] = 0;
   out_3794534418366600876[3] = 0;
   out_3794534418366600876[4] = -state[8];
   out_3794534418366600876[5] = state[7];
   out_3794534418366600876[6] = 0;
   out_3794534418366600876[7] = state[5];
   out_3794534418366600876[8] = -state[4];
   out_3794534418366600876[9] = 0;
   out_3794534418366600876[10] = 0;
   out_3794534418366600876[11] = 0;
   out_3794534418366600876[12] = 1;
   out_3794534418366600876[13] = 0;
   out_3794534418366600876[14] = 0;
   out_3794534418366600876[15] = 1;
   out_3794534418366600876[16] = 0;
   out_3794534418366600876[17] = 0;
   out_3794534418366600876[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_3794534418366600876[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_3794534418366600876[20] = 0;
   out_3794534418366600876[21] = state[8];
   out_3794534418366600876[22] = 0;
   out_3794534418366600876[23] = -state[6];
   out_3794534418366600876[24] = -state[5];
   out_3794534418366600876[25] = 0;
   out_3794534418366600876[26] = state[3];
   out_3794534418366600876[27] = 0;
   out_3794534418366600876[28] = 0;
   out_3794534418366600876[29] = 0;
   out_3794534418366600876[30] = 0;
   out_3794534418366600876[31] = 1;
   out_3794534418366600876[32] = 0;
   out_3794534418366600876[33] = 0;
   out_3794534418366600876[34] = 1;
   out_3794534418366600876[35] = 0;
   out_3794534418366600876[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_3794534418366600876[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_3794534418366600876[38] = 0;
   out_3794534418366600876[39] = -state[7];
   out_3794534418366600876[40] = state[6];
   out_3794534418366600876[41] = 0;
   out_3794534418366600876[42] = state[4];
   out_3794534418366600876[43] = -state[3];
   out_3794534418366600876[44] = 0;
   out_3794534418366600876[45] = 0;
   out_3794534418366600876[46] = 0;
   out_3794534418366600876[47] = 0;
   out_3794534418366600876[48] = 0;
   out_3794534418366600876[49] = 0;
   out_3794534418366600876[50] = 1;
   out_3794534418366600876[51] = 0;
   out_3794534418366600876[52] = 0;
   out_3794534418366600876[53] = 1;
}
void h_13(double *state, double *unused, double *out_5662511839388362108) {
   out_5662511839388362108[0] = state[3];
   out_5662511839388362108[1] = state[4];
   out_5662511839388362108[2] = state[5];
}
void H_13(double *state, double *unused, double *out_2636700044930833918) {
   out_2636700044930833918[0] = 0;
   out_2636700044930833918[1] = 0;
   out_2636700044930833918[2] = 0;
   out_2636700044930833918[3] = 1;
   out_2636700044930833918[4] = 0;
   out_2636700044930833918[5] = 0;
   out_2636700044930833918[6] = 0;
   out_2636700044930833918[7] = 0;
   out_2636700044930833918[8] = 0;
   out_2636700044930833918[9] = 0;
   out_2636700044930833918[10] = 0;
   out_2636700044930833918[11] = 0;
   out_2636700044930833918[12] = 0;
   out_2636700044930833918[13] = 0;
   out_2636700044930833918[14] = 0;
   out_2636700044930833918[15] = 0;
   out_2636700044930833918[16] = 0;
   out_2636700044930833918[17] = 0;
   out_2636700044930833918[18] = 0;
   out_2636700044930833918[19] = 0;
   out_2636700044930833918[20] = 0;
   out_2636700044930833918[21] = 0;
   out_2636700044930833918[22] = 1;
   out_2636700044930833918[23] = 0;
   out_2636700044930833918[24] = 0;
   out_2636700044930833918[25] = 0;
   out_2636700044930833918[26] = 0;
   out_2636700044930833918[27] = 0;
   out_2636700044930833918[28] = 0;
   out_2636700044930833918[29] = 0;
   out_2636700044930833918[30] = 0;
   out_2636700044930833918[31] = 0;
   out_2636700044930833918[32] = 0;
   out_2636700044930833918[33] = 0;
   out_2636700044930833918[34] = 0;
   out_2636700044930833918[35] = 0;
   out_2636700044930833918[36] = 0;
   out_2636700044930833918[37] = 0;
   out_2636700044930833918[38] = 0;
   out_2636700044930833918[39] = 0;
   out_2636700044930833918[40] = 0;
   out_2636700044930833918[41] = 1;
   out_2636700044930833918[42] = 0;
   out_2636700044930833918[43] = 0;
   out_2636700044930833918[44] = 0;
   out_2636700044930833918[45] = 0;
   out_2636700044930833918[46] = 0;
   out_2636700044930833918[47] = 0;
   out_2636700044930833918[48] = 0;
   out_2636700044930833918[49] = 0;
   out_2636700044930833918[50] = 0;
   out_2636700044930833918[51] = 0;
   out_2636700044930833918[52] = 0;
   out_2636700044930833918[53] = 0;
}
void h_14(double *state, double *unused, double *out_556794040786755953) {
   out_556794040786755953[0] = state[6];
   out_556794040786755953[1] = state[7];
   out_556794040786755953[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3387667075937985646) {
   out_3387667075937985646[0] = 0;
   out_3387667075937985646[1] = 0;
   out_3387667075937985646[2] = 0;
   out_3387667075937985646[3] = 0;
   out_3387667075937985646[4] = 0;
   out_3387667075937985646[5] = 0;
   out_3387667075937985646[6] = 1;
   out_3387667075937985646[7] = 0;
   out_3387667075937985646[8] = 0;
   out_3387667075937985646[9] = 0;
   out_3387667075937985646[10] = 0;
   out_3387667075937985646[11] = 0;
   out_3387667075937985646[12] = 0;
   out_3387667075937985646[13] = 0;
   out_3387667075937985646[14] = 0;
   out_3387667075937985646[15] = 0;
   out_3387667075937985646[16] = 0;
   out_3387667075937985646[17] = 0;
   out_3387667075937985646[18] = 0;
   out_3387667075937985646[19] = 0;
   out_3387667075937985646[20] = 0;
   out_3387667075937985646[21] = 0;
   out_3387667075937985646[22] = 0;
   out_3387667075937985646[23] = 0;
   out_3387667075937985646[24] = 0;
   out_3387667075937985646[25] = 1;
   out_3387667075937985646[26] = 0;
   out_3387667075937985646[27] = 0;
   out_3387667075937985646[28] = 0;
   out_3387667075937985646[29] = 0;
   out_3387667075937985646[30] = 0;
   out_3387667075937985646[31] = 0;
   out_3387667075937985646[32] = 0;
   out_3387667075937985646[33] = 0;
   out_3387667075937985646[34] = 0;
   out_3387667075937985646[35] = 0;
   out_3387667075937985646[36] = 0;
   out_3387667075937985646[37] = 0;
   out_3387667075937985646[38] = 0;
   out_3387667075937985646[39] = 0;
   out_3387667075937985646[40] = 0;
   out_3387667075937985646[41] = 0;
   out_3387667075937985646[42] = 0;
   out_3387667075937985646[43] = 0;
   out_3387667075937985646[44] = 1;
   out_3387667075937985646[45] = 0;
   out_3387667075937985646[46] = 0;
   out_3387667075937985646[47] = 0;
   out_3387667075937985646[48] = 0;
   out_3387667075937985646[49] = 0;
   out_3387667075937985646[50] = 0;
   out_3387667075937985646[51] = 0;
   out_3387667075937985646[52] = 0;
   out_3387667075937985646[53] = 0;
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

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_8873621528686367328) {
  err_fun(nom_x, delta_x, out_8873621528686367328);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_6845093829299839856) {
  inv_err_fun(nom_x, true_x, out_6845093829299839856);
}
void pose_H_mod_fun(double *state, double *out_5272508026350459838) {
  H_mod_fun(state, out_5272508026350459838);
}
void pose_f_fun(double *state, double dt, double *out_5613529983893470632) {
  f_fun(state,  dt, out_5613529983893470632);
}
void pose_F_fun(double *state, double dt, double *out_5878277159556682250) {
  F_fun(state,  dt, out_5878277159556682250);
}
void pose_h_4(double *state, double *unused, double *out_5305905984689579201) {
  h_4(state, unused, out_5305905984689579201);
}
void pose_H_4(double *state, double *unused, double *out_575573780401498883) {
  H_4(state, unused, out_575573780401498883);
}
void pose_h_10(double *state, double *unused, double *out_2835732852621838097) {
  h_10(state, unused, out_2835732852621838097);
}
void pose_H_10(double *state, double *unused, double *out_3794534418366600876) {
  H_10(state, unused, out_3794534418366600876);
}
void pose_h_13(double *state, double *unused, double *out_5662511839388362108) {
  h_13(state, unused, out_5662511839388362108);
}
void pose_H_13(double *state, double *unused, double *out_2636700044930833918) {
  H_13(state, unused, out_2636700044930833918);
}
void pose_h_14(double *state, double *unused, double *out_556794040786755953) {
  h_14(state, unused, out_556794040786755953);
}
void pose_H_14(double *state, double *unused, double *out_3387667075937985646) {
  H_14(state, unused, out_3387667075937985646);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
