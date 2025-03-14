#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

void displayBai1()
{

    cout << "======================================\n";
    cout << "0. Nhap n phan tu vao mang\n";
    cout << "1. Xuat mang 1 chieu noi tren ra man hinh \n";
    cout << "2. Xoa 1 phan tu tai vi tri k trong mang. \n";
    cout << "3. Liet ke nhung phan tu mang gia tri lon nhat trong mang. \n";
    cout << "4. Liet ke nhung phan tu mang gia tri nho nhat trong mang. \n";
    cout << "5. Dem so phan tu co gia tri am trong mang. \n";
    cout << "6. Cho biet gia tri am lon nhat trong mang \n";
    cout << "7. Cho biet gia tri duong nho nhat trong mang. \n";
    cout << "8. Tim mot phan tu co khoa bang x co hay khong. \n";
    cout << "9. Dem so phan tu co gia tri bang x trong mang. Neu khong co thi thong bao khong co. \n";
    cout << "-1. Thoat bai 1.\n";
    cout << "=======================================\n\n";
}

void displayBai2() {
    cout << "======================================\n";
    cout << "1. In danh sach sinh vien ra man hinh.\n";
    cout << "2. Liet ke nhung sinh vien co diem trung binh cao nhat lop\n";
    cout << "3. Cho biet so sinh vien co diem trung >= 5. Neu khong co thi thong bao khong co.\n";
    cout << "4. Tim mot sinh vien co name X trong lop hoc (X nhap tu ban phim). \n";
    cout << "5. Xoa mot sinh vien ma so cho truoc trong lop hoc. Neu khong co thi thong bao khong co\n";
    cout << "6. Chen mot sinh vien vao lop hoc, biet rang sau khi chen sanh sach sinh vien van tang dan theo diem trung binh.\n";
    cout << "-1. Thoat bai 1.\n";
    cout << "=======================================\n\n";
}

// Bai 1
class SearchingUtil
{
public:

    // find max
    static int findMaxInVector(vector<int> &v)
    {
        int max = v[0];
        for (int val : v)
        {
            if (max < val)
            {
                max = val;
            }
        }
        return max;
    }
    static int findMinInVector(vector<int> &v)
    {
        int min = v[0];
        for (int x : v)
        {
            if (min > x)
            {
                min = x;
            }
        }
        return min;
    }

    static int findMaxNegativeInVector(vector<int> &v)
    {
        int maxNegative = INT_MIN;
        for (int x : v)
        {
            if (maxNegative < x && x < 0)
            {
                maxNegative = x;
            }
        }
        return maxNegative == INT_MIN ? 0 : maxNegative;
        ;
    }

    static int findMinPositiveInVector(vector<int> &v)
    {
        int minPositive = INT_MAX;
        for (int x : v)
        {
            if (minPositive > x && x > 0)
            {
                minPositive = x;
            }
        }
        return minPositive;
    }

    static int countAllElementsSameValue(vector<int> &v, int x)
    {
        int cnt = 0;
        for (int val : v)
        {
            if (val == x)
                cnt++;
        }
        return cnt;
    }
};

class VectorUtil
{
public:
    // insert n elements
    static void insertNElements(vector<int> &v)
    {
        cout << "Enter n element : ";
        int n;
        cin >> n;
        if (n <= 0)
        {
            cout << "Invalid n element \n\n";
            return;
        }

        for (int i = 0; i < n; i++)
        {
            cout << "Enter x : ";
            int x;
            cin >> x;
            v.push_back(x);
        }
    }
    static void isExistedElement(vector<int> &v)
    {
        if (v.empty())
        {
            cout << "Vector is empty.\n";
            return;
        }
        cout << "Enter x value : ";
        int x; cin >> x;
        bool isExisted = false;
        for (int i = 0 ; i < v.size(); i++) {
            if (x == v[i])
            {
                isExisted = true;
                cout << "Co ton tai o index : " << i << endl;
            }
        }
        if (!isExisted)cout << "Khong ton tai !\n\n";
    }

    // print vector (dynamic array)
    static void printVector(vector<int> &v)
    {
        if (v.empty())
        {
            cout << "Vector is empty.\n";
            return;
        }
        cout << "Array : [ ";
        for (int x : v)
        {
            cout << x << ", ";
        }
        cout << "undefined ]" << endl;
    }

    // delete element
    static void deleteElement(vector<int> &v)
    {
        if (v.empty())
        {
            cout << "Cannot delete index at K because array is empty\n\n";
            return;
        }
        int k; cout << "Enter index K : ";
        cin >> k;

        if (k < 0 || k >= v.size())
        {
            cout << "Index : " << k << ". Out of bounds !\n\n";
            return;
        }
        v.erase(v.begin() + k);
        cout << "Completed delete value : " + k << endl;
        printVector(v);
    }

    static void printAllMaxElementsInVector(vector<int> &v)
    {
        if (v.empty())
        {
            cout << "Vector is empty.\n";
            return;
        }
        int max = SearchingUtil::findMaxInVector(v);
        cout << "All index of max elements in vector :  ";
        for (int i = 0; i < v.size(); i++)
        {
            if (max == v[i])
            {
                cout << i << " ";
            }
        }
        cout << endl;
    }
    static void printAllMinElementsInVector(vector<int> &v)
    {
        if (v.empty())
        {
            cout << "Vector is empty.\n";
            return;
        }
        int min = SearchingUtil::findMinInVector(v);
        cout << "All index of min elements in vector :  ";
        for (int i = 0; i < v.size(); i++)
        {
            if (min == v[i])
            {
                cout << i << " ";
            }
        }
        cout << endl;
    }

    static void countAllNegativeElementInVector(vector<int> &v)
    {
        if (v.empty())
        {
            cout << "Vector is empty.\n";
            return;
        }
        int count = 0;
        for (int x : v)
        {
            if (x < 0)count++;
        }
        cout << "So luong phan tu am trong vector : " << count << endl << endl;
    }




    // print max element in vector
    static void printMaxNegativeElement(vector<int> &v)
    {
        if (v.empty())
        {
            cout << "Vector is empty.\n";
            return;
        }
        int res = SearchingUtil::findMaxNegativeInVector(v);
        if (res == 0) {
            cout << "NOT FOUND max negative number\n";
            return;
        }
        cout << "Max negative element: " << SearchingUtil::findMaxNegativeInVector(v) << endl;
    }


    // Hiển thị giá trị dương nhỏ nhất trong vector
    static void printMinPositiveInVector(vector<int> &v)
    {
        if (v.empty())
        {
            cout << "Vector is empty.\n";
            return;
        }
        int minPositive = SearchingUtil::findMinPositiveInVector(v);
        if (minPositive == INT_MAX)
            cout << "No positive number in the array\n";
        else
            cout << "Minimum positive value in array: " << minPositive << "\n";
    }

    // Kiểm tra xem có phần tử x trong vector không và in kết quả
    static void printContainsElement(vector<int> &v)
    {
        if (v.empty())
        {
            cout << "Array is empty\n";
            return;
        }
        int x; cout << "Enter x value : ";
        cin >> x;
        int count = SearchingUtil::countAllElementsSameValue(v, x);
        cout << "Count " << x << " is " << count << " elements \n\n\n" ;

    }

};

class Bai1
{
private:
    vector<int> v;

public:
    Bai1(vector<int> &v)
    {
        this->v = v;
    }
    void execBai1()
    {
        while (true)
        {
            displayBai1();
            int x;
            cout << "Enter option : ";
            int option;
            cin >> option;
            if (cin.fail()) {
                cout << "Loi: Vui long nhap so nguyen!\n";
                cin.clear();  // Xóa trạng thái lỗi
                cin.ignore(10000, '\n');  // Xóa dữ liệu sai trong bộ đệm
                continue;
            }
            switch (option)
            {
            case 0:
                VectorUtil::insertNElements(v);
                break;
            case 1:
                VectorUtil::printVector(v);
                break;
            case 2:
                VectorUtil::deleteElement(v);
                break;
            case 3:
                VectorUtil::printAllMaxElementsInVector(v);
                break;
            case 4:
                VectorUtil::printAllMinElementsInVector(v);
                break;
            case 5:
                VectorUtil::countAllNegativeElementInVector(v);
                break;
            case 6:
                VectorUtil::printMaxNegativeElement(v);
                break;
            case 7:
                VectorUtil::printMinPositiveInVector(v);
                break;
            case 8:
                VectorUtil::isExistedElement(v);
                break;
            case 9:
                VectorUtil::printContainsElement(v);
                break;
            case -1:
                return;
            default:
                cout << "Lua chon khong hop le. Vui long nhap lai!\n";
            }
        }
    }
};



// Bai 2
class SinhVien {
    
    public :
    string mssv, name;
    float avgGrade;

    SinhVien(string mssv, string name, float avgGrade) {
        this->mssv = mssv;
        this->name = name;
        this-> avgGrade = avgGrade;
    }
    void display() {
        cout << "============================\n";
        cout << "Student's information : \n";
        cout << "MSSV : " << mssv << endl;
        cout << "NAME : " << name << endl;
        cout << "AVERAGE GRADE : " << avgGrade << endl;
        cout << "============================\n\n";
    }
};

class DSSV {
    private :
        vector<SinhVien> dssv;

        float getHighestAvgGradeInClass() {
            if (dssv.empty()) {
                return -1.0;
            }
            SinhVien temp = dssv[0];
            float max = temp.avgGrade;
            for (SinhVien sv : dssv) {
                if (max < sv.avgGrade) {
                    max = sv.avgGrade;
                }
            }
            return max;
        }

    public :
        DSSV() {}
        DSSV(vector<SinhVien>& dssv) {
            this->dssv = dssv;
        }
        void printAllStudents() {
            if (dssv.empty()) {
                cout << "Empty list\n\n";
                return;
            }
            for (SinhVien sv : dssv) {
                sv.display();
            }
        }
        void printStudentsHaveHighestAvgGrade() {
            float max = getHighestAvgGradeInClass();
            if (max == -1.0) {
                cout << "Empty list" << endl;
                return;
            }
            for (SinhVien sv : dssv) {
                if (sv.avgGrade == max) {
                    sv.display();
                }
            }
        }
        void printStudentsWithAvgGradeGreaterThan5() {
            if (dssv.empty()) {
                cout << "Empty list\n\n";
                return;
            }
            bool isExisted = false;
            for (SinhVien sv : dssv) {
                if (sv.avgGrade > 5.0) {
                    isExisted = true;
                    sv.display();
                } 
            }
            if (!isExisted) {
                cout << "============================================================\n";
                cout << "Not existed any student with average grade greater than 5.0\n";
                cout << "============================================================\n";
            } 
        
        }
        void findStudentByName() {
            if (dssv.empty()) {
                cout << "Empty list" << endl;
                return;
            }
            cout << "Enter name's student : ";
            cin.ignore();
            string name;
            getline(cin, name);
            bool isExisted = false;
            for (auto sv : dssv) {
                if (sv.name.find(name) != string::npos) {
                    sv.display();
                    isExisted = true;
                }
            }
            if (!isExisted) {
                cout << "=================================================\n";
                cout << "NOT FOUND ANY STUDENT HAVE NAME IS " << name << endl;
                cout << "=================================================\n";
            }
        }

        void deleteStudentById() {
            if (dssv.empty()) {
                cout << "Empty list\n\n";
                return;
            }
            cout << "Enter mssv's student : ";
            string mssv;
            cin >> mssv;
            for (int i = 0 ; i < dssv.size(); i++) {
                if (dssv[i].mssv == mssv) {
                    dssv.erase(dssv.begin() + i);    
                    cout << "Completed delete student with id : " << mssv <<" !!!\n\n";
                    printAllStudents();
                    return;
                }
            }
            cout << "=================================================\n";
            cout << "NOT FOUND ANY STUDENT HAVE MSSV : " << mssv;
            cout << "=================================================\n";
        }
        static bool cmp(SinhVien& a, SinhVien& b) {
            return a.avgGrade < b.avgGrade;
        }
        void addNewStudent() {
            cout << "=======================================================\n";
            cout << "Enter MSSV : "; string mssv; cin >> mssv; cin.ignore();
            cout << "Enter Name : "; string name; getline(cin, name);
            cout << "Enter average grade : "; float avgGrade; cin >> avgGrade; cin.ignore();
            cout << "======================================================\n";

            if (avgGrade < 0.0 || avgGrade > 10.0) {
                cout << "Invalid average grade" <<endl;
                return;
            }

            SinhVien sv(mssv, name, avgGrade);
            dssv.push_back(sv);
            sort(dssv.begin(), dssv.end(), cmp);
            cout << "Completed insert student into class !!!\n";
            sv.display();
        }

};

class Bai2 {
    private :
        DSSV dssv;
    
    public :
        Bai2(DSSV dssv) {
            this->dssv = dssv;
        }
        void execBai2() {
            while (true)
            {
                displayBai2();
                cout << "Enter option : ";
                int option; cin >> option;
                if (cin.fail()) {
                    cout << "Loi: Vui long nhap so nguyen!\n";
                    cin.clear();  // Xóa trạng thái lỗi
                    cin.ignore(10000, '\n');  // Xóa dữ liệu sai trong bộ đệm
                    continue;
                }
                switch (option)
                {
                case 1:                    
                    dssv.printAllStudents();
                    break;
                case 2 :
                    dssv.printStudentsHaveHighestAvgGrade();
                    break;
                case 3 :
                    dssv.printStudentsWithAvgGradeGreaterThan5();
                    break;

                case 4 :
                    dssv.findStudentByName();
                    break;
                case 5 :
                    dssv.deleteStudentById();
                    break;

                case 6 :
                    dssv.addNewStudent();
                    break;
                case -1:
                    return;
                default:
                    cout << "Lua chon khong hop le. Vui long nhap lai!\n";
                }
            }
            
        }
};


void displayLab3() {
    cout << "======================================\n";
    cout << "Danh sach tap tuan 3\n";
    cout << "1. Bai 1.\n";
    cout << "2. Bai 2.\n";
    cout << "Thoat chuong trinh\n";
    cout << "======================================\n\n";
}


int main()
{
    vector<int> v = {1, 2, 3, 4, 5, 
        6, 7, 8, 9, 
        10,-1,-2, -3, -4, -5, 
        -6, 100, 10 , 20,
         80, 12, 12, 3, 4};

    vector<SinhVien> listSV;
    DSSV dssv(listSV);
    Bai1 bai1(v);
    Bai2 bai2(dssv);
    while (true)
    {
        displayLab3();
        cout << "Enter option : "; int option; cin >> option;
        if (cin.fail()) {
            cout << "Loi: Vui long nhap so nguyen!\n";
            cin.clear();  // Xóa trạng thái lỗi
            cin.ignore(10000, '\n');  // Xóa dữ liệu sai trong bộ đệm
            continue;
        }
        switch (option)
        {
        case 1:
            cout << "Kiem thu bai 1.\n";
            bai1.execBai1();
            break;
        case 2 :
            cout << "Kiem thu bai 2.\n";
            bai2.execBai2();
            break;
        case 0:
            cout << "Thoat chuong trinh !!!";
            return 0;
        default:
            cout << "Lua chon khong hop le. Vui long nhap lai!\n";
        }
    }
    

}