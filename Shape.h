#ifndef SHAPE_OOP
#define SHAPE_OOP

#include <string>
#include <iostream>

const double PI = 3.14159265;

class Named
{
public:
	Named( std::string const & name )
		:m_name(name){}
		virtual ~Named() {}
	std::string const & getName() const { return m_name; }

	private:
	std::string m_name;
};

class Printable : public virtual Named {

public:
	Printable( std::string const name ) : Named( name ) {}
	virtual void Print( std::ostream & stream ) const = 0;
	virtual ~Printable() {}

};

std::ostream & operator << ( std::ostream & stream , Printable const & object ) {
	object.Print( stream );
	return stream;
}

class Shape : public virtual Named {

public:
	Shape( std::string const name ) : Named( name ) { ++sm_count; }
	Shape( Shape const & other ) : Named( other.getName() ) { ++sm_count; }
	virtual ~Shape() { --sm_count; }

	static int getCount() { return sm_count; }

private:
	static int sm_count;

};

int Shape::sm_count = 0;



class Point : public Shape , public Printable {

public:

	Point( std::string const & name , double const & x , double const & y ) 
		:Named( name ) 
		,Shape( name ) 
		,Printable( name ) 
		,m_x( x ) 
		,m_y( y ) {}

	virtual ~Point() {}

	virtual void Print( std::ostream & stream ) const 
	{ 
		stream << getName() <<" is a Point, coordinates: (" << m_x << "," << m_y << ")" << std::endl; 
	}

	double getX() const { return m_x; }
	double getY() const { return m_y; }

private:
	double m_x;
	double m_y;
	
};

class Circle : public Shape , public Printable {

public:
	Circle( std::string const & name , Point const & center , double radius ) 
		:Named( name )
		,Shape( name ) 
		,Printable( name ) 
		,m_center( center ) 
		,m_radius( radius )
		,m_area ( PI*radius*radius ) {}

	virtual ~Circle() {}

	virtual void Print( std::ostream & stream ) const 
	{ 
		stream << getName() << " is a Circle, center: " << getCenter() << "radius: " << getRadius()
			<< ", area: " << getArea() << std::endl;
	}

	double getArea() const { return m_area; }
	double getRadius() const { return m_radius; }
	Point const & getCenter() const { return m_center; }

private:
	
	Point m_center;
	double m_radius;
	double m_area;

	

};

class Rectangle : public Shape , public Printable {

public:
	Rectangle( std::string const & name , Point const & topLeft , Point const & bottomRight ) 
		:Named( name )
		,Shape( name ) 
		,Printable( name ) 
		,m_topLeft( topLeft ) 
		,m_bottomRight( bottomRight )
		{
			m_area = ( bottomRight.getX() - topLeft.getX() ) * ( bottomRight.getY() - topLeft.getY() );
	}

	virtual ~Rectangle() {}

	virtual void Print( std::ostream & stream ) const 
	{ 
		stream << getName() << " is a Rectangle, top left point: (" << m_topLeft.getX() << "," << m_topLeft.getY() << "), width: " 
			<< getWidth() << ", heigth: " << getHeight() << ", area: " << getArea() << std::endl;
	}

	double getWidth() const { return m_bottomRight.getX() - m_topLeft.getX(); }
	double getHeight() const { return m_bottomRight.getY() - m_topLeft.getY(); }
	double getArea() const { return m_area; }
	Point const & getTopLeft() const { return m_topLeft; }
	Point const & getBottomRight() const { return m_bottomRight; }

private:
	
	Point m_topLeft;
	Point m_bottomRight;
	double m_area;

	

};

class Square : public Rectangle {

public:
	Square( std::string const & name , Point const & topLeft , double edge )
		:Named( name ) 
		,Rectangle( name , topLeft , Point( "bottom right" , topLeft.getX() + edge , topLeft.getY() + edge ) ) 
		,m_edge( edge ) {}

	virtual ~Square() {}

	virtual void Print( std::ostream & stream ) const 
	{ 
		stream << getName() << " is a Square, top left point:(" << Rectangle::getTopLeft().getX()  << "," << Rectangle::getTopLeft().getY() << "), width: " << getEdge() 
			<< ", area: " << getArea() << std::endl;
	}

	double getEdge() const { return m_edge; }

private:
	double m_edge;

};

class Polyline : public Shape , public Printable {

public:
	Polyline( std::string const & name ) 
		:Named( name ) 
		,Shape( name ) 
		,Printable( name ) 
		,m_length( 0. ) {}

	virtual ~Polyline() {}

	void addPoint( Point const & point ) {
		if( m_points.is_empty() ) {
			m_points.push_back( point );			
		}
		else {
			XList< Point >::XIterator lastPoint = m_points.end();
			m_points.push_back( point );
			double dx = (*lastPoint).getX() - point.getX();
			double dy = (*lastPoint).getY() - point.getY();
			m_length += sqrt( dx * dx + dy * dy );
		}
	}

	virtual void Print( std::ostream & stream ) const { 
		if( m_points.is_empty() )
			stream << " empty polyline!";
		else
			stream << getName() << " is a Polyline, total length: " << getLength() << ", number of points: " << m_points.get_size();
	}

	double getLength() const { return m_length; }


private:
	double m_length;
	XList< Point > m_points;

};
#endif