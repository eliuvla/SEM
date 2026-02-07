#pragma once

#include "raylib.h"

Vector3 dinamic_test(Vector3 point, float delta){
	float x,y,z;
	
	float u,v,w;
	
	float rho,sigma,beta;
	
	rho = 28;
	sigma = 10;
	beta = 8/3;
	
	x = point.x;
	y = point.y;
	z = point.z;
	
	u = x+delta*(sigma*(y-x));
	v = y+delta*( x*(rho-z)-y);
	w = z+delta*(x*y-beta*z);
	
	//u = x+delta;
	//v = y+delta;
	//w = z+delta;
	
	return Vector3{u,v,w};
	
	
}



