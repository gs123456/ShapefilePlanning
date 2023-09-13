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
    std::vector<std::vector<shp::Point>>linePoints = reader. readAndProcessAllLinePoints();
    std::vector<std::vector<coorconv::UTMCoor>>utmLinePoints;
    // 遍历并输出线要素的点
    for (int i = 0; i < linePoints.size(); ++i) {
        const std::vector<shp::Point>& line = linePoints[i];
        std::cout << "Line " << i << " Points:" << std::endl;
        for (const shp::Point& point : line) {
            std::cout << "X: " << point.getX() << ", Y: " << point.getY() << std::endl;
        }
    }
    WGS84toUTM wgs84toUtmline(linePoints);
    wgs84toUtmline.convertToUTM(utmLinePoints);
// 输出转换后的UTM坐标
for (int i = 0; i < utmLinePoints.size(); ++i) {
    const std::vector<coorconv::UTMCoor>& utmLine = utmLinePoints[i];
    std::cout << "UTM Line " << i << " Points:" << std::endl;
    for (const coorconv::UTMCoor& utmPoint : utmLine) {
        std::cout << "UTM Coor: x = " << utmPoint.x << ", y = " << utmPoint.y << std::endl;
    }
}
    

    return 0;
}