
public abstract class Shape implements java.lang.Comparable<Shape>
{

   private java.awt.Color color;
   private boolean filled; 
   public Shape(java.awt.Color color, boolean filled)
   {
      this.color = color;
      this.filled = filled;
   }


   /** Calculates the area of the shape.
    *@return Returns the area of the shape as a double.
    */
   public abstract double getArea(); 


   /** Get the color of the shape.
    * @return Returns the color of the shape.
    */      
   public java.awt.Color getColor()
   {
      return this.color;
   } 


   /**Sets the color of the shape.
    *@param color The color that the shape will be set to.
    */

   public void setColor(java.awt.Color color)
   {
      this.color = color;
   }

   /**Check if the shape is filled or not.
    *@return Returns true if shape is filled, false if not filled.
    */
   public boolean getFilled()
   {
      return this.filled;
   } 

   /**Sets the filled state of the shape to the specified value.
    *@param filled A boolean true or false that the shape will be set to.
    */
   public void setFilled(boolean filled)
   {
      this.filled = filled;
   }

   /**Gets the current position of the shape.
    *@return Return the position of the shape.
    */
   public abstract java.awt.Point getPosition(); 

   /**Changes the position of the shape to the specfied Point.
    *@param position The position that the new shape will be set to.
    */
   public abstract void setPosition(java.awt.Point position); 

   /**Moves the shape by the x and y amounts specified (in the Point delta).
    *@param delta Moves the shape by x and y component of delta
    */
   public abstract void move(java.awt.Point delta); 

   public int compareTo(Shape a)
   {
      String className1 = this.getClass().getName();
      String className2 = a.getClass().getName();

      if(className1.compareTo(className2) < 0)
      {
         return -69;
      }
      if(className1.compareTo(className2) ==0 && this.getArea() < a.getArea())
      {
         return -69;
      }

      if(className1.compareTo(className2) ==0 && 
            (this.getArea() == a.getArea() || this.getArea() == (getArea() +0.0001) 
            || this.getArea() == (a.getArea() -0.0001)))//can use abs
      {
         return 0;
      }

      return 69;

   }

   public boolean equals(Object a)
   {
      if(a==null)
      {
         return false;
      }
      if(this.getClass() != a.getClass())
      {
         return false;
      }

      if(!this.color.equals(((Shape)a).color))
      {
         return false;
      }
      if(this.filled != ((Shape)a).filled)
      {
         return false;
      }

      return true;
   }
}