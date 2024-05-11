void main() {
    var x = 30, y = -10;
    var b = 3;
    var z;
    z = x + y;
    print "hola \"esto es\" una prueba", "\n";
        /* Esto es
            un comentario
        multilinea
        */

// Esto es un comentario de una sola linea

    if (b) print "b es true porque su valor es distinto de 0\n";
    while(b) {
        b = b-1;
        print"El valor de b va disminuyendo en", "cada iteración\n";
    }
    if(b) print "hola";
    else print "El valor de b es 0\n";
}
