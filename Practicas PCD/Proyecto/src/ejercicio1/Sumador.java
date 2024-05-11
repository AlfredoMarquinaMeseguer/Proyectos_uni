package ejercicio1;

import java.util.Arrays;

public class Sumador extends Thread {

    public void run() {
        super.run();
        int resultado = 0;
        Ejercicio1.cerrojo.lock();
        try {
            while(Ejercicio1.turno != 2){
                Ejercicio1.cerrojo.unlock();
                Ejercicio1.cerrojo.lock();
            }

            resultado = totalArrayEscritura(Ejercicio1.arrayEscritura);
        } finally {
            Ejercicio1.cerrojo.unlock();
        }

        Ejercicio1.lockPrint.lock();
        try {
            System.out.println("El total es: " + resultado + ".");
        } finally {
            Ejercicio1.lockPrint.unlock();
        }
    }

    public static int totalArrayEscritura(Integer... arrayEscritura) {
        return Arrays.stream(arrayEscritura).reduce(0, Integer::sum);
    }
}
