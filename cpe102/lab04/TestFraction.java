/**
           * Test Driver for Fraction Classes
           * 
           * @author Anthony Dinh   
           * @version Lab 4      
           */

public class TestFraction
{
 
   public static void testGetNumerator()
   {
      Fraction a;
      int x = 70;
      a = new Fraction(x,1);
     
      if (a.getNumerator() != 70)
      {
         System.out.println("Error testGetNumerator: Expected 70, found " +a.getNumerator());
      }
     
   }
   
    public static void testGetDenominator()
   {
      Fraction a;
      int x = 69;
      a = new Fraction(1,x);
     
      if (a.getDenominator() != 69)
      {
         System.out.println("Error testGetDenominator: Expected 69, found " +a.getDenominator());
      }
     
   }
   
   public static void testFraction1()
   {
      Fraction a = new Fraction();
      
      if (a.getNumerator() != 0)
      {
         System.out.println("Error testFraction1: Expected default 0, found " +a.getNumerator());
      }
      if (a.getDenominator() !=1)
      {
         System.out.println("Error testFraction1: Expected default 1, found " +a.getDenominator());
      }
   }
   
   public static void testFraction2()
   {
      Fraction a = new Fraction(5,0);
      
      if (a.getNumerator() !=5)
      {
         System.out.println("Error testFraction2: Expected 5, found " +a.getNumerator());
      }
      if (a.getDenominator() !=1)
      {
         System.out.println("Error testFraction1: Expected default 1, found " +a.getDenominator());
      }
   }
   
   public static void testFraction3()
   {
      Fraction a = new Fraction (2,4);
      if (a.getNumerator() != 1)
      {
         System.out.println("Error testFraction3: Expected 1, found " +a.getNumerator());
      }
      if (a.getDenominator() !=2)
      {
         System.out.println("Error testFraction3: Expected 2, found " +a.getDenominator());
      }
   }
   
   public static void testAdd()
   {
      Fraction a,b,c;
      int x = 1;
      int y = 4;
      int z = 2;
      int t = 5;
      int expectedNumerator = 2;
      int expectedDenominator = 5;
      a = new Fraction(x,y);
      b = new Fraction(z,t);
      c = a.add(b);
     
      if (c.getNumerator() != expectedNumerator)
      {
         System.out.println("Error testAdd Numerator: Expected 2, found " +c.getNumerator());
      }
      if (c.getDenominator() != expectedDenominator)
      {
         System.out.println("Error testAdd Demoninator: Expected 5, found " +c.getDenominator());
      }
   }
 
 
   public static void testDiv()
   {
      Fraction a,b,c;
      int x,y,z,t;
      x = 1;
      y = 4;
      z = 3;
      t = 2;
      a = new Fraction (x,y);
      b = new Fraction (z,t);
      c = a.div(b);
     
      if (c.getNumerator() != 1)
      {
         System.out.println("Error testDiv Numerator: Expected 1, found " +c.getNumerator());
      }
      if (c.getDenominator() !=6)
      {
         System.out.println("Error testDiv Denomintaor: Expected 6, found " +c.getDenominator());
      }
   }
   
   public static void testEquals()
   {
      Fraction a,b,c,d;
      a = new Fraction (1,4);
      b = new Fraction (1,4);
     
     
      if ( a.equals(b) == false)
      {
         System.out.println("Error testEquals: Expected true, found " +a.equals(b));
      }      
      else
      {
         System.out.println("testEquals found true!");
      }
   }
   
   public static void testMul()
   {
      Fraction a,b,c;
      a = new Fraction (1,2);
      b = new Fraction (5,6);
      c = a.mul(b);
      
      if (c.getNumerator() != 5)
      {
         System.out.println("Error testMul Numerator: Expected 5, found " +c.getNumerator());
      }
      if (c.getDenominator() != 12)
      {
         System.out.println("Error testMul Denominator: Expected 12, found " +c.getDenominator());
      }
   }
   
   public static void testSub()
   {
      Fraction a,b,c;
      a = new Fraction(1,2);
      b = new Fraction(1,4);
      c = a.sub(b);
      
      if (c.getNumerator() != 1)
      {
         System.out.println("Error testSub Numerator: Expected 1, found " +c.getNumerator());
      }
      if (c.getDenominator() !=4)
      {
         System.out.println("Error testSub Denominator: Expected 4, found " +c.getDenominator());
      }
   } 
   
   public static void testToString()
   {
      Fraction a,b;
      a = new Fraction (1,2);
      b = new Fraction (4,1);
      if (a.toString() != "1/2")
      {
         System.out.println("Error testToString1: Expected 1/2, found " +a.toString());
      }
      
      if (b.toString() != "4")
      {
         System.out.println("Error testtoString2: Expected 4, found " +b.toString());
      }
   }
   
   public static void testValue()
   {
      Fraction a,b;
      double x,y;
      a = new Fraction (1,2);
      x = 1./2;
      b = new Fraction (4,1);
      y = 4.0;
      
      if (a.value() != x)
      {
         System.out.println("Error testValue: Expected " +x +", found " +a.value());
      }
      
      if (b.value() !=y)
      {
         System.out.println("Error testValue: Expected " +y +", found " +b.value());
      } 
    
   }
      
 
   public static void main(String[] args)
   {
      testFraction1();
      testFraction2();
      testFraction3();
      testGetNumerator();
      testGetDenominator();
      testAdd();
      testDiv();
      testEquals();
      testMul();
      testSub();
      testToString();
      testValue();
   }
}