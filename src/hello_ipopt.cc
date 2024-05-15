#include <iostream>
#include <cassert>
#include <cppad/ipopt/solve.hpp>
// 在一个匿名的命名空间中，引入了一个AD类型，它是CppAD库中用于自动微分（Automatic Differentiation）的数据类型。AD类型可以用来表示变量和函数，使其具备微分能力。
namespace {
	using CppAD::AD;

	class FG_eval {
	public:
		typedef CPPAD_TESTVECTOR( AD<double> ) ADvector;
        // fg: function that evaluates the objective and constraints using the syntax
		// 定义一个函数运算符，用于计算目标函数和约束条件的值
		void operator()(ADvector& fg, const ADvector& x)
		{	
			//使用assert来设定fg和x的大小，以确保它们与问题的维度匹配
			//fg 向量用于存储目标函数值和约束条件值，x向量用于存储优化变量
			assert( fg.size() == 4 );
			assert( x.size()  == 4 );

			//  将 x 中的优化变量分配给 AD 类型的变量 x1 到 x4。这是在使用C++ Algorithmic Differentiation（CppAD）时定义问题中的独立变量的方式。
			AD<double> x1 = x[0];
			AD<double> x2 = x[1];
			AD<double> x3 = x[2];
			AD<double> x4 = x[3];
			// 计算目标函数的值，将其存储在 fg[0] 中。这里使用了 x1 到 x4 这些 AD 类型的变量，这意味着这个表达式将被自动微分，以便后续的梯度计算。
			fg[0] = (x1-10.24) * (x1-10.24) + 5.21*x2 + 9.9*(x3-x4)*(x3-x4);
			//  分别计算三个约束条件的值，并将它们存储在 fg[1] 和 fg[2]、 fg[3]中。
			fg[1] = x3-x4;
			fg[2] = x2;
            fg[3] = x2-x4;
			//
			std::cout << "fg[0]:" << fg[0]<< std::endl;
			std::cout << "fg[1]:" << fg[1]<< std::endl;
			std::cout << "fg[2]:" << fg[2]<< std::endl;
            std::cout << "fg[3]:" << fg[3]<< std::endl;

			return;
		}
	};
}

// 该函数用于设置和解决非线性规划问题
// 它首先定义了问题的一些基本参数，如变量数量、约束数量、变量的初始值、变量和约束的上下界等
// 然后创建一个FG_eval对象用于计算目标函数和约束条件
// 最后，使用CppAD::ipopt::solve函数来解决问题，并将结果存储在solution中
bool get_started(void)
{	bool ok = true;
	size_t i;
	// 创建了一个类型别名 Dvector，它是CppAD库中的一个向量类型，用于存储双精度（double）数值。这个向量类型是CppAD库的一部分，通常用于存储问题的变量、约束和其他向量。
	typedef CPPAD_TESTVECTOR( double ) Dvector;

	// 声明了一个 size_t 类型的变量 nx，它表示问题中独立变量（自变量）的数量，也就是问题的变量维度。在这个示例中，有4个独立变量，因此 nx 的值为4。
	size_t nx = 4;
	// 声明了一个 size_t 类型的变量 ng，它表示问题中的约束数量，也就是约束的维度。在这个示例中，有3个约束条件，因此 ng 的值为3。
	size_t ng = 3;
	//  创建了一个名为 xi 的 Dvector 类型的向量，用于存储问题的独立变量（自变量）。这个向量有4个元素，对应于4个自变量。
	Dvector xi(nx);
	// 分别为这4个独立变量设置了初始值。这些值将用作问题的初始猜测，作为非线性规划求解器的起点。
	xi[0] = 10.0;
	xi[1] = 5.0;
	xi[2] = 5.0;
	xi[3] = 100.0;

	//设置问题的变量（自变量）和约束条件的上下界（限制条件）。
	Dvector xl(nx), xu(nx);
	for(i = 0; i < nx; i++)
	{	xl[i] = 0;
		xu[i] = 100;
	}

	Dvector gl(ng), gu(ng);
	gl[0] = 2;     gu[0] = 10;
	gl[1] = 2.99;  gu[1] = 100;
	gl[2] = 0;     gu[2] = 0;

	// 创建了 FG_eval 类的对象 fg_eval，用于计算目标函数和约束条件的值。这是问题的目标函数和约束条件的具体定义。
	FG_eval fg_eval;

	// 创建了一个字符串 options，用于存储Ipopt求解器的选项。
	std::string options;
	// 设置了求解器选项，将 print_level 参数设置为0，以关闭求解器的输出，即不会在控制台打印详细信息，只打印关键信息。
	options += "Integer print_level  0\n";
	//  将 sb 参数设置为 "yes"，这表示使用平衡约束优化方法。
	options += "String  sb           yes\n";
	// 设置最大迭代次数为10次。
	options += "Integer max_iter     10\n";
	// approximate accuracy in first order necessary conditions;
	// see Mathematical Programming, Volume 106, Number 1,
	// Pages 25-57, Equation (6)
	// 设置迭代停止的收敛容差为1e-6。
	options += "Numeric tol          1e-6\n";
	//  启用了二阶导数测试，用于检查目标函数和约束条件的导数是否正确。
	options += "String  derivative_test            second-order\n";
	// maximum amount of random pertubation; e.g.,
	// when evaluation finite diff
	// 将随机扰动的半径设置为0，表示不使用扰动进行数值近似求导。
	options += "Numeric point_perturbation_radius  0.\n";

	// 创建了一个用于存储求解结果的对象 solution，
	CppAD::ipopt::solve_result<Dvector> solution;

	// 调用了 CppAD::ipopt::solve 函数，用于解决非线性规划问题。它传递了问题选项、独立变量的初始值、变量的上下界、约束条件的上下界、问题的定义（fg_eval 对象），以及存储结果的 solution 对象。
	CppAD::ipopt::solve<Dvector, FG_eval>(
		options, xi, xl, xu, gl, gu, fg_eval, solution
	);

	//检查求解器的状态，如果状态为成功（success），则 ok 变量将保持为真。这表示问题已成功求解。
	ok &= solution.status == CppAD::ipopt::solve_result<Dvector>::success;
	// 创建一个名为 check_x 的数组，其中包含了问题的精确解。这个数组中的值是问题的已知精确解。
	double check_x[]  = { 10.24, 2.99, 4.99, 2.99 }; 
	// 设置了相对容差和绝对容差的阈值。这些值用于控制验证解的精度。
	double rel_tol    = 1e-6;  // relative tolerance
	double abs_tol    = 1e-6;  // absolute tolerance
	// 遍历问题中的每个变量，进行解的验证。
	for(i = 0; i < nx; i++)
	{	
		//使用 CppAD::NearEqual 函数来比较问题的解 solution.x[i] 与精确解 check_x[i] 是否足够接近。如果它们的差距在相对容差和绝对容差的范围内，ok 变量将保持为真。
		ok &= CppAD::NearEqual(
			check_x[i],  solution.x[i],   rel_tol, abs_tol     
		); 
		// 使用 std::cout 打印每个变量的解，以便在控制台上查看结果。
        std::cout << "x[" << i << "] = " << solution.x[i] << std::endl;
	}

	return ok;
}

// main program that runs all the tests
int main(void)
{	
    std::cout << "===== Ipopt with CppAD Testing =====" << std::endl;
    bool result = get_started();
    std::cout << "Final checking: " << result << std::endl;
}
