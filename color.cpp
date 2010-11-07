/**
*   color.cpp
*/

#include "color.h"


Color::Color() {
}

Color::Color(float r, float g, float b) {
    this->r = r;
    this->g = g;
    this->b = b;
}

void Color::setRGB(float r, float g, float b) {
	this->r = r;
	this->g = g;
	this->b = b;
}

void Color::setR(float r) {
    this->r = r;
}

float Color::getR() {
  return this->r;
}

void Color::setG(float g) {
    this->g = g;
}

float Color::getG() {
  return this->g;
}

void Color::setB(float b) {
    this->b = b;
}

float Color::getB() {
  return this->b;
}
  


