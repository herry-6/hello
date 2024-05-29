#include <iostream>
#include <vector>
#include <unordered_set>
#include <cmath>
#include <algorithm>

class Point {
public:
    int x, y, n;

    Point(int x, int y, int n) : x(x), y(y), n(n) {}

    int manhattan(const Point& other) const {
        return std::abs(this->x - other.x) + std::abs(this->y - other.y);
    }

    std::vector<Point> generateCentre() const {
        std::vector<Point> centres;
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        for (auto& d : directions) {
            int newX = this->x + d[0];
            int newY = this->y + d[1];
            if (newX >= 0 && newX <= n && newY >= 0 && newY <= n) {
                centres.emplace_back(newX, newY, n);
            }
        }
        return centres;
    }

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    struct HashFunction {
        size_t operator()(const Point& p) const {
            return std::hash<int>()(p.x) ^ (std::hash<int>()(p.y) << 1);
        }
    };

    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        os << "(x, y) = (" << point.x << ", " << point.y << ")";
        return os;
    }
};

std::unordered_set<Point, Point::HashFunction> visited;

void findCentre(const std::vector<Point>& pointsList, int n, Point centre);

int sum(const std::vector<Point>& pointsList, const Point& centre) {
    int total = 0;
    for (const auto& pt : pointsList) {
        total += centre.manhattan(pt);
    }
    return total;
}

void findCentre(const std::vector<Point>& pointsList, int n, Point centre) {
    visited.insert(centre);
    std::cout << "\n--------------------------------------------------------------\n";
    std::cout << "Current centre: " << centre << "\n";
    std::cout << "Sum of manhattan distances (centre): " << sum(pointsList, centre) << "\n";

    auto newCentres = centre.generateCentre();
    for (auto it = newCentres.begin(); it != newCentres.end();) {
        if (visited.find(*it) != visited.end()) {
            it = newCentres.erase(it);
        } else {
            ++it;
        }
    }

    std::cout << "\nNew centres: \n";
    for (const auto& pt : newCentres) {
        std::cout << pt << "\n";
    }

    std::vector<int> distances;
    for (const auto& pt : newCentres) {
        distances.push_back(sum(pointsList, pt));
    }

    std::cout << "Sum of manhattan distances from new centres: ";
    for (const auto& dist : distances) {
        std::cout << dist << " ";
    }
    std::cout << "\n";

    int currentSum = sum(pointsList, centre);
    if (!distances.empty()) {
        int minDistance = *std::min_element(distances.begin(), distances.end());
        if (minDistance < currentSum) {
            Point newCentre = newCentres[std::distance(distances.begin(), std::find(distances.begin(), distances.end(), minDistance))];
            findCentre(pointsList, n, newCentre);
        } else {
            std::cout << "Finalized Minimal centre: " << centre << "\n";
            std::cout << "Cost: " << currentSum << "\n";
        }
    } else {
        std::cout << "Finalized Minimal centre: " << centre << "\n";
        std::cout << "Cost: " << currentSum << "\n";
    }
}

int main() {
    int n = 9;  // Grid dimension

    // Hardcoded coordinates of points
    int coordinates[5][2] = {
        {1, 1},
        {9, 4},
        {4, 6},
        {2, 5},
        {7, 7}
    };

    std::vector<Point> pointsList;
    for (auto& coordinate : coordinates) {
        pointsList.emplace_back(coordinate[0], coordinate[1], n);
    }

    Point initialCentre(0, 0, n);
    findCentre(pointsList, n, initialCentre);

    return 0;
}
