public class Test {
   public static void main(String[] args) {
      java.awt.Color color = new java.awt.Color(5);
      java.awt.Point[] vertices = {
         new java.awt.Point(1, 1),
         new java.awt.Point(5, 1),
         new java.awt.Point(5, 5),
         new java.awt.Point(1, 5),
      };
      
      java.awt.Point[] vertices2 = {
         new java.awt.Point(1, 1),
         new java.awt.Point(5, 1),
         new java.awt.Point(5, 5),
         new java.awt.Point(1, 5),
      };

      

      ConvexPolygon cp = new ConvexPolygon(vertices, color, true);
      ConvexPolygon a = new ConvexPolygon(vertices2,color,true);
      
      if(cp.getArea() != 16) {
         System.out.println("Error Area: " + cp.getArea());
      }

      if(!(cp.equals(a)))
      {
         System.out.println("These convex polygons are not equal");
      }
      
      java.awt.Point point4 = new java.awt.Point(9,6);
      a.setVertex(0,point4);
      
      if((cp.equals(a)))
      {
         System.out.println("These convex polygons shouldn't be equal ");
      }

      
      vertices = new java.awt.Point[]{
         new java.awt.Point(-3, 3),
         new java.awt.Point(11, 2),
         new java.awt.Point(16, 11),
         new java.awt.Point(0, 12),
      };

      cp = new ConvexPolygon(vertices, color, true);
      if(cp.getArea() != 139) {
         System.out.println("Error Area: " + cp.getArea());
      }


   }
}