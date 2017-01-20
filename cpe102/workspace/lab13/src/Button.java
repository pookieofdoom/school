import javax.swing.*;
public class Button 
{
   public static void main(String[] args)
   {
      JFrame frame = new JFrame();
      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      
      JButton button = new JButton("Push Me!");
      
      JPanel contentPane = (JPanel)frame.getContentPane();
      contentPane.add(button);
      
      frame.pack();
      frame.setVisible(true);
   }
   
}
