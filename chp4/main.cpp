#include <iostream>
#include <ios>
#include <algorithm>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

typedef vector<double>::size_type vec_sz;

// 함수 선언부
istream& read_hw(istream&, vector<double>&);
double grade(double, double, const vector<double>&);
double grade(double, double, double);
double median(vector<double>);

int main(void) {
    try { // 예외 처리를 위해 try-catch 추가
        cout << "Enter your first name: ";
        string name;
        cin >> name;
        cout << "Hello, " << name << "!" << endl;

        cout << "Enter midterm and final grades: ";
        double midterm, final;
        if (!(cin >> midterm >> final)) {
            throw domain_error("Invalid input for grades.");
        }

        cout << "Enter all homework grades, then EOF (Ctrl+Z or Ctrl+D): ";
        vector<double> homework;
        read_hw(cin, homework);

        double final_grade = grade(midterm, final, homework);

        streamsize prec = cout.precision();
        cout << "Your final grade is " << setprecision(3)
            << final_grade << setprecision(prec) << endl;

    }
    catch (domain_error& e) {
        cout << endl << e.what() << endl;
        return 1;
    }

    return 0;
}

// 수정 포인트 1: istream&을 반드시 반환해야 합니다.
istream& read_hw(istream& in, vector<double>& hw) {
    if (in) {
        hw.clear();
        double x;
        while (in >> x) {
            hw.push_back(x);
        }
        in.clear(); // EOF 상태를 해제하여 이후 입력이 가능하게 함
    }
    return in; // 이 return 문이 빠져있었습니다!
}

double grade(double mid, double fin, const vector<double>& hw) {
    if (hw.size() == 0) {
        throw domain_error("No homework grades entered.");
    }
    return grade(mid, fin, median(hw));
}

double grade(double midterm, double final, double homework) {
    return midterm * 0.2 + final * 0.4 + homework * 0.4;
}

double median(vector<double> vec) {
    vec_sz size = vec.size();
    if (size == 0) {
        throw domain_error("Median of an empty vector.");
    }

    sort(vec.begin(), vec.end());
    vec_sz mid = size / 2;

    return (size % 2 == 0)
        ? (vec[mid] + vec[mid - 1]) / 2
        : vec[mid];
}
