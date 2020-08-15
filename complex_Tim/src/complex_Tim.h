
#ifndef COMPLEX_TIM_H

#define COMPLEX_TIM_H

//#include <cmath>
#include <sstream>
#include <exception_Tim.h>

#define TIMOTHY_COMPLEX_LOG10 2.302585092994045684018L			//constant number ln(10)
#define TIMOTHY_COMPLEX_LOG1_22 0.1988508587451651901326L		//constant number ln(1.22)
#define TIMOTHY_COMPLEX_PI 3.1415926535897932384626L			//constant number pi
#define TIMOTHY_COMPLEX_PI_2 1.5707963267948966192313L			//constant number pi / 2
#define TIMOTHY_COMPLEX_PI_4 0.7853981633974483096157L			//constant number pi / 4

__TIMOTHY_NAMESPACE_BEGIN

struct re_calculate												//ʵ��������
{
	[[nodiscard]] static long double abs(long double x);
	[[nodiscard]] static long double sqrt(long double x);						//The square root of x
	[[nodiscard]] static long double log(long double x);						//ln(x)
	[[nodiscard]] static long double log10(long double x);						//log10(x)
	[[nodiscard]] static long double logn(long double n, long double x);		//log_n(x)
	[[nodiscard]] static long double exp(long double x);						//exp(x)
	[[nodiscard]] static long double pow(long double n, long double x);			//n^(x), where n is non-negative
	[[nodiscard]] static long double sin(long double x);						//sin(x rad)
	[[nodiscard]] static long double cos(long double x);						//cos(x rad)
	[[nodiscard]] static long double tan(long double x);						//tan(x rad)
	[[nodiscard]] static long double sind(long double x);						//sin(x deg)
	[[nodiscard]] static long double cosd(long double x);						//sin(x deg)
	[[nodiscard]] static long double tand(long double x);						//sin(x deg)
	[[nodiscard]] static long double atan(long double x);						//arctan(x)
	[[nodiscard]] static long double acot(long double x);						//arccot(x)
	[[nodiscard]] static long double asin(long double x);						//arcsin(x)
	[[nodiscard]] static long double acos(long double x);						//arccos(x)
private:
	[[nodiscard]] static long double logarithm(long double x);				//ln(1+x)/(1-x)
	[[nodiscard]] static long double sine(long double x);						//sin(x) when x<PI/2
	[[nodiscard]] static long double cosine(long double x);					//cos(x) when x<PI/2
};

template <typename _Elem, typename _Res = double>				//_Elem��������ʵ�����鲿�����ͣ�_Res�����㸴����ģ�Ƚ�������ͣ�Ĭ��Ϊdouble
class complex
{
public:
	constexpr complex(const _Elem& re = 0, const _Elem& im = 0) : _re(re), _im(im) {}

	template <typename _Elemtype, typename _Restype>
	constexpr complex(const complex<_Elemtype, _Restype>& _Val) : _re(_Val._re), _im(_Val._im) {}

	[[nodiscard]] _Elem Real() const { return _re; }							//����ʵ��
	[[nodiscard]] _Elem Imag() const { return _im; }							//�����鲿

	[[nodiscard]] complex operator-() { return complex(-_re, -_im); }			//���෴��
	[[nodiscard]] complex operator~() { return complex(_re, -_im); }			//����

	//��������

	template <typename _Elemtype, typename _Restype>
	[[nodiscard]] auto operator+(const complex<_Elemtype, _Restype>& _addend) const;

	[[nodiscard]] auto operator+(const _Elem& _addend) const { return *this + static_cast<complex<_Elem>>(_addend); }

	template <typename _Elemtype, typename _Restype>
	[[nodiscard]] auto operator-(const complex<_Elemtype, _Restype>& _subtrahend) const;

	[[nodiscard]] auto operator-(const _Elem& _subtrahend) const { return *this - static_cast<complex<_Elem>>(_subtrahend); }

	template <typename _Elemtype, typename _Restype>
	[[nodiscard]] auto operator*(const complex<_Elemtype, _Restype>& _multiplier) const;

	[[nodiscard]] auto operator*(const _Elem& _multiplier) const { return *this * static_cast<complex<_Elem>>(_multiplier); }

	template <typename _Elemtype, typename _Restype>
	[[nodiscard]] auto operator/(const complex<_Elemtype, _Restype>& _divisor) const;

	[[nodiscard]] auto operator/(const _Elem& _divisor) const { return *this / static_cast<complex<_Elem>>(_divisor); }

	//�ж����

	template <typename _Elemtype, typename _Restype>
	[[nodiscard]] bool operator==(const complex<_Elemtype, _Restype>& _compl) const;

	template <typename _Elemtype>
	[[nodiscard]] bool operator==(const _Elemtype& _compl) const { return *this == static_cast<complex<_Elemtype>>(_compl); }

	//��ֵ

	template <typename _Elemtype, typename _Restype>
	complex& operator=(const complex<_Elemtype, _Restype>& _new_val) { _re = _new_val._re; _im = _new_val._im; return *this; }

	template <typename _Elemtype>
	complex& operator=(const _Elemtype& _new_val) { _re = _new_val; _im = 0; return *this; }

	template <typename _Elemtype, typename _Restype>
	complex& operator+=(const complex<_Elemtype, _Restype>& _addend) { _re += _addend._re; _im += _addend._im; return *this; }

	template <typename _Elemtype>
	complex& operator+=(const _Elemtype& _new_val) { _re += _new_val; return *this; }

	template <typename _Elemtype, typename _Restype>
	complex& operator-=(const complex<_Elemtype, _Restype>& _subtrahend) { _re -= _subtrahend._re; _im -= _subtrahend._im; return *this; }

	template <typename _Elemtype>
	complex& operator-=(const _Elemtype& _new_val) { _re -= _new_val; return *this; }

	template <typename _Elemtype, typename _Restype>
	complex& operator*=(const complex<_Elemtype, _Restype>& _multiplier) {return *this = *this * _multiplier; }

	template <typename _Elemtype>
	complex& operator*=(const _Elemtype& _new_val) { _re *= _new_val; _im *= _new_val; return *this; }

	template <typename _Elemtype, typename _Restype>
	complex& operator/=(const complex<_Elemtype, _Restype>& _divisor) { return *this = *this / _divisor; }

	complex& operator++() { ++_re; return *this; }			//ʵ����1
	complex& operator--() { --_re; return *this; }			//�鲿��1
	complex operator++(int) { return complex(_re++, _im); }	//ʵ����1
	complex operator--(int) { return complex(_re--, _im); }	//�鲿��1

	explicit operator _Elem() const { return _re; }						//��ʽת��ΪԪ�����ͣ�ֻȡʵ��
	explicit operator bool() const { return !(_re == 0 && _im == 0); }	//��ʽת��Ϊ�������ͣ����ҽ���ʵ�����鲿��������ʱΪ��

	template <typename _Elemtype, typename _Restype>
	explicit operator complex<_Elemtype, _Restype>() const				//��ͬ��������֮�������ת��
	{
		return complex<_Elemtype, _Restype>(static_cast<_Elemtype>(_re), static_cast<_Elemtype>(_im));
	}

	//���ڸ����ĸ�������

	[[nodiscard]] _Res modulus() const { return re_calculate::sqrt(_re * _re + _im * _im); }	//���ظ�����ģ
	[[nodiscard]] _Res argument() const 
	{
		return static_cast<_Res>(_re == 0 ? _im > 0 ? TIMOTHY_COMPLEX_PI_2 : _im < 0 ? -TIMOTHY_COMPLEX_PI_2 : 0
			: _re > 0 ? re_calculate::atan(static_cast<long double>(_im) / static_cast<long double>(_re))
			: _im >= 0 ? re_calculate::atan(static_cast<long double>(_im) / static_cast<long double>(_re)) + TIMOTHY_COMPLEX_PI
			: re_calculate::atan(static_cast<long double>(_im) / static_cast<long double>(_re)) - TIMOTHY_COMPLEX_PI);
	}
	complex& setmodarg(_Res _modulus, _Res _argument)											//��ģ�ͷ��Ǹ�ֵ
	{
		_re = static_cast<_Elem>(_modulus * re_calculate::cos(_argument));
		_im = static_cast<_Elem>(_modulus * re_calculate::sin(_argument));
		return *this;
	}

	//���������
	
	template <typename _outstream, typename _Elemtype, typename _Restype>
	friend _outstream& operator<<(_outstream& out, const complex<_Elemtype, _Restype>& _Val);

	template <typename _instream, typename _Elemtype, typename _Restype>
	friend _instream& operator>>(_instream& in, complex<_Elemtype, _Restype>& _Dest);

	template <typename, typename>
	friend class complex;

private:
	_Elem _re;
	_Elem _im;
};

struct complex_calculate		//����������
{
	template <typename _Elem, typename _Res>
	[[nodiscard]] static complex<_Elem, _Res> clog(complex<_Elem, _Res> z)								//��z����Ȼ��������ֵ
	{
		return complex<_Elem, _Res>(static_cast<_Elem>(re_calculate::log(z.modulus())), static_cast<_Elem>(z.argument()));
	}

	template <typename _Elem, typename _Res>
	[[nodiscard]] static complex<_Elem, _Res> clog10(complex<_Elem, _Res> z)							//����10Ϊ�׵Ķ���
	{
		return clog(z) / TIMOTHY_COMPLEX_LOG10;
	}

	template <typename _Elem, typename _Res>
	[[nodiscard]] static complex<_Elem, _Res> cpow(complex<_Elem, _Res> z, _Elem n)						//��z^n
	{
		complex<_Elem, _Res> _result;
		return _result.setmodarg(static_cast<_Res>(re_calculate::pow(z.modulus(), n)), n * z.argument());
	}

	template <typename _Elem, typename _Res>
	[[nodiscard]] static complex<_Elem, _Res> cpow(complex<_Elem, _Res> z1, complex<_Elem, _Res> z2);	//��z1^z2

	template <typename _Elem, typename _Res>
	[[nodiscard]] static complex<_Elem, _Res> cexp(complex<_Elem, _Res> z)								//����eΪ�׵�ָ��
	{
		complex<_Elem> _result;
		return _result.setmodarg(re_calculate::exp(z.Real()), z.Imag());
	}

};



struct complex_format			//�����ʽ��
{
	enum format					//�����������
	{
		def_format = 0,			//Ĭ�������ʽ��(a, b)
		std_math_format = 1,	//��ѧ���������ʽ��a+bi
		engi_math_format = 2,	//���������ʽ��a+bj
		modarg_math_format = 3,	//ģ-���������ʽ��r<theta
		magpi_math_format = 4	//ģ-���������ʽ��r<thetapi
	};

	template <typename _outstream, typename _Elemtype, typename _Restype>
	friend _outstream& operator<<(_outstream& out, const complex<_Elemtype, _Restype>& _Val);

	friend void set_complex_format(format _complex_format_setting);		//���ø��������ʽ

private:
	static inline format _compl_format = def_format;
	complex_format() = delete;
};

using cpl_cal = complex_calculate;
using compl_fmt = complex_format;

void set_complex_format(compl_fmt::format _complex_format_setting);		//���ø��������ʽ

	/*-----------------------------------------------------------------*/
	/**************************�����Ǹ�����������**************************/
	/*-----------------------------------------------------------------*/

inline long double re_calculate::abs(long double x)
{
	return x < 0.0L ? -x : x;
}

template <typename _Elem, typename _Res>
template <typename _Elemtype, typename _Restype>
inline auto complex<_Elem, _Res>::operator+(const complex<_Elemtype, _Restype>& _addend) const
{
	auto re_sum = _re + _addend._re;
	return complex<decltype(re_sum)>(re_sum, _im + _addend._im);
}

template <typename _Elem, typename _Res>
template <typename _Elemtype, typename _Restype>
inline auto complex<_Elem, _Res>::operator-(const complex<_Elemtype, _Restype>& _subtrahend) const
{
	auto re_sub = _re - _subtrahend._re;
	return complex<decltype(re_sub)>(re_sub, _im - _subtrahend._im);
}

template <typename _Elem, typename _Res>
template <typename _Elemtype, typename _Restype>
inline auto complex<_Elem, _Res>::operator*(const complex<_Elemtype, _Restype>& _multiplier) const
{
	auto re_mul = _re * _multiplier._re - _im * _multiplier._im;
	return complex<decltype(re_mul)>(re_mul, _re * _multiplier._im + _im * _multiplier._re);
}

template <typename _Elem, typename _Res>
template <typename _Elemtype, typename _Restype>
auto complex<_Elem, _Res>::operator/(const complex<_Elemtype, _Restype>& _divisor) const
{
	if (_divisor._re == 0 && _divisor._im == 0) throw divided_by_zero();
	_Elemtype square_modulus = _divisor._re * _divisor._re + _divisor._im * _divisor._im;
	auto quo_re = _re * _divisor._re + _im * _divisor._im;
	auto quo_im = _im * _divisor._re - _re * _divisor._im;
	return complex<decltype(quo_re)>(quo_re / square_modulus, quo_im / square_modulus);
}

template <typename _Elem, typename _Res>
template <typename _Elemtype, typename _Restype>
bool complex<_Elem, _Res>::operator==(const complex<_Elemtype, _Restype>& _compl) const
{
	if (_re == _compl._re && _im == _compl._im) return true;
	return false;
}

template <typename _outstream, typename _Elemtype, typename _Restype>
_outstream& operator<<(_outstream& out, const complex<_Elemtype, _Restype>& _Val)
{
	if (compl_fmt::_compl_format == compl_fmt::def_format)
		return out << '(' << _Val._re << ", " << _Val._im << ')';
	if (compl_fmt::_compl_format == compl_fmt::std_math_format
		|| compl_fmt::_compl_format == compl_fmt::engi_math_format)
	{
		bool flag1 = false, flag2 = false;
		if (_Val._re) { out << _Val._re; flag1 = true; }
		if (_Val._im)
		{
			if (flag1) out << '+';
			out << _Val._im << (compl_fmt::_compl_format == compl_fmt::std_math_format ? 'i' : 'j');
			flag2 = true;
		}
		if (!(flag1 || flag2)) out << '0';
		return out;
	}
	if (compl_fmt::_compl_format == compl_fmt::modarg_math_format)
		return out << _Val.modulus() << '<' << _Val.argument();
	if (compl_fmt::_compl_format == compl_fmt::magpi_math_format)
		return out << _Val.modulus() << '<' << _Val.argument() / TIMOTHY_COMPLEX_PI << "pi";
	throw no_format();
}

template <typename _instream, typename _Elemtype, typename _Restype>
_instream& operator>>(_instream& in, complex<_Elemtype, _Restype>& _Dest)
{
	std::string _buf;
	in >> _buf;
	size_t len = _buf.length();
	if (len == 0) return in;
	_Elemtype Re = 0, Im = 0;
	try
	{
		size_t pos;
		if (_buf.at(0) == '(')																//(a,b)ʽ����
		{
			pos = _buf.find_first_of(',');
			if (pos == std::string::npos) throw input_error();
			std::istringstream sin(_buf.substr(1, pos - 1));
			sin >> Re;
			if (sin.fail()) throw input_error();
			size_t end_pos = _buf.find_first_of(')');
			if (end_pos == std::string::npos) throw input_error();
			sin.clear();
			sin.str(_buf.substr(pos + 1, end_pos - pos - 1));
			sin >> Im;
			if (sin.fail()) throw input_error();
			_Dest._re = Re;
			_Dest._im = Im;
		}
		else if ((pos = _buf.find_first_of('<')) != std::string::npos)						//ģ-������ʽ����
		{
			std::stringstream sin(_buf.substr(0, pos));
			_Restype _modulus;
			sin >> _modulus;
			if(sin.fail()) throw input_error();
			size_t pos_p = _buf.find_first_of('p');
			if (pos_p != std::string::npos)													//����pi������
			{
				sin.clear();
				sin.str(_buf.substr(pos + 1, pos_p - pos - 1));
				_Restype _argument;
				sin >> _argument;
				if(sin.fail()) throw input_error();
				_Dest._re = static_cast<_Elemtype>(_modulus * re_calculate::cos(_argument * TIMOTHY_COMPLEX_PI));
				_Dest._im = static_cast<_Elemtype>(_modulus * re_calculate::sin(_argument * TIMOTHY_COMPLEX_PI));
			}
			else																			//������pi������
			{
				sin.clear();
				sin.str(_buf.substr(pos + 1));
				_Restype _argument;
				sin >> _argument;
				if (sin.fail()) throw input_error();
				_Dest._re = static_cast<_Elemtype>(_modulus * re_calculate::cos(_argument));
				_Dest._im = static_cast<_Elemtype>(_modulus * re_calculate::sin(_argument));
			}
		}
		else if (_buf.at(0) >= '0' && _buf.at(0) <= '9' || _buf.at(0) == '+' 
			|| _buf.at(0) == '-' || _buf.at(0) == 'i' || _buf.at(0) == 'j')	//a+bi��a+bjʽ���룬�����Ը��ſ�ͷ
		{
			bool minus = false;
			if (_buf.at(0) == '-')											//����ͷ����
			{
				minus = true;
				_buf = _buf.substr(1);
			}
			else if (_buf.at(0) == '+') _buf = _buf.substr(1);				//ȥ������
			std::istringstream sin;
			pos = _buf.find_first_of("+-");
			if (pos == std::string::npos)									//ʵ��������
			{
				size_t sigpos = _buf.find_first_of("ij");
				if (sigpos == std::string::npos)							//ʵ��
				{
					sin.str(_buf);
					_Dest._im = 0;
					sin >> _Dest._re;
					if (sin.fail()) throw input_error();
					if(minus) _Dest._re = -_Dest._re;
				}
				else if (sigpos == 0)										//����һ��i��j
				{
					_Dest._re = 0;
					_Dest._im = (minus ? -1 : 1);
				}
				else														//������
				{
					sin.str(_buf.substr(0, sigpos));
					_Dest._re = 0;
					sin >> _Dest._im;
					if (sin.fail()) throw input_error();
					if (minus) _Dest._im = -_Dest._im;
				}
			}
			else															//һ�㸴��
			{
				sin.str(_buf.substr(0, pos));
				sin >> _Dest._re;
				if (sin.fail()) throw input_error();
				if (minus) _Dest._re = -_Dest._re;
				size_t sigpos = _buf.find_first_of("ij");
				if (sigpos != std::string::npos)
				{
					if (sigpos == pos + 1)
					{
						_buf.at(sigpos) = '1';
						++sigpos;
					}
					sin.clear();
					sin.str(_buf.substr(pos + 1, sigpos - pos - 1));
					sin >> _Dest._im;
					if (sin.fail()) throw input_error();
					if (_buf.at(pos) == '-') _Dest._im = -_Dest._im;
				}
				else throw input_error();
			}
		}
		else throw input_error();
	}
	catch(...)
	{
		throw input_error();
	}
	return in;
}



__TIMOTHY_NAMESPACE_END

#endif



//template <typename, typename, typename _Elemtype>		//ɾ��
//friend auto operator+(const _Elemtype& _addend1, const complex& _addend2);

//template <typename, typename, typename _Elemtype>		//ɾ��
//friend auto operator-(const _Elemtype& _minuend, const complex& _subtrahend);

//template <typename, typename, typename _Elemtype>		//ɾ��
//friend auto operator*(const _Elemtype& _multiplier1, const complex& _multiplier2);




//template <typename _Elem, typename _Res, typename _Elemtype>		//ɾ��
//inline auto operator+(const _Elemtype& _addend1, const complex<_Elem, _Res>& _addend2)
//{
//	return _addend2 + _addend1;
//}

//template <typename _Elem, typename _Res, typename _Elemtype>		//ɾ��
//auto operator-(const _Elemtype& _minuend, const complex<_Elem, _Res>& _subtrahend)
//{
//	return (-_subtrahend) + static_cast<complex<_Elemtype>>(_minuend);
//}

//template <typename _Elem, typename _Res, typename _Elemtype>		//ɾ��
//inline auto operator*(const _Elemtype& _multiplier1, const complex<_Elem, _Res>& _multiplier2)
//{
//	return _multiplier2 * _multiplier1;
//}

