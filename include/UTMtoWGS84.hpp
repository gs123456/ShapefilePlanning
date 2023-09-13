#ifndef UTMTOGWS84_HPP
#define UTMTOGWS84_HPP

#include "coorconv.h"
#include <vector>
// #include"WGS84UTM.hpp"
class UTMtoWGS84 {
public:
    UTMtoWGS84(const std::vector<coorconv::UTMCoor>& utmCoords, int zone, bool southHemi);
    void convertToWGS84(std::vector<coorconv::WGS84Corr>& wgs84Coords);
    std::vector<coorconv::WGS84Corr> path( const std::vector<double>& x, const std::vector<double>& y,int zone,bool southHemi);
private:
    std::vector<coorconv::UTMCoor> utmCoords;
    int zone;
    bool southHemi;
    double RadToDeg(double radians);
    void processUTMCoordinates(std::vector<coorconv::WGS84Corr>& wgs84Coords);
};

#endif
