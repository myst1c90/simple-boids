/**
*   color.h
*/

#ifndef COLOR_H
#define COLOR_H


class Color {

  float r;
  float g;
  float b;
  
  public:
    
    Color();
    Color(float r, float g, float b);
    
    void setRGB(float r, float g, float b);

    void setR(float r);
    float getR();

    void setG(float g);
    float getG();

    void setB(float b);
    float getB();
  
};


#endif
