
.include "globals.inc"

.segment "VECTORS"
.addr reset ; RESET
.addr reset ; IRQ: will only occur with brk
