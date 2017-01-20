public class Test
{
   public static void main(String[] args)
   {
      A a1 = new C();
      A a2 = new D();
      B b1 = new D();
      B b2 = new E();
      C c = new C();
      D d = new D();
      E e = new E();
      d.methodD((D)b1);
      //d.methodD((D)b2);
      //d = a1;
      //d = a2;
      b1 = new E();
      b2 = new E();
      //b1 = (D)c;
      //b2 = (D)c;
      //b1.methodD(d);
      //b2.methodD(d);
      
      //((D)b1).methodD(d);
      //((D)b2).methodD(d);
      
      a1 = c;
      a2 = c;
      b1.methodB();
      b2.methodB();
      //b1 = new B();
      //b2 = new B();
      e.methodB();
   }
}