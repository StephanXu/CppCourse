#ifndef EXPRESSION_RESULT
#define EXPRESSION_RESULT

#include <iostream>
#include <iomanip>

namespace zjun {

	class line_number {
	private:
		int num;
		int width;
	public:
		line_number(int n, int w):num(n), width(w) {}

		friend std::ostream& operator << (std::ostream& os, 
			const line_number& rhs) {
			os  << "#" << std::setw(rhs.width) << std::setfill('0') 
				<< rhs.num << std::setfill(' ');
			return os;
		}
	};
} // namespace

#ifndef NDEBUG

#define xr(expr) std::cout << zjun::line_number(__LINE__, 2) \
	<< ": " << #expr << "\t==>";\
	std::cout << std::boolalpha << (expr) \
	<< std::noboolalpha << std::endl;

#define xrv(expr) std::cout << zjun::line_number(__LINE__, 2) \
	<< ": " << #expr << "\t==>";\
	expr

#else

#define  xr(expr) (expr)
#define  xrv(expr) expr

#endif //NDEBUG

#endif // EXPRESSION_RESULT