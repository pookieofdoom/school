public interface Shape
{
  /** Calculates the area of the shape.
   *@return Returns the area of the shape as a double.
   */
   public double getArea(); 
   
   
  /** Get the color of the shape.
   * @return Returns the color of the shape.
   */      
   public java.awt.Color getColor(); 
   
   
  /**Sets the color of the shape.
   *@param color The color that the shape will be set to.
   */
   
   public void setColor(java.awt.Color color); 
   
  /**Check if the shape is filled or not.
   *@return Returns true if shape is filled, false if not filled.
   */
   public boolean getFilled(); 
   
  /**Sets the filled state of the shape to the specified value.
   *@param filled A boolean true or false that the shape will be set to.
   */
   public void setFilled(boolean filled);
   
  /**Gets the current position of the shape.
   *@return Return the position of the shape.
   */
   public java.awt.Point getPosition(); 
   
  /**Changes the position of the shape to the specfied Point.
   *@param position The position that the new shape will be set to.
   */
   public void setPosition(java.awt.Point position); 
   
  /**Moves the shape by the x and y amounts specified (in the Point delta).
   *@param delta Moves the shape by x and y component of delta
   */
   public void move(java.awt.Point delta); 
}