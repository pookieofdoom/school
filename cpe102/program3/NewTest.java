public class NewTest
{
   public static void main(String[] args)
   {
      java.awt.Color color = new java.awt.Color(5);
      java.awt.Point point = new java.awt.Point(1,5);
      Circle a = new Circle (69.0, point, color, true);
      Circle b= new Circle (69.0, point, color, true);
    
      if(!(a.equals(b)))
      {
         System.out.println("These circles are not equal");
      }
      java.awt.Point point2 = new java.awt.Point (1,6);
      
      b.setPosition(point2);
      if((a.equals(b)))
      {
         System.out.println("These circles shouln't be equal ");
      }
      
      Rectangle c = new Rectangle(6,9,point,color,true);
      Rectangle d = new Rectangle(6,9,point,color,true);
      
      if(!(c.equals(d)))
      {
         System.out.println("These rectangles are not equal");
      }
      
      d.setPosition(point2);
      if((c.equals(d)))
      {
         System.out.println("These rectangles shouln't be equal ");
      }
      java.awt.Point point3 = new java.awt.Point(6,9);
      
      Triangle e = new Triangle (point,point2,point3,color,true);
      Triangle f = new Triangle (point,point2,point3,color,true);
      
      if(!(e.equals(f)))
      {
         System.out.println("These triangles are not equal");
      }
      
      if(e.getArea() != 2.5)
      {
         System.out.println("Error Area: " +e.getArea());
      } 
      
      if(f.getArea() != 2.5)
      {
         System.out.println("Error Area: " +f.getArea());
      } 
      java.awt.Point point4 = new java.awt.Point(9,6);
      f.setVertexC(point4);
      if((e.equals(f)))
      {
         System.out.println("These triangles shouldn't be equal ");
      }
      
      if(f.getArea() != 4.0)
      {
         System.out.println("Error Area: " +f.getArea());
      } 
      
      
      


      
   }
}