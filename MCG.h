/*
 * MCG.h
 *
 *  Created on: 27/10/2015
 *      Author: Admin
 */

#ifndef SOURCES_MCG_H_
#define SOURCES_MCG_H_



// Constants for use in pll_init
#define NO_OSCINIT 0
#define OSCINIT 1

#define OSC_0 0
#define OSC_1 1

#define LOW_POWER 0
#define HIGH_GAIN 1

#define CANNED_OSC  0
#define CRYSTAL 1

#define PLL_0 0
#define PLL_1 1

#define PLL_ONLY 0
#define MCGOUT 1

// MCG Mode defines

#define BLPI 1
#define FBI  2
#define FEI  3
#define FEE  4
#define FBE  5
#define BLPE 6
#define PBE  7
#define PEE  8

// IRC defines
#define SLOW_IRC 0
#define FAST_IRC 1


unsigned char fll_rtc_init(unsigned char, unsigned char);


// prototypes
void rtc_as_refclk(void);
int fee_fei(int slow_irc_freq);
int fei_fbe(int crystal_val, unsigned char hgo_val, unsigned char erefs_val);
int fbe_fei(int slow_irc_freq);
int fei_fbi(int irc_freq, unsigned char irc_select);
int fbi_fei(int slow_irc_freq);
int fbe_pbe(int crystal_val, signed char prdiv_val, signed char vdiv_val);
int pbe_pee(int crystal_val);
int pee_pbe(int crystal_val);
int pbe_fbe(int crystal_val);
int fbe_fbi(int irc_freq, unsigned char irc_select);
int fbi_fbe(int crystal_val, unsigned char hgo_val, unsigned char erefs_val);
int fbi_fee(int crystal_val, unsigned char hgo_val, unsigned char erefs_val);
int fbe_fee(int crystal_val);
int fee_fbe(int crystal_val);
int pbe_blpe(int crystal_val);
int blpe_pbe(int crystal_val, signed char prdiv_val, signed char vdiv_val);
int blpe_fbe(int crystal_val);
int fbi_blpi(int irc_freq, unsigned char irc_select);
int blpi_fbi(int irc_freq, unsigned char irc_select);
int fei_fee(int crystal_val, unsigned char hgo_val, unsigned char erefs_val);
int fee_fbi(int irc_freq, unsigned char irc_select);
int fbe_blpe(int crystal_val);
int fei_fee_rtc(int rtc_freq);
int fee_fei_rtc(int slow_irc_freq);

int pll_init(int crystal_val, unsigned char hgo_val, unsigned char erefs_val, signed char prdiv_val, signed char vdiv_val, unsigned char mcgout_select);

int fll_freq(int fll_ref);
unsigned char what_mcg_mode(void);
unsigned char atc(unsigned char irc_select, int irc_freq, int mcg_out_freq);
void clk_monitor_0(unsigned char en_dis);


#endif /* SOURCES_MCG_H_ */
