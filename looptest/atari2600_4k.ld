# Linker config file for targeting the Atari 2600.

MEMORY {
       RAM:   start = $80,   size=$80, type = rw, define = yes;
       ROM:   start = $F000, size=$1000, type = ro, file = %O, define = yes;
       TIA:   start = $00,   size=$40, type = rw, define = yes;
       RIOT:  start = $280,  size=$20, type = rw, define = yes;
}

SEGMENTS {
       RODATA:   load=ROM, type=ro, align = $100;	
       CODE:     load=ROM, type=ro, define=yes;
       DATA:     load=ROM, run=RAM, type=rw, define=yes;
       BSS:      load=RAM, type=bss, define=yes;
       VECTORS:  load=ROM, type=ro, start=$FFFC;
       ZEROPAGE: load=RAM, type=zp;
       TIA:      load=TIA, type=rw, define = yes, optional = yes;
       RIOT:     load=RIOT, type=rw, define = yes, optional = yes;
}

