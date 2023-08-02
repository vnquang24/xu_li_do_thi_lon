// DEV : Vũ Nhật Quang
// Date: 02/08/2023
// Description: Tìm đường đi ngắn nhất giữa hai từ bằng thuật toán duyệt theo chiều rộng
// Complexity: O(n^2) O(5757^2)

#include <iostream> 
#include <fstream> 
#include <vector> 
#include <queue> 
using namespace std;

const int MAX = 5775; // Định nghĩa số lượng tối đa các từ (data có 5757 từ)
vector<vector<int>> dothi(MAX); // Mảng 2 chiều lưu trữ đồ thị
vector<int> visited(MAX); // Mảng lưu trạng thái đã duyệt của các đỉnh
vector<string> nhapchuoi; // Mảng lưu trữ các từ
int lienket = 0; // Biến đếm số thành phần liên thông của đồ thị

// Hàm kiểm tra hai từ có khác nhau đúng một chữ cái hay không
bool sosanh(string a, string b);

// Hàm đọc dữ liệu từ file và xây dựng đồ thị
void docdothi();

// Hàm duyệt đồ thị theo chiều sâu từ một đỉnh
void explore(int node);

// Hàm tìm vị trí của một từ trong mảng nhapchuoi
int tim (string s);

// Hàm duyệt toàn bộ đồ thị theo chiều sâu và đếm số thành phần liên thông
void duyetDFS();

// Hàm tìm đường đi ngắn nhất giữa hai từ bằng thuật toán duyệt theo chiều rộng
void duyetBFS();

bool sosanh(string a, string b)
{
    int dem = 0;
    for (int i = 0; i < 5;i++)
    {
        if (a[i] != b[i]) dem++;
    }
    return dem == 1; // Trả về true nếu hai từ khác nhau đúng một chữ cái
}

void docdothi()
{
    ifstream in;
    in.open("data.txt"); // Mở file dữ liệu
    string s;
    while (in >> s) nhapchuoi.push_back(s); // Đọc từng từ và lưu vào mảng nhapchuoi
    for (int i = 0; i < nhapchuoi.size();i++)
    {
        for (int j = i + 1; j < nhapchuoi.size();j++)
        {
            if (sosanh(nhapchuoi[i],nhapchuoi[j])) // Nếu hai từ khác nhau đúng một chữ cái
            {
                dothi[i].push_back(j); // Thêm j vào danh sách kề của i
                dothi[j].push_back(i); // Thêm i vào danh sách kề của j
            } 
        }
    }
}

void explore(int node)
{
    visited[node] = 1; // Đánh dấu đỉnh đã duyệt
    for (int i = 0; i < dothi[node].size(); i++)
    {
        int next_node = dothi[node][i];
        if (visited[next_node] != 1) { // Nếu đỉnh chưa duyệt
            explore(next_node); // Duyệt đỉnh
        }
    }
}

int tim (string s)
{
    for (int i = 0; i < nhapchuoi.size();i++)
    {
        if (s == nhapchuoi[i]) return i; // Nếu tìm thấy từ trong mảng, trả về vị trí
    }
    return -1; // Nếu không tìm thấy, trả về -1
}

void duyetDFS()
{
    for (int i = 0; i < nhapchuoi.size(); i++)
    {
        if (visited[i] == 0)  // Nếu đỉnh chưa duyệt
        {
            lienket++; // Tăng số thành phần liên thông
            explore(i); // Duyệt đỉnh
        } 
    }
    cout << "So thanh phan lien thong cua do thi : "<< lienket << endl; // In số thành phần liên thông
}

void duyetBFS()
{
    string a, b;
    cout << "Nhap vao 2 xau" << endl;
    cout << "Xau 1: ";cin >> a;
    cout << "Xau 2: ";cin >> b;
    queue<int> node;
    vector<int> nutcha(MAX); // Mảng lưu đỉnh cha của mỗi đỉnh
    vector<int> khoangcach(MAX); // Mảng lưu khoảng cách từ đỉnh bắt đầu đến mỗi đỉnh
    bool kiemtra = true;
    int u = tim(a), v = tim(b); // Tìm vị trí của hai từ trong mảng
    for (int i = 0; i < visited.size();i++) visited[i] = 0; // Khởi tạo lại mảng visited
        node.push(u); // Đẩy đỉnh bắt đầu vào queue
    while (node.size() != 0) // Trong khi queue không rỗng
    {
        int nodedangxet = node.front(); // Lấy đỉnh đầu tiên trong queue
        visited[nodedangxet] = 1; // Đánh dấu đỉnh đã duyệt
        node.pop(); // Loại bỏ đỉnh đã duyệt khỏi queue
        for (int i = 0; i < dothi[nodedangxet].size();i++) // Duyệt các đỉnh kề với đỉnh đang xét
        {
            int next_node = dothi[nodedangxet][i];
            if (visited[next_node] == 0)  // Nếu đỉnh chưa duyệt
            {
                visited[next_node] = 1; // Đánh dấu đỉnh đã duyệt
                node.push(next_node); // Đẩy đỉnh vào queue
                nutcha[next_node] = nodedangxet; // Cập nhật đỉnh cha cho đỉnh
                khoangcach[next_node] = khoangcach[u] + 1; // Cập nhật khoảng cách từ đỉnh bắt đầu
                if (next_node == v)  // Nếu đỉnh là đỉnh kết thúc
                {   
                    while(node.size() != 0) node.pop(); // Xóa tất cả các đỉnh trong queue
                    kiemtra = false; // Đánh dấu đã tìm thấy đường đi
                    break;
                } 
            }
        }
    }
    if (kiemtra == true) // Nếu không tìm thấy đường đi
    {
        cout << "Khong co duong di tu " << a << " den " << b << endl;
    }
    else  // Nếu tìm thấy đường đi
    {
        cout << "Duong di tim duoc la : ";
        int nuttieptheo = nutcha[v]; // Bắt đầu từ đỉnh kết thúc
        vector<string> ketqua; // Mảng lưu trữ đường đi
        while (nuttieptheo != u)  // Trong khi chưa đến đỉnh bắt đầu
        {
            ketqua.push_back(nhapchuoi[nuttieptheo]); // Thêm từ vào đường đi
            nuttieptheo = nutcha[nuttieptheo]; // Di chuyển đến đỉnh cha
        } 
        cout << a << " ";
        for (int i = ketqua.size() - 1; i >= 0;i--) cout << ketqua[i] << " "; // In đường đi từ đỉnh bắt đầu đến đỉnh kết thúc
        cout << b << endl; 
    } 
}

int main()
{
    docdothi(); // Đọc dữ liệu từ file và xây dựng đồ thị
    duyetDFS(); // Duyệt đồ thị theo chiều sâu và đếm số thành phần liên thông
    duyetBFS(); // Tìm đường đi ngắn nhất giữa hai từ bằng thuật toán duyệt theo chiều rộng
}