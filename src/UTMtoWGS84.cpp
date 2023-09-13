#include "UTMtoWGS84.hpp"

UTMtoWGS84::UTMtoWGS84(const std::vector<coorconv::UTMCoor>& utmCoords, int zone, bool southHemi)
    : utmCoords(utmCoords), zone(zone), southHemi(southHemi) {}

void UTMtoWGS84::convertToWGS84(std::vector<coorconv::WGS84Corr>& wgs84Coords) {
    processUTMCoordinates(wgs84Coords);
}
double UTMtoWGS84::RadToDeg(double radians) {
    return radians * 180.0 / M_PI;
}
void UTMtoWGS84::processUTMCoordinates(std::vector<coorconv::WGS84Corr>& wgs84Coords) {
    wgs84Coords.clear();

coorconv::WGS84Corr wgsCoord; // 在循环之外声明 wgsCoord 变量

    for (auto& utmCoord : utmCoords) {
        // 添加平移坐标到输入的UTM坐标
    double translation_x = 422700.0; 
    double translation_y = 4454100.0; 

        utmCoord.x += translation_x;
        utmCoord.y += translation_y;

        // 使用UTMXYToLatLon函数进行UTM到WGS84的转换
        coorconv::UTMXYToLatLon(utmCoord, zone, southHemi, wgsCoord);

        // 转换纬度和经度到度数
        wgsCoord.lat = UTMtoWGS84::RadToDeg(wgsCoord.lat);
        wgsCoord.lon = UTMtoWGS84::RadToDeg(wgsCoord.lon);

        wgs84Coords.push_back(wgsCoord);
    }
    }
std::vector<coorconv::WGS84Corr> UTMtoWGS84::path(const std::vector<double>& x,const std::vector<double>& y,int zone,bool southHemi) {
    std::vector<coorconv::UTMCoor> utmCoords;

    // 从x和y填充utmCoords
    for (size_t i = 0; i < x.size(); ++i) {
        coorconv::UTMCoor utmCoord;
        utmCoord.x = x[i];
        utmCoord.y = y[i];
        utmCoords.push_back(utmCoord);
    }

    // 创建UTMtoWGS84对象
    UTMtoWGS84 utmToWGS84(utmCoords, zone, southHemi);

    // 创建一个向量以存储WGS84坐标
    std::vector<coorconv::WGS84Corr> wgs84Coords;

    // 将UTM转换为WGS84
    utmToWGS84.convertToWGS84(wgs84Coords);

    return wgs84Coords;
}


// std::vector<double> x = {35.65065133, 40.05733914};
//     std::vector<double> y = {66.738428497, 72.45333006};
//     int zone = 50;
//     bool southHemi = false;
//     std::vector<coorconv::UTMCoor> utmCoords; 
//     UTMtoWGS84 utmToWGS84(utmCoords, zone, southHemi);

//     // 调用path函数
//     std::vector<coorconv::WGS84Corr> wgs84Coords = utmToWGS84.path(x, y, zone, southHemi);

//     // 打印或处理WGS84坐标
//     for (const auto& wgsCoord : wgs84Coords) {
//         std::cout << "Longitude: " << wgsCoord.lon << " Latitude: " << wgsCoord.lat << std::endl;
//     }