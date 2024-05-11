package ejercicio2;

/**
 * Clase que representa al proceso Coche que para por el cruce
 */
public class Coche extends Thread {
    private static final int DIRECCIONES = 2;
    private static final int TIEMPO_ESPERA = 7000;
    private static final int TIEMPO_CRUCE = 500;
    public final static int MAX_PASAR_COCHES = 4;

    private SemaforoCarretera s;
    private int calleInicial;
    private int id;

    /**
     * Contructor del proceso
     *
     * @param semaforo     referencia al semaforo que cambiar turno y contiene las variables compartidas
     * @param calleInicial la dirección que debe cruzar en un principio
     * @param id           el id del proceso @class Coche
     */
    public Coche(SemaforoCarretera semaforo, int calleInicial, int id) {
        super();
        this.s = semaforo;
        this.calleInicial = calleInicial;
        this.id = id;
    }

    /**
     * Método ejecutado por el proceso al ser lanzado
     */
    @Override
    public void run() {
        /* NOTE: por motivos de tiempo, se me olvido que esto no estaba comentado, no se ha podido comentar
        correctamente. Por favor, lea la @class Peaton que está comentada y es muy similar
         */
        int turnoPasar = this.calleInicial;

        try {
            s.getMutex().acquire();
        } catch (InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        System.out.println("Comienzo ejecución coche:" + id);
        while (s.getTurno() != -1) {
            if (s.getTurno() != turnoPasar || s.getPasando()[turnoPasar] >= MAX_PASAR_COCHES
                    || s.getPasando()[turnoAnterior(turnoPasar)] != 0) {
                s.getEsperando()[turnoPasar]++;
                s.getMutex().release();
                try {
                    s.getSemaforosTurnos()[turnoPasar].acquire();
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }

                s.getEsperando()[turnoPasar]--;
            }

            if (s.getTurno() == -1) {
                System.out.println("=Saliendo coche " + id);
                break;
            }

            s.getPasando()[turnoPasar]++;

            System.out.println(
                    "*Pasando Coche " + id + " en dirección " + turnoPasar + " total " + s.getPasando()[turnoPasar]);
            if (s.getEsperando()[turnoPasar] != 0 && s.getPasando()[turnoPasar] < MAX_PASAR_COCHES) {
                System.out.println("#Coche " + id + " hace un realease." + s.getPasando()[turnoPasar]);
                s.getSemaforosTurnos()[turnoPasar].release();
            } else {
                System.out.println("%Coche " + id + " no hace nada." + s.getPasando()[turnoPasar]);
                s.getMutex().release();
            }
            // Pasar
            try {
                Thread.sleep(TIEMPO_CRUCE);
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            // Fin Pasar
            try {
                s.getMutex().acquire();
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            System.out.println("-Ha Pasado Coche " + id + " en dirección " + turnoPasar);
            s.getPasando()[turnoPasar]--;
            if (s.getTurno() == turnoPasar && s.getEsperando()[turnoPasar] != 0) {
                System.out.println("##Coche " + id + " libera tras pasar . " + s.getPasando()[turnoPasar] + " "
                        + s.getSemaforosTurnos()[turnoPasar].getQueueLength());
                s.getSemaforosTurnos()[turnoPasar].release();
            } else if (s.getPasando()[turnoPasar] == 0 && turnoPasar != s.getTurno()
                    && s.getEsperando()[turnoPasar + 1] > 0) {
                System.out.println("$Coche " + id + " libera siguiente Turno. " + s.getPasando()[turnoPasar]);
                s.getSemaforosTurnos()[turnoPasar + 1].release();
            } else {
                System.out.println("%Coche " + id + " no hace nada");
                s.getMutex().release();
            }

            try {
                Thread.sleep(TIEMPO_ESPERA);
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
            // Cambiar de dirección
            turnoPasar = (turnoPasar + 1) % DIRECCIONES;
            try {
                s.getMutex().acquire();
            } catch (InterruptedException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
//			System.out.println("Coche"+id +" vuelve a intentar cruzar en dirección "+turnoPasar);
        }
        System.out.println("FIN coche " + id + " " + s.getMutex().hasQueuedThreads());
        s.getMutex().release();
    }

    /**
     * Método auxiliar que calcula en turno anterior al actual
     * @param turno turno actual
     * @return turno anterior
     */
    private int turnoAnterior(int turno) {
        int anterior = (turno - 1) % 3;
        return (anterior == -1) ? 2 : anterior;
    }

}
