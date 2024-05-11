package ejercicio1;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class Generador extends Thread {

    private ReentrantLock l;
    private Condition c;

    public void run() {
        Ejercicio1.cerrojo.lock();
        try {
            for (int i = 0; i < 110; i++) {
                if (i % 11 % 2 == 1)
                    Ejercicio1.arrayLectura[i] = (int) (Math.random() * (3)) + 1;
                else
                    Ejercicio1.arrayLectura[i] = (int) (Math.random() * (5)) + 1;
            }
            Ejercicio1.turno++;
        } finally {
            Ejercicio1.cerrojo.unlock();
        }
    }
}
