  /**
           * Explore.java
           *
           * Anthony Dinh
           * Lab 3 
           */
public class Explore 
{
   public static void main(String[] args)
   {      
      Object ref;
      ref = new MyClass(); // Yes, you can do this, every object in Java is an Object via inheritance - polymorphism!

      // Before you compile and run, can you predicte which method's output you will see, the one for class Object
      // or the one for class MyClass?
      System.out.println(ref.toString());
   }
 
}