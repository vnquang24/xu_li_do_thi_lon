// DEV : Vũ Nhật Quang
// Date: 02/08/2023
// Description: Tìm số lượng thành phần liên thông mạnh trong đồ thị bằng thuật toán Kosaraju.
//              Tìm đường đi ngắn nhất giữa chúng bằng thuật toán BFS.
// Complexity: O(n^2) O(5757^2)
#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <map>
#define MAX 5757
using namespace std;

vector<vector<int>> doThi(MAX,vector<int>(MAX));
vector<vector<int>> doThiDao(MAX,vector<int>(MAX));
vector<vector<int>> thanhPhanLienThong;
vector<int> visited(MAX);
vector<int> tam;
vector<string> xauDauVao; 
stack<int> nodes;
int soThanhPhan = 0;

// Hàm đếm số lượng ký tự c trong chuỗi s
int demKyTuTrongXau(char c, string s)
{
    int dem = 0;
    for (auto i : s) if (i == c) dem++; // Duyệt qua từng ký tự trong chuỗi s, nếu ký tự đó bằng c thì tăng biến đếm lên 1
    return dem;
}

// Hàm so sánh hai chuỗi a và b, trả về true nếu tất cả các ký tự trong a đều xuất hiện trong b và số lượng không vượt quá số lượng trong b
bool soSanh(string a, string b)
{
    int dem = 0;
    map<char,int> demKyTu;
    for (int i = 1; i < 5;i++)
    {
        auto it = demKyTu.find(a[i]);
        if (it == demKyTu.end()) demKyTu[a[i]] = 1; // Nếu ký tự a[i] chưa xuất hiện trong map, thêm nó vào với giá trị là 1
        else it->second = it->second + 1; // Nếu đã xuất hiện, tăng giá trị lên 1
    }
    for (auto i : demKyTu) 
    {
        if (i.second > demKyTuTrongXau(i.first,b)) return false; // Nếu số lượng ký tự i trong a lớn hơn số lượng ký tự i trong b, trả về false
    }
    return true;
}

// Hàm đọc dữ liệu từ file và xây dựng đồ thị
void docDoThi()
{
    int dem = 0;
    ifstream in;
    in.open("data.txt"); 
    string s;
    while (in >> s) xauDauVao.push_back(s); // Đọc từng chuỗi từ file và thêm vào vector xauDauVao
    for (int i = 0; i < xauDauVao.size();i++)
    {
        for (int j = 0; j < xauDauVao.size();j++)
        {
            if (i == j) continue;
            if (soSanh(xauDauVao[i],xauDauVao[j])) 
            {
                doThi[i][j] = 1; // Nếu chuỗi i có thể chuyển thành chuỗi j, thêm cạnh từ i đến j vào đồ thị
                doThiDao[j][i] = 1; // Và thêm cạnh từ j đến i vào đồ thị đảo
                dem++;
            }
        }
    }  
}

// Hàm tìm vị trí của chuỗi s trong vector xauDauVao, trả về -1 nếu không tìm thấy
int tim(string s)
{
    for (int i = 0; i < xauDauVao.size();i++)
    {
        if (s == xauDauVao[i]) return i;
    }
    return -1;
}

// Hàm duyệt đồ thị theo chiều sâu bắt đầu từ node, dùng để xác định các thành phần liên thông của đồ thị
void duyet(int node)
{
    nodes.push(node); // Thêm node vào stack
    visited[node] = 1; // Đánh dấu node đã được duyệt
    for (int i = 0; i < xauDauVao.size(); i++)
    {
        if (doThi[node][i] == 1)
            if (visited[i]!=1) {
                duyet(i); // Nếu node i chưa được duyệt và có cạnh từ node đến i, duyệt tiếp node i
            }
    }
}

// Hàm duyệt đồ thị đảo theo chiều sâu bắt đầu từ node, dùng để xác định các thành phần liên thông mạnh của đồ thị
void duyet2(int node)
{
    tam.push_back(node); // Thêm node vào vector tạm
    visited[node] = 1; // Đánh dấu node đã được duyệt
    for (int i = 0; i < xauDauVao.size(); i++)
    {
        if (doThiDao[node][i] == 1)
            if (visited[i]!=1) {
                duyet2(i); // Nếu node i chưa được duyệt và có cạnh từ node đến i trong đồ thị đảo, duyệt tiếp node i
            }
    }
}

// Hàm tìm các thành phần liên thông mạnh của đồ thị bằng thuật toán Kosaraju
void DFS()
{
    for (int i = 0; i < xauDauVao.size(); i++)
    {
        if (visited[i] == 0) duyet(i); // Duyệt đồ thị từ mỗi node chưa được duyệt
    }
    for (int i = 0; i < visited.size();i++) visited[i] = 0; // Reset vector visited
    while (nodes.size() != 0)
    {
        int node = nodes.top();
        nodes.pop();
        for (int i = 0; i < xauDauVao.size();i++)
        {
            if (visited[i] == 0)
            {
                soThanhPhan++;
                duyet2(i); // Duyệt đồ thị đảo từ mỗi node chưa được duyệt
                if (tam.size() != 0) thanhPhanLienThong.push_back(tam); // Thêm vector tạm vào vector chứa các thành phần liên thông mạnh
                tam.clear(); // Xóa vector tạm
            }
        }
    }
    cout << "So thanh phan lien thong manh cua do thi : "<< soThanhPhan << endl; // In ra số lượng thành phần liên thông mạnh của đồ thị
}

// Hàm tìm và in ra các chuỗi cùng thành phần liên thông mạnh với chuỗi nhập vào
void inThanhPhan()
{
    string s;
    cout << "Nhap vao xau can tim :" ; cin >> s;
    int viTri = tim(s); // Tìm vị trí của chuỗi s trong vector xauDauVao
    cout << "Cac xau cung thanh phan lien thong manh voi xau dau vao la : ";
    for (int i = 0 ; i < thanhPhanLienThong.size();i++)
    {
        for (int j = 0; j < thanhPhanLienThong[i].size();j++) 
        {
            if (thanhPhanLienThong[i][j] == viTri)
            {
                for (int k = 0; k < thanhPhanLienThong[i].size();k++) cout << xauDauVao[thanhPhanLienThong[i][k]] << " "; // In ra các chuỗi cùng thành phần liên thông mạnh với s
                break;
            }
        }
    } 
    cout << endl;
}

// Hàm tìm đường đi ngắn nhất giữa hai chuỗi a và b bằng thuật toán BFS
void BFS()
{
    
    string a, b;
    cout << "Nhap vao 2 xau" << endl;
    cout << "Xau 1: ";cin >> a;
    cout << "Xau 2: ";cin >> b;
    queue<int> nodes;
    vector<int> cha(MAX); // Vector lưu cha của mỗi node
    vector<int> khoangCach(MAX); // Vector lưu khoảng cách từ node bắt đầu đến mỗi node
    bool kiemTra = true;
    int u = tim(a), v = tim(b); // Tìm vị trí của a và b trong vector xauDauVao
    if (u == -1 || v == -1) 
    {
        cout << "Mot hoac ca hai xau khong ton tai trong CSDL";
        return;
    }
    for (int i = 0; i < visited.size();i++) visited[i] = 0; // Reset vector visited
    nodes.push(u);
    while (nodes.size() != 0)
    {
        int node = nodes.front();
        visited[node] = 1;
        nodes.pop();
        for (int i = 0; i < MAX;i++)
        {
            if (doThi[node][i] == 1 && visited[i] == 0) 
            {
                visited[i] = 1;
                nodes.push(i);
                cha[i] = node; // Gán node là cha của i
                khoangCach[i] = khoangCach[u] + 1; // Tăng khoảng cách từ u đến i lên 1
                if (i == v) 
                {   
                    while(nodes.size() != 0) nodes.pop();
                    kiemTra = false;
                    break;
                } 
            }
        }
    }
    
    if (kiemTra == true)
    {
        cout << "Khong co duong di tu " << a << " den " << b << endl;
    }
    else 
    {
        cout << "Duong di tim duoc la : ";
        int nodeTiepTheo = cha[v];
        vector<string> ketQua;
        while (nodeTiepTheo != u) 
        {
            ketQua.push_back(xauDauVao[nodeTiepTheo]); // Thêm chuỗi tại vị trí nodeTiepTheo vào vector kết quả
            nodeTiepTheo = cha[nodeTiepTheo]; // Cập nhật nodeTiepTheo là cha của node hiện tại
        } 
        cout << a << " ";
        for (int i = ketQua.size() - 1; i >= 0;i--) cout << ketQua[i] << " "; // In ra đường đi từ a đến b
        cout << b << endl; 
    } 
}

int main()
{
    docDoThi(); // Đọc dữ liệu từ file và xây dựng đồ thị
	DFS(); // Tìm các thành phần liên thông mạnh của đồ thị
    inThanhPhan(); // Tìm và in ra các chuỗi cùng thành phần liên thông mạnh với chuỗi nhập vào
    BFS(); // Tìm đường đi ngắn nhất giữa hai chuỗi nhập vào
}
