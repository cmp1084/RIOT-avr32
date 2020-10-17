/*****************************************************************************

*****************************************************************************/

#include <avr32/io.h>
	.global _rstart
	.global _rstext
	.equ MCCTRL_1,0x04
	.equ MCCTRL_2,0x05
	.equ OSCCTRL0,0x107
	.equ ROSAHCS1,0x616e
	.equ ROSAHCS2,0x6d6a
	.section  .reset, "ax", @progbits

	.type _rstart, @function
_rstart:
	lda.w pc,_rstext

	.section  .text._rstext, "ax", @progbits
	.type _rstext, @function
_rstext:

	//Set initial stack pointer.
	lda.w sp,_estack
	lda.w r0,_eappstack
	st.w --sp,r0
	ldmts sp,sp
	ld.w r0,sp++

	//Set EVBA, exception processing in application mode
	// lda.w r0,_evba
	mtsr AVR32_EVBA,r0
	csrf 0x15
	csrf 0x16
	ld.w r11,r12[AVR32_PM_RCAUSE]
	cp.w r11,0x01
	brne idata_
	mov r11,lo(ROSAHCS1)
	orh r11,hi(ROSAHCS2)
	st.w r12[AVR32_PM_GPLP],r11

	mov r12,lo(AVR32_PM_ADDRESS)
	orh r12,hi(AVR32_PM_ADDRESS)
	mov r11,OSCCTRL0
	st.w r12[AVR32_PM_OSCCTRL0],r11
	mov r11,MCCTRL_1
	st.w r12[AVR32_PM_MCCTRL],r11
	mov r10,(1 << AVR32_PM_OSC0RDY)
xw8:ld.w r11,r12[AVR32_PM_POSCSR]
	tst r11,r10
	breq xw8
	mov r11,MCCTRL_2
	st.w r12[AVR32_PM_MCCTRL],r11

	//Setup initialized data.
idata_:
	lda.w r0,_data
	lda.w r1,_edata
	cp r0,r1
	brhs idata_end
	lda.w r2,_data_lma
idata_loop:
	ld.w r4,r2++
	st.w r0++,r4
	cp r0,r1
	brlo idata_loop
idata_end:

	//Clear uninitialized data.
	lda.w r0,__bss_start
	lda.w r1,_end
	cp r0,r1
	brhs udata_end
	mov r2,0
	mov r3,0
udata_loop:
	st.w r0++,r2
	cp.w r0,r1
	brlo udata_loop
udata_end:

	lda.w pc,main
