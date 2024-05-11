package ejercicio2;

import java.util.concurrent.Semaphore;

/**
 * La Clase que se encarga principalmente de cambiar de turno, también contiene todas las variables compartidas
 */
public class SemaforoCarretera extends Thread {
    public static final int NUM_SEMAFOROS = 3;
    private static final int NUM_TURNOS = 3;
    private Semaphore mutex;
    private int turno;
    // Semáforos binarios que se activan cuando es el turno del indice correspondiente
    private Semaphore[] semaforosTurnos;
    // Número de procesos esperando que pertenecen al turno del indice correspondiente
    private int[] esperando;
    // Número de procesos pasando que pertenecen la turno del indice correspondiente
    private int[] pasando;

    /**
     * Constructor de la Clase, como todas las variables compartidas empiezan siempre en el mismo valor, no es necesario
     * tener ningún parámetro.
     */
    public SemaforoCarretera() {
        super();
        this.mutex = new Semaphore(1);
        this.turno = 0;
        this.semaforosTurnos = new Semaphore[NUM_SEMAFOROS];
        this.esperando = new int[NUM_SEMAFOROS];
        this.pasando = new int[NUM_SEMAFOROS];

        for (int i = 0; i < NUM_SEMAFOROS; i++) {
            this.semaforosTurnos[i] = new Semaphore(0);
            this.esperando[i] = 0;
            this.pasando[i] = 0;
        }
    }

    /**
     * Obtener la variable compartida mutex
     *
     * @return el mutex
     */
    public Semaphore getMutex() {
        return mutex;
    }

    /**
     * Obtener la variable compartida turno
     *
     * @return el turno
     */
    public int getTurno() {
        return turno;
    }

    /**
     * Obtener el array de semáforos semaforosTurno
     *
     * @return semaforosTurnos
     */
    public Semaphore[] getSemaforosTurnos() {
        return semaforosTurnos;
    }

    /**
     * Obtener el array de transeúntes esperando
     *
     * @return esperando
     */
    public int[] getEsperando() {
        return esperando;
    }

    /**
     * Obtener el array de transeuntes pasando
     *
     * @return pasando
     */
    public int[] getPasando() {
        return pasando;
    }

    /**
     * Código que se ejecuta al lanzar el proceso, su función es cambiar el turno.
     */
    @Override
    public void run() {
        // Se espar un tiempo inicial para
        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        for (int i = 0; i < NUM_TURNOS; i++) {
            try {
                this.mutex.acquire(); // Se acquiere la exclusión mutua para editar la variable compartida turno

                // Se pasa al siguiente turno
                this.turno = (this.turno + 1) % 3;
                System.out.println("~Cambio de Turno nº " + (i + 1) + " turno actual " + this.turno);

                this.mutex.release(); // Libera exclusión mutua
                Thread.sleep(5000); // Espera a que termine el turno
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
        // Terminamos  el programa
        try {
            this.mutex.acquire();
            this.turno = -1; // Se cambia el turno a -1 para indicar el fin
            System.out.println("~Cambio de Turno a Fin " + this.turno);
            for (int i = 0; i < 3; i++) {
                if (semaforosTurnos[i].hasQueuedThreads()) {
                    System.out.println("/ Liberando Parados " + i);
                    // Se liberan todos los procesos esperando. Estos comprueban si se ha terminado el programa antes
                    // de realizar cualqueir acción. Así que no debe haber ningún problema.
                    semaforosTurnos[i].release(semaforosTurnos[i].getQueueLength());
                }
            }
            this.mutex.release();
        } catch (Exception ex){
            ex.printStackTrace();
        }
    }
}
