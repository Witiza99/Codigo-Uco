/**********************************************************************/
/*   ____  ____                                                       */
/*  /   /\/   /                                                       */
/* /___/  \  /                                                        */
/* \   \   \/                                                       */
/*  \   \        Copyright (c) 2003-2009 Xilinx, Inc.                */
/*  /   /          All Right Reserved.                                 */
/* /---/   /\                                                         */
/* \   \  /  \                                                      */
/*  \___\/\___\                                                    */
/***********************************************************************/

/* This file is designed for use with ISim build 0x7708f090 */

#define XSI_HIDE_SYMBOL_SPEC true
#include "xsi.h"
#include <memory.h>
#ifdef __GNUC__
#include <stdlib.h>
#else
#include <malloc.h>
#define alloca _alloca
#endif
static const char *ng0 = "E:/xinlinx/Practica1v2/Registro.vhd";
extern char *IEEE_P_2592010699;

unsigned char ieee_p_2592010699_sub_1744673427_503743352(char *, char *, unsigned int , unsigned int );


static void work_a_0827584957_3212880686_p_0(char *t0)
{
    char *t1;
    unsigned char t2;
    char *t3;
    char *t4;
    char *t5;
    int t6;
    char *t7;
    char *t8;
    int t9;
    char *t10;
    char *t11;
    int t12;
    char *t13;
    char *t14;
    int t15;
    char *t16;
    int t18;
    char *t19;
    int t21;
    char *t22;
    int t24;
    char *t25;
    int t27;
    char *t28;
    char *t29;
    char *t30;
    char *t31;
    char *t32;
    char *t33;
    unsigned int t34;
    unsigned int t35;
    unsigned int t36;
    unsigned int t37;
    unsigned int t38;
    unsigned int t39;

LAB0:    xsi_set_current_line(49, ng0);
    t1 = (t0 + 1472U);
    t2 = ieee_p_2592010699_sub_1744673427_503743352(IEEE_P_2592010699, t1, 0U, 0U);
    if (t2 != 0)
        goto LAB2;

LAB4:
LAB3:    t1 = (t0 + 3400);
    *((int *)t1) = 1;

LAB1:    return;
LAB2:    xsi_set_current_line(51, ng0);
    t3 = (t0 + 1192U);
    t4 = *((char **)t3);
    t3 = (t0 + 5296);
    t6 = xsi_mem_cmp(t3, t4, 3U);
    if (t6 == 1)
        goto LAB6;

LAB15:    t7 = (t0 + 5299);
    t9 = xsi_mem_cmp(t7, t4, 3U);
    if (t9 == 1)
        goto LAB7;

LAB16:    t10 = (t0 + 5302);
    t12 = xsi_mem_cmp(t10, t4, 3U);
    if (t12 == 1)
        goto LAB8;

LAB17:    t13 = (t0 + 5305);
    t15 = xsi_mem_cmp(t13, t4, 3U);
    if (t15 == 1)
        goto LAB9;

LAB18:    t16 = (t0 + 5308);
    t18 = xsi_mem_cmp(t16, t4, 3U);
    if (t18 == 1)
        goto LAB10;

LAB19:    t19 = (t0 + 5311);
    t21 = xsi_mem_cmp(t19, t4, 3U);
    if (t21 == 1)
        goto LAB11;

LAB20:    t22 = (t0 + 5314);
    t24 = xsi_mem_cmp(t22, t4, 3U);
    if (t24 == 1)
        goto LAB12;

LAB21:    t25 = (t0 + 5317);
    t27 = xsi_mem_cmp(t25, t4, 3U);
    if (t27 == 1)
        goto LAB13;

LAB22:
LAB14:    xsi_set_current_line(79, ng0);
    t1 = (t0 + 1672U);
    t3 = *((char **)t1);
    t1 = (t0 + 3496);
    t4 = (t1 + 56U);
    t5 = *((char **)t4);
    t7 = (t5 + 56U);
    t8 = *((char **)t7);
    memcpy(t8, t3, 4U);
    xsi_driver_first_trans_fast(t1);

LAB5:    goto LAB3;

LAB6:    xsi_set_current_line(53, ng0);
    t28 = (t0 + 1672U);
    t29 = *((char **)t28);
    t28 = (t0 + 3496);
    t30 = (t28 + 56U);
    t31 = *((char **)t30);
    t32 = (t31 + 56U);
    t33 = *((char **)t32);
    memcpy(t33, t29, 4U);
    xsi_driver_first_trans_fast(t28);
    goto LAB5;

LAB7:    xsi_set_current_line(56, ng0);
    t1 = (t0 + 1672U);
    t3 = *((char **)t1);
    t1 = xsi_vhdl_bitvec_srl(t1, t3, 4U, 2);
    t2 = (4U != 4U);
    if (t2 == 1)
        goto LAB24;

LAB25:    t4 = (t0 + 3496);
    t5 = (t4 + 56U);
    t7 = *((char **)t5);
    t8 = (t7 + 56U);
    t10 = *((char **)t8);
    memcpy(t10, t1, 4U);
    xsi_driver_first_trans_fast(t4);
    goto LAB5;

LAB8:    xsi_set_current_line(59, ng0);
    t1 = (t0 + 5320);
    t4 = (t0 + 3496);
    t5 = (t4 + 56U);
    t7 = *((char **)t5);
    t8 = (t7 + 56U);
    t10 = *((char **)t8);
    memcpy(t10, t1, 4U);
    xsi_driver_first_trans_fast(t4);
    goto LAB5;

LAB9:    xsi_set_current_line(62, ng0);
    t1 = (t0 + 5324);
    *((int *)t1) = 0;
    t3 = (t0 + 5328);
    *((int *)t3) = 3;
    t6 = 0;
    t9 = 3;

LAB26:    if (t6 <= t9)
        goto LAB27;

LAB29:    goto LAB5;

LAB10:    xsi_set_current_line(67, ng0);
    t1 = (t0 + 1672U);
    t3 = *((char **)t1);
    t1 = xsi_vhdl_bitvec_not(t1, t3, 4U);
    t2 = (4U != 4U);
    if (t2 == 1)
        goto LAB31;

LAB32:    t4 = (t0 + 3496);
    t5 = (t4 + 56U);
    t7 = *((char **)t5);
    t8 = (t7 + 56U);
    t10 = *((char **)t8);
    memcpy(t10, t1, 4U);
    xsi_driver_first_trans_fast(t4);
    goto LAB5;

LAB11:    xsi_set_current_line(70, ng0);
    t1 = (t0 + 1032U);
    t3 = *((char **)t1);
    t1 = (t0 + 1672U);
    t4 = *((char **)t1);
    t1 = xsi_vhdl_bitvec_and(t1, t3, 4U, t4, 4U);
    t2 = (4U != 4U);
    if (t2 == 1)
        goto LAB33;

LAB34:    t5 = (t0 + 3496);
    t7 = (t5 + 56U);
    t8 = *((char **)t7);
    t10 = (t8 + 56U);
    t11 = *((char **)t10);
    memcpy(t11, t1, 4U);
    xsi_driver_first_trans_fast(t5);
    goto LAB5;

LAB12:    xsi_set_current_line(73, ng0);
    t1 = (t0 + 1032U);
    t3 = *((char **)t1);
    t1 = (t0 + 1672U);
    t4 = *((char **)t1);
    t1 = xsi_vhdl_bitvec_or(t1, t3, 4U, t4, 4U);
    t2 = (4U != 4U);
    if (t2 == 1)
        goto LAB35;

LAB36:    t5 = (t0 + 3496);
    t7 = (t5 + 56U);
    t8 = *((char **)t7);
    t10 = (t8 + 56U);
    t11 = *((char **)t10);
    memcpy(t11, t1, 4U);
    xsi_driver_first_trans_fast(t5);
    goto LAB5;

LAB13:    xsi_set_current_line(76, ng0);
    t1 = (t0 + 1672U);
    t3 = *((char **)t1);
    t1 = xsi_vhdl_bitvec_rol(t1, t3, 4U, 1);
    t2 = (4U != 4U);
    if (t2 == 1)
        goto LAB37;

LAB38:    t4 = (t0 + 3496);
    t5 = (t4 + 56U);
    t7 = *((char **)t5);
    t8 = (t7 + 56U);
    t10 = *((char **)t8);
    memcpy(t10, t1, 4U);
    xsi_driver_first_trans_fast(t4);
    goto LAB5;

LAB23:;
LAB24:    xsi_size_not_matching(4U, 4U, 0);
    goto LAB25;

LAB27:    xsi_set_current_line(63, ng0);
    t4 = (t0 + 1032U);
    t5 = *((char **)t4);
    t4 = (t0 + 5324);
    t12 = *((int *)t4);
    t15 = (t12 - 3);
    t34 = (t15 * -1);
    xsi_vhdl_check_range_of_index(3, 0, -1, *((int *)t4));
    t35 = (1U * t34);
    t36 = (0 + t35);
    t7 = (t5 + t36);
    t2 = *((unsigned char *)t7);
    t8 = (t0 + 5324);
    t18 = *((int *)t8);
    t21 = (t18 - 3);
    t37 = (t21 * -1);
    t38 = (1 * t37);
    t39 = (0U + t38);
    t10 = (t0 + 3496);
    t11 = (t10 + 56U);
    t13 = *((char **)t11);
    t14 = (t13 + 56U);
    t16 = *((char **)t14);
    *((unsigned char *)t16) = t2;
    xsi_driver_first_trans_delta(t10, t39, 1, 0LL);

LAB28:    t1 = (t0 + 5324);
    t6 = *((int *)t1);
    t3 = (t0 + 5328);
    t9 = *((int *)t3);
    if (t6 == t9)
        goto LAB29;

LAB30:    t12 = (t6 + 1);
    t6 = t12;
    t4 = (t0 + 5324);
    *((int *)t4) = t6;
    goto LAB26;

LAB31:    xsi_size_not_matching(4U, 4U, 0);
    goto LAB32;

LAB33:    xsi_size_not_matching(4U, 4U, 0);
    goto LAB34;

LAB35:    xsi_size_not_matching(4U, 4U, 0);
    goto LAB36;

LAB37:    xsi_size_not_matching(4U, 4U, 0);
    goto LAB38;

}

static void work_a_0827584957_3212880686_p_1(char *t0)
{
    char *t1;
    char *t2;
    char *t3;
    char *t4;
    char *t5;
    char *t6;
    char *t7;

LAB0:    xsi_set_current_line(86, ng0);

LAB3:    t1 = (t0 + 1672U);
    t2 = *((char **)t1);
    t1 = (t0 + 3560);
    t3 = (t1 + 56U);
    t4 = *((char **)t3);
    t5 = (t4 + 56U);
    t6 = *((char **)t5);
    memcpy(t6, t2, 4U);
    xsi_driver_first_trans_fast_port(t1);

LAB2:    t7 = (t0 + 3416);
    *((int *)t7) = 1;

LAB1:    return;
LAB4:    goto LAB2;

}


extern void work_a_0827584957_3212880686_init()
{
	static char *pe[] = {(void *)work_a_0827584957_3212880686_p_0,(void *)work_a_0827584957_3212880686_p_1};
	xsi_register_didat("work_a_0827584957_3212880686", "isim/test_practica1_isim_beh.exe.sim/work/a_0827584957_3212880686.didat");
	xsi_register_executes(pe);
}
