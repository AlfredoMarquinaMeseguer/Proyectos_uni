package ejercicio3;

/**
 *  Clase cliente que simula un cliente en un banco para el ejercicio 3
 */
public class Cliente extends Thread {
    /**
     * Id del proceso
     */
    private int id;
    /**
     * Tiempo de espera en máquina
     */
    private int x;
    /**
     * Tiempo de espera en Mesa
     */
    private int y;
    /**
     * Máquina que se le ha asignado
     */
    private int maquinaAsignada;
    /**
     * Id de la mesa utilizada
     */
    private int colaMesa;
    /**
     * Copia del estado de las colas a la hora de elegirla mejor
     */
    private int[] personasEnColaMesas;
    /**
     * Puntero al monitor Banco que controla la
     */
    private Banco banco;
    /**
     * Puntero al monitor Pantalla que controla la exclusión mutua de la pantalla
     */
    private Pantalla pantalla;


    /**
     * Constructor de la clase Clinete, requiere del id y los punteros a los monitores usado
     * @param id el id del cliente
     * @param banco el monitor banco al que realizar peticiones de máquinas y mesas
     * @param pantalla el monitor de las exclusión mutua de la pantalla
     */
    public Cliente(int id, Banco banco, Pantalla pantalla) {
        this.id = id;
        this.banco = banco;
        this.pantalla = pantalla;
        this.x = (int) (Math.random() * 10000) + 1;
        this.y = (int) (Math.random() * 20000) + 1;
    }

    /**
     * Método que se ejecutar en concurrencia
     */
    @Override
    public void run() {
        super.run();

        // Utilizar la máquina
        maquinaAsignada = banco.irAMaquina(); // Pedir una máquina
        try {
            // Simular uso
            Thread.sleep(x);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        // Liberar máquina y obtener tiempos colas
        banco.liberarMaquina(maquinaAsignada);

        // Obtener la cola con menor tiempo de espera
        // colaMesa = menorColaDeMesa(personasEnColaMesas);
        Mensaje msj = banco.solicitudAdelantadaMesa();
        personasEnColaMesas = msj.getColas();
        colaMesa = msj.getColaAsignada();

        pantalla.esperarPantalla();
        System.out.println("--------------------------------------------------------------" +
                "\nCliente " + id + " ha solicitado su servicio en la máquina: " + maquinaAsignada +
                "\nTiempo en solicitar el servicio: " + x +
                "\nSerá atendido en la mesa: " + colaMesa +
                "\nTiempo en la mesa = " + y +
                "\nTiempo de espera en la mesa1 = " + personasEnColaMesas[0] + ", mesa2 = " + personasEnColaMesas[1] +
                ", mesa3 = " + personasEnColaMesas[2] + ", mesa4 = " + personasEnColaMesas[3] +
                "\n--------------------------------------------------------------");
        pantalla.liberarPantalla();


        banco.esperarMesa(colaMesa);
        try {
            // Simular uso
            Thread.sleep(y);
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        banco.liberarMesa(colaMesa);
    }

}
