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
		int degree=0,targetdegree,fps[6],statetargetdegree[6],randomitem,itemleft[MAX_ITEM+1];
		string itemname[MAX_ITEM+1];
		Uint32 lasttime=0;
		string rouletSaveData;
		
		void init(string loc)
		{
		 memset(&itemleft,0,sizeof(itemleft));
		 itemname[1]="Flashdrive";
		 itemname[2]="Salt&Snack";
		 itemname[3]="Pen";
		 itemname[4]="Wristband";
		 itemname[5]="Candy";
		 itemname[6]="Surprise!";
		 itemname[7]="Milo&Snack";
		 itemname[8]="Snack";
		 rouletSaveData=loc;
		 loadData();
		}
		void loadData()
		{
		 FILE *rouletFile=fopen(rouletSaveData.c_str(),"r");
		 if (rouletFile==NULL)
		 {
		  saveData();
		  return;
		 }
		 char read[2048];
		 
		 for(int c=1;c<MAX_ITEM+1;c++)
		 {
		  if (!fgets(read,2048,rouletFile))
		  {
		   printf("[System/Roulet] Load Data Failed\n");
		   fprintf(logFile,"[System/Roulet] Load Data Failed\n");
		   break;
		  }
		  sscanf(read,"%d",&itemleft[c]);
		 }
		 fclose(rouletFile);
		}
		void saveData()
		{
		 FILE *rouletFile=fopen(rouletSaveData.c_str(),"w");
		 
		 for(int c=1;c<MAX_ITEM+1;c++)
		 {
		  fprintf(rouletFile,"%d %s\n",itemleft[c],itemname[c].c_str());
		 }
		 fclose(rouletFile);
		}
		void render()
		{
		 renderImage(x,y,w,h,degree,img);
		}
		void loadImg(string loc)
		{
		 img=loadImage(loc);
		}
		int calculateItemLeft()
		{
		 int r=0;
		 for(int c=1;c<MAX_ITEM+1;c++)r+=itemleft[c];
		 return r;
		}
		void activate()
		{
		 if (state==0)
		 {
		  if (calculateItemLeft()==0)
		  {
		   printf("[System/Roulet] Waring No Item Left\n");
		   fprintf(logFile,"[System/Roulet] Waring No Item Left\n");
		   return;
		  }
		  
		  #if USE_PERCENT
		  int randompercent;
		  do
		  {
		   randompercent=rand()%100;
		   printf("[System/Roulet] Use Random Percent %d\n",randompercent);
		   fprintf(logFile,"[System/Roulet] Use Random Percent %d\n",randompercent);
		   if (randompercent>=0&&randompercent<2)randomitem=1;//Flashdrive
		   else if (randompercent>=2&&randompercent<29)randomitem=2;//Salt&Snack
		   else if (randompercent>=29&&randompercent<56)randomitem=3;//Pen
		   else if (randompercent>=56&&randompercent<59)randomitem=4;//Wristband
		   else if (randompercent>=59&&randompercent<70)randomitem=5;//Candy
		   else if (randompercent>=70&&randompercent<70)randomitem=6;//Surprise!
		   else if (randompercent>=70&&randompercent<85)randomitem=7;//Milo&Snack
		   else if (randompercent>=85&&randompercent<100)randomitem=8;//Snack
		  }
		  while(itemleft[randomitem]==0);
		  itemleft[randomitem]--;
		  saveData();
		  #else
		  randomitem=(rand()%calculateItemLeft())+1;
		  printf("[System/Roulet] Use Random ID %d\n",randomitem);
		  fprintf(logFile,"[System/Roulet] Use Random ID %d\n",randomitem);
		  for(int c=1;c<MAX_ITEM+1;c++)
		  {
		   randomitem-=itemleft[c];
		   if (randomitem<=0)
		   {
		   	randomitem=c;
		   	itemleft[c]--;
		   	saveData();
		   	break;
		   }
		  }
		  #endif
		  
		  targetdegree=(360-((randomitem-1)*(360/MAX_ITEM)))%360;
		  printf("[Gacha] Get Item ID %d [%s]\n",randomitem,itemname[randomitem].c_str());
		  fprintf(logFile,"[Gacha] Get Item ID %d [%s]\n",randomitem,itemname[randomitem].c_str());
		  printf("\nItem Left\n");
		  fprintf(logFile,"\nItem Left\n");
		  for(int c=1;c<MAX_ITEM+1;c++)
		  {
		   printf("Item ID %d [%s] Left %d\n",c,itemname[c].c_str(),itemleft[c]);
		  }
		  printf("\n");
		  fprintf(logFile,"\n");
		 
		  //BEGIN set fps and degree
		  fps[0]=0;
		  fps[1]=1;
		  fps[2]=1;
		  fps[3]=5;
		  fps[4]=10;
		  fps[5]=10;
		  statetargetdegree[0]=0;
		  statetargetdegree[2]=810;
		  statetargetdegree[3]=450;
		  statetargetdegree[4]=270;
		  statetargetdegree[5]=90;
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
		 	 3	 move fps  5 ,450 degree
		 	 4	 move fps 10 ,270 degree
		  	 5	 move fps 10 ,90 degree
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
