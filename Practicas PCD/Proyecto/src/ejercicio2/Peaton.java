package ejercicio2;

/**
 * Clase que representa a un peatón intentado pasar por el paso de cebra.
 */
public class Peaton extends Thread {
    public final static int TURNO_PEATONES = 2, ANTERIOR_TURNO = 1;
    private static final long TIEMPO_CRUCE = 3000;
    private static final long TIEMPO_ESPERA = 8000;
    private static final int MAX_PASAR_PEATONES = 10;
    private SemaforoCarretera s;
    private int id;

    /**
     * Contructor de la clase peaton
     *
     * @param s  la clase que contiene las vairbles compartidas
     * @param id el id del proceso
     */
    public Peaton(SemaforoCarretera s, int id) {
        super();
        this.s = s;
        this.id = id;
    }

    /**
     * El método principal donde se ejecuta el código del peatón
     */
    @Override
    public void run() {

        try {
            s.getMutex().acquire();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        System.out.println("Comienzo ejecución peaton: " + id);
        while (s.getTurno() != -1) {
			/* Un peaton no puede pasar directamente si se cumple una de las siguiente condiciones:
				1. No es su turno
				2. Ya están pasando el número máximo de Peatones
				3. Hay coches del turno anterior pasando
			 */
            if (s.getTurno() != TURNO_PEATONES || s.getPasando()[TURNO_PEATONES] == MAX_PASAR_PEATONES
                    || s.getPasando()[ANTERIOR_TURNO] != 0) {
                // En caso de no pasar, se añade a esperando
                s.getEsperando()[TURNO_PEATONES]++;
                s.getMutex().release(); // Se libera el mutex
                try {
                    s.getSemaforosTurnos()[TURNO_PEATONES].acquire(); // Aquí se espera
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }

                // Una vez liberado se reduce el número de peatones esperando
                s.getEsperando()[TURNO_PEATONES]--;
            }
            // Si se ha terminado la ejecución se puede salir del bucle
            if (s.getTurno() == -1) {
                System.out.println("=Saliendo peaton " + id);
                break;
            }
            // Como está pasando se aumenta el núemor de peatones pasando
            s.getPasando()[TURNO_PEATONES]++;

            System.out.println("*Pasando peaton:" + id);
            // Si hay más peatones esperando y no se ha llegado todavía al máximo, se liberan más peatones, despertar
            // encadenado
            if (s.getEsperando()[TURNO_PEATONES] != 0 && s.getPasando()[TURNO_PEATONES] < MAX_PASAR_PEATONES) {
                System.out.println("#Peaton " + id + " hace un release." + s.getPasando()[TURNO_PEATONES]);
                // Se cede la exclusión mutua al siguiente proceso, por lo que no se tiene que liberar y no se ha tenido
                // que pedir.
                s.getSemaforosTurnos()[TURNO_PEATONES].release();
            } else {
                // Sino se puede despertar ningún otro proceso se libera el mutex.
                System.out.println("%Peaton " + id + " no hace nada." + s.getPasando()[TURNO_PEATONES]);
                s.getMutex().release();
            }
            // Pasar
            try {
                Thread.sleep(TIEMPO_CRUCE);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            // Fin Pasar
            try {
                // Obtenemos otra vez la exclusión mutua para poder realizar las comprobaciones y actualizar el
                // número de transeuntes pasando.
                s.getMutex().acquire();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("-Ha pasado peaton: " + id);
            // Se reduce el número de transeuntes pasando
            s.getPasando()[TURNO_PEATONES]--;
            // Si seguimos en el mismo turno, se puede liberar a un @class Peaton esperando
            if (s.getTurno() == TURNO_PEATONES) {
                System.out.println("## Peaton " + id + " despierta siguiente");
                // Cedemos la exclusión mutua por lo que no tenemo que liberar el mutex
                s.getSemaforosTurnos()[TURNO_PEATONES].release();
                // Si no quedan peatones pasando y ya ha terminado nuestro turno despertamos un proceso del siguiente turno
            } else if (s.getPasando()[TURNO_PEATONES] == 0 && TURNO_PEATONES != s.getTurno()) {
                // Esta acción solo debe realizarse por el último peatón pasando
                System.out.println("$Peaton " + id + " libera siguiente Turno. " + s.getPasando()[TURNO_PEATONES]);
                s.getSemaforosTurnos()[0].release(); // Se cede la exclusión mutua al proceso despertado
            } else {
                // Como no hemos podido ceder la exclusión mutua, la liberamos
                System.out.println("%Peaton " + id + " no hace nada");
                s.getMutex().release();
            }
            // Se espera un tiempo antes de volver a pasar
            try {
                Thread.sleep(TIEMPO_ESPERA);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            // Se necesita la exclusión mutua para poder realizar las comprobaciones del principio del bucle
            try {
                s.getMutex().acquire();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("Peaton " + id + " vuelve a intentar cruzar.");
        }
        System.out.println("FIN peaton " + id);
        s.getMutex().release(); // Liberamos la exclusión mutua para no provocar un deadlock.
    }

}
