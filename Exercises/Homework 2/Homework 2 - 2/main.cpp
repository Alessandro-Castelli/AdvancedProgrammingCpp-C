#include <iostream>
using namespace std;

/**
 * Class Time
 */
class Time{
protected:
    int hour;
    int minute;
    int second;

public:
    // Constructor
    Time(int h, int m, int s){
        setTime(h, m, s);
    }

    // Set the time with validation
    void setTime(int h, int m, int s) {
        if (h >= 0 && h < 24 && m >= 0 && m < 60 && s >= 0 && s < 60) {
            hour = h;
            minute = m;
            second = s;
        } else {
            hour = 0;
            minute = 0;
            second = 0;
            cout << "Invalid time. Setting to 00:00:00." << endl;
        }
    }

    // Get the current time and display it
    void getTime(int& h, int& m, int& s) const {
        h = hour;
        m = minute;
        s = second;

        cout<<"Current Time: "<< h <<":"<< m <<":" << s << endl;
    }

    // Increment the time by one second
    void incrementTime() {
        second++;
        if (second >= 60) {
            second = 0;
            minute++;
            if (minute >= 60) {
                minute = 0;
                hour++;
                if (hour >= 24) {
                    hour = 0;
                }
            }
        }
    }
};


int main() {
    Time t(100,100,100);

    t.setTime(99, 99, 99);

    t.setTime(1,0,0);

    int h, m, s;
    t.getTime(h, m, s);

    t.incrementTime();
    t.getTime(h, m, s);

    for (int i=0; i<3599;i++) {
        t.incrementTime();
    }

    t.getTime(h, m, s);

    return 0;
}
