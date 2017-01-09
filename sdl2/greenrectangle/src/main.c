#include <psp2/kernel/processmgr.h>
#include <SDL2/SDL.h>
#include <psp2/ctrl.h>

//Screen dimension constants
enum {
  SCREEN_WIDTH  = 960,
  SCREEN_HEIGHT = 544
};
#define BOX_SIZE_X    64
#define BOX_SIZE_Y    64
#define BOX_INCREMENT 5

int my_x1=( SCREEN_WIDTH  * 31) / 64;
int my_y1=( SCREEN_HEIGHT * 33) / 64;

int my_x2= BOX_SIZE_X;
int my_y2= BOX_SIZE_Y;

SDL_Window    * gWindow   = NULL;
SDL_Renderer  * gRenderer = NULL;
SDL_Event       event;
SDL_Rect        fillRect;
SceCtrlData     pad;

int main(int argc, char *argv[]) 
{
  int quit=0;

  if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
      return -1;


  if ((gWindow = SDL_CreateWindow( "GreenRectangle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
    return -1;

  //if ((gRenderer = SDL_CreateRenderer( gWindow, -1, 0)) == NULL)
  if ((gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_PRESENTVSYNC)) == NULL)
      return -1;

  while(pad.buttons != (SCE_CTRL_LTRIGGER | SCE_CTRL_RTRIGGER) )
    {
      // read the pad
      sceCtrlPeekBufferPositive(0, &pad, 1);

      if (pad.buttons & SCE_CTRL_RIGHT)
	my_x1=my_x1+BOX_INCREMENT;
      if (pad.buttons & SCE_CTRL_LEFT)
	my_x1=my_x1-BOX_INCREMENT;

      if (pad.buttons & SCE_CTRL_UP)
	my_y1=my_y1-BOX_INCREMENT;
      if (pad.buttons & SCE_CTRL_DOWN)
	my_y1=my_y1+BOX_INCREMENT;

      if (my_x1<10)                          my_x1=10;
      if (my_x1>SCREEN_WIDTH -BOX_SIZE_X) my_x1=SCREEN_WIDTH-BOX_SIZE_X;

      if (my_y1<10)                          my_y1=10;
      if (my_y1>SCREEN_HEIGHT-BOX_SIZE_Y) my_y1=SCREEN_HEIGHT-BOX_SIZE_Y;
      
      fillRect = { my_x1, my_y1, my_x2, my_y2   };

      // clear screen
      SDL_SetRenderDrawColor( gRenderer, 0,0,0,0);
      SDL_RenderClear(gRenderer);
      // fill the green box
      SDL_SetRenderDrawColor( gRenderer, 0,255,0,255);
      SDL_RenderFillRect( gRenderer, &fillRect );
      
      SDL_RenderPresent( gRenderer );
      SDL_Delay(5);
    }
  SDL_DestroyRenderer( gRenderer );
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;
  gRenderer = NULL;
  
  SDL_Quit();
  sceKernelExitProcess(0);
  return 0;
}
