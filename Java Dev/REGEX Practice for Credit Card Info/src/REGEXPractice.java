public class REGEXPractice {

    public static void main(String [] args){

        REGEXPracticeTests regexPracticeTests = new REGEXPracticeTests();

        try{

         regexPracticeTests.doTests();

        }
        catch(Exception e){

            System.out.println(e.getMessage());

        }


    }




}
