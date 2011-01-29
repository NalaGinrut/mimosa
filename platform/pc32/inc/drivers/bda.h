#ifndef	__MIMOSA_BDA_H
#define __MIMOSA_BDA_H
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


/* BIOS Data Area 
 * This file doesn't contain EBDA cause it's not standardize!
 */

/*
Offset	Size	Description
 00h	WORD	Base I/O address of 1st serial I/O port, zero if none
 02h	WORD	Base I/O address of 2nd serial I/O port, zero if none
 04h	WORD	Base I/O address of 3rd serial I/O port, zero if none
 06h	WORD	Base I/O address of 4th serial I/O port, zero if none
		    Note: Above fields filled in turn by POST as it finds serial
		    ports. POST never leaves gaps. DOS and BIOS serial device
		    numbers may be redefined by re-assigning these fields.
 08h	WORD	Base I/O address of 1st parallel I/O port, zero if none
 0Ah	WORD	Base I/O address of 2nd parallel I/O port, zero if none
 0Ch	WORD	Base I/O address of 3rd parallel I/O port, zero if none
 0Eh	WORD	[non-PS] Base I/O address of 4th parallel I/O port, zero if none
		[PS] Segment of Extended BIOS Data Segment
		    Note: Above fields filled in turn by POST as it finds
		    parallel ports. POST never leaves gaps. DOS and BIOS
		    parallel device numbers may de redefined by re-assigning
		    these fields.
 10h	WORD	Installed hardware:
		    bits 15-14: number of parallel devices
		    bit     13: [Conv] Internal modem
		    bit     12: reserved
		    bits 11- 9: number of serial devices
		    bit      8: reserved
		    bits  7- 6: number of diskette drives minus one
		    bits  5- 4: Initial video mode:
				    00b = EGA,VGA,PGA
				    01b = 40 x 25 color
				    10b = 80 x 25 color
				    11b = 80 x 25 mono
		    bit      3: reserved
		    bit      2: [PS] =1 if pointing device
				[non-PS] reserved
		    bit      1: =1 if math co-processor
		    bit      0: =1 if diskette available for boot
 12h	BYTE	[Conv] POST status
		[AT] {Manufacturing test initialisation flags}
 13h	WORD	Base memory size in kbytes (0-640)
 15h	BYTE	[AT] {Manufacturing test scratch pad}
 16h	BYTE	[AT] {Manufacturing test scratch pad}
		[PS/2 Mod 30] BIOS control flags
 17h	BYTE	Keyboard status flags 1:
		    bit 7 =1 INSert active
		    bit 6 =1 Caps Lock active
		    bit 5 =1 Num Lock active
		    bit 4 =1 Scroll Lock active
		    bit 3 =1 either Alt pressed
		    bit 2 =1 either Ctrl pressed
		    bit 1 =1 Left Shift pressed
		    bit 0 =1 Right Shift pressed
 18h	BYTE	Keyboard status flags 2:
		    bit 7 =1 INSert pressed
		    bit 6 =1 Caps Lock pressed
		    bit 5 =1 Num Lock pressed
		    bit 4 =1 Scroll Lock pressed
		    bit 3 =1 Pause state active
		    bit 2 =1 Sys Req pressed
		    bit 1 =1 Left Alt pressed
		    bit 0 =1 Left Ctrl pressed
 19h	BYTE	Keyboard: Alt-nnn keypad workspace
 1Ah	WORD	Keyboard: ptr to next character in keyboard buffer
 1Ch	WORD	Keyboard: ptr to first free slot in keyboard buffer
 1Eh 16 WORDs	Keyboard circular buffer (but see 80h, 82h for override)
 3Eh	BYTE	Diskette recalibrate status:
		    bit 7 =1 Diskette hardware interrupt occurred
		    bits 6-4 reserved
		    bit 3 =1 Recalibrate diskette 3
		    bit 2 =1 Recalibrate diskette 2
		    bit 1 =1 Recalibrate diskette 1
		    bit 0 =1 Recalibrate diskette 0
 3Fh	BYTE	Diskette motor status:
		    bit 7 =1 current operation is write or format
			  =0 current operation is read or verify
		    bit 6    reserved
		    bits 5-4 diskette drive number selected (0-3)
		    bit 3 =1 diskette 3 motor on
		    bit 2 =1 diskette 2 motor on
		    bit 1 =1 diskette 1 motor on
		    bit 0 =1 diskette 0 motor on
 40h	BYTE	Diskette motor turn-off time-out count
 41h	BYTE	Diskette last operation status (0 = OK)
		    bit 7 =1 drive not ready
		    bit 6 =1 seek error
		    bit 5 =1 general controller failure
		    bits 4-0:
			    00h no error
			    01h invalid request
			    02h address mark not found
			    03h write-protect error
			    04h sector not found
			    06h diskette change line active
			    08h DMA overrun
			    09h DMA across 64k boundary
			    0Ch media type unknown
			    10h CRC error on read
 42h  7 BYTEs	Diskette/Fixed disk status/command bytes
 49h	BYTE	Video current mode
 4Ah	WORD	Video columns on screen
 4Ch	WORD	Video page (regen buffer) size in bytes
 4Eh	WORD	Video current page start address in regen buffer
 50h 16 BYTEs	Video cursor position (col, row) for eight pages, 0 based
 60h	WORD	Video cursor type, 6845 compatible, hi=startline, lo=endline
 62h	BYTE	Video current page number
 63h	WORD	Video CRT controller base address: color=03D4h, mono=03B4h
 65h	BYTE	Video current setting of mode select register 03D8h/03B8h
 66h	BYTE	Video current setting of CGA palette register 03D9h
 67h	DWORD	POST real mode re-entry point after certain resets
 6Bh	BYTE	POST last unexpected interrupt
 6Ch	DWORD	Timer ticks since midnight
 70h	BYTE	Timer overflow, non-zero if has counted past midnight
 71h	BYTE	Ctrl-Break flag: bit 7=1
 72h	WORD	POST reset flag:
		    = 1234h if to bypass memory test (warm boot)
		    = 4321h [PS/2 MCA only] if to preserve memory
		    = 5678h [Conv] system suspended
		    = 9ABCh [Conv] manufacturing test mode
		    = ABCDh [Conv] POST loop mode
		    =	64h Burn-in mode
 74h	BYTE	Fixed disk last operation status: {except ESDI drives}
		    00h no error
		    01h invalid function request
		    02h address mark not found
		    03h write protect error
		    04h sector not found
		    05h reset failed
		    07h drive parameter activity failed
		    08h DMA overrun
		    09h DMA data boundary error
		    0Ah bad sector flag detected
		    0Bh bad track detected
		    0Dh invalid number of sectors for Format
		    0Eh control data address mark detected
		    0Fh DMA arbitration level out of range
		    10h uncorrectable ECC or CRC error
		    11h ECC corrected data error
		    20h general controller failed
		    40h seek failed
		    80h time out
		    AAh drive not ready
		    BBh undefined error
		    CCh write fault on selected drive
		    E0h status error/error register is zero
		    FFh sense failed
 75h	BYTE	Fixed disk: number of fixed disk drives
 76h	BYTE	Fixed disk: control byte    {IBM document only for XT}
 77h	BYTE	Fixed disk: I/O port offset {IBM document only for XT}
 78h  3 BYTEs	Parallel devices 1-3 time-out counters
 7Bh	BYTE	parallel device 4 time-out counter [non-PS]
		bit 5 set if Virtual DMA Spec supported [PS] (see INT 4B)
 7Ch  4 BYTEs	Serial devices 1-4 time-out counters
 80h	WORD	Keyboard buffer start as offset from segment 40h (normally 1Eh)
 82h	WORD	Keyboard buffer end+1 as offset from segment 40h (normally 3Eh)
		[XT BIOS dated 11/08/82 ends here]
 84h	BYTE	Video EGA/MCGA/VGA rows on screen minus one
 85h	WORD	Video EGA/MCGA/VGA character height in scan-lines
 87h	BYTE	Video EGA/VGA control: [MCGA: =00h]
		    bit 7:  =1 if not to clear RAM (see INT 10h, AH=00h)
		    bits 6-5: RAM on adapter = (this field + 1) * 64K
		    bit 4:  reserved
		    bit 3:  =0 if EGA/VGA video system active, =1 if inactive
		    bit 2:  =1 if to wait for display enable (what means this?)
		    bit 1:  =0 for color or ECD monitor, =1 for mono monitor
		    bit 0:  =0 alphanumeric cursor emulation enabled, =1 not.
			    When enabled, text mode cursor size (INT 10,AH=01h)
			    settings looking like CGA ones are translated to
			    equivalent EGA/VGA ones.
 88h	BYTE	Video EGA/VGA switches: [MCGA: reserved]
		    bits 7-4: power-on state of feature connector bits 3-0
		    bits 3-0: configuration switches 4-1 (=0 on, =1 off)
		      Values as read:
			0h Pri MDA,	    Sec EGA+old color display 40 x 25
			1h Pri MDA,	    Sec EGA+old color display 80 x 25
			2h Pri MDA,	    Sec EGA+ECD normal mode (CGA emul)
			3h Pri MDA,	    Sec EGA+ECD enhanced mode
			4h Pri CGA 40 x 25, Sec EGA mono display
			5h Pri CGA 80 x 25, Sec EGA mono display
			6h Pri EGA+old color display 40 x 25,  Sec MDA
			7h Pri EGA+old color display 80 x 25,  Sec MDA
			8h Pri EGA+ECD normal mode (CGA emul), Sec MDA
			9h Pri EGA+ECD enhanced mode,	       Sec MDA
			Ah Pri EGA mono display,	       Sec CGA 40 x 25
			Bh Pri EGA mono display,	       Sec CGA 80 x 25
		    When bit4 of 40h:89h is 0, VGA emulates 350-line EGA if
		    this byte is x3h or x9h, otherwise emulates 200-line CGA in
		    400-line double scan. VGA resets this byte to x9h after the
		    mode set.
 89h	BYTE	Video MCGA/VGA mode-set option control:
		    bits 7 and 4:
			0 0  350-line mode requested
			0 1  400-line mode at next mode set
			1 0  200-line mode requested
			1 1  reserved
			Apparently VGA BIOS mode set disregards bit 7 and uses
			byte 40h:88h to determine 200/350 selection when bit 4
			is zero. Presumably bit 7 is a convenience for other
			purposes. Bit 7 is reset to zero after the mode set.
		    bit 6:  =1 if display switching enabled, =0 if disabled
		    bit 5:  reserved
		    bit 4:  [VGA]  =1 if to use 400-line mode at next mode set
				   =0 if to emulate EGA at next mode set
				      This bit set to 1 after the mode set.
			    [MCGA] =1 use 400-line mode at next mode set
				   =0 emulate CGA, digital monitor, 200 lines,
					  8 x 8 text font at next mode set
				      Bit unchanged by mode set.
		    bit 3:  =0 if default palette loading enabled at mode set
		    bit 2:  =1 if mono display, =0 if color display
		    bit 1:  =1 if gray scale summing enabled, =0 if disabled
		    bit 0:  [VGA] =1 if VGA active, =0 if not
			    [MCGA] reserved, zero
 8Ah	BYTE	Video [MCGA/VGA]: index into Display Combination Code table
 8Bh	BYTE	Diskette media control [not XT]:
		    bits 7-6: Last data rate set by controller:
			      00=500kbps, 01=300kbps, 10=250kbps, 11=reserved
		    bits 5-4: Last diskette drive step rate selected
		    bits 3-2: {Data rate at start of operation}
		    bits 1-0: reserved
 8Ch	BYTE	Fixed disk controller status [not XT]
 8Dh	BYTE	Fixed disk controller Error Status [not XT]
 8Eh	BYTE	Fixed disk Interrupt Control [not XT]
 8Fh	BYTE	Diskette controller information [not XT]:
		    bit 7:  reserved
		    bit 6:  =1 drive 1 determined
		    bit 5:  =1 drive 1 is multi-rate, valid if drive determined
		    bit 4:  =1 drive 1 supports 80 tracks, always valid
		    bit 3:  reserved
		    bit 2:  =1 drive 0 determined
		    bit 1:  =1 drive 0 is multi-rate, valid if drive determined
		    bit 0:  =1 drive 0 supports 80 tracks, always valid
 90h	BYTE	Diskette drive 0 media state
 91h	BYTE	Diskette drive 1 media state
		    bits 7-6: Data rate: 00=500kbps, 01=300kbps, 10=250kbps
		    bit    5: =1 if double stepping reqd (e.g. 360kB in 1.2MB)
		    bit    4: =1 if media established
		    bit    3: reserved
		    bits 2-0: on exit from BIOS, contain:
			    000 trying 360kB in 360kB
			    001 trying 360kB in 1.2MB
			    010 trying 1.2MB in 1.2MB
			    011 360kB in 360kB established
			    100 360kB in 1.2MB established
			    101 1.2MB in 1.2MB established
			    110 reserved
			    111 all other formats/drives
 92h	BYTE	Diskette drive 0 media state at start of operation
 93h	BYTE	Diskette drive 1 media state at start of operation
 94h	BYTE	Diskette drive 0 current track number
 95h	BYTE	Diskette drive 1 current track number
 96h	BYTE	Keyboard status byte 3
		    bit 7 =1 read-ID in progress
		    bit 6 =1 last code read was first of two ID codes
		    bit 5 =1 force Num Lock if read-ID and enhanced keyboard
		    bit 4 =1 enhanced keyboard installed
		    bit 3 =1 Right Alt pressed
		    bit 2 =1 Right Ctrl pressed
		    bit 1 =1 last code read was E0h
		    bit 1 =1 last code read was E1h
 97h	BYTE	Keyboard status byte 2
		    bit 7 =1 keyboard transmit error flag
		    bit 6 =1 LED update in progress
		    bit 5 =1 RESEND received from keyboard
		    bit 4 =1 ACK received from keyboard
		    bit 3 reserved, must be zero
		    bit 2 Caps Lock LED
		    bit 1 Num Lock LED
		    bit 0 Scroll Lock LED
 98h	DWORD	Timer2: [AT, PS exc Mod 30] ptr to user wait-complete flag
					    (see INT 15, AX=8300h)
 9Ch	DWORD	Timer2: [AT, PS exc Mod 30] user wait count in microseconds
 A0h	BYTE	Timer2: [AT, PS exc Mod 30] Wait active flag:
		    bit 7 =1 wait time elapsed
		    bits 6-1 reserved
		    bit 0 =1 INT 15h, AH=86h has occurred
 A1h  7 BYTEs	reserved for network adapters (oh really?)
 A4h	DWORD	[PS/2 Mod 30] Saved Fixed Disk Interrupt Vector
 A8h	DWORD	Video: EGA/MCGA/VGA ptr to Video Save Pointer Table (see below)
 ACh-AFh	reserved
 B0h	DWORD	ptr to 3363 Optical disk driver or BIOS entry point.
		    When 3363 BIOS present, the signature "OPTIC ",00h occurs 3
		    bytes beyond this entry point.
		    When 3363 BIOS and 3363 File System Driver present, the
		    signature "FILE SYSTEM DRIVER",00h occurs 3 bytes beyond
		    this entry point.
 B4h	WORD	reserved
 B6h  3 BYTEs	reserved for POST?
 B9h  7 BYTEs	???
 C0h 14 BYTEs	reserved
 CEh	WORD	count of days since last boot?
 D0h-EFh	reserved
 F0h-FFh	reserved for user
100h	BYTE	Print Screen Status byte
 
Format of Extended BIOS Data Area (see 40:0Eh for ptr) [PS only]
Offset	Size	Description
 00h	BYTE	Length of EBDA in kilobytes
 01h 15 BYTEs	reserved
 17h	BYTE	Number of entries in POST error log (0-5)
 18h  5 WORDs	POST error log (each word is a POST error number)
 19h-21h	reserved
 22h	DWORD	Pointing Device Driver entry point
 26h	BYTE	Pointing Device Flags 1
		   bit 7:    =1 command in progress
		   bit 6:    =1 resend
		   bit 5:    =1 acknowledge
		   bit 4:    =1 error
		   bit 3:    =0 reserved
		   bits 2-0: index count
 27h	BYTE	Pointing Device Flags 2
		   bit 7:    =1 device driver far call flag
		   bits 6-3: reserved
		   bits 2-0: package size
 28h  7 BYTEs	Pointing Device Auxiliary Device Data
 2Fh	BYTE	reserved
 30h	DWORD	Vector for INT 07h stored here during 80387 interrupt
 34h	DWORD	Vector for INT 01h stored here during INT 07h emulation
 38h	BYTE	Scratchpad for 80287/80387 interrupt code
 39h	WORD	Timer3: Watchdog timer initial count
 3Bh	BYTE	??? seen non-zero on Model 30
 3Ch	BYTE	???
 3Dh 16 BYTEs	Fixed Disk parameter table for drive 0 (oh really?)
 4Dh 16 BYTEs	Fixed Disk parameter table for drive 1 (oh really?)
		    Neither of above seen on any Model 30, 50, 60 yet.
 5Dh-6Bh	???
 6Ch	BYTE	Fixed disk: (=FFh on ESDI systems)
		    bits 7-4: Channel number 00-0Fh
		    bits 3-0: DMA arbitration level 00-0Eh
 6Dh and up:	??? seen non-zero on Model 60
3F0h	BYTE	Fixed disk buffer (???!!!)
 
Format of Video Save Pointer Table [EGA/VGA/MCGA only]:
Offset	Size	Description
 00h	DWORD	ptr to Video Parameter Table
 04h	DWORD	ptr to Parameter Dynamic Save Area, else 0 [EGA/VGA only]
 08h	DWORD	ptr to Alphanumeric Character Set Override, else 0
 0Ch	DWORD	ptr to Graphics Character Set Override, else 0
 10h	DWORD	[VGA only] ptr to Secondary Save Pointer Table, must be valid
 14h	DWORD	reserved, zero
 18h	DWORD	reserved, zero
Note: table initially in ROM, copy to RAM to alter, then update 40h:A8h.
 
Format of Secondary Video Save Pointer Table [VGA only]:
Offset	Size	Description
 00h	WORD	Length of this table in bytes, including this word (1Ah)
 02h	DWORD	ptr to Display Combination Code Table, must be valid
 06h	DWORD	ptr to second Alphanumeric Character Set Override, else 0
 0Ah	DWORD	ptr to User Palette Profile Table, else 0
 0Eh	DWORD	reserved, zero
 12h	DWORD	reserved, zero
 16h	DWORD	reserved, zero
Note: table initially in ROM, copy to RAM to alter, then alter Save Ptr Table.
 
Format of Video Parameter Table [EGA, VGA only]:
An array of 23 [EGA] or 29 [VGA] elements, each element being 64 bytes long.
Elements appear in the order:
 00h-03h	Modes 00h-03h in 200-line CGA emulation mode
 04h-0Eh	Modes 04h-0Eh
 0Fh-10h	Modes 0Fh-10h when only 64kB RAM on adapter
 11h-12h	Modes 0Fh-10h when >64kB RAM on adapter
 13h-16h	Modes 00h-03h in 350-line mode
 17h		VGA Modes 00h or 01h in 400-line mode
 18h		VGA Modes 02h or 03h in 400-line mode
 19h		VGA Mode  07h in 400-line mode
 1Ah-1Ch	VGA Modes 11h-13h
 
Format of Video Parameter Table element [EGA, VGA only]:
Offset	Size	Description
 00h	BYTE	Columns on screen		  (see 40h:4Ah)
 01h	BYTE	Rows on screen minus one	  (see 40h:84h)
 02h	BYTE	Height of character in scan lines (see 40h:85h)
 03h	WORD	Size of video buffer		  (see 40h:4Ch)
 05h  4 BYTEs	Values for Sequencer Registers 1-4
 09h	BYTE	Value for Miscellaneous Output Register
 0Ah 25 BYTEs	Values for CRTC Registers 00h-18h
 23h 20 BYTEs	Values for Attribute Controller Registers 00h-13h
 37h  9 BYTEs	Values for Graphics Controller Registers 00h-08h
 
Format of Video Parameter Table [MCGA only] {guesswork from inspection}:
    - 16 triplet BYTEs of R,G,B DAC info for 16 colors;
    - An array of 11 elements, each element being 32 bytes long.
	  Elements appear in the order:
		Modes 00h,01h in 200-line mode for digital displays
		Modes 00h,01h in 400-line mode for analog displays
		Modes 02h,03h in 200-line mode for digital displays
		Modes 02h,03h in 400-line mode for analog displays
		Modes 04h,05h in 200-line mode for digital displays
		Modes 04h,05h in 400-line mode for analog displays
		Mode  06h in 200-line mode for digital displays
		Mode  06h in 400-line mode for analog displays
		Mode  11h
		Mode  13h in 200-line mode for digital displays
		Mode  13h in 400-line mode for analog displays
 
Format of Video Parameter Table element [MCGA only]:
Offset	Size	Description
 00h	BYTE	Columns on screen		  (see 40h:4Ah)
 01h	BYTE	Rows on screen minus one	  (see 40h:84h)
 02h	BYTE	Height of character in scan lines (see 40h:85h)
 03h	WORD	Size of video buffer		  (see 40h:4Ch)
 05h	WORD	??? always zero
 07h 21 BYTEs	Video data registers 00h-14h to port 3D5h indexed by 3D4h
 1Ch	BYTE	PEL Mask to port 3C6h
 1Dh	BYTE	CGA Mode Control to port 3D8h
 1Eh	BYTE	CGA Border Control to port 3D9h
 1Fh	BYTE	Extended Mode Control to port 3DDh
 
Format of Video Parameter Dynamic Save Area [EGA, VGA only]:
Offset	Size	Description
 00h 16 BYTEs	Last data written to Attribute Controller Palette Registers 0-15
 10h	BYTE	Last data written to Attribute Controller Overscan Register
 11h-FFh	Reserved
		Note: Need for table was that EGA registers were write-only.
		Note: If default values (from the Video Parameter Table) are
		      over-ridden at a mode set by the VGA User Palette Profile
		      Table, then the Dynamic Save Area is updated with the
		      default values, not the User Profile ones.
 
Format of Alphanumeric Character Set Override:
Offset	Size	Description
 00h	BYTE	Length in bytes of each character in font table
 01h	BYTE	Character generator RAM bank to load, 0=normal
 02h	WORD	Number of characters in font table, normally 256
 04h	WORD	Code of first character in font table, normally 0
 06h	DWORD	ptr to font table
 0Ah	BYTE	Displayable rows (FFh=use maximum calculated value)
 0Bh	BYTEs	Array of mode values to which this font is to pertain
	BYTE	FFh end of array
 
Format of Second Alphanumeric Character Set Override:
Authorities differ, some say same as first override above, but IBM say:
Offset	Size	Description
 00h	BYTE	Length in bytes of each character in font table
 01h	BYTE	Character generator RAM bank to load, normally non-zero
 02h	BYTE	reserved
 03h	DWORD	ptr to font table
 07h	BYTEs	Array of mode values to which this font is to pertain
	BYTE	FFh end of array
 
Format of Graphics Character Set Override:
Offset	Size	Description
 00h	BYTE	Number of displayable character rows
 01h	WORD	Length in bytes of each character in font table
 03h	DWORD	ptr to font table
 07h	BYTEs	Array of mode values to which this font is to pertain
	BYTE	FFh end of array
 
Format of Display Combination Code Table [VGA only]:
Offset	Size	Description
 00h	BYTE	Number of entries in the DCC table at offset 04h
 01h	BYTE	Version number
 02h	BYTE	Maximum display type code that can appear in DCC table
 03h	BYTE	reserved
 04h	ARRAY OF 2 BYTEs Each pair of bytes gives a valid display combination
		    Meaning of each byte:
			00h	no display
			01h	MDA with mono display
			02h	CGA with color display
			03h	reserved
			04h	EGA with color display
			05h	EGA with mono display
			06h	Professional Graphics Controller
			07h	VGA with mono display
			08h	VGA with color display
			09h	reserved
			0Ah	MCGA with digital color display
			0Bh	MCGA with analog mono display
			0Ch	MCGA with analog color display
			FFh	unrecognised video system
 
Format of User Palette Profile Table [VGA only]:
Offset	Size	Description
 00h	BYTE	Underlining: 01h=enable in all alphanumeric modes
			     00h=enable in monochrome alphanumeric modes only
			     FFh=disable in all alphanumeric modes
 01h	BYTE	reserved
 02h	WORD	reserved
 04h	WORD	Number (0-17) of Attribute Controller registers in table
 06h	WORD	Index (0-16) of first Attribute Controller register in table
 08h	DWORD	ptr to table of Attribute Controller registers to override
			Table is an array of BYTEs.
 0Ch	WORD	Number (0-256) of video DAC Color registers in table
 0Eh	WORD	Index (0-255) of first video DAC Color register in table
 10h	DWORD	ptr to table of video DAC Color registers to override
			Table is ??? triplets ??? of BYTEs???
 14h	BYTEs	array of mode values to which this profile is to pertain
	BYTE	FFh end of array
*/

#define	BDA_COM1		0x400 // IO port for COM1 serial (word)
#define BDA_COM2		0x402
#define BDA_COM3		0x404
#define BDA_COM4		0x406
#define BDA_SDEV_14TO		0x47C // Serial devices 1-4 time-out counters

#define	BDA_LPT1		0x408 // IO port for LPT1 parallel (word)
#define BDA_LPT2		0x40A
#define BDA_LPT3		0x40C
#define BDA_LPT4		0x40E 
#define BDA_PDEV_13TO		0x478 // Parallel devices 1-3 time-out counters
#define BDA_PDEV_4TO 		0x47B // Parallel device 4 time-out counter
 
#define BDA_AVAIL_HW		0x410 // packed bit flags for detected hardware
#define BDA_POST_STAT		0x412
#define BDA_MEM_SIZE		0x413 // Base memory size in kbytes (0~640)

#define BDA_KBD_STAT1		0x417 // Keyboard status flags 1
#define BDA_KBD_STAT2		0x418 // Keyboard status flags 2
#define BDA_KBD_ALT		0x419 // Keyboard Alt-nnn keypad workspace
#define BDA_CTRL_BREAK		0x471 // Ctrl-Break flag: bit 7=1
#define BDA_PRTSCR_STAT		0x500 // Print Screen Status byte
#define BDA_KBD_BUF_NEXT	0x41A // Keyboard ptr to next character in keyboard buffer
#define BDA_KBD_BUF_FREE	0x41C // Keyboard ptr to first free slot in keyboard buffer
#define BDA_CIRC_BUF		0x41E // Keyboard circular buffer
#define BDA_KBD_STAT3		0x496 // Keyboard status byte 3
#define BDA_KBD_STAT4		0x497 // Keyboard status byte 2
#define BDA_KBD_BUFS		0x480 // Keyboard buffer start as offset from segment 40h (normally 1Eh)
#define BDA_KBD_BUFE		0x482 // Keyboard buffer end+1 as offset from segment 40h (normally 3Eh)

/* 0x43E~0x442 used by diskette device ,we don't need it now!
 */
#define BDA_VIDEO_MODE		0x449 // Video current mode
#define BDA_VIDEO_COL		0x44A // Video columns on screen
#define BDA_VIDEO_PGSIZE	0x44C // Video page (regen buffer) size in bytes
#define BDA_VIDEO_PGADDR	0x44E // Video current page start address in regen buffer
#define BDA_VIDEO_CURPOS	0x450 // Video cursor position (col ,row) for eight pages, 0 based
#define BDA_VIDEO_CURTYPE	0x460 // Video cursor type ,6845 compatible ,hi=startline ,lo=endline
#define BDA_VIDEO_PGNUM		0x462 // Video current page number
#define BDA_VIDEO_CRT		0x463 // Video CRT controller base address: color=03D4h ,mono=03B4h
#define BDA_VIDEO_MODESET	0x465 // Video current setting of mode select register 03D8h/03B8h
#define BDA_VIDEO_CGASET	0x466 // Video current setting of CGA palette register 03D9h
#define BDA_VIDEO_ROWS		0x484 // Video EGA/MCGA/VGA rows on screen minus one
#define BDA_CHAR_HEIGHT		0x485 // Video EGA/MCGA/VGA character height in scan-lines
#define BDA_VIDEO_CTRL		0x487 // Video EGA/VGA control: [MCGA: =00h]
#define BDA_VIDEO_SWITCH	0x488 // Video EGA/VGA switches: [MCGA: reserved]
#define BDA_MV_MODESET		0x489 // Video MCGA/VGA mode-set option control
#define BDA_MV_IDX		0x48A // Video [MCGA/VGA]: index into Display Combination Code table
#define BDA_VIDEO_PTAB_SAVED	0x4A8 // Video: EGA/MCGA/VGA ptr to Video Save Pointer Table

#define BDA_RMODE_ENTRY		0x467 // POST real mode re-entry point after certain resets
#define BDA_LAST_INTR		0x46B // POST last unexpected interrupt

#define BDA_TICKS		0x46C // IRQ0 timer ticks since boot
#define BDA_TIMER_OVERFLOW	0x470 // Timer overflow ,non-zero if has counted past midnight

#define BDA_TIMER2_WAIT		0x498 // Timer2: [AT ,PS exc Mod 30] ptr to user wait-complete flag
#define BDA_TIMER2_CNT		0x49C // Timer2: [AT ,PS exc Mod 30] user wait count in microseconds
#define BDA_TIMER2_AWAIT	0x4A0 // Timer2: [AT ,PS exc Mod 30] Wait active flag
#define BDA_DAYS		0x4CE // Count of days since last boot?

#define BDA_HD_LOSTAT		0x474 // Fixed disk last operation status: {except ESDI drives}
#define BDA_HD_NUM		0x475 // Hard disk drives detected
#define BDA_HD_CTRL		0x476 // Fixed disk: control byte
#define BDA_HD_IO		0x477 // Fixed disk: I/O port offset
#define BDA_HD_STAT		0x48C // Fixed disk controller status [not XT]
#define BDA_HD_ERRSTAT		0x48D // Fixed disk controller Error status [not XT]
#define BDA_HD_INTRCTRL		0x48E // Fixed disk Interrupt Control [not XT]
// 0x48F~0x495 ued for diskette, we don't need them

#define BDA_HD_INTV_SAVED	0x4A4 // [PS/2 Mod 30] Saved Fixed Disk Interrupt Vector

#define BDA_3363		0x4B0 // ptr to 3363 Optical disk driver or BIOS entry point (I dont't know how to use...)
				
#define BDA_POST_RESET		0x472 // POST reset flag
#define POST_WORM_BOOT		0x1234
#define POST_PS2		0x4312
#define POST_SYS_SUS		0x5678
#define POST_TEST		0x9ABC
#define POST_LOOP		0xABCD
#define POST_BURN		0x64






#endif // End of __MIMOSA_BDA_H;
