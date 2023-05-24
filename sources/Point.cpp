#include "Point.hpp"
#include <cmath>
#include <stdexcept>

namespace ariel{
    
    Point::Point(double _x_pos, double _y_pos):x_pos(_x_pos), y_pos(_y_pos){}
    double Point::distance(Point another)
    {
        /* when the result is NaN (not a number).
           The exception is then caught and handled accordingly. */
        try {
            double x_diff = x_pos - another.get_X();
            double y_diff = y_pos - another.get_Y();
            double distance = sqrt(x_diff * x_diff + y_diff * y_diff);
            if (std::isnan(distance)) {
                throw std::runtime_error("Error: Invalid distance calculation.");
            }
            return distance;
            } catch (const std::exception& e) {
            /*  Handle the exception */
            std::cerr << "Exception caught: " << e.what() << std::endl;
            /*  You can choose to rethrow the exception or return a default value */
            throw std::runtime_error("Error ");; 
            /* Re-throw the exception
               return 0.0; 
               Return a default value
            */ 
        }
    }

    Point Point::moveTowards(Point p, Point another, double rad)
    {
        if (rad < 0) {
            throw  std::invalid_argument("invalid distance");
        }
        double X_diff = another.get_X() - p.x_pos;
        double Y_diff = another.get_Y() - p.y_pos;
        Point res(0.0,0.0);
        // Updating the current point's position towards the other point
        // double magnitude = pow(X_diff, 2) + pow(Y_diff, 2);
        double magnitude = sqrt(X_diff * X_diff + Y_diff * Y_diff);
        if (magnitude > rad) {
            double ratio = rad/magnitude;
            res.x_pos = p.x_pos + (X_diff * ratio);
            res.y_pos += p.y_pos + (Y_diff * ratio);
        } else {
            res.x_pos = another.get_X();
            res.y_pos = another.get_Y();
        }
        return res;
    }
    
    double Point::get_X () const 
    {
        return this->x_pos;
    }

    double Point::get_Y () const 
    {
        return this->y_pos;
    }

}