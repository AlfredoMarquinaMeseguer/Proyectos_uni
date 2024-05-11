package ejercicio4;

import messagepassing.MailBox;

/**
 * Clase donde se ejecuta el main
 */
public class Ejercicio4 {
    /**
     * Número de procesos cliente al principio de la ejecución del programa.
     */
    private static final int N_CLIENTES = 30;

    /**
     * El problema
     *
     * @param args no se usa
     */
    public static void main(String[] args) {
        /* Buzones de escritura para ejercicio4.Controlador */
        MailBox solicitudCaja = new MailBox();
        // Recibe las solicitudes de los procesos persona que
        // quieren ser asignados a una caja.

        MailBox buzonTerminar = new MailBox();
        // Recibe mensajes de los procesos que terminan. Va asociado a la variable
        // procesosRestantes, cada vez que recibe uno, esta se decrementa. Cuando
        // Llegue a cero el proceso controlador debe terminar.

        // Los siguientes buzones son para el control de la exclusión mutua
        // Sin embargo la exclusión mutua de la pantall se controla con un buzón
        // de testigo descentralizado.

        MailBox abrirCajaA = new MailBox();
        // Recibe peticiones de procesos persona que quieren obtener la
        // exclusión mútua de la caja A

        MailBox liberarCajaA = new MailBox();
        // Recibe mensajes del proceso que tiene la exclusión mútua de la
        // caja A para liberarla.

        MailBox abrirCajaB = new MailBox();
        // Recibe peticiones de procesos persona que quieren obtener la
        // exclusión mútua de la caja B.

        MailBox liberarCajaB = new MailBox();
        // Recibe mensajes del proceso que tiene la exclusión mútua de la
        // caja B para liberarla.

        /* Buzones de escritura para ejercicio4.Persona */
        // Como en Java la clase MailBox que representa un buzón no se puede pasar como parámetro por MailBox, se debe tener
        // los buzones respuesta ya presentes en la clase. De esta manera, simplemente se puede pasar el id del proceso y
        // responder al buzón con la posición igual a este id, que será el de dicho proceso.

        MailBox[] respuestaSolicitudCaja = new MailBox[N_CLIENTES];
        // Para responder a las peticiones de SolicitudCaja

        MailBox[] respuestaAbrirCajaA = new MailBox[N_CLIENTES];
        // Para responder a las peticiones de AbrirCajaA

        MailBox[] respuestaLiberarCajaA = new MailBox[N_CLIENTES];
        // Para responder a las peticiones de LiberarCajaA;

        MailBox[] respuestaAbrirCajaB = new MailBox[N_CLIENTES];
        // Para responder a las peticiones de AbrirCajaB;

        MailBox[] respuestaLiberarCajaB = new MailBox[N_CLIENTES];
        // Para responder a las peticiones de LiberarCajaB;

        MailBox mutexEscritura = new MailBox();

        /* Clases de procesos */
        Controlador controlador;
        Persona[] clientes;

        System.out.println("Definiendo clases.");

        for (int i = 0; i < N_CLIENTES; i++) {
            respuestaSolicitudCaja[i] = new MailBox();
            respuestaAbrirCajaA[i] = new MailBox();
            respuestaLiberarCajaA[i] = new MailBox();
            respuestaAbrirCajaB[i] = new MailBox();
            respuestaLiberarCajaB[i] = new MailBox();
        }

        controlador = new Controlador(solicitudCaja, buzonTerminar, abrirCajaA, liberarCajaA, abrirCajaB, liberarCajaB,
                respuestaSolicitudCaja, respuestaAbrirCajaA, respuestaLiberarCajaA, N_CLIENTES);

        clientes = new Persona[N_CLIENTES];
        for (int i = 0; i < N_CLIENTES; i++)
            clientes[i] = new Persona(i, solicitudCaja, buzonTerminar, abrirCajaA, liberarCajaA, abrirCajaB,
                    liberarCajaB, respuestaSolicitudCaja[i], respuestaAbrirCajaA[i], respuestaAbrirCajaB[i],
                    mutexEscritura);

        System.out.println("Comezando Ejecución");
        // Se envia el primer testigo desde el main.
        mutexEscritura.send("ok");
        // Lanzamos los procesos
        controlador.start();
        for (Persona p : clientes)
            p.start();

        try {
            controlador.join();
            for (Persona p : clientes)
                p.join();
        } catch (Exception ex) {
            ex.printStackTrace();
        }

        System.out.println("Ejecución terminada");
    }
}