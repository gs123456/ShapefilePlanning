#ifndef READER_HPP
#define READER_HPP

#include "ShapefileReader.hpp"  // 包含 ShapefileReader 类的头文件
#include <iostream>
#include <string>
#include <iomanip> 

class Reader {
public:
    Reader(const std::string& shapefile);
    std::vector<std::vector<shp::Point>> polygonPoints; // 存储多边形所有的点的容器
    std::vector<shp::Point> polygonCenters;//存储多边形中心的容器
    std::vector<std::vector<shp::Point>> processPolygonGeometryAndGetPoints(shp::GeometryType geometryType, shp::Geometry* geometry);
    std::vector<std::vector<shp::Point>> readAndProcessAllpoints();//读取并输出所有多边形所有点的接口
    std::vector<std::vector<shp::Point>>readAndProcessFirstLastPointsOfAllLines(); //第一个点和最后一个点
   std::vector<std::vector<shp::Point>> processLineGeometryAndGetFirstLastPoints(shp::GeometryType geometryType, shp::Geometry* geometry);//第一个点和最后一个点
   std::vector<std::vector<shp::Point>>processLineGeometryAndGetPoints(shp::GeometryType geometryType, shp::Geometry* geometry);
   std::vector<std::vector<shp::Point>> readAndProcessAllLinePoints();//读取并输出所有多边形的接口
   
    shp::Point calculatePolygonCenter(const std::vector<shp::Point>& points);
    std::vector<shp::Point> calculatePolygonCenters(const std::vector<std::vector<shp::Point>>& polygonPoints);
    std::vector<shp::Point> readAndProcessCenters();//读取并输出所有多边形中心坐标点的接口
private:
    shp::ShapefileReader reader_;
};

#endif // READER_HPP