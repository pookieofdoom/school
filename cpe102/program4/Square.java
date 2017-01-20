
import java.awt.Point;

public class Square extends Rectangle
{
   public Square(int sideLength, Point position, java.awt.Color color, boolean filled)
   {
      super(sideLength, sideLength, position,color,filled);
   }
   
   public int getSize()
   {
      return (int)getVertex(1).getX()-(int)getVertex(0).getX();
   }
   
   public void setSize(int size)
   {
      super.setHeight(size);
      super.setWidth(size);
   }
   
   public void setHeight(int height)
   {
      super.setHeight(height);
      super.setWidth(height);
   }
   public void setWidth(int width)
   {
      super.setHeight(width);
      super.setWidth(width);
   }
}

   