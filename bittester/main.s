
.include "vcs.inc"
.include "globals.inc"

.segment "ZEROPAGE"

showbuf: .byte $00,$00,$00,$00,$00,$00,$00,$00,$00,$00,$00
tmp    : .byte $00

.segment "RODATA"
   
.segment "CODE"

reset:
   sei
   cld
   ldx #$ff
   txs
   inx
   txa
@loop:
   sta $00,x
   inx
   bne @loop

loop:
   lda #$00
   sta PF0
   sta PF1
   sta PF2
   sta CTRLPF
   
   lda #$2e
   sta COLUP0
   sta COLUP1
   sta COLUPF

vblankstart:
   lda #$02
   sta WSYNC
   sta VBLANK
   sta WSYNC
   sta WSYNC
   sta WSYNC
   sta VSYNC
   sta WSYNC
   sta WSYNC
   lda #$29
   sta TIM64T
   lda #$00
   sta WSYNC
   sta COLUBK
   sta VSYNC
   
waitforpicturestart:
   lda #$2f
   sta TIM64T
   
; do the fancy stuff here   
   lda SWCHA
   sta showbuf
   lda SWCHB
   sta showbuf+1
   lda INPT4
   sta showbuf+2
   lda INPT5
   sta showbuf+3
   sta RESP0
   sta RESP1

   
@wait:
   lda INTIM
   bne @wait
   sta VBLANK
   
   lda showbuf+0
   jsr hextosprites
   lda showbuf+1
   jsr hextosprites
   lda showbuf+2
   jsr hextosprites
   lda showbuf+3
   jsr hextosprites
   lda showbuf+4
   jsr hextosprites
   lda showbuf+5
   jsr hextosprites
   lda showbuf+6
   jsr hextosprites
   lda showbuf+7
   jsr hextosprites
   lda showbuf+8
   jsr hextosprites
   lda showbuf+9
   jsr hextosprites
   lda showbuf+10
   jsr hextosprites

   lda #38
   bit SWCHB
   bmi timing60hz
   clc
   adc #50
timing60hz:
   tax
@loop4:
   sta WSYNC
   dex
   bne @loop4
   
   lda SWCHB
   and #$01
   bne longjump
   jmp ($FFFE)
longjump:
   jmp vblankstart


hextosprites:
   pha
   and #$f0
   lsr
   tax
   pla
   and #$0f
   asl
   asl
   asl
   tay
   lda #$08
   sta tmp
@loop:
   sta WSYNC
   lda hexgfx,x
   sta GRP0
   lda hexgfx,y
   sta GRP1
   inx
   iny
   sta WSYNC
   dec tmp
   bne @loop
   rts
   