#include <iostream>
#include <vector>
#include <climits>
#include "../utils/utils.hpp"

using std::cout;
using std::endl;
using std::min;
using std::vector;
using point = std::pair<double, double>;

/**
 * @brief finds distance between two cloest points in the plane by brute force
 * @input a list of n points, n >= 2;
 * @output the distance of two cloest pair;
 */
double cloest_pair_bf(vector<point> &points)
{
    if (points.size() < 2)
        throw "the size of points should be larger than 1";

    double min_dist = __DBL_MAX__;
    for (int i = 0; i < points.size() - 1; i++)
        for (int j = i + 1; j < points.size(); j++)
            min_dist = min(min_dist,
                           pow(points[i].first - points[j].first, 2) +
                               pow(points[i].second - points[j].second, 2));

    return sqrt(min_dist);
}

int main()
{
    //vector<point> points = {point(0, 0), point(1, 1), point(0, 1), point(2, 2), point(0.3, 0.3)};
    int size = randint(2, 1000);
    vector<point> points;
    for (int i = 0; i < size; i++)
        points.push_back(point(randouble(-10, 10), randouble(-10, 10)));

    cout << cloest_pair_bf(points) << endl;
}