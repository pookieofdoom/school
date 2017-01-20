
import java.awt.Point;

public class Triangle extends ConvexPolygon
{
   
   public Triangle (Point a, Point b,Point c, java.awt.Color color, 
      boolean filled)
   {
      super(new Point[] {a,b,c},color, filled); 
   }
   
   public Point getVertexA()
   {
      return super.getVertex(0);
   }
   
   public void setVertexA(Point point)
   {
      super.setVertex(0,point);
   }
   
   public Point getVertexB()
   {
      return super.getVertex(1);
   }
   
   public void setVertexB(Point point)
   {
      super.setVertex(1,point);
   }
   
   public java.awt.Point getVertexC()
   {
      return super.getVertex(2);
   }
   
   public void setVertexC(Point point)
   {
      super.setVertex(2,point);
   }

   public double getArea()
   {
      double x = getVertex(0).getX()*(getVertex(1).getY() - getVertex(2).getY()) + getVertex(1).getX()*(getVertex(2).getY() - getVertex(0).getY()) 
         + getVertex(2).getX()*(getVertex(0).getY() - getVertex(1).getY());
      return Math.abs(x/2.0);    
   }
   

   
}
