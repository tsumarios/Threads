/******************************************
 *
 *  Title:  Simple Java Threads Implementation
 *  Author: zMrDevJ
 *  Date: 12/21/2017
 *
 *****************************************/

/* Main class */
public class MyThread{

	/* Main */
	public static void main(String[] args) {
		/* Shared data */
		Shared shared = new Shared();

		/* Create threads */
		Thread t1 = new Thread(new T1(shared), "t1");
		Thread t2 = new Thread(new T2(shared), "t2");

		/* Start threads */
		t1.start();
		t2.start();

		/* Wait for threads end */
		try{
			t1.join();
			t2.join();
		}catch(InterruptedException ie){
			ie.printStackTrace();
		}

	}
}

/* Shared data and mutex class */
class Shared{
	int shared = 100;

	/* Synchronized method */
	public synchronized void method(){
		/* Get thread name */
		String thread = Thread.currentThread().getName();
		System.out.println("Thread: " + thread);
	}
}

/* Thread 1 class */
class T1 implements Runnable{
	/* Shared data */
	Shared shared;

	/* Constructor */
	public T1(Shared shared) { this.shared = shared; }

	/* Run method */
	public void run(){
		try{
			Thread.sleep(100);
		}catch(InterruptedException ie){
			ie.printStackTrace();
		}

		shared.method();
	}
}

/* Thread 2 class */
class T2 implements Runnable{
	/* Shared data */
	Shared shared;

	/* Constructor */
	public T2(Shared shared) { this.shared = shared; }

	/* Run method */
	public void run(){
		try{
			Thread.sleep(100);
		}catch(InterruptedException ie){
			ie.printStackTrace();
		}

		shared.method();
	}
}
