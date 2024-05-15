#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

void main01()
{
    // MatrixXd 表示的是动态数组，初始化的时候指定数组的行数和列数
    Eigen::MatrixXd m(2, 2); 
    m(0, 0) = 3;
    m(1, 0) = 2;
    m(0, 1) = 1;
    m(1, 1) = 0;
    std::cout << m << std::endl;
}

void main02()
{
    MatrixXd m = MatrixXd::Random(3, 3);
    m = (m + MatrixXd::Constant(3, 3, 1.2)) * 101;
    cout <<"m = " << m << endl;

    VectorXd v(3);
    v << 1 , 2, 3;
    cout <<"v = " << v << endl;
    cout <<"m * v = " << endl << m * v << endl;

}

void main03()
{
    MatrixXd m0 = MatrixXd::Random(3, 3);           //随机初始化初始化的值在[-1,1]区间内,矩阵大小3X3
    MatrixXd m1 = MatrixXd::Constant(3, 3, 2.4);    //常量值初始化,矩阵里面的值全部为2.4 ,三个参数分别代表：行数，列数，常量值
    Matrix2d m2 = Matrix2d::Zero();                 //零初始化.矩阵里面的值全部为0
    Matrix3d m3 = Matrix3d::Ones();                 // 矩阵里面的值全部初始化为1
    Matrix4d m4 = Matrix4d::Identity();             //初始化为单位矩阵
    Matrix3d m5;                                    //逗号初始化
    m5 << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    cout << "m0 =" << endl << m0 << endl;
    cout << "m1 =" << endl << m1 << endl;
    cout << "m2 =" << endl << m2 << endl;
    cout << "m3 =" << endl << m3 << endl;
    cout << "m4 =" << endl << m4 << endl;
    cout << "m5 =" << endl << m5 << endl;


    MatrixXf mat = MatrixXf::Ones(2, 3);
    std::cout << "before: " << endl << mat << std::endl << std::endl;
    mat = (MatrixXf(2, 2) << 0, 1, 2, 0).finished() * mat;    //此处使用了临时变量，然后使用逗号初始化，在此必须使用finish（）方法来获取实际的矩阵对象。
    std::cout << "after: " << endl << mat << std::endl;
}

void main04()
{
    // Array
    ArrayXXf a(3, 3);
    ArrayXXf b(3, 3);

     a << 1, 2, 3,
            4, 5, 6,
            7, 8, 9;
    b << 1, 2, 3,
            1, 2, 3,
            1, 2, 3;
    cout << "a + b = " << endl << a + b << endl << endl;
    cout << "a - 2 = " << endl << a - 2 << endl;
    cout << "a * b = " << endl << a * b << endl;
    cout << "a / b = " << endl << a / b << endl;

    ArrayXXf rand = ArrayXXf::Random(2,2);     // 初始化2X2  Array
    cout << rand << endl;
    rand *= 2;
    cout << "rand = " << endl
         << rand << endl;
    cout << "rand.abs() = " << endl
         << rand.abs() << endl;
    cout << "rand.abs().sqrt() =" << endl
         << rand.abs().sqrt() << endl;
    cout << "rand.min(rand.abs().sqrt()) = " << endl
         << rand.min(rand.abs().sqrt()) << endl;

}

void main05()
{
    Matrix2i a;
    a << 1, 2, 3, 4;
    cout << "Here is the matrix a:\n" << a << endl;
    // a = a.transpose(); // !!! do NOT do this !!!
    a.transposeInPlace();
    cout << "and the result of the aliasing effect:\n" << a << endl;

    

}

int main()
{
    main05();
}
