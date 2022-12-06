
/* Copyright (C) 2003  Advanced Micro Devices Inc. */
#include <stdio.h>
#include "internal.h"

typedef enum {
	/* VAL2 */
	RDMD0			= _BITUL(16),
	/* VAL1 */
	TDMD3			= _BITUL(11),
	TDMD2			= _BITUL(10),
	TDMD1			= _BITUL(9),
	TDMD0			= _BITUL(8),
	/* VAL0 */
	UINTCMD			= _BITUL(6),
	RX_FAST_SPND		= _BITUL(5),
	TX_FAST_SPND		= _BITUL(4),
	RX_SPND			= _BITUL(3),
	TX_SPND			= _BITUL(2),
	INTREN			= _BITUL(1),
	RUN			= _BITUL(0),

	CMD0_CLEAR 		= 0x000F0F7F,   /* Command style register */

}CMD0_BITS;
typedef enum {

	/* VAL3 */
	CONDUIT_MODE		= _BITUL(29),
	/* VAL2 */
	RPA			= _BITUL(19),
	DRCVPA			= _BITUL(18),
	DRCVBC			= _BITUL(17),
	PROM			= _BITUL(16),
	/* VAL1 */
	ASTRP_RCV		= _BITUL(13),
	RCV_DROP0		= _BITUL(12),
	EMBA			= _BITUL(11),
	DXMT2PD			= _BITUL(10),
	LTINTEN			= _BITUL(9),
	DXMTFCS			= _BITUL(8),
	/* VAL0 */
	APAD_XMT		= _BITUL(6),
	DRTY			= _BITUL(5),
	INLOOP			= _BITUL(4),
	EXLOOP			= _BITUL(3),
	REX_RTRY		= _BITUL(2),
	REX_UFLO		= _BITUL(1),
	REX_LCOL		= _BITUL(0),

	CMD2_CLEAR 		= 0x3F7F3F7F,   /* Command style register */

}CMD2_BITS;
typedef enum {

	/* VAL3 */
	ASF_INIT_DONE_ALIAS	= _BITUL(29),
	/* VAL2 */
	JUMBO			= _BITUL(21),
	VSIZE			= _BITUL(20),
	VLONLY			= _BITUL(19),
	VL_TAG_DEL		= _BITUL(18),
	/* VAL1 */
	EN_PMGR			= _BITUL(14),
	INTLEVEL		= _BITUL(13),
	FORCE_FULL_DUPLEX	= _BITUL(12),
	FORCE_LINK_STATUS	= _BITUL(11),
	APEP			= _BITUL(10),
	MPPLBA			= _BITUL(9),
	/* VAL0 */
	RESET_PHY_PULSE		= _BITUL(2),
	RESET_PHY		= _BITUL(1),
	PHY_RST_POL		= _BITUL(0),

}CMD3_BITS;
typedef enum {

	INTR			= _BITUL(31),
	PCSINT			= _BITUL(28),
	LCINT			= _BITUL(27),
	APINT5			= _BITUL(26),
	APINT4			= _BITUL(25),
	APINT3			= _BITUL(24),
	TINT_SUM		= _BITUL(23),
	APINT2			= _BITUL(22),
	APINT1			= _BITUL(21),
	APINT0			= _BITUL(20),
	MIIPDTINT		= _BITUL(19),
	MCCINT			= _BITUL(17),
	MREINT			= _BITUL(16),
	RINT_SUM		= _BITUL(15),
	SPNDINT			= _BITUL(14),
	MPINT			= _BITUL(13),
	SINT			= _BITUL(12),
	TINT3			= _BITUL(11),
	TINT2			= _BITUL(10),
	TINT1			= _BITUL(9),
	TINT0			= _BITUL(8),
	UINT			= _BITUL(7),
	STINT			= _BITUL(4),
	RINT0			= _BITUL(0),

}INT0_BITS;
typedef enum {

	/* VAL3 */
	LCINTEN			= _BITUL(27),
	APINT5EN		= _BITUL(26),
	APINT4EN		= _BITUL(25),
	APINT3EN		= _BITUL(24),
	/* VAL2 */
	APINT2EN		= _BITUL(22),
	APINT1EN		= _BITUL(21),
	APINT0EN		= _BITUL(20),
	MIIPDTINTEN		= _BITUL(19),
	MCCIINTEN		= _BITUL(18),
	MCCINTEN		= _BITUL(17),
	MREINTEN		= _BITUL(16),
	/* VAL1 */
	SPNDINTEN		= _BITUL(14),
	MPINTEN			= _BITUL(13),
	TINTEN3			= _BITUL(11),
	SINTEN			= _BITUL(12),
	TINTEN2			= _BITUL(10),
	TINTEN1			= _BITUL(9),
	TINTEN0			= _BITUL(8),
	/* VAL0 */
	STINTEN			= _BITUL(4),
	RINTEN0			= _BITUL(0),

	INTEN0_CLEAR 		= 0x1F7F7F1F, /* Command style register */

}INTEN0_BITS;

typedef enum {

	PMAT_DET		= _BITUL(12),
	MP_DET		        = _BITUL(11),
	LC_DET			= _BITUL(10),
	SPEED_MASK		= _BITUL(9) | _BITUL(8) | _BITUL(7),
	FULL_DPLX		= _BITUL(6),
	LINK_STATS		= _BITUL(5),
	AUTONEG_COMPLETE	= _BITUL(4),
	MIIPD			= _BITUL(3),
	RX_SUSPENDED		= _BITUL(2),
	TX_SUSPENDED		= _BITUL(1),
	RUNNING			= _BITUL(0),

}STAT0_BITS;

#define PHY_SPEED_10		0x2
#define PHY_SPEED_100		0x3


int amd8111e_dump_regs(struct ethtool_drvinfo *info __maybe_unused,
		       struct ethtool_regs *regs)
{

	u32 *reg_buff = (u32 *)regs->data;
	u32 reg;

	fprintf(stdout, "Descriptor Registers\n");
	fprintf(stdout, "---------------------\n");

	/* Transmit descriptor base address register */
	reg = reg_buff[0];
	fprintf(stdout,
		"0x00100: Transmit descriptor base address register %08X\n",reg);

	/* Transmit descriptor length register */
	reg = reg_buff[1];
	fprintf(stdout,
		"0x00140: Transmit descriptor length register 0x%08X\n",reg);

	/* Receive descriptor base address register */
	reg = reg_buff[2];
	fprintf(stdout,
		"0x00120: Receive descriptor base address register %08X\n",reg);

	/* Receive descriptor length register */
	reg = reg_buff[3];
	fprintf(stdout,
		"0x00150: Receive descriptor length register 0x%08X\n",reg);

	fprintf(stdout, "\n");


	fprintf(stdout, "Command Registers\n");
	fprintf(stdout, "-------------------\n");

	/* Command 0 Register */
	reg = reg_buff[4];
	fprintf(stdout,
		"0x00048: Command 0 register  0x%08X\n"
		"	Interrupts:				%s\n"
		"	Device:					%s\n",
		reg,
		reg & INTREN   		? "Enabled"     : "Disabled",
		reg & RUN    		? "Running"     : "Stopped");

	/* Command 2 Register */
	reg = reg_buff[5];
	fprintf(stdout,
		"0x00050: Command 2 register  0x%08X\n"
		"	Promiscuous mode:			%s\n"
		"	Retransmit on underflow:		%s\n",
		reg,
		reg & PROM   		? "Enabled"     : "Disabled",
		reg & REX_UFLO   	? "Enabled"     : "Disabled");
	/* Command 3 Register */
	reg = reg_buff[6];
	fprintf(stdout,
		"0x00054: Command 3 register  0x%08X\n"
		"	Jumbo frame:				%s\n"
		"	Admit only VLAN frame:	 		%s\n"
		"	Delete VLAN tag:			%s\n",
		reg,
		reg & JUMBO  		? "Enabled"     : "Disabled",
		reg &  VLONLY 		? "Yes"     : "No",
		reg &  VL_TAG_DEL 		? "Yes"     : "No");

	/* Command 7 Register */
	reg = reg_buff[7];
	fprintf(stdout,
		"0x00064: Command 7 register  0x%08X\n",
		 reg);

	fprintf(stdout, "\n");
	fprintf(stdout, "Interrupt Registers\n");
	fprintf(stdout, "-------------------\n");

	/* Interrupt 0 Register */
	reg = reg_buff[8];
	fprintf(stdout,
		"0x00038: Interrupt register  0x%08X\n"
		"	Any interrupt is set: 			%s\n"
		"	Link change interrupt:	  		%s\n"
		"	Register 0 auto-poll interrupt:		%s\n"
		"	Transmit interrupt:			%s\n"
		"	Software timer interrupt:		%s\n"
		"	Receive interrupt:			%s\n",
		 reg,
		 reg &   INTR		? "Yes"     : "No",
		 reg &   LCINT		? "Yes"     : "No",
		 reg &   APINT0		? "Yes"     : "No",
		 reg &   TINT0		? "Yes"     : "No",
		 reg &   STINT		? "Yes"     : "No",
		 reg &   RINT0		? "Yes"     : "No"
		 );
	/* Interrupt 0 enable Register */
	reg = reg_buff[9];
	fprintf(stdout,
		"0x00040: Interrupt enable register  0x%08X\n"
		"	Link change interrupt:	  		%s\n"
		"	Register 0 auto-poll interrupt:		%s\n"
		"	Transmit interrupt:			%s\n"
		"	Software timer interrupt:		%s\n"
		"	Receive interrupt:			%s\n",
		 reg,
		 reg &   LCINTEN		? "Enabled"     : "Disabled",
		 reg &   APINT0EN		? "Enabled"     : "Disabled",
		 reg &   TINTEN0		? "Enabled"     : "Disabled",
		 reg &   STINTEN		? "Enabled"     : "Disabled",
		 reg &   RINTEN0		? "Enabled"     : "Disabled"
		);

	fprintf(stdout, "\n");
	fprintf(stdout, "Logical Address Filter Register\n");
	fprintf(stdout, "-------------------\n");

	/* Logical Address Filter Register */
	fprintf(stdout,
		"0x00168: Logical address filter register  0x%08X%08X\n",
		 reg_buff[11],reg_buff[10]);

	fprintf(stdout, "\n");
	fprintf(stdout, "Link status Register\n");
	fprintf(stdout, "-------------------\n");

	/* Status 0  Register */
	reg = reg_buff[12];
	if(reg & LINK_STATS){
	fprintf(stdout,
		"0x00030: Link status register  0x%08X\n"
		"	Link status:	  		%s\n"
		"	Auto negotiation complete	%s\n"
		"	Duplex				%s\n"
		"	Speed				%s\n",
		reg,
		reg &  LINK_STATS 		? "Valid"     : "Invalid",
		reg &  AUTONEG_COMPLETE		? "Yes"	      : "No",
		reg &  FULL_DPLX 		? "Full"      : "Half",
		((reg & SPEED_MASK) >> 7 == PHY_SPEED_10) ? "10Mbits/ Sec":
							"100Mbits/Sec");

	}
	else{
	fprintf(stdout,
		"0x00030: Link status register  0x%08X\n"
		"	Link status:	  		%s\n",
		reg,
		reg &  LINK_STATS 		? "Valid"     : "Invalid");
	}
	return 0;

}
