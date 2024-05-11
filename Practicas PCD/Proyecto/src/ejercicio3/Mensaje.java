package ejercicio3;

/**
 * Clase que se utiliza en vez de un struct, para pasar dos parámetros por un return. Únicamente para pasar info.
 */
public class Mensaje {
    /**
     *  Copia del estado de las colas en el momento de asignar la mejor
     */
    private final int[] colas;
    /**
     * Cola asignada
     */
    private final int colaAsignada;


    /**
     * Contructor
     * @param colas las colas
     * @param colaAsignada la cola asignada
     */
    public Mensaje(int[] colas, int colaAsignada) {
        this.colas = colas.clone();
        this.colaAsignada = colaAsignada;
    }

    public int[] getColas() {
        return colas;
    }

    public int getColaAsignada() {
        return colaAsignada;
    }
}
