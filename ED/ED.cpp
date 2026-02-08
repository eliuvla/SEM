#include "raylib.h"


#include <cstdio>
#include <time.h> 

#include "dynamic.h"



int main(){
	
	int width = 640;
	int height = 480;
	bool pause = 0;
	
	
	SetConfigFlags(FLAG_VSYNC_HINT|FLAG_MSAA_4X_HINT); 
	InitWindow(width, height, "sound cantor");

	ToggleFullscreen();
	
	DisableCursor();
	
	Camera camera = { 0 };
	camera.position = (Vector3){10.0f, 10.0f, 10.0f };    // Camera position
	camera.target = (Vector3){ 1.0f, 1.0f, 1.0f };      // Camera looking at point
	camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 80.0f;                                // Camera field-of-view Y
	camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type
	
	
	ContinuousDynamic test;
	
	test.Init();
	
	srand(time(NULL));
	
	
	SetTargetFPS(60);
	
	while(!WindowShouldClose()){
		
		if(IsKeyPressed(KEY_P)){
			pause = !pause;
		}

		if(!pause){
			test.Update();
		}
		
		UpdateCamera(&camera, CAMERA_FREE);
		
		
		
		BeginDrawing();
		
			ClearBackground(BLACK);
			
			
			
			
			
			BeginMode3D(camera);
			
				//DrawLine3D(Vector3{0,0,0}, Vector3{100,0,0}, RED);
				//DrawLine3D(Vector3{0,0,0}, Vector3{0,100,0}, GREEN);
				//DrawLine3D(Vector3{0,0,0}, Vector3{0,0,100}, BLUE);
			
				test.Draw();
			
			EndMode3D();
			
			
			
			
			
			
			
			
			
			
			DrawFPS(10, 10);
		
		EndDrawing();
		
		
		
		
	}
	
	

	
	CloseWindow();
	
}