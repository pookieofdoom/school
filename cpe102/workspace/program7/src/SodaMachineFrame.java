/**
 * 
 * 
 * @author Anthony Dinh
 * @version Program 7
 */

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.NumberFormat;
import javax.swing.*;
import javax.swing.border.EtchedBorder;


public class SodaMachineFrame extends JFrame 
{
   private SodaMachine machine;
   private JPanel east, center, west;
   private JTextField depositText, changeText, totalText;
   private JButton coinReturn;
   private JButton button[];
   private NumberFormat nf = NumberFormat.getCurrencyInstance();
   private double change;

   public SodaMachineFrame(SodaMachine machine)
   {
      this.machine = machine; 
      JPanel east = new JPanel();
      JPanel center = new JPanel();
      JPanel west = new JPanel();
      int numSoda = machine.getCount();
      String startMoney = nf.format(0.00);


      //set the size of the panels
      east.setPreferredSize(new Dimension(150,300));
      center.setPreferredSize(new Dimension(150,300));
      west.setPreferredSize(new Dimension(150,300));

      //set the layout of the panels 
      east.setLayout(new GridLayout(5,1));
      center.setLayout(new GridLayout(3,1));
      west.setLayout(new GridLayout(numSoda, 1));

      //set the border of the panels
      east.setBorder(new EtchedBorder());
      center.setBorder(new EtchedBorder());
      west.setBorder(new EtchedBorder());

      //add the panels to the frame
      getContentPane().add(east, BorderLayout.EAST);
      getContentPane().add(center, BorderLayout.CENTER);
      getContentPane().add(west, BorderLayout.WEST);

      //set the frame to be un-resizable
      setResizable(false);


      //adding buttons to the west panel
      button = new JButton[numSoda];
      for(int i=0; i<numSoda; i++)
      {
         button[i] = new JButton();
         button[i].setText(machine.getSodaName(i));
         button[i].setEnabled(false);
         west.add(button[i]);
         button[i].addActionListener(new sodaButton());


      }


      //adding  to east
      JButton nickel = new JButton("Nickel");
      east.add(nickel);
      nickel.addActionListener(new nickelButton());

      JButton dime = new JButton("Dime");
      east.add(dime);
      dime.addActionListener(new dimeButton());

      JButton quarter = new JButton("Quarter");
      east.add(quarter);
      quarter.addActionListener(new quarterButton());

      JButton hd = new JButton("Half Dollar");
      east.add(hd);
      hd.addActionListener(new hdButton());

      JButton dollar = new JButton("Dollar");
      east.add(dollar);
      dollar.addActionListener(new dollarButton());


      //center adding

      //deposit
      JPanel deposit = new JPanel();
      deposit.setLayout(new FlowLayout());
      deposit.setBorder(new EtchedBorder());
      JLabel depositName = new JLabel("Amount Deposited");
      deposit.add(depositName);
      depositText = new JTextField(6);
      depositText.setText(startMoney);
      depositText.setHorizontalAlignment(JTextField.RIGHT);
      depositText.setEditable(false);
      deposit.add(depositText);
      coinReturn = new JButton("Coin Return");
      coinReturn.setEnabled(false);
      deposit.add(coinReturn);
      center.add(deposit);
      coinReturn.addActionListener(new returnButton());


      //change
      JPanel changePanel = new JPanel();
      changePanel.setLayout(new FlowLayout());
      changePanel.setBorder(new EtchedBorder());
      JLabel changeName = new JLabel("Change Returned");
      changePanel.add(changeName);
      changeText = new JTextField(6);
      changeText.setText(startMoney);
      changeText.setHorizontalAlignment(JTextField.RIGHT);
      changeText.setEditable(false);
      changePanel.add(changeText);
      center.add(changePanel);

      //Total Sales
      JPanel total = new JPanel();
      total.setLayout(new FlowLayout());
      total.setBorder(new EtchedBorder());
      JLabel totalName = new JLabel("Total Sales");
      total.add(totalName);
      totalText = new JTextField(6);
      totalText.setText(startMoney);
      totalText.setHorizontalAlignment(JTextField.RIGHT);
      totalText.setEditable(false);
      total.add(totalText);
      center.add(total);







      pack();

   }


   private class nickelButton implements ActionListener
   {

      public void actionPerformed (ActionEvent event)
      {
         machine.deposit(5);
         double count = machine.getDeposits()/100.;
         depositText.setText(nf.format(count));
         changeText.setText(nf.format(0));
         coinReturn.setEnabled(true);
         for(int i=0; i<machine.getCount();i++)
         {
            if(machine.sufficientFunds() && machine.getSodaCount(i) !=0)
            {
               button[i].setEnabled(true);
            }
         }


      }

   }
   private class dimeButton implements ActionListener
   {

      public void actionPerformed(ActionEvent event)
      {
         machine.deposit(10);
         double count = machine.getDeposits()/100.;
         depositText.setText(nf.format(count));
         changeText.setText(nf.format(0));
         coinReturn.setEnabled(true);
         for(int i=0; i<machine.getCount();i++)
         {
            if(machine.sufficientFunds() && machine.getSodaCount(i) !=0)
            {
               button[i].setEnabled(true);
            }
         }
      }
   }

   private class quarterButton implements ActionListener
   {
      public void actionPerformed(ActionEvent event)
      {
         machine.deposit(25);
         double count = machine.getDeposits()/100.;
         depositText.setText(nf.format(count));
         changeText.setText(nf.format(0));
         coinReturn.setEnabled(true);
         for(int i=0; i<machine.getCount();i++)
         {
            if(machine.sufficientFunds() && machine.getSodaCount(i) !=0)
            {
               button[i].setEnabled(true);
            }
         }

      }
   }
   private class hdButton implements ActionListener
   {
      public void actionPerformed(ActionEvent event)
      {
         machine.deposit(50);
         double count = machine.getDeposits()/100.;
         depositText.setText(nf.format(count));
         changeText.setText(nf.format(0));
         coinReturn.setEnabled(true);
         for(int i=0; i<machine.getCount();i++)
         {
            if(machine.sufficientFunds() && machine.getSodaCount(i) !=0)
            {
               button[i].setEnabled(true);
            }
         }
      }
   }

   private class dollarButton implements ActionListener
   {
      public void actionPerformed(ActionEvent event)
      {
         machine.deposit(100);
         double count = machine.getDeposits()/100.;
         depositText.setText(nf.format(count));
         changeText.setText(nf.format(0));
         coinReturn.setEnabled(true);
         for(int i=0; i<machine.getCount();i++)
         {
            if(machine.sufficientFunds() && machine.getSodaCount(i) !=0)
            {
               button[i].setEnabled(true);
            }
         }
      }
   }

   private class sodaButton implements ActionListener
   {

      public void actionPerformed(ActionEvent event)
      {

         for(int i=0; i<machine.getCount();i++)
         {

            if(event.getSource().equals(button[i])) 
            {

               change = machine.dispenseSoda(i)/100.;
               changeText.setText(nf.format(change));
            }


            button[i].setEnabled(false);
         }
         coinReturn.setEnabled(false);

         double totalSales = machine.getSales()/100.;
         totalSales= totalSales + machine.returnDeposits()/100.;
         depositText.setText(nf.format(0));

         totalText.setText(nf.format(totalSales));
      }
   }

   private class returnButton implements ActionListener
   {
      public void actionPerformed(ActionEvent event)
      {
         for(int i=0; i<machine.getCount();i++)
         {
            button[i].setEnabled(false);

         }
         coinReturn.setEnabled(false);
         double change = machine.returnDeposits()/100.;
         changeText.setText(nf.format(change));
         depositText.setText(nf.format(0));

      }
   }

}
