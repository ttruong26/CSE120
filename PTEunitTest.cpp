#include <iostream>
#include <cmath>
#include <cassert>

// Function for testing distance calculation
void testCalculateDistance() {
    double result = calculateDistance(0, 0, 3, 4);
    assert(fabs(result - 500.0) < 0.001); // Check if the distance calculation is correct, considering millimeter conversion
    cout << "testCalculateDistance passed." << endl;
}
