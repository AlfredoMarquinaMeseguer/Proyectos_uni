package ejercicio4;

import messagepassing.MailBox;

/**
 * Clase que simula una persona en un supermercado
 */
public class Persona extends Thread {
    /**
     * Número de veces que se tiene que repetir el proceso
     */
    private static final int N_REPETICIONES = 5;
    /**
     * Número de milisegundos en un segundo
     */
    public static final int MILIS_A_SEGUNDOS = 1000;
    /**
     * Respuesta a un mensaje cuando no importa el contenido
     */
    public static final String OK = "ok";
    /****** Buzones de enviar ******/
    /**
     * Recibe las solicitudes de los procesos persona que quieren ser asignados a una caja.
     */
    private final MailBox solicitudCaja;
    /**
     * Recibe mensajes de los procesos que terminan. Va asociado a la variable procesosRestantes, cada vez que recibe
     * uno, esta se decrementa. Cuando Llegue a cero el proceso controlador debe terminar.
     */
    private final MailBox buzonTerminar;

    // Los siguientes buzones son para el control de la exclusión mutua
    // Sin embargo la exclusión mutua de la pantall se controla con un buzón
    // de testigo descentralizado.
    /**
     * Recibe peiciones de procesos persona que quieren obtener la exclusión mútua de la caja A.
     */
    private final MailBox abrirCajaA;

    /**
     * Recibe mensajes del proceso que tiene la exclusión mútua de la caja A para liberarla.
     */
    private final MailBox liberarCajaA;

    /**
     * Recibe peticiones de procesos persona que quieren obtener la exclusión mútua de la caja B.
     */
    private final MailBox abrirCajaB;

    /**
     * Recibe mensajes del proceso que tiene la exclusión mútua de la caja B para liberarla.
     */
    private final MailBox liberarCajaB;

    /****** Buzones de recibir******/
    // Como en Java la clase MailBox que representa un buzón no se puede pasar como parámetro por MailBox, se debe tener
    // los buzones respuesta ya presentes en la clase. De esta manera, simplemente se puede pasar el id del proceso y
    // responder al buzón con la posición igual a este id, que será el de dicho proceso.

    /**
     * Para responder a las peticiones de SolicitudCaja.
     */
    private final MailBox respuestaSolicitudCaja;

    /**
     * Para responder a las peticiones de AbrirCajaA.
     */
    private final MailBox respuestaAbrirCajaA;

    /**
     * Para responder a las peticiones de AbrirCajaB.
     */
    private final MailBox respuestaAbrirCajaB;

    /****** Buzón control del a exclusión mutua pantalla con testigo ******/
    /**
     * Este buzón sirve para el control de la exclusión mutua mediante paso de testigo.
     */
    private final MailBox mutexEscritura;

    /**
     *El id del proceso
     */
    private final Integer id;


    /**
     * Guardamos la caja utilizada para imprimir en el mensaje más tarde
     */
    private String caja; // También puede ser un enum

    /**
     * El tiempo que pasa la persona en caja.
     */
    private Integer tiempoPago;

    /**
     * Contructor de la clase
     * @param id el id del proceso
     * @param solicitudCaja buzón en el que realizar la solicitud de la caja
     * @param buzonTerminar buzón en el que notificar el final de la ejecución
     * @param abrirCajaA buzón en el que solicitar la exclusión mutua de la caja A
     * @param liberarCajaA buzón en el que notificar la liberación de la exblusión mutua de la caja A
     * @param abrirCajaB buzón en el que solicitar la exclusión mutua de la caja B
     * @param liberarCajaB buzón en el que notificar la liberación de la exblusión mutua de la caja B
     * @param respuestaSolicitudCaja buzón en que recibir la respuesta del controlador a solitudCaja
     * @param respuestaAbrirCajaA buzón en que recibir la respuesta del controlador a abrirCajaA
     * @param respuestaAbrirCajaB buzón en que recibir la respuesta del controlador a abrirCajaB
     * @param mutexEscritura buzón de paso de testigo para el control de la exclusión mutua de la escritura en pantalla
     */
    public Persona(Integer id, MailBox solicitudCaja, MailBox buzonTerminar, MailBox abrirCajaA, MailBox liberarCajaA, MailBox abrirCajaB, MailBox liberarCajaB, MailBox respuestaSolicitudCaja, MailBox respuestaAbrirCajaA,  MailBox respuestaAbrirCajaB,  MailBox mutexEscritura) {
        this.id = id;
        this.solicitudCaja = solicitudCaja;
        this.buzonTerminar = buzonTerminar;
        this.abrirCajaA = abrirCajaA;
        this.liberarCajaA = liberarCajaA;
        this.abrirCajaB = abrirCajaB;
        this.liberarCajaB = liberarCajaB;
        this.respuestaSolicitudCaja = respuestaSolicitudCaja;
        this.respuestaAbrirCajaA = respuestaAbrirCajaA;
        this.respuestaAbrirCajaB = respuestaAbrirCajaB;
        this.mutexEscritura = mutexEscritura;
    }

    /**
     * Método auxiliar que genera un tiempo que la persona va a utilizar para pasearse por la tienda
     * @return el tiempo a pasearse por la tienda
     */
    private Integer tiempoPaseoPorLaTienda() {
        return ((int) (Math.random() * 10)+1) * MILIS_A_SEGUNDOS;
    }

    @Override
    public void run() {
        for (int i = 0; i < N_REPETICIONES; i++) {

            ///// 1 Realiza la compra
            try {
                // Este tiempo de espera simula a la persona paseando por la tienda o algo
                Thread.sleep(tiempoPaseoPorLaTienda());
            } catch (Exception ignored) {}

            ///// 2 Solicita una Caja
            solicitudCaja.send(id); // Se hace una solicitud de caja
            // Se espera la respuesta que es un mensaje que contiene el tiempo de espera en caja y la caja asignada
            String respuestaSolicitud = respuestaSolicitudCaja.receive().toString();

            // Este Método separa el mensaje escrito en String e inserta los valores en las variables tiempoPago y caja
            decodificarMensaje(respuestaSolicitud);

            ///// 3 y 4 realiza el pago en una caja y las libera
            // Solicitas exclusión mutua de la caja correspondiente
            if (caja.equals(Controlador.CAJA_A)) {
                abrirCajaA.send(id); // Solicita exclusión mutua
                respuestaAbrirCajaA.receive(); // Se espera la respuesta
                try {
                    Thread.sleep(tiempoPago * MILIS_A_SEGUNDOS); // Se espera el tiempo de pago
                } catch (Exception ignored) {
                }

                liberarCajaA.send(id); // Se envia petición de liberaciópn de la exclusión mutua
            } else {
                abrirCajaB.send(id); // Solicita exclusión mutua
                respuestaAbrirCajaB.receive(); // Se espera la respuesta
                try {
                    Thread.sleep(tiempoPago * MILIS_A_SEGUNDOS); // Se espera el tiempo de pago
                } catch (Exception ignored) {
                }

                liberarCajaB.send(id); // Se envia petición de liberaciópn de la exclusión mutua
            }

            ///// 5 Imprime en pantalla información
            mutexEscritura.receive(); // Solicita la exlucisón mutua

            // Imprime por pantalla la información del pago
            // informaciónDelPago forma el mensaje según enunciado
            System.out.println(informacionDelPago());

            mutexEscritura.send(OK); // Solicita la exlucisón mutua
        }
        buzonTerminar.send(OK); // Se informa al controlador cuando se termina de el proceso
    }

    /**
     * Método auxiliar para formar el mensaje a mostrar por pantalla
     * @return el mensaje bien formateado con la información requerida
     */
    private String informacionDelPago() {
        return "\nejercicio4.Persona " + id + " ha usado la caja " + caja + "\nTiempo de pago = " + tiempoPago
                + "\n\tThread.sleep(" + tiempoPago + ")\n" + "ejercicio4.Persona " + id + " liberando la caja " + caja;
    }

    /**
     * Método auxiliar que decodifica el mensaje devuelto por respuestaSolicitudCaja
     * @param respuestaSolicitud el mensaje devuelto por la respuesta de solicitudCaja
     */
    private void decodificarMensaje(String respuestaSolicitud) {
        String[] elementos = respuestaSolicitud.split(Controlador.SEPARADOR); // Se separa los elementos por el separador
        // Se castea el primero a integer, este representa el tiempo de pago
        this.tiempoPago = Integer.valueOf(elementos[0]);
        this.caja = elementos[1]; // Este valor representa la caja a la que se le ha asignado el proceso
    }
}
