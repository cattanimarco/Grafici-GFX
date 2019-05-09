#include <iostream>

#include "DriverFile.h"

DriverFile::DriverFile(void)
{
		int b, x, y;
	HEZDIMAGE hDib;
	HEZDFONT hFont;

		// Create output file name
		char fname[ 256 ] = { 0 };
		sprintf( fname, "test-%d.bmp", 24 );
		printf( "Creating %s\n", fname );

		// Create image
		hDib = ezd_create( 640, -480, 24, 0 );

	// Fill in the background
		ezd_fill( hDib, 0x404040 );

		// // Test fonts
		// hFont = ezd_load_font( EZD_FONT_TYPE_MEDIUM, 0, 0 );
		// if ( hFont )
		// 	ezd_text( hDib, hFont, "--- EZDIB Test ---", -1, 10, 10, 0xffffff );

		// Draw random lines
		for ( x = 20; x < 300; x += 10 )
			ezd_line( hDib, x, ( x & 1 ) ? 50 : 100, x + 10, !( x & 1 ) ? 50 : 100, 0x00ff00 ),
			ezd_line( hDib, x + 10, ( x & 1 ) ? 50 : 100, x, !( x & 1 ) ? 50 : 100, 0x0000ff );

		// Random red box
		ezd_fill_rect( hDib, 200, 150, 400, 250, 0x900000 );

		// Random yellow box
		ezd_fill_rect( hDib, 300, 200, 350, 280, 0xffff00 );

		// Dark outline for yellow box
		ezd_rect( hDib, 300, 200, 350, 280, 0x000000 );

		// Draw random dots
		for ( y = 150; y < 250; y += 4 )
			for ( x = 50; x < 150; x += 4 )
				ezd_set_pixel( hDib, x, y, 0xffffff );

		// Circles
		for ( x = 0; x < 40; x++ )
			ezd_circle( hDib, 400, 60, x, x * 5 );

		// Save the test image
		ezd_save( hDib, fname );
}

void DriverFile::drawPixel(Point point, int thickness, Color color)
{
	// std::cout << "DriverCout::drawPixel x: " << point.x
	// 		  << " y: " << point.y
	// 		  << " value: " << point.value
	// 		  << " tickness: " << thickness
	// 		  << " color: (" << (int)color.red
	// 		  << "," << (int)color.green
	// 		  << "," << (int)color.blue
	// 		  << ")" << std::endl;
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void DriverFile::drawLine(Line line, int thickness, Color color)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	//drawPixel(line.begin,thickness,color);
}

void DriverFile::drawCircle(Circle circle, int thickness, Color color)
{
}

void DriverFile::drawRectangle(Rectangle rectangle, int thickness, Color color)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

void DriverFile::fillRectangle(Rectangle rectangle, Color color)
{
}

void DriverFile::fillCircle(Circle circle, Color color)
{
}
