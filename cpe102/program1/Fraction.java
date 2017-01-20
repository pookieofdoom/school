   /**
           * Fraction class
           * 
           * @author Anthony Dinh   
           * @version Program 1    
           */
public class Fraction
{

   //instance variable
   private int numerator;
   private int denominator; 
   
   //constructor
   public Fraction()
   {
      numerator = 0;
      denominator = 1;
   }
   public Fraction(int numerator)
   {
      this.numerator = numerator;
      denominator = 1;
   }
   public Fraction (int numerator, int denominator)    
   {
      int div;
      this.numerator = numerator;
      this.denominator = denominator;
      if(this.denominator <=0)
      {
       throw new IllegalArgumentException();
      }
      div =gcd(this.numerator, this.denominator);
      
      this.numerator = this.numerator/div;
      this.denominator = this.denominator/div;
      
   }
   //methods
   public Fraction add(Fraction other)
   {
      int multdenom = this.denominator * other.denominator;
      int multnum1 = this.numerator * other.denominator;
      int multnum2 = other.numerator * this.denominator;
      return new Fraction (multnum1 + multnum2, multdenom);
   }
   
   public Fraction div(Fraction other)
   {
      int x = this.numerator * other.denominator;
      int y = this.denominator * other.numerator;
      if(y <0)
      {
         y = y * -1;
         x = x * -1;
      }
      
         return new Fraction (x,y);
     
   }
   
   public boolean equals(Fraction other)
   {
      if (this.numerator != other.numerator)
      {
         return false;
      }
      if(this.denominator != other.denominator)
      {
         return false;
      }
      return true;
   }
   
   public int getDenominator()
   {
      
      return denominator;
   }
   
   public int getNumerator()
   {
    
      return numerator;
   }
   
   public Fraction mul(Fraction other)
   {
      int x = this.numerator * other.numerator;
      int y = this.denominator * other. denominator;
      return new Fraction (x,y);
   }
   
   public Fraction sub(Fraction other)
   {
      int multdenom = this.denominator * other.denominator;
      int multnum1 = this.numerator * other.denominator;
      int multnum2 = other.numerator * this.denominator;
      return new Fraction (multnum1 - multnum2, multdenom);
   }
   
   public java.lang.String toString()
   {
      if (this.denominator ==1)
      {
         return Integer.toString(this.numerator);
      }
      else
      {
         return Integer.toString(this.numerator) +"/"+Integer.toString(this.denominator);
      }
   }
   
   public double value()
   {
      return this.numerator * 1.0 / this.denominator;
   }

   // used wikipedia to help code the algorithm for gcd
   //http://en.wikipedia.org/wiki/Euclidean_algorithm
   private int gcd(int numerator, int denominator)
   {
      int a,b,c;
      a = Math.abs(numerator);
      b = Math.abs(denominator);
      boolean found = false;
      while(found == false) 
      {
         c = b;
         b = a%b;
         a = c;
         if(b ==0)
         {
            found =true;
         }
               
      }
      return a;
   }
   
}


            
