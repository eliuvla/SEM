#pragma once

#include "raylib.h"
#include "functions.h"

#include <math.h>

struct ContinuousDynamic{
	int max_curves = 1000;
	int max_points = 2;
	float max_diff = .1;

	float size = .1;

	float delta = 0.01;
	
	Vector3 initial_position = {1,1,1};

	Color * colors;
	Vector3 * initials_positions;
	Vector3** curves;
	
	Model model = LoadModel("fish.glb");
	
	Vector3 (* dinamic)(Vector3 point, float delta );
	
	void Init();
	void Update();
	void Draw();
	
	
};


void ContinuousDynamic::Init(){
	float rx,ry,rz; 
	int r,b,g;
	dinamic = dinamic_test;
	initials_positions = new Vector3[max_curves];
	colors = new Color[max_curves];
	curves = new Vector3*[max_curves];
	

	for(int i=0; i<max_curves; i++){
		rx = max_diff*((float) rand()/RAND_MAX -.5);
		ry = max_diff*((float) rand()/RAND_MAX -.5);
		rz = max_diff*((float) rand()/RAND_MAX -.5);
		initials_positions[i] = {initial_position.x+rx, initial_position.y+ry, initial_position.z+rz};

		r = 55+rand()%200;
		g = 55+rand()%200;
		b = 55+rand()%200;

		colors[i] = {r,g,b, 255};


	}

	for(int i =0; i<max_curves; i++){
		curves[i] = new Vector3[max_points];
		curves[i][0] = initials_positions[i];
	}


	for(int i=0; i<max_curves; i++){
		for(int j=1; j<max_points; j++){
			curves[i][j] = dinamic(curves[i][j-1],delta);
		}
	}
	
	
}

void ContinuousDynamic::Update(){
	
	
	
	for(int i=0; i<max_curves; i++){
		for(int j=0; j<max_points-1; j++){
			curves[i][j] = curves[i][j+1];
		}
		curves[i][max_points-1] = dinamic(curves[i][max_points-1], delta);
	}
	
	
	
	
	
}

void ContinuousDynamic::Draw(){
	
	
	Color color;
	Vector3 d,p,n;
	float angle;


	for(int i=0; i<max_curves; i++){
		for(int j=0; j<max_points-1; j++){

			color = {(colors[i].r*i)/max_points, (colors[i].g*i)/max_points, (colors[i].b*i)/max_points, 255};
			color = colors[i];
			//DrawLine3D(curves[i][j], curves[i][j+1],color);

		}

		d = curves[i][1];
		p = curves[i][0];
		
		d.x = d.x-p.x;
		d.y = d.y-p.y;
		d.z = d.z-p.z;
		
		p = {0,0,1};
		
		n.x = d.y*p.z-d.z*p.y;
		n.y = -(d.x*p.z-d.z*p.x);
		n.z = d.x*p.y-d.y*p.x;
		
		float a,b,c;
		
		a = sqrt((p.x*p.x)+(p.y*p.y)+(p.z*p.z));
		b = sqrt((d.x*d.x)+(d.y*d.y)+(d.z*d.z));
		c = (p.x*d.x)+(p.y*d.y)+(p.z*d.z);
		
		angle = acos(c/(a*b));

		n = {10*n.x/(a*b),10*n.y/(a*b),10*n.z/(a*b)};
		p = {10*p.x/a,10*p.y/a,10*p.z/a};
		d = {10*d.x/b,10*d.y/b,10*d.z/b};

		DrawModelEx(model, curves[i][0], n, -(360/(2*PI))*angle, {size,size,size}, WHITE);


	}
	

	
	
	
	

	
	
	DrawGrid(10, 1);
	
	
}