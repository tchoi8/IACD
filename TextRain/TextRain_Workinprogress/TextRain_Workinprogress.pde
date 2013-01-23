PFont f;
String message = "qwertyuiopASDFGHJKLZXCVBNM<L";
Letter[] letters;
import processing.video.*;
int numPixels;
Capture video;
int m, n;
int index = 0;
int threshold = 95; //would like to make threshold controllable,,, or auto detection..? 

void setup() {
  size(640, 480, P2D);  
  strokeWeight(5);
  video = new Capture(this, width, height);
  video.start();  
  numPixels = video.width * video.height;
  noCursor();
  smooth();
  
  f = createFont("Arial",25,true);
  textFont(f);
  letters = new Letter[message.length()];
  int x = 8;// Initialize Letters at the correct x location
  for (int i = 0; i < message.length(); i++) {
    letters[i] = new Letter(x,200,message.charAt(i)); 
    x += 30;
    //alternatively.. x += textWidth(message.charAt(i));
  }
  
}


void draw() {
 
  if (video.available()) {
    video.read();
 
    video.filter(GRAY);
    image(video, 0, 0);
    video.loadPixels();
    
    float pixelBrightness; // Declare variable to store a pixel's color
    for (int i = 0; i < letters.length; i++) {
      letters[i].display();
 
     if (mousePressed) {
       letters[i].goup();
       letters[i].display();
    } else {
    letters[i].shake();
    letters[i].check();
    }

  }
updatePixels();
  } 

}
class Letter {
      char letter;
      // The object knows its original "home" location
      float homex,homey;
      // As well as its current location
      float x,y;
    
      Letter (float x_, float y_, char letter_) {
        homex = x = x_;
        homey = y = y_;
        letter = letter_; 
      }

  // Display the letter
void display() {
    fill(0, 102, 153, 204);
    textAlign(LEFT);
    text(letter,x,y);
   //x+=10;
 }

void shake() {
      int m,n; //whould call again? 
      m = int(x);
      n= int(y);
      int testValue= get(m,n);
      float testBrightness = brightness(testValue) ;
       if (testBrightness > threshold){
            x += random(-1,1);
            y += random(5,6);
            
       if (y > 400) {
       y = -height; 
      index = (index + 1) % letters.length;
    }
           } 
      else {
          x -= random(-1,1);
          y -= random(5,6);      
      }
 }
   
   
void check(){ 
   float q= textWidth(message);
     
      if (y> 460){
          y = 30;
          index = (index +1)%letters.length;
        fill(323,22,22);
        noStroke();
        rect(10,30,40,40);  //this is a quirky way to see the state of checking... need to find a better way
        }
      else if (y<30){
           y = 60;
          index = (index +1)%letters.length;
      fill(223,22,22);
      noStroke();
      rect(10,30,40,40);     
      }

        else {fill(123,22,22);
        noStroke();
        rect(10,30,40,40);   }
          
}    
 
void goup() { //means Go Up! 
    x -= random(-2,2);
    y -= random(10,15);
  }

   

} 
