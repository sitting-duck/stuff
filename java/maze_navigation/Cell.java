

public class Cell {

    String data = "";

    public Cell(String _data) {
       if(_data.compareTo("0") == 0 ||
	  _data.compareTo("1") == 0 ||
	  _data.compareTo("S") == 0 ||
	  _data.compareTo("E") == 0 ||
    _data.compareTo("*") == 0) {
	  
	    data = _data;  	
       } else {
           System.out.println("Error: invalid constructor value for Cell! Innitializing empty cell.");
	   data = "";
       } 
    }

    public void set(String _data) {
    	data = _data;
    }

    public String get() {
    	return data;
    } 

}

