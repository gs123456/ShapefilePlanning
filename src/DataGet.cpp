// reader.cpp

#include "DataGet.hpp"


Reader::Reader(const std::string& shapefile) : reader_(shapefile) {}

std::vector<std::vector<shp::Point>> Reader::processPolygonGeometryAndGetPoints(shp::GeometryType geometryType, shp::Geometry* geometry) {
    std::vector<std::vector<shp::Point>> allPolygonPoints;

    if (geometry) {
        // 检查几何对象是否为多边形类型
        if (shp::isPolygon(geometryType)) {
            // 将几何对象强制转换为多边形对象
            shp::Polygon* polygon = dynamic_cast<shp::Polygon*>(geometry);
            if (polygon) {
                // 获取多边形的所有环
                std::vector<shp::Ring> rings = polygon->getRings();
                for (const auto& ring : rings) {
                    // 获取环中的所有点
                    std::vector<shp::Point> points = ring.getPoints();
                    allPolygonPoints.push_back(points);
                }
            }
        }
    }

    return allPolygonPoints;
}
std::vector<std::vector<shp::Point>> Reader::readAndProcessAllpoints() {


    reader_.features([&](shp::Feature feature) {

        shp::Geometry* geometry = feature.getGeometry();
        if (geometry) {
            shp::GeometryType geometryType = reader_.getGeometryType();
            std::vector<std::vector<shp::Point>> points = processPolygonGeometryAndGetPoints(geometryType, geometry);
            polygonPoints.insert(polygonPoints.end(), points.begin(), points.end());
        }
    });

    return polygonPoints;
}
std::vector<std::vector<shp::Point>> Reader::processLineGeometryAndGetPoints(shp::GeometryType geometryType, shp::Geometry* geometry) {
    std::vector<std::vector<shp::Point>> allLinePoints;

    if (geometry) {
        // 检查几何对象是否为线类型
        if (shp::isLine(geometryType)) {
            // 将几何对象强制转换为线对象
            shp::Line* line = dynamic_cast<shp::Line*>(geometry);
            if (line) {
                // 获取线的所有点
                std::vector<shp::Point> points = line->getPoints();
                allLinePoints.push_back(points);
            }
        }
    }

    return allLinePoints;
}

std::vector<std::vector<shp::Point>> Reader::readAndProcessAllLinePoints() {
    std::vector<std::vector<shp::Point>> linePoints;

    reader_.features([&](shp::Feature feature) {
        shp::Geometry* geometry = feature.getGeometry();
        if (geometry) {
            shp::GeometryType geometryType = reader_.getGeometryType();
            std::vector<std::vector<shp::Point>> points = processLineGeometryAndGetPoints(geometryType, geometry);
            linePoints.insert(linePoints.end(), points.begin(), points.end());
        }
    });



    return linePoints;
}

std::vector<std::vector<shp::Point>> Reader::processLineGeometryAndGetFirstLastPoints(shp::GeometryType geometryType, shp::Geometry* geometry) {
   std::vector<std::vector<shp::Point>>firstLastPoints;

    if (geometry) {
        // 检查几何对象是否为线类型
        if (shp::isLine(geometryType)) {
            // 将几何对象强制转换为线对象
            shp::Line* line = dynamic_cast<shp::Line*>(geometry);
            if (line) {
                // 获取线的第一个点和最后一个点
                std::vector<shp::Point> points = line->getPoints();
                if (!points.empty()) {
                    std::vector<shp::Point> firstLastPair;
                    firstLastPair.push_back(points.front());
                    firstLastPair.push_back(points.back());
                    firstLastPoints.push_back(firstLastPair);
                }
            }
        }
    }

    return firstLastPoints;
}

std::vector<std::vector<shp::Point>> Reader::readAndProcessFirstLastPointsOfAllLines() {
    std::vector<std::vector<shp::Point>>firstLastPoints;

    reader_.features([&](shp::Feature feature) {
        shp::Geometry* geometry = feature.getGeometry();
        if (geometry) {
            shp::GeometryType geometryType = reader_.getGeometryType();
            std::vector<std::vector<shp::Point>> points = processLineGeometryAndGetFirstLastPoints(geometryType, geometry);
            firstLastPoints.insert(firstLastPoints.end(), points.begin(), points.end());
        }
    });

    return firstLastPoints;
}





shp::Point Reader::calculatePolygonCenter(const std::vector<shp::Point>& points) {
    double centerX = 0.0;
    double centerY = 0.0;

    // 计算所有点的坐标之和
    for (const auto& point : points) {
        centerX += point.getX();
        centerY += point.getY();
    }

    // 计算坐标的平均值
    centerX /= points.size();
    centerY /= points.size();

    // 创建中心点对象并返回
    return shp::Point(centerX, centerY);
}
std::vector<shp::Point> Reader::calculatePolygonCenters(const std::vector<std::vector<shp::Point>>& polygonPoints) {

    // 遍历每个多边形的点集合并计算中心点
    for (const auto& points : polygonPoints) {
        shp::Point center = calculatePolygonCenter(points);
        polygonCenters.push_back(center);
    }

    return polygonCenters;
}
std::vector<shp::Point> Reader::readAndProcessCenters() {

    std::vector<std::vector<shp::Point>> polygonPoints;

    reader_.features([&](shp::Feature feature) {
        shp::Geometry* geometry = feature.getGeometry();
        if (geometry) {
            shp::GeometryType geometryType = reader_.getGeometryType();
            std::vector<std::vector<shp::Point>> points = processPolygonGeometryAndGetPoints(geometryType, geometry);
            polygonPoints.insert(polygonPoints.end(), points.begin(), points.end());
        }
    });

    // 计算并返回多边形的中心点
    std::vector<shp::Point> polygonCenters = calculatePolygonCenters(polygonPoints);
    
    return polygonCenters;
}
