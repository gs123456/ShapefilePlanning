#include "WGS84toUTM.hpp"

WGS84toUTM::WGS84toUTM(const std::vector<std::vector<shp::Point>>& points) : polygonPoints(points) {}

void WGS84toUTM::convertToUTM(std::vector<std::vector<coorconv::UTMCoor>>& utmPolygonPoints) {
    processPolygonPoints(utmPolygonPoints);
}
coorconv::UTMCoor WGS84toUTM::convertPointToUTM(double latitude, double longitude) {
    coorconv::UTMCoor utmCoord;
    double translation_x = 422700.0; 
    double translation_y = 4454100.0; 

    wgsCoord.lon = longitude;
    wgsCoord.lat = latitude;

    coorconv::LatLonToUTMXY(wgsCoord, utmCoord);
    
        utmCoord.x -= translation_x;
        utmCoord.y -= translation_y;

    return utmCoord;
}
void WGS84toUTM::processPolygonPoints(std::vector<std::vector<coorconv::UTMCoor>>& utmPolygonPoints) {
    // 循环处理多边形点并进行UTM坐标转换
    double translation_x = 422700.0; 
    double translation_y = 4454100.0; 
    for (const auto& polygon : polygonPoints) {
        std::vector<coorconv::UTMCoor> utmPolygon; // 为每个多边形创建一个内部容器
        for (const auto& point : polygon) {
            coorconv::UTMCoor utmCoord;

            // 将经纬度坐标赋值给命名的WGS84坐标对象
            wgsCoord.lon = point.getX();
            wgsCoord.lat = point.getY();

            coorconv::LatLonToUTMXY(wgsCoord, utmCoord);
                        // 对UTM坐标进行平移
            utmCoord.x -= translation_x;
            utmCoord.y -= translation_y;

            utmPolygon.push_back(utmCoord);
        }
        utmPolygonPoints.push_back(utmPolygon); // 将内部容器添加到外部容器
    }
}

