#include "DataGet.hpp"
#include <iostream>
#include <vector>
#include <iomanip>
#include "coorconv.h"
#include"WGS84UTM.hpp"
#include "UTMtoWGS84.hpp"
#include "WGS84toUTM.hpp"
#include"vgp.h"
int main() {
    Reader reader("../data/Road.shp");
    std::vector<std::vector<shp::Point>> polygonPoints = reader.readAndProcessAllpoints();
    // 创建一个用于存储转换后的UTM坐标的容器
    std::vector<std::vector<coorconv::UTMCoor>> utmPolygonPoints;
    std::vector<std::vector<shp::Point>>linePoints = reader. readAndProcessAllLinePoints();
    std::vector<std::vector<coorconv::UTMCoor>>utmLinePoints;

    std::vector<double> x,y;

    // 创建WGS84toUTM对象并进行坐标转换，多边形点
    WGS84toUTM wgs84toUtm(polygonPoints);
    wgs84toUtm.convertToUTM(utmPolygonPoints);
    // double latitude,longtitude;
    WGS84toUTM wgs84toUtmline(linePoints);
    wgs84toUtmline.convertToUTM(utmLinePoints);
    VGPlanner vgp;
    vgp.set_start(22.65,40.55);
    vgp.set_goal(109.88,909.33);
    vgp.set_obstacles(utmPolygonPoints);
    vgp.point2point();
    // vgp.point2build();
    vgp.get_result(x,y);
    int zone = 50;
    bool southHemi = false;
    std::vector<coorconv::UTMCoor> utmCoords; 
    UTMtoWGS84 utmToWGS84(utmCoords, zone, southHemi);

    // 调用path函数
    std::vector<coorconv::WGS84Corr> wgs84Coords = utmToWGS84.path(x, y, zone, southHemi);

    // 打印或处理WGS84坐标
    for (const auto& wgsCoord : wgs84Coords) {
        std::cout << std::fixed << std::setprecision(9) << "Longitude: " << wgsCoord.lon << " Latitude: " << std::fixed << std::setprecision(9) << wgsCoord.lat << std::endl;
    }
     
    // 调用convertPointToUTM函数将单个点转换为UTM坐标
    double latitude =40.237540239;
    double longitude =116.097282128;
    coorconv::UTMCoor utmPoint = wgs84toUtm.convertPointToUTM(latitude, longitude);
    std::cout << std::fixed << std::setprecision(9) << "x: " << utmPoint.x << " y " << std::fixed << std::setprecision(9) << utmPoint.y<< std::endl;


    return 0;
}