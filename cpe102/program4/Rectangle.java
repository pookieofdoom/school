
import java.awt.Point;


public class Rectangle extends ConvexPolygon
{


   public Rectangle(int width, int height, java.awt.Point position, java.awt.Color color, boolean filled)
   {
      super(new Point[] {position, new Point((int)(position.getX()+width),(int)(position.getY())),
            new Point((int)(position.getX()+width),(int)(position.getY()+height)), 
            new Point((int)(position.getX()),(int)(position.getY()+height))}, color,filled);

   }

   public int getWidth()
   {
      return (int)getVertex(1).getX()-(int)getVertex(0).getX();
   }
   

   
   
  public void setWidth(int width)
  {
     super.setVertex(1, new Point((int)getVertex(0).getX()+width,(int)getVertex(1).getY()));
     super.setVertex(2, new Point((int)getVertex(3).getX()+width,(int)getVertex(2).getY()));
  }
   

   public int getHeight()
   {
      return (int)getVertex(3).getY()-(int)getVertex(0).getY();
   }

   
   public void setHeight(int height)
   {
      super.setVertex(2, new Point((int)getVertex(2).getX(),(int)getVertex(1).getY()+height));
      super.setVertex(3, new Point((int)getVertex(3).getX(),(int)getVertex(0).getY()+height));
   }
   public void setVertex(int index, java.awt.Point vertex)
   {
      throw new UnsupportedOperationException();
   }



}

