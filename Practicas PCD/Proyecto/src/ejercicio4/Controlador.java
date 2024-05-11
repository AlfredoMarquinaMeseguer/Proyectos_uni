package ejercicio4;

import messagepassing.MailBox;
import messagepassing.Selector;

/**
 * Clase principal del problema. Asigna personas a caja y controla la exclusión mutua de estas.
 */
public class Controlador extends Thread {
    /**
     * El tiempo máximo que puede estar una @class Persona en una caja
     */
    private static final int MAX_TIEMPO = 10;
    /**
     * El timepo mínimo que puede estar una @class Persona en una Caja
     */
    private static final int MIN_TIEMPO = 1;
    /**
     * El tiempo mínimo que se debe estimar que una persona estará par que se le asigne la caja A
     */
    private static final int MIN_TIEMPO_A = 5;
    /**
     * String de respuesta cuando esta da igual
     */
    private static final String OK = "ok";
    /**
     * El separador para el mensaje que contiene dos datos
     */
    public static final String SEPARADOR = ",";
    /**
     * String que indica la caja A
     */
    public static final String CAJA_A = "A";
    /**
     * String que indica la caja B
     */
    public static final String CAJA_B = "B";
    /****** Buzones de recibir ******/
    /**
     * Recibe las solicitudes de los procesos persona que quieren ser asignados a una caja.
     */
    private final MailBox solicitudCaja;
    /**
     * Recibe mensajes de los procesos que terminan. Va asociado a la variable procesosRestantes, cada vez que recibe
     * uno, esta se decrementa. Cuando llegue a cero el proceso controlador debe terminar.
     */
    private final MailBox buzonTerminar;

    // Los siguientes buzones son para el control de la exclusión mutua
    // Sin embargo la exclusión mutua de la pantalla se controla con un buzón
    // de testigo descentralizado.

    /**
     * Recibe peticiones de procesos persona que quieren obtener la exclusión mútua de la caja A.
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

    /****** Buzones de respuetas******/
    // Como en Java la clase MailBox que representa un buzón no se puede pasar como parámetro por MailBox, se debe tener
    // los buzones respuesta ya presentes en la clase. De esta manera, simplemente se puede pasar el id del proceso y
    // responder al buzón con la posición igual a este id, que será el de dicho proceso.

    /**
     * Para responder a las peticiones de SolicitudCaja.
     */
    private final MailBox[] respuestaSolicitudCaja;

    /**
     * Para responder a las peticiones de AbrirCajaA.
     */
    private final MailBox[] respuestaAbrirCajaA;

    /**
     * Para responder a las peticiones de AbrirCajaB.
     */
    private final MailBox[] respuestaAbrirCajaB;

    /****** Selector******/
    /**
     * Objeto necesario para implementar un selector que nos permita escuchar las peticioens de varios buzones de
     * recibir al mismo tiempo.
     */
    private final Selector selector;

    /****** Entero ******/
    /**
     * Lleva la cuenta de los procesos que quedan ejecutando. Cuando llega a cero se termina el proceso
     * @class ejercicio4.Controlador .
     */
    private int procesosRestantes;

    /****** Booleanos ******/
    /**
     * Variable para el seguimiento de la exclusión mútua de la Caja A.
     */
    private boolean cajaALibre;

    /**
     * Variable para el seguimiento de la exclusión mútua de la Caja B.
     */
    private boolean cajaBLibre;

    /**
     * Contructor del proceso Controlador
     * @param solicitudCaja buzón en el que recibe las solicitudes de caja
     * @param buzonTerminar buzón en el que se informa que un proceso ha terminado
     * @param abrirCajaA buzón en el que se solicita la exclusión muta de la Caja A
     * @param liberarCajaA buzón en el que se libera la exclusión mutua de la Caja A
     * @param abrirCajaB buzón en el que se solicita la exblusión mutua de la Caja B
     * @param liberarCajaB buzón en el que se libera la exclusión mutua de la Caja B
     * @param respuestaSolicitudCaja array de buzones de respuesta para cuando se solicita una caja
     * @param respuestaAbrirCajaA array de buzones de respuesta para cuando se pide la exclusión mutua de la Caja A
     * @param respuestaAbrirCajaB array de buzones de respuesta para cuando se pide la exclusión mutua de la Caja B
     * @param procesosRestantes número de procesos con los que se empieza la ejecución
     */
    public Controlador(MailBox solicitudCaja, MailBox buzonTerminar, MailBox abrirCajaA, MailBox liberarCajaA,
                       MailBox abrirCajaB, MailBox liberarCajaB, MailBox[] respuestaSolicitudCaja,
                       MailBox[] respuestaAbrirCajaA, MailBox[] respuestaAbrirCajaB, int procesosRestantes) {
        this.solicitudCaja = solicitudCaja;
        this.buzonTerminar = buzonTerminar;
        this.abrirCajaA = abrirCajaA;
        this.liberarCajaA = liberarCajaA;
        this.abrirCajaB = abrirCajaB;
        this.liberarCajaB = liberarCajaB;
        this.respuestaSolicitudCaja = respuestaSolicitudCaja;
        this.respuestaAbrirCajaA = respuestaAbrirCajaA;
        this.respuestaAbrirCajaB = respuestaAbrirCajaB;
        this.procesosRestantes = procesosRestantes;
        // Las cajas compartidas están libres
        this.cajaALibre = true;
        this.cajaBLibre = true;
        // Definir el selector
        this.selector = new Selector();
        this.selector.addSelectable(this.solicitudCaja, false);
        this.selector.addSelectable(this.abrirCajaA, false);
        this.selector.addSelectable(this.liberarCajaA, false);
        this.selector.addSelectable(this.abrirCajaB, false);
        this.selector.addSelectable(this.liberarCajaB, false);
        this.selector.addSelectable(this.buzonTerminar, false);
    }

    /**
     * Método que se ejecuta cuando le lanza el proceso.
     */
    @Override
    public void run() {
        // Definimos las variables locales a utilizar en este metodo
        Integer id; // El id del proceso que se está comunicando con el controlador
        int tiempoEspera; // El tiempo de espera estimado para la solicitud de caja
        String caja; // Variable auxiliar para contener la caja asignada a la solicitud de caja

        do {
            // Denifinimos las guardas del selector, se han puesto en orden del según su aparición en el switch
            solicitudCaja.setGuardValue(true);              // 1
            abrirCajaA.setGuardValue(cajaALibre);           // 2
            liberarCajaA.setGuardValue(!cajaALibre);        // 3
            abrirCajaB.setGuardValue(cajaBLibre);           // 4
            liberarCajaB.setGuardValue(!cajaBLibre);        // 5
            buzonTerminar.setGuardValue(true);              // 6

            switch (selector.selectOrBlock()) {
                case 1:
                    id = (Integer) solicitudCaja.receive(); // Se obtiene el id del proceso persona según el mensaje
                    tiempoEspera = generarTiempoEspera(); // Se estima el tiempo que va a tardar

                    // Se le asigna una caja según el tiempo de pago
                    if (tiempoEspera >= MIN_TIEMPO_A) caja = CAJA_A;
                    else caja = CAJA_B;

                    // Se le responde al proceso que solicitó con los datos estimados
                    respuestaSolicitudCaja[id].send(crearMensaje(tiempoEspera, caja));
                    break;
                case 2:
                    id = (Integer) abrirCajaA.receive(); // Se obtiene el id del proceso persona según el mensaje

                    // Se le asigna el valor false a la cajaA para que ningún otro proceso pueda pedirla
                    cajaALibre = false;

                    // Se le responde al proceso que preguntó para que sepa que la operación ha terminado
                    respuestaAbrirCajaA[id].send(OK);
                    break;
                case 3:
                    liberarCajaA.receive(); // Se obtiene el id del proceso persona según el mensaje

                    // Se le asigna el valor true a la cajaA para liberla
                    cajaALibre = true;

                    break;
                case 4:
                    abrirCajaB.receive(); // Se obtiene el id del proceso persona según el mensaje

                    // Se le asigna el valor false a la cajaB para que ningún otro proceso pueda pedirla
                    cajaBLibre = false;

                    break;
                case 5:
                    liberarCajaB.receive();// Se obtiene el id del proceso persona según el mensaje

                    // Se le asigna el valor true a la cajaA para liberla
                    cajaBLibre = true;

                    break;
                case 6:
                    buzonTerminar.receive(); // Se recibe un mensaje cuando un proceso persona termina
                    procesosRestantes--; // Se actualiza el número de procesos que siguen activos
            }
            // Se termina el proceso controlador cuando el número de procesos cliente sea cero.
        } while (procesosRestantes != 0);
    }

    /**
     * Codifica los argumentos en un mensaje de String para poder pasar varios valores por MailBox sin tener que crear
     * un objeto serializable. Este mensaje debe ser "decodificado" por el proceso que lo recibe.
     *
     * @param tiempoEspera tiempo en segundos que el proceso debe espera en caja
     * @param caja         caja asignada
     * @return un string que contiene el tiempo y la caja asignada segados por un separador
     */
    private String crearMensaje(Integer tiempoEspera, String caja) {
        return tiempoEspera.toString() + SEPARADOR + caja;
    }

    /**
     * Genera un número aleatorio entre MAX_TIEMPO y MIN_TIEMPO que representa el tiempo en segundos que un proceso
     * tardará en pasar por caja
     *
     * @return un número entero aleatorio entre MAX_TIMEPO y MIN_TIEMPO
     */
    public Integer generarTiempoEspera() {
        return (int) (Math.random() * (MAX_TIEMPO - MIN_TIEMPO + 1)) + MIN_TIEMPO;
    }
}
