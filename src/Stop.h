
#ifndef AED_PROJ_2_STOPS_H
#define AED_PROJ_2_STOPS_H

#include <iostream>
#include <cmath>

/**
 * Pretty much a modified version of the BFS algorithm
 *
 * Big O of O(V + E)
 */

class Stop {
    std::string code;
    std::string name;
    std::string zone;
    std::pair<double, double> coordinates;
public:
    /**
     * Constructor for Stop class
     */
     explicit Stop(std::string c = "", std::string n = "", std::string z = "", double lat = 0, double lon = 0):
        code(std::move(c)), name(std::move(n)), zone(std::move(z)), coordinates(lat, lon){};


     /**Getters*/
     /**
      * Getter for the code attribute
      * @return the stop's code
      */
     std::string getCode() const {
         return code;
     }


     /**
      * Getter for the name sttribute
      * @return the stop's name
      */
     std::string getName() const{
         return name;
     }

     /**
      * Getter for the zone attribute
      * @return the stops's zone
      */

     std::string getZone() const{
         return zone;
     }

     /**
      * Getter for the latitude attribute
      * @return the stop's latitude
      */
     double getLatitude() const{
         return coordinates.first;
     }

     /**
      * Getter for the longitude attribute
      * @return the stop's longitude
      */
     double getLongitude() const{
         return coordinates.second;
     }

     /**
      * Returns the distance between this destination Stop
      * @param stop the destination stop
      * @return the distance between both stops
      */
     double getDistance(const Stop& stop) const;

};



#endif //AED_PROJ_2_STOPS_H
