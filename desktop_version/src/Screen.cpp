#include "Screen.h"

#include "FileSystemUtils.h"
#include "GraphicsUtil.h"

#include <stdlib.h>

// Used to create the window icon
extern "C"
{
	extern unsigned lodepng_decode24(
		unsigned char** out,
		unsigned* w,
		unsigned* h,
		const unsigned char* in,
		size_t insize
	);
}

Screen::Screen()
{
    hw_screen = NULL;
    m_screen = NULL;
    isWindowed = true;
    stretchMode = 0;
    isFiltered = false;
    filterSubrect.x = 1;
    filterSubrect.y = 1;
    filterSubrect.w = 318;
    filterSubrect.h = 238;

    hw_screen = SDL_SetVideoMode(320, 240, 32, SDL_DOUBLEBUF | SDL_HWSURFACE);

	m_screen = hw_screen;

    badSignalEffect = false;
    glScreen = true;
}

void Screen::ResizeScreen(int x , int y)
{
	static int resX = 320;
	static int resY = 240;
	if (x != -1 && y != -1)
	{
		// This is a user resize!
		resX = x;
		resY = y;
	}
}

void Screen::GetWindowSize(int* x, int* y)
{
  *x = 320;
  *y = 240;
}

void Screen::UpdateScreen(SDL_Surface* buffer, SDL_Rect* rect )
{
    if((buffer == NULL) && (m_screen == NULL) )
    {
        return;
    }

    if(badSignalEffect)
    {
        buffer = ApplyFilter(buffer);
    }


    FillRect(m_screen, 0x000);
    BlitSurfaceStandard(buffer,NULL,m_screen,rect);

    if(badSignalEffect)
    {
        SDL_FreeSurface(buffer);
    }

}

const SDL_PixelFormat* Screen::GetFormat()
{
    return hw_screen->format;
}

void Screen::setPlayerPosition(int x, int y)
{
  this->x = x;
  this->y = y;
}

void Screen::FlipScreen()
{
	SDL_Rect src = { 0, 0, 320, 240 };
	BlitSurfaceStandard(m_screen, &src, hw_screen, NULL);
	SDL_Flip(hw_screen);
}

void Screen::toggleFullScreen()
{
	isWindowed = !isWindowed;
	ResizeScreen(-1, -1);
}

void Screen::toggleStretchMode()
{
	stretchMode = (stretchMode + 1) % 3;
	ResizeScreen(-1, -1);
}

void Screen::toggleLinearFilter()
{

}

void Screen::ClearScreen( int colour )
{
    //FillRect(m_screen, colour) ;
}
