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
    // Reader reader("../data/Building.shp");
    // // std::vector<std::vector<shp::Point>> polygonPoints = reader.readAndProcessAllpoints();
    // // // 创建一个用于存储转换后的UTM坐标的容器
    // // std::vector<std::vector<coorconv::UTMCoor>> utmPolygonPoints;

// int polygonCount = 0; // 用于跟踪多边形的计数器
// // 遍历外部向量
// for (const std::vector<shp::Point>& polygon : polygonPoints) {
//     // 遍历内部向量
//      std::cout << "Polygon " << polygonCount << ":" << std::endl;
//     for (const shp::Point& point : polygon) {
//         // 打印坐标
//         std::cout << "X: " << point.getX ()<< ", Y: " << point.getY() << std::endl;
//     }
        // 增加多边形计数器
//     polygonCount++;
// }

    // WGS84toUTM wgs84toUtm(polygonPoints);
    // wgs84toUtm.convertToUTM(utmPolygonPoints);
  
// 输出转换后的UTM坐标
// for (int i = 0; i < utmPolygonPoints.size(); ++i) {
//     const std::vector<coorconv::UTMCoor>& utmPolygon = utmPolygonPoints[i];
//     std::cout << "UTM PolygonPoints " << i << " Points:" << std::endl;
//     for (const coorconv::UTMCoor& utmPoint : utmPolygon) {
//         std::cout << "UTM Coor: x = " << utmPoint.x << ", y = " << utmPoint.y << std::endl;
//     }
// }
 // 打开CSV文件以写入数据
    // std::ofstream csvFile("output.csv");

    // if (!csvFile.is_open()) {
    //     std::cerr << "Failed to open CSV file." << std::endl;
    //     return 1;
    // }

    // for (int i = 0; i < utmPolygonPoints.size(); ++i) {
    //     const std::vector<coorconv:: UTMCoor>& utmPolygon = utmPolygonPoints[i];
    //     csvFile << "UTM PolygonPoints " << i << " Points:" << std::endl;
    //     for (const coorconv::UTMCoor& utmPoint : utmPolygon) {
    //         csvFile << std::fixed << std::setprecision(9)  << utmPoint.x <<","<< std::fixed << std::setprecision(9)  << utmPoint.y << std::endl;
    //     }
    // }

    // // 关闭CSV文件
    // csvFile.close();

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
        Reader reader("../data/Road.shp");
        std::vector<std::vector<shp::Point>>linePoints = reader.readAndProcessFirstLastPointsOfAllLines();
        
    // std::vector<std::vector<shp::Point>>linePoints = reader. readAndProcessFirstAndLastLinePoints();
    // std::vector<std::vector<coorconv::UTMCoor>>utmLinePoints;
    // 遍历并输出线要素的点
    for (int i = 0; i < linePoints.size(); ++i) {
        const std::vector<shp::Point>& line = linePoints[i];
        std::cout << "Line " << i << " Points:" << std::endl;
        for (const shp::Point& point : line) {
            std::cout << "X: " << point.getX() << ", Y: " << point.getY() << std::endl;
        }
    }
//     WGS84toUTM wgs84toUtmline(linePoints);
//     wgs84toUtmline.convertToUTM(utmLinePoints);
// // 输出转换后的UTM坐标
// for (int i = 1; i < utmLinePoints.size(); ++i) {
//     const std::vector<coorconv::UTMCoor>& utmLine = utmLinePoints[i];
//     std::cout << "UTM Line " << i << " Points:" << std::endl;
//     for (const coorconv::UTMCoor& utmPoint : utmLine) {
//         std::cout <<std::fixed << std::setprecision(9) << utmPoint.x << ", " <<std::fixed << std::setprecision(9)<< utmPoint.y << std::endl;
//     }
// }
    
}