
import java.awt.Point;

public class ConvexPolygon extends Shape
{
   private java.awt.Point[]  vertices;

   public ConvexPolygon(java.awt.Point[] vertices, java.awt.Color color, boolean filled)
   {
      super(color,filled);       
      this.vertices = new Point[vertices.length];  
      for(int i=0;i<vertices.length;i++)
      {
         this.vertices[i]= new Point (vertices[i]);
      }
      
   }


   public java.awt.Point getVertex(int index)
   {
      return new Point (this.vertices[index]);
   }

   public void setVertex(int index, java.awt.Point vertex)
   {
      this.vertices[index] = new Point(vertex);
   }

   public boolean equals(Object o)
   {
      if(!super.equals(o))
      {
         return false;
      }
      if(this.vertices.length != ((ConvexPolygon)o).vertices.length)
      {
         return false;
      }
      for (int i=0; i<this.vertices.length;i++)
      {
         if(!(this.vertices[i].equals( ((ConvexPolygon)o).vertices[i])))
         {
            return false;
         }
      }

      return true;
   }

   public double getArea()
   {
      double sum1 =0.0;
      double sum2=0.0;
      for (int i = 0; i<this.vertices.length;i++)
      {
         if(i!=this.vertices.length-1)
         {
            sum1 = sum1 + this.vertices[i].getX()*this.vertices[i+1].getY();
            sum2 = sum2 +this.vertices[i].getY()*this.vertices[i+1].getX();

         }
         else
         {
            sum1 = sum1 + this.vertices[i].getX() * this.vertices[0].getY();
            sum2 = sum2 +this.vertices[i].getY() * this.vertices[0].getX();
         }
      }


      return 0.5 * (sum1-sum2);
   }


   public java.awt.Point getPosition()
   {
      return new Point(this.vertices[0]);
   } 

   public void setPosition(java.awt.Point position)
   {
      int xdiff, ydiff;
      xdiff = (int)position.getX() - (int)this.vertices[0].getX();
      ydiff = (int)position.getY() - (int)this.vertices[0].getY();
      this.vertices[0] = new Point(position);
      for (int i=1; i<this.vertices.length;i++)
      {
         java.awt.Point np = new java.awt.Point(xdiff+(int)this.vertices[i].getX(), 
               ydiff+(int)this.vertices[i].getY());

         this.setVertex(i,np);
      }

   }

   public void move(java.awt.Point delta)
   {
      double x = delta.getX();
      double y = delta.getY();
      for(int i=0; i<this.vertices.length;i++)
      {
         this.vertices[i].setLocation(this.vertices[i].getX() + x, this.vertices[i].getY() + y);
      }
   }



}