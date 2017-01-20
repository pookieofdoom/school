
public class Algorithms 
{
	public static void linearAlgTime(long N)
	{
		for(long i=1; i<N;i++)
		{
			int x = 1;
		}
	}
	
	public static void quadraticAlgTime(long N)
	{
		for(long i=1; i<N; i++)
		{
			for(long j=1; j<N; j++)
			{
				int x = 1;
			}
		}
	}
	
	public static void logarithmicAlgTime(long N)
	{
		for(long i =N;i>1;i=i/2)
		{
			int x = 1;
		}
	}
	
	public static void NlogNAlgTime(long N)
	{
		for(long i =1; i<N; i++)
		{
			for(long j = N; j>1; j=j/2)
			{
				int x = 1;
			}
		}
	}
}
