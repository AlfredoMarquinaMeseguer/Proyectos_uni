package ejercicio2;


/**
 * Clase donde de encuentra el main del ejercicio
 */
public class Ejercicio2 {

	/**
	 * El problema
	 * @param args no se utiliza
	 */
	public static void main(String[] args) {
		SemaforoCarretera semaforo = new SemaforoCarretera(); // Semáforo que coordina
		Coche[] procesosCoches = new Coche[100]; // Los proceso que simulan coches
		Peaton[] procesosPeatones = new Peaton[50]; // Los procesos que simular peatones

		System.out.println("Contruyendo procesos");
		// Los primeros cincuenta coches empiezan en la dirección Norte-Sur (0)
		for (int i = 0; i < 50; i++)
			procesosCoches[i] = new Coche(semaforo, 0, i);

		// Los restantes empiezan en la dirección Este-Oeste (1)
		for (int i = 50; i < 100; i++)
			procesosCoches[i] = new Coche(semaforo, 1, i);

		// Definición de los peatones que pasan por el paso de cebra
		for (int i = 0; i < 50; i++)
			procesosPeatones[i] = new Peaton(semaforo, i);

		System.out.println("Comenzando Ejecución");

		// Lanzamos procesos
		semaforo.start();
		for (int i = 0; i < procesosCoches.length; i++)
			procesosCoches[i].start();

		for (int i = 0; i < procesosPeatones.length; i++)
			procesosPeatones[i].start();

		// Esperamos que terminen
		try {
			semaforo.join();
			for (int i = 0; i < procesosCoches.length; i++)
				procesosCoches[i].join();

			for (int i = 0; i < procesosPeatones.length; i++)
				procesosPeatones[i].join();
		} catch (Exception e) {
			e.printStackTrace();
		}
		System.out.println("\n\nFin de la ejecución");
	}
}
