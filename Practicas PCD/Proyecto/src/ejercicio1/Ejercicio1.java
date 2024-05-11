package ejercicio1;

import java.util.concurrent.locks.ReentrantLock;

/**
 * Clase principal que contine el main y las variables compartidas
 */
public class Ejercicio1 {
	public static ReentrantLock lockPrint = new ReentrantLock();
	public static ReentrantLock cerrojo = new ReentrantLock();

	public static Integer[] arrayLectura = new Integer[110];
	public static Integer[] arrayEscritura = new Integer[10];
	public static int consumidoresEjecutando = 10;
	// Como con Reentrant lock no se puede crear un semáforo nulo, que sería lo necesario para sincronizar los procesos
	// lo sustituimos por una variable turno que se va actualizando conforme terminan los turnos.
	public static int turno = 0;

	/**
	 * El problema
	 * @param args lo que quieras, no se usa
	 */
	public static void main(String[] args) {
		Consumidor[] procesos = new Consumidor[10];
		Generador generador = new Generador();
		Sumador sumador = new Sumador();

		System.out.println("Comienzo");

		System.out.println("Creando procesos");
		for (int i = 0; i < 10; i++) {
			procesos[i] = new Consumidor(i, i * 11, (i + 1) * 11 - 1);
		}

		System.out.println("Ejecutando procesos");
		sumador.start();
		for(Consumidor p: procesos) p.start();
		generador.start();

		try {
			generador.join();
			for (Consumidor p: procesos) p.join();
			sumador.join();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		System.out.println("Fin de ejecución de procesos.");

		System.out.println("Array Lectura:[");
		for (Integer i : arrayLectura)
			System.out.print(i + ", ");
		System.out.print("].\nArray Escritura:[");
		for (Integer i : arrayEscritura)
			System.out.print(i + ",");
		System.out.println("].");
	}
}
