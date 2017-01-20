
public class RunTimes 
{
	public static void main(String[] args)
	{
		long startTime;
		long endTime;
		long runtime;
		long N;
		System.out.println("Logarithmic algorithm's running times: ");
		for(N = 10000; N<100000000;N=N*2)
		{
			startTime = System.nanoTime();
			Algorithms.logarithmicAlgTime(N);
			endTime = System.nanoTime();
			runtime = (endTime - startTime) / 1000000;
			System.out.println("T(" +N +") = " +runtime);
			
		}
		
		System.out.println("\nLinear algorithm's running times: ");
		for(N = 10000;N<100000000;N=N*2)
		{
			startTime = System.nanoTime();
			Algorithms.linearAlgTime(N);
			endTime = System.nanoTime();
			runtime = (endTime - startTime) / 1000000;
			System.out.println("T(" +N +") = " +runtime);
		}
		
		System.out.println("\nNlogN algorithm's running times: ");
		for(N = 10000;N<100000000;N=N*2)
		{
			startTime = System.nanoTime();
			Algorithms.NlogNAlgTime(N);
			endTime = System.nanoTime();
			runtime = (endTime - startTime) / 1000000;
			System.out.println("T(" +N +") = " +runtime);
		}
		
		System.out.println("\nQuadratic algorithm's running times: ");
		for(N = 10000;N<400000;N=N*2)
		{
			startTime = System.nanoTime();
			Algorithms.quadraticAlgTime(N);
			endTime = System.nanoTime();
			runtime = (endTime - startTime) / 1000000;
			System.out.println("T(" +N +") = " +runtime);
		}
	}

}
