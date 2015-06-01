
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.StringTokenizer;


public class ID3 {

	
	/**
	 * List of Attributes and num true and false values that will be taken from training file.
	 */
	private ArrayList<Attribute> mTrainingAttributeList = null;
	
	/**
	 * List of Attributes and num true and false values that will be taken from testing file.
	 */
	private ArrayList<Attribute> mTestingAttributeList = null;
	
	private ArrayList<Attribute> treeNodes = null;
	
	/**
	 * Root node will contain the Attribute that is chosen to be the root node based on the value of its information gain
	 */
	Node root;
		
	/**
	 * @param args
	 * the user should enter two file names.  The first file should contain the training data, the second file should contain the testing data
	 */
	public static void main(String[] args) {
		
		//if the user did not specify the two file names in the program call on the terminal, then we'll have to collect them here
		/*if(args.length != 2){
			Scanner scanIn = new Scanner(System.in);
			String input;
			System.out.print("Please enter the name of the file that you want to use for training data: ");
			String trainingFile = scanIn.nextLine();			
			System.out.print("Please enter the name of the file that you want to use for testing data: ");
			String testingFile = scanIn.nextLine();	
			ID3 id3 = new ID3(trainingFile, testingFile);
		}else{
		ID3 id3 = new ID3(args[0], args[1]);
		}*/
		
		ID3 id3 = new ID3("train-win.dat", "test-win.dat");
		id3.createTree();
		System.out.println("\n\ntree:");
		for(int i = 0; i < id3.getTree().size(); i++){
			System.out.print(" " + id3.getTree().get(i).getName() + " ");
		}
		System.out.println();
	}
	
	/**
	 * ID3 constructor takes two filenames as parameters.  The first file should contain training data and the second file should contain testing data 
	 * @param _trainingFile, String referring to the filename of the file containing the training data
	 * @param _testingFile String referring to the filename of the file containing the testing data
	 */
	ID3(String _trainingFile, String _testingFile){
					
		mTrainingAttributeList = new ArrayList<Attribute>();
		mTestingAttributeList = new ArrayList<Attribute>();
		treeNodes = new ArrayList<Attribute>();
		root = new Node();
		
		System.out.print("Training File: \n\t");
		getAttributesFromFile(_trainingFile, mTrainingAttributeList);
		System.out.print("Testing File: \n\t");
		getAttributesFromFile(_testingFile, mTestingAttributeList);		
	}
	
	
	public void createTree(){
		
		int round = 0;
		while(mTrainingAttributeList.size() > 0){
			
			System.out.println("\n\nround: " + round);
			
			double currentInformationGain = -1;
			double currentHighestInformationGain = -1;
			int currentBestAttribute = -1;
			Attribute tempAttr;
			
			//calculate the information gain for each attribute and select the one with the highest information gain
			for(int i = 0; i < mTrainingAttributeList.size(); i++){
				currentInformationGain = calculateInformationGain(mTrainingAttributeList.get(i));
				tempAttr =  mTrainingAttributeList.get(i);
				System.out.println(tempAttr.getName() +  " igain: " +  currentInformationGain + " true: " + tempAttr.getNumTrue() + " false: " + tempAttr.getNumFalse() + " diff: " + Math.abs(tempAttr.getNumFalse() - tempAttr.getNumTrue()));
				if(currentInformationGain > currentHighestInformationGain){ 
					currentHighestInformationGain = currentInformationGain;
					currentBestAttribute = i;
				}
			}
			if(round == 0){root.setAttribute(mTrainingAttributeList.get(currentBestAttribute));}			
			treeNodes.add(mTrainingAttributeList.get(currentBestAttribute));		
			mTrainingAttributeList.remove(currentBestAttribute);			
			round++;
		}				
	}
	
	
public void createTreee(){
		
		int round = 0;
		while(mTrainingAttributeList.size() > 0){
			
			System.out.println("\n\nround: " + round);
			
			double currentEntropy = -1;
			double currentLowestEntropy = -1;
			int currentBestAttribute = -1;
			Attribute tempAttr;
			
			//calculate the information gain for each attribute and select the one with the highest information gain
			for(int i = 0; i < mTrainingAttributeList.size(); i++){
				currentEntropy = calculateEntropy(mTrainingAttributeList.get(i));
				tempAttr =  mTrainingAttributeList.get(i);
				System.out.println(tempAttr.getName() +  " igain: " +  currentEntropy + " true: " + tempAttr.getNumTrue() + " false: " + tempAttr.getNumFalse() + " diff: " + Math.abs(tempAttr.getNumFalse() - tempAttr.getNumTrue()));
				if(currentEntropy < currentLowestEntropy){ 
					currentLowestEntropy = currentEntropy;
					currentBestAttribute = i;
				}
			}
			root.setAttribute(mTrainingAttributeList.get(currentBestAttribute));
			treeNodes.add(mTrainingAttributeList.get(currentBestAttribute));		
			mTrainingAttributeList.remove(currentBestAttribute);
			
			round++;
		}				
	}
	public double calculateInformationGain(Attribute _attribute){
		double informationGain = calculateEntropy(_attribute) - calculateConditionalEntropy(_attribute);
		return informationGain;
	}
	
	public double calculateEntropy(final Attribute _attribute){
		
		double numTrue = _attribute.getNumTrue();
		double numFalse = _attribute.getNumFalse();
		double numValues =  numTrue + numFalse;		
		
		double ratioTrue = numTrue / numValues;
		double ratioFalse = _attribute.getNumFalse()/numValues;
		double entropyTrue = ratioTrue*log2(ratioTrue);
		double entropyFalse = ratioFalse*log2(ratioFalse);
		double entropy = (-1)*(entropyTrue + entropyFalse);		
		if(entropy > 1.0 || entropy < 0.0 ){System.out.println("Entropy cannot be greater than 1 or less than 0!!!");}
		return entropy;
	}
	
	public double calculateConditionalEntropy(final Attribute _attribute){
		
		double numTrue = _attribute.getNumTrue();
		double numFalse = _attribute.getNumFalse();
		double totalNum = numTrue + numFalse;
		
		double numTrueTrue =  _attribute.getNumTrueTrue();
		double numTrueFalse = _attribute.getNumTrueFalse();
		double numFalseTrue = _attribute.getNumFalseTrue();
		double numFalseFalse = _attribute.getNumFalseFalse();
		
		double ratioTrueTrue =  numTrueTrue/numTrue;
		double ratioTrueFalse =  numTrueFalse/numTrue;
		double ratioFalseTrue =  numFalseTrue/numFalse;
		double ratioFalseFalse =  numFalseFalse/numFalse;
		
		double ratioTrue = _attribute.getNumTrue() / totalNum;
		double ratioFalse = _attribute.getNumFalse() / totalNum;
		
		double trueTrueEntropy = ratioTrueTrue*log2(ratioTrueTrue);		
		double trueFalseEntropy = ratioTrueFalse*log2(ratioTrueFalse);
		double falseTrueEntropy = ratioFalseTrue*log2(ratioFalseTrue);
		double falseFalseEntropy = ratioFalseFalse*log2(ratioFalseFalse);
		
		double trueEntropy = (trueTrueEntropy + trueFalseEntropy);
		double falseEntropy = (falseTrueEntropy + falseFalseEntropy);
		
		double conditionalEntropy = (-1)*((ratioTrue*trueEntropy) + (ratioFalse*falseEntropy));
		//System.out.println(" cond ent: " + conditionalEntropy);
		if((conditionalEntropy < 0) || conditionalEntropy > 1){System.out.println("Error: invalid conditional entropy value");}
		return conditionalEntropy;
	}
	
	public double log2(double num){ 
		if( num < 0){			
			throw new IllegalArgumentException();
		}
		double result = (Math.log(num))/(Math.log(2));
		return result;
		}
	
	/**
	 * This function gathers Attributes from the specified file, and records the number of true and false values for each attribute 
	 * @param _file, String referring to the filename
	 */
	private void getAttributesFromFile(String _fileName, ArrayList<Attribute> _attributeList){
		
		File file = new File(_fileName);
		
		//the scanner object will be used for file io
		Scanner scanner = null;
		try{
			scanner = new Scanner(file);
		}catch(FileNotFoundException error){
			System.out.println("File not found.  Program exiting.");
			System.exit(1);
		}			
		
		//put each line in the file into the array lines[]
		ArrayList<String> lines = new ArrayList<String>();
		while(scanner.hasNextLine()){lines.add(scanner.nextLine());}
		
		//the first line contains all the attribute names, so we will use the first line to populate mAttributeList		
		String token = null;
		Attribute attribute = null;
		StringTokenizer stringTokenizer = null;
		
		//this loop breaks the first line into tokens and populates the Attributes list
		stringTokenizer = new StringTokenizer(lines.get(0)); 
		while(stringTokenizer.hasMoreTokens()){
			token = stringTokenizer.nextToken();
			attribute = new Attribute(token);
			_attributeList.add(attribute);
			System.out.print(" " + token + " ");					
		}
		//remove the "class" attribute, because it is not really an attribute
		_attributeList.remove(_attributeList.size() - 1);
		
		//iterates through the lines. Notice we're starting at line 1 and not line 0 because we've already processed the first line
		for(int i = 1; i < lines.size(); i++ ){
			stringTokenizer = new StringTokenizer(lines.get(i));  	
			
			//iterates through the tokens on each line. Notice we stop before we hit "class" because that category is special
			for(int j = 0; j < _attributeList.size(); j++){
				//get next token
				token = stringTokenizer.nextToken();
				//add it to the appropriate attribute's value list
				_attributeList.get(j).getValueList().add(Integer.parseInt(token));
				if(token.equals("0")){ _attributeList.get(j).plusOneFalse();}
				else if(token.equals("1")){ _attributeList.get(j).plusOneTrue();}
				else{System.out.println("error");}
			}
										
			//grab the class token and do stuff
			String classToken = stringTokenizer.nextToken();
			//for each attribute
			for(int k = 0; k < _attributeList.size(); k++){
				Attribute currentAttribute =  _attributeList.get(k);				
				String attrValue = currentAttribute.getValueList().get(i - 1).toString();
				if(attrValue.equals("1") && classToken.equals("1")){_attributeList.get(k).plusOneTrueTrue();}
				else if(attrValue.equals("1") && classToken.equals("0")){_attributeList.get(k).plusOneTrueFalse();}
				else if(attrValue.equals("0") && classToken.equals("1")){_attributeList.get(k).plusOneFalseTrue();}
				else if(attrValue.equals("0") && classToken.equals("0")){_attributeList.get(k).plusOneFalseFalse();}											
				else{System.out.println("error");}
			}							
		}
		
		System.out.print("RESULTS:\n");
		for(int j = 0; j < _attributeList.size(); j++){
			System.out.print(_attributeList.get(j).getName() + "\n\t");
			System.out.print("True: " + _attributeList.get(j).getNumTrue() + " False: " + _attributeList.get(j).getNumFalse() + " ");
			System.out.print("TrueTrue: " + _attributeList.get(j).getNumTrueTrue() + " TrueFalse: " + _attributeList.get(j).getNumTrueFalse() );
			System.out.print(" FalseTrue: " + _attributeList.get(j).getNumFalseTrue() + " " + " FalseFalse: " + _attributeList.get(j).getNumFalseFalse() + "\n\n");
		}
	}
	
	public Node getRoot(){return root;}
	
	public ArrayList<Attribute> getTree(){return treeNodes;}
}
