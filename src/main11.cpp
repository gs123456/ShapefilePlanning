#include "DataGet.hpp"
#include <iostream>
#include <vector>
#include <iomanip>
#include "coorconv.h"
#include"Feature.hpp"
#include"WGS84UTM.hpp"
#include "UTMtoWGS84.hpp"
#include "WGS84toUTM.hpp"
#include"vgp.h"
#include <fstream>


int main() {

        // Reader reader("../data/Road.shp");
//         std::vector<std::vector<shp::Point>>FLlinePoints = reader.readAndProcessFirstLastPointsOfAllLines();
//         std::vector<std::vector<coorconv::UTMCoor>>FLutmLinePoints;
//         for (int i = 0; i < FLlinePoints.size(); ++i) {
//             const std::vector<shp::Point>& line = FLlinePoints[i];
//             std::cout << "Line " << i << " Points:" << std::endl;
//             for (const shp::Point& point : line) {
//                 std::cout << std::fixed << std::setprecision(9)<< "X: " << point.getX() << std::fixed << std::setprecision(9) <<", Y: " << point.getY() << std::endl;
//             }
//         }
//      WGS84toUTM wgs84toUtmline(FLlinePoints);
//     wgs84toUtmline.convertToUTM(FLutmLinePoints);  
//         // 输出转换后的UTM坐标
// for (int i = 1; i < FLutmLinePoints.size(); ++i) {
//     const std::vector<coorconv::UTMCoor>& utmLine = FLutmLinePoints[i];
//     std::cout << "UTM Line " << i << " Points:" << std::endl;
//     for (const coorconv::UTMCoor& utmPoint : utmLine) {
//         std::cout <<std::fixed << std::setprecision(9) << utmPoint.x << ", " <<std::fixed << std::setprecision(9)<< utmPoint.y << std::endl;
//     }
// }
//     Reader reader("../data/Road.shp");
//     std::vector<std::vector<shp::Point>>linePoints = reader. readAndProcessAllLinePoints();
//     std::vector<std::vector<coorconv::UTMCoor>>utmLinePoints;
//     // 遍历并输出线要素的点
//     for (int i = 0; i < linePoints.size(); ++i) {
//         const std::vector<shp::Point>& line = linePoints[i];
//         std::cout << "Line " << i << " Points:" << std::endl;
//         for (const shp::Point& point : line) {
//             std::cout << "X: " << point.getX() << ", Y: " << point.getY() << std::endl;
//         }
//     }
//     WGS84toUTM wgs84toUtmline(linePoints);
//     wgs84toUtmline.convertToUTM(utmLinePoints);
// // 输出转换后的UTM坐标
// for (int i = 0; i < utmLinePoints.size(); ++i) {
//     const std::vector<coorconv::UTMCoor>& utmLine = utmLinePoints[i];
//     std::cout << "UTM Line " << i << " Points:" << std::endl;
//     for (const coorconv::UTMCoor& utmPoint : utmLine) {
//         std::cout << "UTM Coor: x = " << utmPoint.x << ", y = " << utmPoint.y << std::endl;

//     }
// }
//     //  打开CSV文件以写入数据
//     std::ofstream csvFile("lineoutput.csv");

//     if (!csvFile.is_open()) {
//         std::cerr << "Failed to open CSV file." << std::endl;
//         return 1;
//     }

//     for (int i = 0; i < utmLinePoints.size(); ++i) {
//         const std::vector<coorconv:: UTMCoor>&  utmLine = utmLinePoints[i];
//         csvFile << "UTM LinePoints " << i+1 << " Points:" << std::endl;
//         for (const coorconv::UTMCoor& utmPoint : utmLine) {
//             csvFile << std::fixed << std::setprecision(9)  << utmPoint.x <<","<< std::fixed << std::setprecision(9)  << utmPoint.y << std::endl;
//         }
//     }

//     // 关闭CSV文件
//     csvFile.close();

//     return 0;
 std::vector<std::vector<shp::Point>> points; 
    WGS84toUTM converter(points);
  double x = 40.23591771 ;
  double y = 116.100057818;
   coorconv::UTMCoor utmCoord = converter.convertPointToUTM(x, y);

    // 现在你可以在这里使用utmCoord，它包含了转换后的UTM坐标
    std::cout << "UTM X: " << std::fixed << std::setprecision(9)  << utmCoord.x << ", UTM Y: " << std::fixed << std::setprecision(9)  <<utmCoord.y << std::endl;

}