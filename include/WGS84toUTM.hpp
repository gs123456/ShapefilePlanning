#ifndef WGS84TOUMT_HPP
#define WGS84TOUMT_HPP

#include "coorconv.h"
#include "DataGet.hpp"
#include <vector>
class WGS84toUTM {
public:
    WGS84toUTM(const std::vector<std::vector<shp::Point>>& polygonPoints);

    void convertToUTM(std::vector<std::vector<coorconv::UTMCoor>>& utmPolygonPoints);
   
   coorconv::UTMCoor convertPointToUTM(double latitude, double longitude); // 
private:
    std::vector<std::vector<shp::Point>> polygonPoints;
    coorconv::WGS84Corr wgsCoord;

    void processPolygonPoints(std::vector<std::vector<coorconv::UTMCoor>>& utmPolygonPoints);
    
};

#endif
