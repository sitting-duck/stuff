package countsbinary1sininteger;

import java.io.Console;
import java.util.Scanner;

/**
 *
 * @author Ashley
 */
public class CountsBinary1sInInteger {
    
    static int numBits_Recursive;
    //public static boolean isNumeric(String str);
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args){
        
        while(true)
        {
            System.out.println("This program will count the number of binary 1's in an integer value.");
            System.out.println("Please enter an integer or press x to exit.");
                
        
            Scanner kb = new Scanner(System.in);
            //put the kb input in the string
            String input = kb.next();
            
            if(input.equals("x") || input.equals("X") )
            {
               System.exit(0);
            }
            else
            {
              while(!(isNumeric(input)))
              {
                  System.out.print("Input Invalid. Please enter an integer: ");
                  input = kb.next();                  
              }
                            
              int value = Integer.parseInt(input);
                                                          
              System.out.println("Iterative:");
              System.out.println("The number of 1's in the binary representation of " + input + " is " + CountOnes_Iterative(value));
              
              value = Integer.parseInt(input);
              
              System.out.println("Recursive:");
              System.out.println("The number of 1's in the binary representation of " + input + " is " + CountOnes_Recursive(value));
                                                                      
            }                                                                        
       }          
    }
    
   public static boolean isNumeric(String str)
    {
      return str.matches("-?\\d+(\\.\\d+)?");  //match a number with optional '-' and decimal.
    }
   
   public static int CountOnes_Recursive(int value)
   {
       int returnVal;
       
       if(value == 0)
       {
           returnVal = numBits_Recursive;
           numBits_Recursive = 0;
           return returnVal;           
       }
       else
       {
            numBits_Recursive += value & 1;
            value >>=1;

            return CountOnes_Recursive(value);    
            
       }       
   }
   
   public static int CountOnes_Iterative(int value)
   {
       int numBits;                             
              for(numBits = 0; value != 0; value >>=1)
              {                               
                int isAOne = value & 1;
                numBits += isAOne;                                  
              }
      return numBits;
   }
    
}
