#pragma once
#include <iostream>
class GeometryCpp {

public:
    class PointCpp {
    public:
        PointCpp(int x, int y) : x(x), y(y) {}
        int getX() const { return x; }
        int getY() const { return y; }

    private:
        int x;
        int y;
    };

    static bool isSegmentIntersect(const PointCpp& p1, const PointCpp& q1, const PointCpp& p2, const PointCpp& q2) {
        auto onSegment = [](const PointCpp& p, const PointCpp& q, const PointCpp& r) {
            return (q.getX() <= std::max(p.getX(), r.getX()) && q.getX() >= std::min(p.getX(), r.getX()) &&
                    q.getY() <= std::max(p.getY(), r.getY()) && q.getY() >= std::min(p.getY(), r.getY()));
        };

        auto orientation = [](const PointCpp& p, const PointCpp& q, const PointCpp& r) {
            int val = (q.getY() - p.getY()) * (r.getX() - q.getX()) - (q.getX() - p.getX()) * (r.getY() - q.getY());
            if (val > 0) return 1;
            if (val < 0) return 2;
            return 0;
        };

        int o1 = orientation(p1, q1, p2);
        int o2 = orientation(p1, q1, q2);
        int o3 = orientation(p2, q2, p1);
        int o4 = orientation(p2, q2, q1);

        if ((o1 != o2) && (o3 != o4)) {
            return true;
        }
        if ((o1 == 0) && onSegment(p1, p2, q1)) {
            return true;
        }
        if ((o2 == 0) && onSegment(p1, q2, q1)) {
            return true;
        }
        if ((o3 == 0) && onSegment(p2, p1, q2)) {
            return true;
        }
        if ((o4 == 0) && onSegment(p2, q1, q2)) {
            return true;
        }

        return false;
    }
};

// void testGeometryCpp() {
//     GeometryCpp::PointCpp p1(1, 1);
//     GeometryCpp::PointCpp q1(10, 1);
//     GeometryCpp::PointCpp p2(1, 2);
//     GeometryCpp::PointCpp q2(10, 2);

//     bool result1 = GeometryCpp::isSegmentIntersect(p1, q1, p2, q2);
//     std::cout << "Test 1: Line segments intersect (expected: true) - Result: " << std::boolalpha << result1 << std::endl;

//     GeometryCpp::PointCpp p3(0, 0);
//     GeometryCpp::PointCpp q3(0, 3);
//     GeometryCpp::PointCpp p4(0, 1);
//     GeometryCpp::PointCpp q4(0, 4);

//     bool result2 = GeometryCpp::isSegmentIntersect(p3, q3, p4, q4);
//     std::cout << "Test 2: Line segments do not intersect (expected: false) - Result: " << std::boolalpha << result2 << std::endl;
// }

// int main() {
//     testGeometryCpp();
//     return 0;
// }
