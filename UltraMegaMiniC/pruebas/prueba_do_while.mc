void main(){
    var a= 3;

    print "Primer do while ", a ,"\n";
    do 
    {
        print "El valor de a es ",a,"\n";
        a = a-1;
    } while (a);

    a =5;
    print "\nSegundo con while ", a,"\n";
    while (a) { print "El valor de a es ",a, "\n"; a = a-1; } 
}