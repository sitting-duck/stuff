import java.awt.Canvas;
import java.awt.Dimension;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class Squares extends Frame{

	public static void main(String[] args) {
		new Squares();
		//new Anisotr();
	}
	
	Squares(){
		super("Squares");
		addWindowListener(new WindowAdapter(){
			public void windowClosing(WindowEvent e){
				System.exit(0);
			}
		});
		setSize(600, 600);
		add("Center", new CvSquares());
		show();
	}
	
	class CvSquares extends Canvas{
		
		int xCenter, yCenter, maxX, maxY;		
		float pixelSize, rWidth = 10.0F, rHeight = 10.0F, 
				x1a, x2a, y1a, y2a,
				x1b, x2b, y1b, y2b,
				x1c, x2c, y1c, y2c, 
				x1d, x2d, y1d, y2d,
				factor = 1;
		
		void initgr(){
			Dimension d = getSize();
			maxX = d.width -1; maxY = d.height -1;
			pixelSize = Math.max(rWidth/maxX, rHeight/maxY);
			xCenter = maxX/2; yCenter = maxY/2;			
		}
		
		int iX(float x){return Math.round(xCenter + x/pixelSize);}		
		//int iY(float y){return maxY - Math.round(yCenter - y/pixelSize);}
		int iY(float y){return maxY - Math.round(yCenter + y/pixelSize);}
		float fx(int x){return (x - xCenter) * pixelSize;}		
		float fy(int y){return (yCenter - y) * pixelSize;}
		
		public void paint(Graphics g){
			initgr();					
			
			for(int i = 0; i < 10; i++){
				
				//set coordinates for upright square
				x1a = (-rWidth/2)*factor; y1a = (rHeight/2)*factor;  x2a = (rWidth/2)*factor;  y2a = (rHeight/2)*factor;			
				x1b = (rWidth/2)*factor;  y1b = (rHeight/2)*factor;  x2b = (rWidth/2)*factor;  y2b = (-rHeight/2)*factor;
				x1c = (rWidth/2)*factor;  y1c = (-rHeight/2)*factor; x2c = (-rWidth/2)*factor; y2c = (-rHeight/2)*factor;
				x1d = (-rWidth/2)*factor; y1d = (-rHeight/2)*factor; x2d = (-rWidth/2)*factor; y2d = (rHeight/2)*factor;
				
				//draw upright square
				g.drawLine(iX(x1a), iY(y1a), iX(x2a), iY(y2a));
				g.drawLine(iX(x1b), iY(y1b), iX(x2b), iY(y2b));
				g.drawLine(iX(x1c), iY(y1c), iX(x2c), iY(y2c));
				g.drawLine(iX(x1d), iY(y1d), iX(x2d), iY(y2d));
				
				//set coordinates for diamond
				x1a = (0)*factor; y1a = (rHeight/2)*factor;  x2a = (rWidth/2)*factor;  y2a = (0)*factor;			
				x1b = (rWidth/2)*factor;  y1b = (0)*factor;  x2b = (0)*factor;  y2b = (-rHeight/2)*factor;
				x1c = (0)*factor;  y1c = (-rHeight/2)*factor; x2c = (-rWidth/2)*factor; y2c = (0)*factor;
				x1d = (-rWidth/2)*factor; y1d = (0)*factor; x2d = (0)*factor; y2d = (rHeight/2)*factor;
				
				//draw diamond
				g.drawLine(iX(x1a), iY(y1a), iX(x2a), iY(y2a));
				g.drawLine(iX(x1b), iY(y1b), iX(x2b), iY(y2b));
				g.drawLine(iX(x1c), iY(y1c), iX(x2c), iY(y2c));
				g.drawLine(iX(x1d), iY(y1d), iX(x2d), iY(y2d));
				
				factor = 0.5F*factor;				
			}
					
		}
	}
}
