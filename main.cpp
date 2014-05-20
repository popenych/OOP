#include "XList.h"
#include "Shape.h"

#include <iostream>


void main()
{
	XList< Printable * > figures;
	figures.push_back( new Point( "figure #1" , 5. , 3. ) );
	figures.push_back( new Circle( "figure #2" , Point( "Circle center" , 8.3 , 9.6 ) , 5. ) );
	figures.push_back( new Rectangle( "figure #3" , Point( "Rectangle top left corner" , -7.8 , 1.2 ) , Point( "Rect bottom right corner" , 8.2 , 3.8 ) ) );
	figures.push_back( new Square( "figure #4" , Point( " Square top left corner " , 0. , 0. ) , 100. ) );	
	Polyline * somePolyline = new Polyline( "figure #5" );
	somePolyline->addPoint( Point( "Polyline point 1" , 1. , 1. ) );
	somePolyline->addPoint( Point( "Polyline point 2" , 4. , 4. ) );
	somePolyline->addPoint( Point( "Polyline point 3" , 10. , 4. ) );
	somePolyline->addPoint( Point( "Polyline point 4" , 10. , 10. ) );
	somePolyline->addPoint( Point( "Polyline point 5" , 13. , 17. ) );
	figures.push_back( somePolyline );
		

	std::cout << "Number of figures: " << Shape::getCount() << std::endl << "Figures info from begin to end:" << std::endl;

		
	for( XList< Printable * >::XIterator it = figures.begin(); it != ++figures.end(); ++it )
	{
		std::cout << *(*it) << std::endl;
	}

	std::cout<<std::endl;
	std::cout << "Figures info end to begin:" << std::endl;

	for( XList< Printable * >::XIterator it = figures.end(); it != --figures.begin(); --it )
	{
		std::cout << *(*it) << std::endl;
	}

	for( XList< Printable * >::XIterator it = figures.begin(); it != ++figures.end(); ++it )
	{
		delete (*it);
	}

	figures.remove();

	std::cout<<std::endl;
	std::cout << "Number of figures: " << Shape::getCount() << " ... must be 0" << std::endl;
	
}


