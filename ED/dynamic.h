#pragma once

#include "raylib.h"
#include "functions.h"

#include <math.h>

struct ContinuousDynamic{
	int max_points = 10000;
	float delta = 0.001;
	
	
	Vector3 initial_position = {1,1,1};
	
	Vector3* points = new Vector3[max_points];   
	
	Model model = LoadModel("fish.glb");
	
	
	
	Vector3 (* dinamic)(Vector3 point, float delta ) = dinamic_test;
	
	void Init();
	void Update();
	void Draw();
	
	
};


void ContinuousDynamic::Init(){
	
	points[0] = initial_position;
	
	for(int i = 0; i<max_points-1; i++){
		points[i+1] = dinamic(points[i], delta);
	}
	
	
	
}

void ContinuousDynamic::Update(){
	
	
	
	for(int i=0; i<max_points-1; i++){
		points[i] = points[i+1];
	}
	
	
	points[max_points-1] = dinamic(points[max_points-1], delta);
	
	
	
	
}

void ContinuousDynamic::Draw(){
	
	
	Color color;
	Vector3 direction,position,normal;
	float angle;
	
	for(int i=0; i<max_points-1; i++){
		
		color = {20,(i*200)/max_points,20,255};
		
		//DrawCylinderEx(points[i], points[i+1], .1, .1, 4, color);
		DrawLine3D(points[i], points[i+1],color);
		//DrawCubeV(points[i], {1,1,1}, RED);
		
		
		//DrawTriangleStrip3D(points, max_points,RED);
		
	}
	
	//DrawModelEx(model, points[0], Vector3 rotationAxis, float rotationAngle, .05, WHITE);
	
	
	
	//DrawCylinderEx(points[i], points[i+1], .1, .1, 4, color);
	
	
	
	direction = points[1];
	position = points[0];
	
	direction.x -= position.x;
	direction.y -= position.y;
	direction.z -= position.z;
	
	position = {10,0,0};
	
	
	normal.x = direction.y*position.z-direction.z*position.y;
	normal.y = -(direction.x*position.z-direction.z*position.x);
	normal.z = direction.x*position.y-direction.y*position.x;
	
	
	DrawLine3D(Vector3{0,0,0}, position, BLUE);
	DrawLine3D(Vector3{0,0,0}, direction, GREEN);
	DrawLine3D(Vector3{0,0,0}, normal, RED);
	
	
	float a,b,c;
	
	a = sqrt((position.x*position.x)+(position.y*position.y)+(position.z*position.z));
	b = sqrt((direction.x*direction.x)+(direction.y*direction.y)+(direction.z*direction.z));
	c = (position.x*direction.x)+(position.y*direction.y)+(position.z*direction.z);
	
	angle = acos(c/(a*b));
	
	
	//DrawModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint);
	
	DrawModelEx(model, points[0], normal, (360/(2*PI))*angle, {1,1,1}, WHITE);
	
	DrawModelEx(model, {0,0,0}, {0,1,0}, (360/(2*PI))*angle, {1,1,1}, WHITE);
	
	
	DrawGrid(10, 1);
	
	
}