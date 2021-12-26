#include"config.h"
#include"system.h"
#include"obj.h"

int main(int argc,char* args[])
{
	bool run=true;
	
	srand(time(NULL));
	if (init()==0)
	{
	 printf("[System] Initialize Error\n");
	 return 0;
	}
	
	//BEGIN Get Screen Resolution
	int WINDOW_W,WINDOW_H;
	
	if (FULLSCREEN)
	{
	 SDL_DisplayMode DM;
	 SDL_GetCurrentDisplayMode(0,&DM);
	 WINDOW_W=DM.w;
	 WINDOW_H=DM.h;
	}
	else
	{
	 SDL_GetWindowSize(window,&WINDOW_W,&WINDOW_H);
	}
	//END
	
	//BEGIN point obj
	image point;
	
	point.loadImg("resource/point.png");
	point.w=50;
	point.h=50;
	point.x=(WINDOW_W/2)-(point.w/2);
	point.y=100;
	//END
	
	//BEGIN rouret obj
	roulet roulet;
	
	roulet.loadImg("resource/roulet.png");
	roulet.w=800;
	roulet.h=800;
	roulet.x=(WINDOW_W/2)-(roulet.w/2);
	roulet.y=120;
	//END
	
	while(run)
	{
	 while(SDL_PollEvent(&e)!=0)
	 {
	  if (e.type==SDL_QUIT)run=false;
	  if (e.type==SDL_KEYDOWN)roulet.activate();
	 }
	 roulet.event();
	 renderClear();
	 roulet.render();
	 point.render();
	 renderShow();
	}
}