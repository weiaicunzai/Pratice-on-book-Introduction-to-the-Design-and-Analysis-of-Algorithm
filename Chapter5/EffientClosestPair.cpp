#include <iostream>
#include <vector>
#include <chrono>
#include "../utils/utils.hpp"

using std::abs;
using std::cout;
using std::endl;
using std::min;
using std::sort;
using std::vector;
using point = std::pair<double, double>;
using clk = std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::time_point;

/**
 * @brief finds distance between two cloest points in the plane by brute force
 * @input a list of n points, n >= 2;
 * @output the distance of two cloest pair;
 */
double cloest_pair_bf(const vector<point> &points)
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

double cloest_pair_dc(const vector<point> &P, vector<point> Q)
{
    if (P.size() <= 3)
        return cloest_pair_bf(P);

    vector<point> Pl = vector<point>(P.begin(), P.begin() + P.size() / 2);
    vector<point> Pr = vector<point>(P.begin() + P.size() / 2, P.end());
    vector<point> Ql = Pl;
    vector<point> Qr = Pr;
    sort(Ql.begin(), Ql.end(), [](point p1, point p2) { return p1.second < p2.second; });
    sort(Qr.begin(), Qr.end(), [](point p1, point p2) { return p1.second < p2.second; });

    double dl = cloest_pair_dc(Pl, Ql);
    double dr = cloest_pair_dc(Pr, Qr);
    double d = min(dl, dr);

    double mid = P[P.size() / 2 - 1].first;

    vector<point> S;

    //copy all the points of Q for which |x − m| < d into array S[0..num − 1]
    for (auto x : Q)
        if (abs(x.first - mid) < d)
            S.push_back(x);

    double dminsq = pow(d, 2);

    //convert size_t to long to prevent overflow
    for (int i = 0; i < (long)S.size() - 2; i++)
    {
        int k = i + 1;
        //at tops compare 7 times
        while (k <= S.size() - 1 && pow(S[k].second - S[i].second, 2) < dminsq)
        {
            dminsq = min(dminsq,
                         pow(S[k].second - S[i].second, 2) +
                             pow(S[k].first - S[i].first, 2));
            k++;
        }
    }

    return sqrt(dminsq);
}
int main()
{

    int size = randint(15000, 15000);
    vector<point> P;
    for (int i = 0; i < size; i++)
        P.push_back(point(randouble(-10, 10), randouble(-10, 10)));
    vector<point> Q = P;

    sort(P.begin(), P.end(), [](point p1, point p2) { return p1.first < p2.first; });
    sort(Q.begin(), Q.end(), [](point p1, point p2) { return p1.second < p2.second; });

    cout << "array size: " << endl;
    cout << P.size() << endl;
    cout << endl;

    time_point<clk> t1 = clk::now();
    cout << "The divide and conquer approach's result is: " << endl;
    cout << cloest_pair_dc(P, Q) << " "
         << "and ";
    time_point<clk> t2 = clk::now();
    milliseconds diff = duration_cast<milliseconds>(t2 - t1);
    std::cout << "it takes " << diff.count() << "ms" << std::endl;
    cout << endl;

    time_point<clk> t3 = clk::now();
    cout << "The brute force approach's result is: " << endl;
    cout << cloest_pair_bf(P) << " "
         << "and ";
    time_point<clk> t4 = clk::now();
    diff = duration_cast<milliseconds>(t4 - t3);
    std::cout << "it takes " << diff.count() << "ms" << std::endl;

    cout << endl;
}