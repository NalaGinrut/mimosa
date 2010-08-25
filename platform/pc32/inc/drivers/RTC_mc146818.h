#ifndef __RTC_MC146818_H
#define __RTC_MC146818_H
/* Copyleft(c)2010 HackerFellowship. All lefts reserved.
  
 * NalaGinrut <NalaGinrut@gmail.com>
  
 * May Lord Bless!Happy Hacking!
  
 * This program is free software;you can redistribute it and /or modify
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundataion;either version 2 of the License,or (at 
 * your option) any later version.
  
 * You should have read the GNU General Public License before start "RTFSC".
  
 * If not,see <http://www.gnu.org/licenses/>
 */

#include <bsp_types.h>
#include <bsp_bits.h>

#define RTC_PORT	0x70


// RTC time count resters index, all the results are in BCD format;
#define CUR_SEC		(0x00) // current second;
#define ALA_SEC		(0x01) // alarm second;
#define CUR_MIN		(0x02)
#define ALA_MIN		(0x03)
#define CUR_HOU		(0x04)
#define ALA_HOU		(0x05)
#define WEEK_DAY	(0x06) // day of week;
#define MON_DAY		(0x07) // day of month;
#define RTC_MON		(0x08) 
#define RTC_YEAR	(0x09) // year in BCD (00~99);

// RTC status registers;
#define RTC_REGA	(0x0A)
#define RTC_REGB	(0x0B)
#define RTC_REGC	(0x0C)
#define RTC_REGD	(0x0D)

// CMOS data for PC32;// day of month;
#define DIAGS_B		(0x0E) // Diagnostic status BYTE;
#define SHUTS_B		(0x0F) // Shutdown status BYTE;
#define DISKT_B		(0x10) // Diskette drive type for A&B BYTE;
#define AMIE1_B		(0x11) // Reserved or AMI extended CMOS setyp BYTE;
#define FIXDR_B		(0x12) // Fixed disk drive type for drive 0&1 BYTE;
#define AMIE2_B		(0x13) // Reserved or AMI extended CMOS setyp BYTE;
#define EQUIP_B		(0x14) // Equipment BYTE;
#define LMEMS_B		(0x15) // LSB of System base memory in KB;
#define MMEMS_B		(0x16) // MSB of System base memory in KB;
#define LMEME_B		(0x17) // LSB of Total extended memory in KB;
#define MMEME_B		(0x18) // MSB of Total extended memory in KB;
#define DRICE_B		(0x19) // Drive C extended BYTE;
#define DRIDE_B		(0x1A) // Dirve D extended BYTE;
// 1B~27 is reserved;
// 28~2D is platform dependented;
#define MCHKS_B		(0x2E) // CMOS MSB checksum over 10~2D;
#define LCHKS_B		(0x2F) // CMOS LSB checksum over 10~2D;
#define LEMA1_B		(0x30) // LSB of extended memory found above 1MB at POST;
#define HEMA1_B		(0x31) // MSB of extended memory found above 1MB at POST;
#define DATEC_B		(0X32) // Date century in BCD;
#define INFOF_B		(0x33) // Infomation flags;
// 34~3F is reserved;


/* The rest is depend on specific PC32 platform. We won't list them here for other porting works someday.
 */


#endif // End of __RTC_MC146818_H;
