package ejercicio3;


/**
 * Clase donde se contiene el método main del problema
 */
public class Ejercicio3 {
    /**
     * El problema
     * @param args mete lo que quieras que no voy a coger nada
     */
    public static void main(String[] args) {
        Banco banco = new Banco();
        Pantalla pantalla = new Pantalla();
        Cliente[] clientes = new Cliente[50];

        for (int i = 0; i < clientes.length; i++)
            clientes[i] = new Cliente(i, banco, pantalla);

        System.out.println("Inicio de la  ejecución\n\n");
        banco.start();
        pantalla.start();

        for (Cliente cliente : clientes) cliente.start();

        try {
            for (Cliente cliente : clientes) cliente.join();
        } catch (Exception ex) {
            ex.printStackTrace();
        }

        System.out.println("\n\nFin de la ejecución");

    }
}
