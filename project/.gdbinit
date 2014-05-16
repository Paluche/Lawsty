target extended localhost:3333
file build/PuLSE.elf
monitor reset init

define flash_run
  make
  monitor reset halt
  load
  monitor reset init
  cont
