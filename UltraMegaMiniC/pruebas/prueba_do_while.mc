void main(){
    var a= 3;

    print "Primer do while", a ,"\n";
    do 
    {
        print "El valor de a es ",a,"\n";
        a = a-1;
    } while (a);

    print "\nSegundo do while\n";
    a =5;
    while (a) { print "El valor de a es ",a, "\n"; a = a-1; } 
}