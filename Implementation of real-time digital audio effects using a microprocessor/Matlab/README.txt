Ejecutar todo desde la ruta donde se haya guardado la carpeta TFG. Por ejemplo:
C:\Users\luisl\OneDrive\Escritorio\IngenieriaDeTelecomunicaciones\Cuarto\TrabajoFinDeGrado\TFG
Introducir esa misma ruta en la línea del efecto main

Poner este mismo aviso en el main de Matlab.
Hacer que el usuario introduzca en matlab la ruta, indicándole el ejemplo de mi ruta.
Se recomienda que la ruta no incluya espacios ni carácteres raros o con tildes.

Poner las distintas pistas de audio que tengo y poner un mensaje en el codigo de descomentar la
que se desee escuchar. Poner un aviso en matlab de que hay algunas pistas muy largas. Si se desea
parar de escuchar se debe teclear clear sound en la ventana de comandos. O mejor poner algo de 
este estilo 
%Limitamos a los 15 primeros segundos, para ficheros de larga duración 
if(length(x)>15*Fs) 
    x=x(1:15*Fs); 
end

Preguntarle al usuario los parámetros de entrada que quiere elegir para el efecto elegido:
%Prompt for and store 'Damping', 'Min_Cutoff' and 'Max_Cutoff' and 'Width'
Variables
damping = input('\n What Damping Factor would you like to
use?\n(Recommended value 0.05)\n>');
width = input('\n What Rate would you like to use? (Hz)\n(Recommended value
1000)\n>');
min_cutoff = input('\n What minimum Cut-Off Frequency would you like to
use? (Hz)\n(Recommended value 250)\n>');
max_cutoff = input('\n What maximum Cut-Off Frequency would you like to
use? (Hz)\n(Recommended value 5000)\n>');