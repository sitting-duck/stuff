import java.util.ArrayList;


public class Attribute {

	private String name = null;
	
	private int numTrue = 0;
	
	private int numFalse = 0;
	
	private int numTrueTrue = 0;
	
	private int numTrueFalse = 0;
	
	private int numFalseTrue = 0;
	
	private int numFalseFalse = 0;
	
	ArrayList<Integer> valueList = null;
	
	Attribute(String _name){name = _name; valueList = new ArrayList<Integer>();}
	
	public String getName(){return name;}
	
	public int getNumTrue(){return numTrue;}
	
	public int getNumFalse(){return numFalse;}
	
	public int getNumTrueTrue(){return numTrueTrue;}
	
	public int getNumTrueFalse(){return numTrueFalse;}
	
	public int getNumFalseTrue(){return numFalseTrue;}
	
	public int getNumFalseFalse(){return numFalseFalse;}
	
	public ArrayList<Integer> getValueList(){return valueList;}
	
	public void plusOneTrue(){numTrue++;}
	
	public void plusOneFalse(){numFalse++;}
	
	public void plusOneTrueTrue(){numTrueTrue++;}
	
	public void plusOneTrueFalse(){numTrueFalse++;}
	
	public void plusOneFalseTrue(){numFalseTrue++;}
	
	public void plusOneFalseFalse(){numFalseFalse++;}
	
}
