import javax.swing.*;
import java.awt.event.*;
import java.awt.*;
public class ButtonTextFieldEvent 
{
   public static void main(String[] args)
   {
      JFrame frame = new JFrame();
      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
      
      JButton button = new JButton("Push Me!");
      
      final JTextField text = new JTextField(15);
      text.setText("0");
      
      JPanel contentPane = (JPanel)frame.getContentPane();
      contentPane.add(button);
      contentPane.add(text);
      
      contentPane.setLayout(new FlowLayout());
      
      class MyListener implements ActionListener
      {
         private int count = 0;
         public void actionPerformed(ActionEvent event)
         {
            count++;
            text.setText(Integer.toString(count));
         }
      }
      button.addActionListener(new MyListener());
      frame.pack();
      frame.setVisible(true);
   }
}
