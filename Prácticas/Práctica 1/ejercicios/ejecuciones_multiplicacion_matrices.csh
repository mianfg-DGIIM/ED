#!/bin/csh
@ inicio = 10
@ fin = 1010
@ incremento = 50
set ejecutable = multiplicacion_matrices
set salida = tiempos_multiplicacion_matrices.dat

@ i = $inicio
echo > $salida
while ( $i <= $fin )
  echo Ejecución tam = $i
  echo `./{$ejecutable} $i 10000` >> $salida
  @ i += $incremento
end
