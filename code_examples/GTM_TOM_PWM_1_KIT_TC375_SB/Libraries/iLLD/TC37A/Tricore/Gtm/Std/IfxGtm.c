/**
 * \file IfxGtm.c
 * \brief GTM  basic functionality
 *
 * \version iLLD_1_0_1_12_0
 * \copyright Copyright (c) 2018 Infineon Technologies AG. All rights reserved.
 *
 *
 *                                 IMPORTANT NOTICE
 *
 * Use of this file is subject to the terms of use agreed between (i) you or
 * the company in which ordinary course of business you are acting and (ii)
 * Infineon Technologies AG or its licensees. If and as long as no such terms
 * of use are agreed, use of this file is subject to following:
 *
 * Boost Software License - Version 1.0 - August 17th, 2003
 *
 * Permission is hereby granted, free of charge, to any person or organization
 * obtaining a copy of the software and accompanying documentation covered by
 * this license (the "Software") to use, reproduce, display, distribute,
 * execute, and transmit the Software, and to prepare derivative works of the
 * Software, and to permit third-parties to whom the Software is furnished to
 * do so, all subject to the following:
 *
 * The copyright notices in the Software and this entire statement, including
 * the above license grant, this restriction and the following disclaimer, must
 * be included in all copies of the Software, in whole or in part, and all
 * derivative works of the Software, unless such copies or derivative works are
 * solely in the form of machine-executable object code generated by a source
 * language processor.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
 * SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
 * FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/

#include "IfxGtm.h"
#include "Scu/Std/IfxScuWdt.h"
#include "Scu/Std/IfxScuCcu.h"

/******************************************************************************/
/*-------------------------Function Implementations---------------------------*/
/******************************************************************************/

void IfxGtm_disable(Ifx_GTM *gtm)
{
    uint16 psw = IfxScuWdt_getCpuWatchdogPassword();

    IfxScuWdt_clearCpuEndinit(psw);
    gtm->CLC.B.DISR = 1;
    IfxScuWdt_setCpuEndinit(psw);
}


void IfxGtm_enable(Ifx_GTM *gtm)
{
    uint16 psw = IfxScuWdt_getCpuWatchdogPassword();

    IfxScuWdt_clearCpuEndinit(psw);
    gtm->CLC.B.DISR = 0;
    IfxScuWdt_setCpuEndinit(psw);
}


float32 IfxGtm_getSysClkFrequency(void)
{
    return IfxScuCcu_getGtmFrequency();
}


float32 IfxGtm_getClusterFrequency(Ifx_GTM *gtm, IfxGtm_Cluster cluster)
{
    float32 Freq;
    uint8   clsDiv = ((gtm->CLS_CLK_CFG.U) >> (cluster * 2)) & 0x3;

    if (clsDiv == 0)
    {
        Freq = 0.0; /* cluster is disabled - return 0 */
    }
    else
    {
        Freq = IfxGtm_getSysClkFrequency() / clsDiv;
    }

    return Freq;
}