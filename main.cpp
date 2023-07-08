#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

  class WindData {
  private:
   vector<int> windSpeed;
   vector<string> windDirection;
  public:
   WindData();
   WindData(vector<int> windSpeed, vector<string> windDirection);
   void addData(int speed, string direction);
   void printData();
   void printData(int startIndex, int endIndex);
   void findDeviation();
};

//define addData
void WindData::addData(int speed, string direction) {
  this->windSpeed.push_back(speed);
  this->windDirection.push_back(direction);
}
//define printData
void WindData::printData() {
  for (int i = 0; i < this->windSpeed.size(); i++) {
    cout << this->windSpeed.at(i) << " " << this->windDirection.at(i) << endl;
  }
}

//overload printData
void WindData::printData(int startIndex, int endIndex) {
    for (int i = startIndex; i <= endIndex; i++) {
        cout << windSpeed[i] << " " << windDirection[i] << endl;
    }
}

//constructor
WindData::WindData() {
  this->windSpeed.resize(0);
  this->windDirection.resize(0);
}
// define constructor for WindData if you want to add data to the vector
WindData::WindData(vector<int> windSpeed, vector<string> windDirection) {
  this->windSpeed = windSpeed;
  this->windDirection = windDirection;
}


// attempt to find deviation first attempt
void WindData::findDeviation() {
        // Create a copy of the windSpeed vector
        std::vector<int> sortedWindspeeds = this->windSpeed;

        // Sort the copy in ascending order
        std::sort(sortedWindspeeds.begin(), sortedWindspeeds.end());

        // Find the most common windspeed
        int mostCommon = sortedWindspeeds[0];
        int currentCount = 1;
        int maxCount = 1;

        for (size_t i = 1; i < sortedWindspeeds.size(); i++) {
            if (sortedWindspeeds[i] == sortedWindspeeds[i - 1]) {
                currentCount++;
            } else {
                if (currentCount > maxCount) {
                    maxCount = currentCount;
                    mostCommon = sortedWindspeeds[i - 1];
                }

                currentCount = 1;
            }
        }

        // Check if the last element is the most common
        if (currentCount > maxCount) {
            maxCount = currentCount;
            mostCommon = sortedWindspeeds.back();
        }

        // Print the most common windspeed
        std::cout << "Most common windspeed: " << mostCommon << std::endl;

        // Check for deviations greater than 10
        for (int windspeed : this->windSpeed) {
            if (std::abs(windspeed - mostCommon) > 10) {
                std::cout << "Deviation greater than 10: " << windspeed << std::endl;
            }
        }
    }

int main() {
//instantiate of WindData wd;
WindData wd;

// open CSV file called data.csv
ifstream file("data.csv");
// ignore the heading
string heading;
getline(file, heading);
// store windSpeed column into vector windSpeed, and windDirection into vector windDirection
string line;
while (getline(file, line)) {
  istringstream iss(line);
  string token;
  getline(iss, token, ','); // assuming the windSpeed column is the first column
  int speed = stoi(token);
  getline(iss, token, ','); // assuming the windDirection column is the second column
  string direction = token;
  wd.addData(speed, direction);
  }
wd.printData();
wd.findDeviation();
return 0;
}