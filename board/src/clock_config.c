/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/
/*
 * How to setup clock using clock driver functions:
 *
 * 1. CLOCK_SetSimSafeDivs, to make sure core clock, bus clock, flexbus clock
 *    and flash clock are in allowed range during clock mode switch.
 *
 * 2. Call CLOCK_Osc0Init to setup OSC clock, if it is used in target mode.
 *
 * 3. Set MCG configuration, MCG includes three parts: FLL clock, PLL clock and
 *    internal reference clock(MCGIRCLK). Follow the steps to setup:
 *
 *    1). Call CLOCK_BootToXxxMode to set MCG to target mode.
 *
 *    2). If target mode is FBI/BLPI/PBI mode, the MCGIRCLK has been configured
 *        correctly. For other modes, need to call CLOCK_SetInternalRefClkConfig
 *        explicitly to setup MCGIRCLK.
 *
 *    3). Don't need to configure FLL explicitly, because if target mode is FLL
 *        mode, then FLL has been configured by the function CLOCK_BootToXxxMode,
 *        if the target mode is not FLL mode, the FLL is disabled.
 *
 *    4). If target mode is PEE/PBE/PEI/PBI mode, then the related PLL has been
 *        setup by CLOCK_BootToXxxMode. In FBE/FBI/FEE/FBE mode, the PLL could
 *        be enabled independently, call CLOCK_EnablePll0 explicitly in this case.
 *
 * 4. Call CLOCK_SetSimConfig to set the clock configuration in SIM.
 */

/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Clocks v4.0
processor: MKV58F1M0xxx24
package_id: MKV58F1M0VLQ24
mcu_data: ksdk2_0
processor_version: 3.0.0
board: TWR-KV58F220M
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

#include "fsl_smc.h"
#include "clock_config.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MCG_PLL_DISABLE                                   0U  /*!< MCGPLLCLK disabled */
#define OSC_CAP0P                                         0U  /*!< Oscillator 0pF capacitor load */
#define SIM_OSC32KSEL_LPO_CLK                             3U  /*!< OSC32KSEL select: LPO clock */
#define SIM_PLLFLLSEL_MCGPLLCLK_CLK                       1U  /*!< PLLFLL select: MCGPLLCLK clock */

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* System clock frequency. */
extern uint32_t SystemCoreClock;

/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_CONFIG_SetSimSafeDivs
 * Description   : This function sets the system clock dividers in SIM to safe 
 * value.
 *
 *END**************************************************************************/
static void CLOCK_CONFIG_SetSimSafeDivs(void)
{
    SIM->CLKDIV1 = 0x01170000U;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_CONFIG_SetFllExtRefDiv
 * Description   : Configure FLL external reference divider (FRDIV).
 * Param frdiv   : The value to set FRDIV.
 *
 *END**************************************************************************/
static void CLOCK_CONFIG_SetFllExtRefDiv(uint8_t frdiv)
{
    MCG->C1 = ((MCG->C1 & ~MCG_C1_FRDIV_MASK) | MCG_C1_FRDIV(frdiv));
}

/*******************************************************************************
 ************************ BOARD_InitBootClocks function ************************
 ******************************************************************************/
void BOARD_InitBootClocks(void)
{
    HSCLOCK();
}

/*******************************************************************************
 *************************** Configuration HSCLOCK *****************************
 ******************************************************************************/
/* clang-format off */
/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: HSCLOCK
called_from_default_init: true
outputs:
- {id: Bus_clock.outFreq, value: 114 MHz}
- {id: Core_clock.outFreq, value: 228 MHz}
- {id: ERCLK32K.outFreq, value: 1 kHz}
- {id: Flash_clock.outFreq, value: 22.8 MHz}
- {id: FlexBus_clock.outFreq, value: 57 MHz}
- {id: LPO_clock.outFreq, value: 1 kHz}
- {id: MCGFFCLK.outFreq, value: 1.5 MHz}
- {id: MCGIRCLK.outFreq, value: 32.768 kHz}
- {id: OSCERCLK.outFreq, value: 48 MHz}
- {id: OSCERCLK_UNDIV.outFreq, value: 48 MHz}
- {id: PLLFLLCLK.outFreq, value: 228 MHz}
- {id: System_clock.outFreq, value: 228 MHz}
settings:
- {id: MCGMode, value: PEE}
- {id: powerMode, value: HSRUN}
- {id: MCG.FCRDIV.scale, value: '1'}
- {id: MCG.FLL_mul.scale, value: '2560', locked: true}
- {id: MCG.FRDIV.scale, value: '32'}
- {id: MCG.IREFS.sel, value: MCG.FRDIV}
- {id: MCG.PLLS.sel, value: MCG.PLL_DIV2}
- {id: MCG.PRDIV.scale, value: '4', locked: true}
- {id: MCG.VDIV.scale, value: '38', locked: true}
- {id: MCG_C1_IRCLKEN_CFG, value: Enabled}
- {id: MCG_C2_RANGE0_CFG, value: Very_high}
- {id: MCG_C2_RANGE0_FRDIV_CFG, value: Very_high}
- {id: OSC_CR_ERCLKEN_CFG, value: Enabled}
- {id: OSC_CR_ERCLKEN_UNDIV_CFG, value: Enabled}
- {id: SIM.OSC32KSEL.sel, value: PMC.LPOCLK}
- {id: SIM.OUTDIV1.scale, value: '1', locked: true}
- {id: SIM.OUTDIV2.scale, value: '2', locked: true}
- {id: SIM.OUTDIV3.scale, value: '4', locked: true}
- {id: SIM.OUTDIV4.scale, value: '10', locked: true}
- {id: SIM.PLLFLLSEL.sel, value: MCG.MCGPLLCLK}
- {id: SIM.RMIICLKSEL.sel, value: SIM.ENET_1588_CLK_EXT}
- {id: SIM.TIMESRCSEL.sel, value: SIM.ENET_1588_CLK_EXT}
sources:
- {id: OSC.OSC.outFreq, value: 48 MHz, enabled: true}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/
/* clang-format on */

/*******************************************************************************
 * Variables for HSCLOCK configuration
 ******************************************************************************/
//237.5Mhz
//�ȶ���Bus/Flashδ��Ƶ
//.prdiv = 0x3U,  
//.vdiv = 0x16U,
//.clkdiv1 = 0x1390000U,
//250Mhz
//���ȶ���Bus/Flash��Ƶ
//.prdiv = 0x3U,
//.vdiv = 0x18U,
//.clkdiv1 = 0x1370000U,
//256.25Mhz
//���ȶ���Bus/Flash��Ƶ
//.prdiv = 0x3U,
//.vdiv = 0x19U,
//.clkdiv1 = 0x1370000U,
//262.5Mhz
//�ϲ��ȶ���Bus/Flash��Ƶ
//.prdiv = 0x3U,
//.vdiv = 0x1AU,
//.clkdiv1 = 0x1370000U,
//268.75Mhz
//���ȶ���Bus/Flashδ��Ƶ
//.prdiv = 0x3U,
//.vdiv = 0x1BU,
//.clkdiv1 = 0x1390000U,
const mcg_config_t mcgConfig_HSCLOCK =
    {
        .mcgMode = kMCG_ModePEE,                  /* PEE - PLL Engaged External */
        .irclkEnableMode = kMCG_IrclkEnable,      /* MCGIRCLK enabled, MCGIRCLK disabled in STOP mode */
        .ircs = kMCG_IrcSlow,                     /* Slow internal reference clock selected */
        .fcrdiv = 0x0U,                           /* Fast IRC divider: divided by 1 */
        .frdiv = 0x0U,                            /* FLL reference clock divider: divided by 32 */
        .drs = kMCG_DrsHigh,                      /* High frequency range */
        .dmx32 = kMCG_Dmx32Default,               /* DCO has a default range of 25% */
        .pll0Config =
            {
                .enableMode = MCG_PLL_DISABLE,    /* MCGPLLCLK disabled */    
                .prdiv = 0x3U,                    /* PLL Reference divider: divided by 3 */
                .vdiv = 0x1AU,                    /* VCO divider: multiplied by 42 */
            },
    };
const sim_clock_config_t simConfig_HSCLOCK =
    {
        .pllFllSel = SIM_PLLFLLSEL_MCGPLLCLK_CLK, /* PLLFLL select: MCGPLLCLK clock */
        .er32kSrc = SIM_OSC32KSEL_LPO_CLK,        /* OSC32KSEL select: LPO clock */
        .clkdiv1 = 0x1370000U,                    /* SIM_CLKDIV1 - OUTDIV1: /1, OUTDIV2: /2, OUTDIV3: /4, OUTDIV4: /10 */
    };
const osc_config_t oscConfig_HSCLOCK =
    {
        .freq = 50000000U,                        /* Oscillator frequency: 50000000Hz */
        .capLoad = (OSC_CAP0P),                   /* Oscillator capacity load: 0pF */
        .workMode = kOSC_ModeExt,                 /* Use external clock */
        .oscerConfig =
            {
                .enableMode = kOSC_ErClkEnable,   /* Enable external reference clock, disable external reference clock in STOP mode */
                .erclkDiv = 0,                    /* Divider for OSCERCLK: divided by 1 */
            }
    };

/*******************************************************************************
 * Code for HSCLOCK configuration
 ******************************************************************************/
void HSCLOCK(void)
{
    /* Set HSRUN power mode */
    SMC_SetPowerModeProtection(SMC, kSMC_AllowPowerModeAll);
    SMC_SetPowerModeHsrun(SMC);
    while (SMC_GetPowerModeState(SMC) != kSMC_PowerStateHsrun)
    {
    }
    /* Set the system clock dividers in SIM to safe value. */
    CLOCK_CONFIG_SetSimSafeDivs();
    /* Initializes OSC0 according to board configuration. */
    CLOCK_InitOsc0(&oscConfig_HSCLOCK);
    CLOCK_SetXtal0Freq(oscConfig_HSCLOCK.freq);
    /* Configure FLL external reference divider (FRDIV). */
    CLOCK_CONFIG_SetFllExtRefDiv(mcgConfig_HSCLOCK.frdiv);
    /* Set MCG to PEE mode. */
    CLOCK_BootToPeeMode(kMCG_OscselOsc,
                        kMCG_PllClkSelPll0,
                        &mcgConfig_HSCLOCK.pll0Config);
    /* Configure the Internal Reference clock (MCGIRCLK). */
    CLOCK_SetInternalRefClkConfig(mcgConfig_HSCLOCK.irclkEnableMode,
                                  mcgConfig_HSCLOCK.ircs, 
                                  mcgConfig_HSCLOCK.fcrdiv);
    /* Set the clock configuration in SIM module. */
    CLOCK_SetSimConfig(&simConfig_HSCLOCK);
    /* Set SystemCoreClock variable. */
    SystemCoreClock = HSCLOCK_CORE_CLOCK;
}

