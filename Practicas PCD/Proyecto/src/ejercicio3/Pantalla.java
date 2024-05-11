package ejercicio3;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

/**
 * Clase monitor para controlar la exclusión mutua de la pantalla
 */
public class Pantalla extends Thread {
    /**
     * Cerrojo del monitor
     */
    private final ReentrantLock l;
    /**
     * Cola asociada a la pantalla
     */
    private final Condition pantalla;
    /**
     * Variable que indica si la pantalla se encuentra libre o no
     */
    private boolean pantallaLibre;
    /**
     * Indica el número de procesos esperando la exclusión mutua. Se utiliza por la falta de la función empty, se podría
     * utilizar l.hasQueuedThreads(), pero no es correcto.
     */
    private int esperando;

    /**
     * Cosntructor de la clase
     */
    public Pantalla() {
        this.l = new ReentrantLock(true);
        this.pantalla = l.newCondition();
        this.pantallaLibre = true;
        this.esperando = 0;
    }

    /**
     * Pedir la exclusión mutua del recurso no compartible Pantalla
     */
    public void esperarPantalla() {
        l.lock();
        try {
            if (!pantallaLibre) {
                esperando++;
                pantalla.await();
            } else {
                pantallaLibre = false;
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        } finally {
            l.unlock();
        }
    }

    /**
     * Liberar la exclusión mutua del recurso no compartible Pantalla
     */
    public void liberarPantalla() {
        l.lock();
        try {

            if (esperando > 0) {
                esperando--;
                pantalla.signal();
            } else {
                pantallaLibre = true;
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        } finally {
            l.unlock();
        }
    }
}

