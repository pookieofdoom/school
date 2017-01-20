import javax.swing.*;
import java.awt.Event.*;
import java.awt.*;
public class ButtonTextField 
{
   public static void main(String[] args)
   {
      JFrame frame = new JFrame();
      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      
      JButton button = new JButton("Push Me!");
      JTextField text = new JTextField(15);
      text.setText("Hello World!");
      
      JPanel contentPane = (JPanel)frame.getContentPane();
      contentPane.add(button);
      contentPane.add(text);
      
      contentPane.setLayout(new FlowLayout());
      
      frame.pack();
      frame.setVisible(true);
   }
}
