package ejercicio1;

/**
 * Procesos que lee una porción del array de lectura y calcula un subtotal que acaba colocando en el array de escritura
 */
public class Consumidor extends Thread {
	private final int processId;
	private final int inicioArrayLectura;
	private final int finArrayLectura;

	/**
	 * Constructor con los datos exclusivos del proceso concreto
	 * @param processId el id del proceso
	 * @param inicioArrayLectura el inicio del trozo que puede acceder
	 * @param finArrayLectura el fin del trozo que puede acceder
	 */
	public Consumidor(int processId, int inicioArrayLectura, int finArrayLectura) {
		super();
		this.processId = processId;
		this.inicioArrayLectura = inicioArrayLectura;
		this.finArrayLectura = finArrayLectura;
	}

	 @Override
	public void run() {

		Ejercicio1.cerrojo.lock();
        try {
			while(Ejercicio1.turno != 1){
				Ejercicio1.cerrojo.unlock();
				Ejercicio1.cerrojo.lock();
			}
        } finally {
			Ejercicio1.cerrojo.unlock();
        }
        int operacion;
		int temp;
		int total = Ejercicio1.arrayLectura[inicioArrayLectura];

		for (int i = inicioArrayLectura + 2; i <= finArrayLectura; i+=2) {
			temp = Ejercicio1.arrayLectura[i];
			operacion= Ejercicio1.arrayLectura[i-1];
			total = calcular(total, temp, operacion);
		}
		Ejercicio1.arrayEscritura[processId] = total;

		Ejercicio1.cerrojo.lock();
		Ejercicio1.consumidoresEjecutando--;
		if (Ejercicio1.consumidoresEjecutando == 0)
			Ejercicio1.turno = 2;
		Ejercicio1.cerrojo.unlock();

		Ejercicio1.lockPrint.lock();
		System.out.println("***************\nProceso terminado: " + processId + "\nDa como resultado: " + total
				+ "\n***************");
		Ejercicio1.lockPrint.unlock();

	}

	/**
	 * Método auxiliar que calcula una opearación entre dos número
	 * @param num1 primer número de la operación
	 * @param num2 segundo número de la operación
	 * @param operacion operación a realizar
	 * @return el resultado
	 */
	private int calcular(int num1, int num2, int operacion) {
		int total;

		try {
			switch (operacion) {
			case 1:
				total = num1 + num2;
				break;
			case 2:
				total = num1 - num2;
				break;

			case 3:
				total = num1 * num2;
				break;
			default:
				throw new IllegalArgumentException("Error calculando la operacion " + num1 + " " + num2 + " "
						+ operacion + " En el proceso " + processId);
			}
		} catch (Exception e) {
			e.printStackTrace();
			total = 0;
		}
		return total;
	}
}
