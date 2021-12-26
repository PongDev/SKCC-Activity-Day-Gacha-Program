class image
{
	public:
		SDL_Texture *img=NULL;
		int x=0,y=0,w=0,h=0;
		int degree=0;
		
		void render()
		{
		 renderImage(x,y,w,h,degree,img);
		}
		void setPos(int ix,int iy,int iw,int ih)
		{
		 x=ix;
		 y=iy;
		 w=iw;
		 h=ih;
		}
		void loadImg(string loc)
		{
		 img=loadImage(loc);
		}
};

class roulet
{
	public:
		SDL_Texture *img=NULL;
		SDL_Event e;
		int x=0,y=0,w=0,h=0,state=0;
		int degree=0,targetdegree,fps[6],statetargetdegree[6];
		Uint32 lasttime=0;
		
		void render()
		{
		 renderImage(x,y,w,h,degree,img);
		}
		void loadImg(string loc)
		{
		 img=loadImage(loc);
		}
		void activate()
		{
		 if (state==0)
		 {
		  targetdegree=(rand()%MAX_ITEM)*(360/MAX_ITEM);
		  printf("%d\n",(((360-targetdegree)/(360/MAX_ITEM))%8)+1);
		 
		  //BEGIN set fps and degree
		  fps[0]=0;
		  fps[1]=1;
		  fps[2]=1;
		  fps[3]=5;
		  fps[4]=10;
		  fps[5]=15;
		  statetargetdegree[0]=0;
		  statetargetdegree[2]=810;
		  statetargetdegree[3]=450;
		  statetargetdegree[4]=270;
		  statetargetdegree[5]=180;
		  statetargetdegree[1]=(((360-((statetargetdegree[2]+statetargetdegree[3]+statetargetdegree[4]+statetargetdegree[5])%360))+targetdegree+(360-degree))%360)+(360*(rand()%3));
		  //END
		  
		  state=1;
		  lasttime=SDL_GetTicks();
	 	 }
		}
		void event()
		{
		 if (state==0)return;
		 /*BEGIN state definition
		 state	 definition
		 	 0	 stop
		 	 1	 move fps  1 ,x degree
		 	 2	 move fps  1 ,810 degree
		 	 3	 move fps  5,450 degree
		 	 4	 move fps 10 ,270 degree
		  	 5	 move fps 15 ,180 degree
		 END*/
	 	 if (SDL_GetTicks()-lasttime>=fps[state])
	 	 {
	 	  lasttime=SDL_GetTicks();
	 	  degree+=min(DEGREE_PER_MOVE,statetargetdegree[state]);
	 	  if (statetargetdegree[state]>=DEGREE_PER_MOVE)statetargetdegree[state]-=DEGREE_PER_MOVE;
	 	  else
	 	  {
	 	   statetargetdegree[state]=0;
	 	   state++;
	 	   state%=6;
	 	  }
	 	 }
		}
};
