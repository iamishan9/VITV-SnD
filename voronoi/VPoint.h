#ifndef VPoint_h
#define VPoint_h

#include "vector"

/*
	A structure that stores 2D point
*/

struct VPoint
{
public:
    
	double x, y;

	std::vector<VPoint*> sommets;;;;;;;;;;;;;;;

	/*
		Constructor for structure; x, y - coordinates
	*/

    VPoint(double nx, double ny) 
	{
		x = nx; 
		y = ny;
	}

	void AddSommet(VPoint *s) {
        sommets.push_back(s);
    }

    bool isEqual(VPoint p2) {
        return (x == p2.x) && (y == p2.y);
    }
};

#endif