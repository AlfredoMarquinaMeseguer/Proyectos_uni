package ejercicio3;

import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;

/**
 * Clase principal del ejercicio 3. Se encarga de coordinar el uso de las máquinas y las mesas como recursos no
 * compartibles
 */
public class Banco extends Thread {
    /**
     * Constante que contiene la cantidad de Máquina presentes
     */
    private final static int N_MAQUINAS = 3;
    /**
     * Constante que contiene la cantidad de mesas existentes
     */
    private final static int N_MESAS = 4;
    /**
     * Cerrojo que aseguara la ejecución de los procesos en exclusión mutua
     */
    ReentrantLock l;
    ///// Para las máquinas
    /**
     * Cola de las máquinas
     */
    Condition colaMaquina;
    /**
     * Array de booleanos, cuando un elemento se encuentra a true quiere indicar que la máquina del id igual al indice
     * se encuentra libre.
     */
    boolean[] maquinasLibres;
    /**
     * Entero que indica el número de máquinas libres en el momento
     */
    int maquinas;
    // Para las mesas
    /**
     * Colas de las mesas, cada mesa tiene su propia cola
     */
    final Condition[] colasMesas;
    /**
     * Número de personas esperando en la cola de mismo índice
     */
    int[] esperandoMesa;
    /**
     * Indica si la mesa relacionada con la cola del mismo índice se encuentra libre
     */
    boolean[] mesasLibres;

    /**
     * Constructor del Monitor Banco
     */
    public Banco() {
        this.l = new ReentrantLock(true);
        this.colaMaquina = l.newCondition();
        this.maquinasLibres = new boolean[N_MAQUINAS];
        this.maquinas = N_MAQUINAS;
        for (int i = 0; i < N_MAQUINAS; i++)
            maquinasLibres[i] = true;

        this.colasMesas = new Condition[N_MESAS];
        this.esperandoMesa = new int[N_MESAS];
        this.mesasLibres = new boolean[N_MESAS];

        for (int i = 0; i < N_MESAS; i++) {
            this.colasMesas[i] = l.newCondition();
            this.esperandoMesa[i] = 0;
            this.mesasLibres[i] = true;
        }
    }

    /**
     * Método para solicitar la exclusión mutua de una máquina
     *
     * @return el id de la máquina a utilizar
     */
    public int irAMaquina() {
        int id = 0;
        l.lock();
        try {
            while (maquinas == 0)
                colaMaquina.await();

            while (!maquinasLibres[id])
                id++;
            maquinasLibres[id] = false;
            maquinas--;
        } catch (Exception ex) {
            ex.printStackTrace();
        } finally {
            l.unlock();
        }
        return id;
    }

    /**
     * Método para liberar la exclusión mutua de la máquina utilizada
     *
     * @param id el id de la máquina que ha sido utilizada
     */
    public void liberarMaquina(int id) {
        int[] copiaEsperandoMesa;
        l.lock();
        try {
            maquinasLibres[id] = true;
            maquinas++;
            colaMaquina.signal();
        } catch (Exception exception) {
            exception.printStackTrace();
        } finally {
            l.unlock();
        }
    }

    /**
     * Método para pedir cola de mesa, también "reserva" sitio en la cola. Se realiza en banco en vez de en cliente,
     * porque si se hace en cliente se tienden a apilar todos en una sola. Sin embargo, al ejecutarse en Banco, como
     * tiene acceso directo al array de seguiemiento de tiempos de colas, se ejecuta correctamente.
     *
     * @return un objeto que contiene la cola asignada y el estado de los tiempos en el momento de asignarla.
     */
    public Mensaje solicitudAdelantadaMesa() {
        l.lock();
        int mejorCola;
        int[] copiaColas;
        try {
            mejorCola = menorColaDeMesa(esperandoMesa);
            copiaColas = esperandoMesa.clone();
            esperandoMesa[mejorCola]++;
        } finally {
            l.unlock();
        }
        return new Mensaje(copiaColas, mejorCola);
    }

    /**
     * Método para solicitar la exclusión mutua de una mesa en concreto
     *
     * @param id el id de la mesa que se quiere utilizar
     */
    public void esperarMesa(int id) {
        l.lock();
        try {
            if (!mesasLibres[id]) {
                colasMesas[id].await();
            } else {
                esperandoMesa[id]--;
                mesasLibres[id] = false;
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        } finally {
            l.unlock();
        }
    }

    /**
     * Método para liberar la exclusión mutua de una mesa
     *
     * @param id el id de la mesa de la que se quiere liberar
     */
    public void liberarMesa(int id) {
        l.lock();
        try {
            if (esperandoMesa[id] > 0) {
                esperandoMesa[id]--;
                colasMesas[id].signal();
            } else {
                mesasLibres[id] = true;
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        } finally {
            l.unlock();
        }
    }


    /**
     * Función auxiliar para calcular cuál es la cola con el menor número de personas.
     *
     * @param personasEnColaMesas Array de colas, los valores son el número de personas esperando
     * @return El indice de la cola con menor número de personas esperando
     */
    private int menorColaDeMesa(int[] personasEnColaMesas) {
        // El indice de la cola con menor personas esperando
        int indiceMenor = 0; // Suponemos que el primero es el menor y comprobamos a partir de ahí
        for (int i = 1; i < personasEnColaMesas.length; i++)
            // Se comprubea si la mesa de indice i es menor que la actual menor
            if (personasEnColaMesas[indiceMenor] > personasEnColaMesas[i])
                // En caso de que lo sea, esta se convierte en la nueva menor
                indiceMenor = i;

        // Devolvemos cual es el menor
        return indiceMenor;
    }
}
