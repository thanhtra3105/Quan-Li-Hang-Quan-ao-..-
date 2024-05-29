#include <iostream>
#include <fstream>
#include <string>
#include <iomanip> // dùng thư viện này để căn chỉnh vị trí in ra -> dùng hàm setw();
using namespace std;

void display()
{
    cout << left << setw(10) << "ID" << left << setw(15) << "TEN" << left << setw(15) << "GIOI TINH" << left << setw(15) << "SIZE"
         << left << setw(15) << "NAM SX" << left << setw(15) << "NUOC SX" << left << setw(15) << "MAU" << left << setw(15)
         << "GIA(VND)" << left << setw(15) << "SO LUONG" << endl;
}

class ThongTin
{
    string ID;
    string Ten;
    string GioiTinh;
    string Size;
    string NamSX;
    string NuocSX;
    string MauSac;
    int Gia, SoLuong;      // gia va so luong tung sp
    int SL;                // so luong tong cac sp
    string value[100][10]; // mang gan gia tri trong file
public:
    ThongTin()
    {
    }
    ~ThongTin() {}
    void nhap();                   // them san pham
    void hienthi(int pos);         // hien thi thong tin tung sp
    void doc_file();               // doc thong tin sp tu file
    void xoa_hang(int pos);        // xoa san pham
    void sap_xep();                // ham sap xep
    string get_ten(int pos);       // lay ten
    string get_ID(int pos);        // lay ID
    string get_GT(int pos);        // lay gioi tinh
    string get_size(int pos);      // lay size
    int get_SL(int pos);           // lay so luong cua san pham
    int get_Gia(int pos);          // lay gia
    void set_SL(int pos, string);  // set sl sp
    void set_Gia(int pos, string); // set gia sp
};

void ThongTin::nhap()
{
    fstream file;
    file.open("OUT.csv", ios::out | ios::app);
    cin.ignore();
    cout << "Nhap ma hang:";
    getline(cin, ID);

    cout << "Nhap ten hang:";
    getline(cin, Ten);

    cout << "Nhap gioi tinh:";
    getline(cin, GioiTinh);

    fflush(0); // xoa bo dem
    cout << "Nhap size:";
    getline(cin, Size);
    // cin.ignore();   // xoa ki tu cach

    cout << "Nhap nam SX:";
    getline(cin, NamSX);
    // cin.ignore();
    cout << "Nhap nuoc san xuat:";
    getline(cin, NuocSX);
    // cin.ignore();
    cout << "Nhap mau sac:";
    getline(cin, MauSac);

    fflush(0);
    cout << "Nhap gia:";
    cin >> Gia;
    cout << "Nhap so luong:";
    cin >> SoLuong;
    /// luu vao file
    if (file.is_open())
    {
        file << ID << "," << Ten << "," << GioiTinh << "," << Size << "," << NamSX << "," << NuocSX << ","
             << MauSac << "," << Gia << "," << SoLuong << "\n";
    }
    else
    {
        cout << "Khong the mo file!!!\n";
    }
    file.close();
}

void ThongTin::hienthi(int pos)
{
    ID = value[pos][0];
    Ten = value[pos][1];
    GioiTinh = value[pos][2];
    Size = value[pos][3];
    NamSX = value[pos][4];
    NuocSX = value[pos][5];
    MauSac = value[pos][6];
    Gia = stoi(value[pos][7]);
    SoLuong = stoi(value[pos][8]);

    cout << left << setw(10) << ID << left << setw(15) << Ten << left << setw(15) << GioiTinh << left << setw(15) << Size
         << left << setw(15) << NamSX << left << setw(15) << NuocSX << left << setw(15) << MauSac << left << setw(15)
         << Gia << left << setw(15) << SoLuong << endl;
}

void ThongTin::xoa_hang(int pos)
{
    fstream file;
    file.open("OUT.csv", ios::in);
    string line[20];
    int count = 0;
    while (!file.eof())
    {
        file >> line[count++];
    }
    file.close();
    file.open("OUT.csv", ios::out);
    for (int i = 0; i < count - 1; i++)
    {
        if (pos != i)
        {
            file << line[i];
            file << "\n";
        }
    }
    file.close();
}
void ThongTin::sap_xep()
{
    string line[20];
    int count = 0;
    fstream file;
    file.open("OUT.csv", ios::in);
    count = 0;
    while (!file.eof())
    {
        file >> line[count++];
    }
    file.close();

    for (int i = 1; i < SL - 1; i++)
    {
        for (int j = 1; j < SL - 1 - i; j++)
        {
            if (stoi(value[j][0]) > stoi(value[j + 1][0]))
            {
                string temp;
                temp = line[j];
                line[j] = line[j + 1];
                line[j + 1] = temp;
                // sap xep 1 luot roi ghi do file
                file.open("OUT.csv", ios::out);
                for (int i = 0; i < count - 1; i++)
                {
                    file << line[i];
                    file << "\n";
                }
                file.close();
                // mở file để đọc lại dữ liêu
                file.open("OUT.csv", ios::in);
                count = 0;
                while (!file.eof())
                {
                    file >> line[count++];
                }
                file.close();
                doc_file();
            }
        }
    }
    cout << "Da sap xep hang hoa theo ID tu nho den lon!!!" << endl;
}
void ThongTin::doc_file()
{
    for (int i = 0; i < 20; i++) // cho toi da tam 20 san pham de chay toi uu
    {
        for (int j = 0; j < 9; j++)
        {
            value[i][j] = "";
        }
    }
    fstream file;
    file.open("OUT.csv", ios::in);
    string line[20];
    SL = 0;
    int k = 0;
    while (!file.eof())
    {
        file >> line[SL++];
    }
    for (int i = 1; i < SL; i++) // cho i chay tu 1 vi line[0] se chua dong ve id,ten,...; line[1] moi chua gia tri
    {
        k = 0;
        for (int j = 0; j <= line[i].length(); j++)
        {
            if (line[i][j] == ',')
            {
                k++;
                j++;
            }
            value[i][k] += line[i][j];
        }
    }
    file.close();
}

string ThongTin::get_ID(int pos)
{
    ID = value[pos][0];
    return ID;
}
string ThongTin::get_ten(int pos)
{
    Ten = value[pos][1];
    return this->Ten;
}
int ThongTin::get_SL(int pos)
{
    SoLuong = stoi(value[pos][8]);
    return this->SoLuong;
}

string ThongTin::get_GT(int pos)
{
    GioiTinh = value[pos][2];
    return this->GioiTinh;
}
string ThongTin::get_size(int pos)
{
    Size = value[pos][3];
    return this->Size;
}
int ThongTin::get_Gia(int pos)
{
    Gia = stoi(value[pos][7]);
    return this->Gia;
}
void ThongTin::set_Gia(int pos, string gia)
{
    fstream f;
    string line[50];
    int count = 0;
    f.open("OUT.csv", ios::in);
    while (!f.eof())
    {
        f >> line[count++];
    }
    f.close();
    string temp = "";
    int dem = 0;
    int len = line[pos].length();
    int vitri = 0;
    for (int i = 0; i < len; i++)
    {
        temp += line[pos][i];
        vitri++;
        if (line[pos][i] == ',')
        {
            dem++;
            if (dem == 7)
            {
                temp += gia;
                break;
            }
        }
    }
    vitri += value[pos][7].length();
    
    while (vitri < len)
    {
        temp += line[pos][vitri];
        vitri++;
    }
    line[pos] = temp;
    f.open("OUT.csv", ios::out);
    for (int i = 0; i < count - 1; i++)
    {
        f << line[i];
        f << "\n";
    }
    f.close();
}
void ThongTin::set_SL(int pos, string sl)
{
    fstream f;
    string line[50];
    int count = 0;
    f.open("OUT.csv", ios::in);
    while (!f.eof())
    {
        f >> line[count++];
    }
    f.close();
    string temp = "";
    int dem = 0;
    int len = line[pos].length();
    int vitri = 0;
    for (int i = 0; i < len; i++)
    {
        temp += line[pos][i];
        vitri++;
        if (line[pos][i] == ',')
        {
            dem++;
            if (dem == 8)
            {
                temp += sl;
                break;
            }
        }
    }

    line[pos] = temp;
    f.open("OUT.csv", ios::out);
    for (int i = 0; i < count - 1; i++)
    {
        f << line[i];
        f << "\n";
    }
    f.close();
}
/////////////////////////////////////
class QuanLi
{
    ThongTin *t;
    int SL = 0; // so luong tat ca sp co trong kho
public:
    QuanLi()
    {
        t = new ThongTin; // cap phat bien t kieu ThongTin
    }
    ~QuanLi()
    {
        delete[] t;
    }
    void get_SL();     // lay so luong tong san pham
    void nhap();       // them san pham
    void xoa();        // xoa san pham
    void sapxep();     // sap xep theo ID
    void update();     // cap nhat hang hoa
    void hienthi();    //
    void tim_ten();    // tim theo ten
    void tim_ID();     // tim theo ID
    void kiemtra_ID(); // kiem tram so luong sp theo ID
    void loc_GT();     // loc san pham theo gioi tinh
    void loc_size();   // loc sp theo size
};

void QuanLi::nhap()
{
    t->nhap();
    SL++; // moi lan nhap 1 sp thi SL se tang len 1
}
void QuanLi::xoa()
{
    string ID;
    cout << "Nhap ID can xoa: ";
    cin >> ID;
    for (int i = 0; i < SL; i++)
    {
        if (ID == t->get_ID(i))
            t->xoa_hang(i);
    }
}
void QuanLi::sapxep()
{
    t->sap_xep();
}
void QuanLi::update()
{
    string ID;

    int choice;
    cout << "Nhap ID san pham can cap nhat: \n";
    cin >> ID;
    string sl;
    string gia;
    for (int i = 1; i < SL; i++)
    {
        if (ID == t->get_ID(i))
        {
            cout << "1. Cap nhat so luong\n";
            cout << "2. Cap nhat gia\n";
            cin >> choice;
            switch(choice)
            {
            case 1:
                cout << "Nhap so luong cap nhat: \n";
                cin >> sl;
                t->set_SL(i, sl); // set gia vao vi tri va soluong
                break;
            case 2:
                cout << "Nhap gia cap nhat: \n";
                cin >> gia;
                t->set_Gia(i, gia); // set gia vao vi tri va gia
                break;
            default:
                break;
            break;
            }
        }
    }
}
void QuanLi::hienthi()
{
    display();
    for (int i = 1; i < SL; i++)
    {
        t->hienthi(i);
    }
}

void QuanLi::get_SL()
{
    SL = 0;
    fstream f;
    string line;
    f.open("OUT.csv", ios::in);
    while (!f.eof())
    {
        f >> line;
        SL++;
    }
    f.close();
    SL--;
    //cout << "SO LUONG:" << SL << endl;
   
    t->doc_file();
}

void QuanLi::tim_ID()
{
    string ID;
    bool flag = false;
    cout << "Nhap ID san pham can tim:";
    cin >> ID;
    for (int i = 1; i < SL; i++)
    {
        if (ID == t->get_ID(i))
        {
            flag = true;
            display();
            t->hienthi(i);
        }
    }
    if (!flag)
    {
        cout << "Khong tim thay san pham" << endl;
    }
}
void QuanLi::tim_ten()
{
    string name;
    bool flag = false;
    cout << "Nhap ten san pham can tim:";
    cin >> name;
    display();
    for (int i = 1; i < SL; i++)
    {
        if (name == t->get_ten(i))
        {
            flag = true;
            t->hienthi(i);
        }
    }
    if (!flag)
    {
        cout << "Khong tim thay san pham" << endl;
    }
}

void QuanLi::kiemtra_ID()
{
    string ID;
    cout << "Nhap ID san pham can kiem tra:";
    cin >> ID;
    for (int i = 1; i < SL; i++)
    {
        if (ID == t->get_ID(i))
        {
            if (t->get_SL(i) == 0)
                cout << "San pham co ID la " << ID << " da het hang\n";
            else
                cout << "So luong con lai la:" << t->get_SL(i) << endl;
        }
    }
}

void QuanLi::loc_GT()
{
    string gt;
    cout << "Nhap gioi tinh can loc: ";
    cin >> gt;
    display();
    for (int i = 1; i < SL; i++)
    {
        if (gt == t->get_GT(i))
            t->hienthi(i); // hien thi tat ca sp co gioi tinh can loc
    }
}

void QuanLi::loc_size()
{
    string size;
    cout << "Nhap kich co can loc: ";
    cin >> size;
    display();
    for (int i = 1; i < SL; i++)
    {
        if (size == t->get_size(i))
            t->hienthi(i); // hien thi tat ca sp co gioi tinh can loc
    }
}

void copy_file() // copy file IN sang OUT
{
    // doc thong tin file IN.csv
    cout << "COPY file" << endl;
    string *line = new string[50];
    fstream f;
    f.open("IN.csv", ios::in); // mo file de doc du lieu
    int count = 0;
    while (!f.eof())
    {
        f >> line[count];
        count++;
    }
    f.close(); // close file IN.csv
    cout << count << endl;
    fstream file;
    file.open("OUT.csv", ios::out); // mo file OUT.csv để copy dữ liệu từ file IN.csv
    cout << line[0] << endl;
    for (int i = 0; i < count - 1; i++)
    {
        file << line[i];
        file << "\n";
    }
    // file << line[7];
    file.close();
    delete[] line;
}

int main()
{
    QuanLi q;
    ThongTin t;
    copy_file();
    int choice;
    do
    {
        q.get_SL();
        cout << "MENU" << endl;
        cout << "1. Quan li trang thai\n";
        cout << "2. Tien ich\n";
        cout << "3. Thong tin hang\n";
        cout << "4. Thoat\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            int p;
            cout << "1. Them hang hoa\n";
            cout << "2. Cap nhat hang hoa\n";
            cout << "3. Sap xep hang hoa\n";
            cout << "4. Xoa hang\n";
            cout << "0. Quay lai!\n";
            cin >> p;
            switch (p)
            {
            case 1:
                q.nhap();
                // system("pause");
                break;
            case 2:
                q.update();
                break;
            case 3:
                q.sapxep();
                break;
            case 4:
                q.xoa();
                break;
            default:
                break;
            }
            system("pause");
            break;

        case 2:
            int lc;
            cout << "1. Tim theo ten\n";
            cout << "2. Tim theo ID\n";
            cout << "3. Kiem tra tinh trang ma hang\n";
            cout << "4. Loc thong tin theo gioi tinh\n";
            cout << "5. Loc thong tin theo kich co\n";
            cout << "0. Quay lai!\n";
            cin >> lc;
            switch (lc)
            {
            case 1:
                q.tim_ten();
                break;
            case 2:
                q.tim_ID();
                break;
            case 3:
                q.kiemtra_ID();
                break;
            case 4:
                q.loc_GT();
                break;
            case 5:
                q.loc_size();
                break;
            default:
                break;
            }
            system("pause");
            break;

        case 3:
            q.hienthi();
            system("pause");
            break;

        case 4:
            exit(1);
        default:
            break;
        }
    } while (1);
}


/*
Nhóm yêu cầu	Chi tiết
Thông tin hàng	Mã hàng
    Tên hàng
    Giới tính
    Kích thước
    Năm sản xuất
    Nước sản xuất
    Màu sắc
    Giá
    Số lượng
Quản lý trạng thái	Cho phép cập nhật thông tin hàng (dùng file)
    Cho phép thêm (dùng file) hoặc xóa bớt thông tin hàng
    Sắp xếp theo mã hàng
Chức năng tiện ích	Tìm kiếm sản phẩm theo tên mã hàng
    Tìm kiếm sản phẩm theo tên hàng
    Cho phép lọc thông tin giới tính/kích thước
    Kiểm tra tình trạng mã hàng (đã hết hoặc còn số lượng bao nhiêu)
Thiết kế luồng	Menu chính
    Menu thông tin hàng
    Menu quản lý trạng thái
    Menu tiện ích
*/