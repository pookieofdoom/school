


public class Canvas 
{
   private java.util.ArrayList<Shape> list;

   public Canvas()
   {
      list = new java.util.ArrayList<Shape>();
   }
   
   public void add(Shape shape)
   {
      this.list.add(shape);
   }
   
   public Shape remove(int index)
   {
      if(index > list.size()-1)
      {
         return null;
      }
      Shape temp;
      temp = this.list.remove(index);
      return temp;
   }
   
   public Shape get(int index)
   {
      return this.list.get(index);
   }
   
   public int size()
   {
     
      return this.list.size();
   }
   
   public java.util.ArrayList<Circle> getCircles()
   {
      
      java.util.ArrayList<Circle> newlist = new java.util.ArrayList<Circle>();
      for(int i=0; i<this.list.size();i++)
      {
         
         if(this.list.get(i) instanceof Circle)
         {
            newlist.add((Circle)this.list.get(i));
            
         }
      }
      return newlist;
   }
   
   public java.util.ArrayList<Rectangle> getRectangles()
   {
      
      java.util.ArrayList<Rectangle> newlist = new java.util.ArrayList<Rectangle>();
      for(int i=0; i<this.list.size();i++)
      {
         
         if(this.list.get(i) instanceof Rectangle && !(this.list.get(i) instanceof Square))
         {
            newlist.add((Rectangle)this.list.get(i));
            
         }
      }
      return newlist;
   }
   
   public java.util.ArrayList<Triangle> getTriangles()
   {
      
      java.util.ArrayList<Triangle> newlist = new java.util.ArrayList<Triangle>();
      for(int i=0; i<this.list.size();i++)
      {
         
         if(this.list.get(i) instanceof Triangle)
         {
            newlist.add((Triangle)this.list.get(i));
            
         }
      }
      return newlist;
   } 
   
   public java.util.ArrayList<ConvexPolygon> getConvexPolygons()
   {
      
      java.util.ArrayList<ConvexPolygon> newlist = new java.util.ArrayList<ConvexPolygon>();
      for(int i=0; i<this.list.size();i++)
      {
         
         if(this.list.get(i) instanceof ConvexPolygon && !(this.list.get(i) instanceof Rectangle)
               && !(this.list.get(i) instanceof Square) && !(this.list.get(i) instanceof Triangle))
         {
            newlist.add((ConvexPolygon)this.list.get(i));
            
         }
      }
      return newlist;
   } 
   
   public java.util.ArrayList<Shape> getShapesByColor(java.awt.Color color)
   {
      
      java.util.ArrayList<Shape> newlist = new java.util.ArrayList<Shape>();
      for(int i=0; i<this.list.size();i++)
      {
         if(this.list.get(i).getColor() == color)
         {
            newlist.add(this.list.get(i));
            
         }
      }
      return newlist;
   }
   
   public double getAreaOfAllShapes()
   {
      double sum = 0.0;
      for(int i=0; i<this.list.size();i++)
      {
         sum = list.get(i).getArea() + sum;
      }
      return sum;
   }

}
      
   
