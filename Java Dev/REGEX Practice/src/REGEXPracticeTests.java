import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class REGEXPracticeTests {

    REGEXPracticeTests(){}

    public void doTests() throws Exception {

        try{

            testREGEXToGetInitialExpirationDateStringFromDescription();

        }
        catch(Exception e){

            throw e;

        }

    }

    /*
    This test is here in case anything about the way CorduroWalletItem objects are stored ever changes on the back end, this test will let us know if the code
    for extracting the expiration date from the description string attribute is broken.
     */
    public void testREGEXToGetInitialExpirationDateStringFromDescription() throws Exception {

        String testInput = "Name on Card: Ashley Tharp\n" +
                "Credit Card: XXXX-XXXX-XXXX-4705\n" +
                "Expired Date: 2/1/2022 12:00:00 AM";

        String initialExpirationDatePatternString = "(Expired Date: )[0-9]{1,2}/[0-9]{1,2}/[0-9]{4}";


        //create a pattern object
        Pattern initialExpirationDatePattern = Pattern.compile(initialExpirationDatePatternString);

        //now create the matcher object
        Matcher initialExpirationDatematcher = initialExpirationDatePattern.matcher(testInput);

        if(initialExpirationDatematcher.find() == false){
            throw new Exception("did not find proper match for initial expiration date string in CorduroWalletItem description string. Adjust REGEX String.");
        }
        else{

            //get the matching string
            Integer start = initialExpirationDatematcher.start();
            Integer end = initialExpirationDatematcher.end();

            String matchingInitialExpirationDateString = testInput.substring(start, end);

            if(matchingInitialExpirationDateString.equals("Expired Date: 2/1/2022") == false){
                throw new Exception("matcher found improper string: " + matchingInitialExpirationDateString + "  Adjust REGEX String.");
            }

            //now that we've got the initial string, we have to strip "Expired Date: " from it
            matchingInitialExpirationDateString = matchingInitialExpirationDateString.replace("Expired Date: ", "");

            //now we have to get the expiration month, which will be all the number digits starting at the beginning of the string until we hit a '/'
            String expirationMonthPatternString = "[0-9]{1,2}/";

            //create the pattern object for the expiration month
            Pattern expirationMonthPattern = Pattern.compile(expirationMonthPatternString);

            //create the matcher object for the expiration month
            Matcher expirationMonthMatcher = expirationMonthPattern.matcher(matchingInitialExpirationDateString);

            if(expirationMonthMatcher.find() == false){
                throw new Exception("did not find a month string from the extracted expiration date string, adjust your REGEX.");
            }

            //get the matching expiration month string
            start = expirationMonthMatcher.start();
            end = expirationMonthMatcher.end();

            String matchingExpirationMonthString = matchingInitialExpirationDateString.substring(start, end);

            if(matchingExpirationMonthString.equals("2/") == false){
                throw new Exception("found improper string: " + matchingExpirationMonthString + " for month from expiration date string, adjust your REGEX.");
            }

            //now that we've got the expiration month, we can get the expiration year
            String expirationYearString = matchingInitialExpirationDateString.substring(matchingInitialExpirationDateString.length() - 2, matchingInitialExpirationDateString.length());

            if(expirationYearString.equals("22") == false){
                throw new Exception("found improper string for year from expiration date string, fix your code");
            }

            System.out.println("PASSED: regex string found appropriate initial expiration date string");

        }


    }

}
