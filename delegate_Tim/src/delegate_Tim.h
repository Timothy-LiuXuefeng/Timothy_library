
#ifndef DELEGATE_TIM_H

#define DELEGATE_TIM_H

#include <cstdarg>
#include <typeinfo>
#include <exception_Tim.h>
#include <set>
#include <limits>

#ifdef _DEBUG

#include <iostream>
using std::cout; 
using std::endl; 

#endif

__TIMOTHY_NAMESPACE_BEGIN

template <typename _Rtn, typename..._arg>											//����ֵ����Ϊ_Rtn����������Ϊ_arg��ί�У������������Ϊvoid������Դ�ģ�����
class delegate
{
public:
	typedef _Rtn(*FUNPTR)(_arg...);
	constexpr static inline unsigned int npos = std::numeric_limits<unsigned int>::max();	//��������ʾ�Ҳ���λ��

	//���캯��

	delegate() : _fp(new FUNPTR[1]), _func_num(0), _capacity(1) {}
	delegate(FUNPTR func) : _fp(new FUNPTR[1]), _func_num(1), _capacity(1) { _fp[0] = func; }		//����ί��
	delegate(unsigned int _num, ...);									//�ಥί�У�ί�еĺ�������Ϊ_num
	delegate(unsigned int _cap) : _fp(new FUNPTR[_cap == 0 ? (++_cap) : _cap]), 
		_func_num(0), _capacity(_cap) {}											//Ԥ�ȸ�ί�з���_cap��������1��������ָ��Ŀռ�
	delegate(FUNPTR* _First, FUNPTR* _Last);										//�ಥί�У�������ָ������_First��_Lastȫ��ί�У�����_First��������_Last��
	delegate(const delegate& _srcdelg);
	delegate(delegate&& _srcdelg) noexcept
	{
		_capacity = _func_num = _srcdelg._func_num;
		_fp = _srcdelg._fp;
		_srcdelg._fp = nullptr;
		_srcdelg._func_num = 0;
	}

	//ʹ��ί��

	void reset() { _func_num = 0; }											//����ί�У�ʹ�䲻ί���κκ���
	void __cdecl reset(unsigned int _num, ...);								//����ί�У�ʹ��ί��_num��������_num���������ֻ��_num������ָ����Ϊ����
	void clear();															//����ί�У�������ڴ�ռ�
	void clear(FUNPTR _newfunc);											//����ί�У�����ڴ�ռ䣬��ʹ��ί��1������
	void __cdecl clear(unsigned int _num, ...);								//����ί�У�����ڴ�ռ䣬��ʹ��ί��_num��������_num���������ֻ��_num������ָ����Ϊ����
	void __cdecl append(unsigned int _num, ...);							//�ں������_num��ί�У�_num���������ֻ��_num������ָ����Ϊ����
	void allocate(unsigned int _num);										//����ί�У������·���_num������ָ��Ŀռ䣬������Ϊ1
	void reallocate();														//��������ڴ�ռ���С���뵱ǰί�еĺ�����������ͬ
	void change(FUNPTR _From, FUNPTR _To);									//������_fromָ��ĺ����滻Ϊ_toָ��ĺ���
	void insert(unsigned int _Pos, FUNPTR _Func);							//��_Posλ�ò��뺯��_Func����_Pos >= _func_num����β������
	void insert(unsigned int _Pos, const FUNPTR* const _Start, int _Num);	//��_Posλ�ò���Ӻ���_Start��ʼ��_Num������
	void erase(unsigned int _Pos, unsigned int _Num = 1);					//ɾ����_Pos��ʼ��_Num��������_NumĬ��Ϊ1
	[[nodiscard]] unsigned int find(FUNPTR _toFind) const;								//Ѱ��_toFindָ��ĺ������ֵĵ�һ��λ�ã����Ҳ���������Timothy::delegate<_Rtn, _arg...>::npos
	[[nodiscard]] unsigned int find(unsigned int _StartPos, FUNPTR _ToFind) const;		//Ѱ�Ҵ�_startPosλ�ÿ�ʼ��_toFindָ��ĺ������ֵĵ�һ��λ�ã����Ҳ���������Timothy::delegate<_Rtn, _arg...>::npos
	[[nodiscard]] unsigned int rfind(FUNPTR _ToFind) const;								//Ѱ��_toFindָ��ĺ������ֵ����һ��λ�ã����Ҳ���������Timothy::delegate<_Rtn, _arg...>::npos
	[[nodiscard]] unsigned int rfind(unsigned int _EndPos, FUNPTR _ToFind) const;		//Ѱ�Ҵ�_endPos֮ǰ��_toFindָ��ĺ������ֵ����һ��λ�ã����Ҳ���������Timothy::delegate<_Rtn, _arg...>::npos

	
	//���²�������������С�ѷ�����ڴ�ռ�

	_Rtn operator() (_arg...) const;										//�������ί�еĸ����������������һ�����õĺ����ķ���ֵ
	delegate& operator= (const delegate& _newdelg);							//ί��֮���໥��ֵ
	delegate& operator= (delegate && _newdelg) noexcept;					//ί�е��ƶ���ֵ
	delegate& operator= (FUNPTR _newfunc);									//��ί�����¸�ֵ����Ϊ����ί��
	delegate& operator+= (const delegate& _adddelg);						//��ί��β�������һ��ί��_adddelg
	delegate& operator+= (FUNPTR _addfunc);									//��β�����_addfuncָ��ĺ���
	delegate& operator-= (const delegate& _subdelg);						//�����һ��ί��_subdelgί�е����к����ڱ�ί��������ί��
	delegate& operator-= (FUNPTR _subfunc);									//������һ��_addfuncָ��ĺ���
	delegate& operator*= (unsigned int times);								//��ί�з��������ظ�times��
	[[nodiscard]] delegate operator+ (const delegate& _adddelg) const;		//����һ��ί�У�Ϊ����ί�����
	[[nodiscard]] delegate operator+ (FUNPTR _addfunc) const;				//����һ��ί�У�Ϊһ��ί����һ���������
	[[nodiscard]] delegate operator- (const delegate& _subdelg) const;		//����һ��ί�У�Ϊǰһ��ί�������һ��ί��_subdelgί�е����к�����ǰһ��ί��������ί��
	[[nodiscard]] delegate operator- (FUNPTR _subfunc) const;				//����һ��ί�У�Ϊԭί��������һ��_addfuncָ��ĺ�����õ���ί��
	[[nodiscard]] delegate operator* (unsigned int times) const;			//����һ��ί�У�Ϊһ��ί���ظ�times��
	FUNPTR& operator[] (unsigned int _Pos);									//���ص�_Pos��ί�еĺ�����ָ�룬���_Pos������ί�еĺ������������׳��쳣Timothy::out_range
	const FUNPTR& operator[] (unsigned int _Pos) const;						//���ص�_Pos��ί�еĺ�����ָ�룬���_Pos������ί�еĺ������������׳��쳣Timothy::out_range
	[[nodiscard]] unsigned int NumOfFuncs() const { return _func_num; }		//���ص�ǰί�еĺ����ĸ���
	[[nodiscard]] bool empty() const { return !_func_num; }					//�ж�ί���Ƿ�Ϊ��

	//��ȡί�еĸ�������

	[[nodiscard]] inline unsigned int number() const { return _func_num; }	//��ȡ��ǰί�еĺ�������
	[[nodiscard]] inline unsigned int capacity() const { return _capacity; }//��ȡ��ǰί�е�����

	//��������

	~delegate() { delete[] _fp; }

protected:
	FUNPTR* _fp;
	unsigned int _func_num;
	unsigned int _capacity;
}; 

template <typename... _arg>
using Action = delegate<void, _arg...>;										//�޷���ֵ��ί��

template <typename _Rtn, typename..._arg>
delegate<_Rtn, _arg...>::delegate(unsigned int _num, ...)
{
	if (!_num)
	{
		_fp = new FUNPTR[1];
		_capacity = 1;
		_func_num = 0;
		return;
	}
	_fp = new FUNPTR[_num];
	_capacity = _func_num = _num;
	va_list ap;
	va_start(ap, _num);
	for (unsigned int i = 0; i < _num; ++i)
		_fp[i] = va_arg(ap, FUNPTR);
	va_end(ap);
}

template <typename _Rtn, typename..._arg>
delegate<_Rtn, _arg...>::delegate(FUNPTR* _First, FUNPTR* _Last)
{
	if (_First == _Last)
	{
		_fp = new FUNPTR[1];
		_capacity = 1;
		_func_num = 0;
		return;
	}
	_fp = new FUNPTR[_capacity = _func_num = _Last - _First];
	for (unsigned int i = 0; i < _func_num; ++i)
		_fp[i] = _First[i];
}

template <typename _Rtn, typename..._arg>
delegate<_Rtn, _arg...>::delegate(const delegate& _srcdelg)
{
	if (&_srcdelg == this)
	{
		_capacity = 1;
		_func_num = 0;
		_fp = new FUNPTR[1];
		return;
	}
	_capacity = _func_num = _srcdelg._func_num;
	_fp = new FUNPTR[_func_num];
	for (int i = 0; i < _func_num; ++i)
		_fp[i] = _srcdelg[i];
}

template <typename _Rtn, typename..._arg>
void delegate<_Rtn, _arg...>::reset(unsigned int _num, ...)
{
	if (_capacity < _num)
	{
		delete[] _fp;
		_fp = new FUNPTR[_capacity = _num];
	}
	_func_num = _num;
	va_list ap;
	va_start(ap, _num);
	for (unsigned int i = 0; i < _num; ++i)
		_fp[i] = va_arg(ap, FUNPTR);
	va_end(ap);
}

template <typename _Rtn, typename..._arg>
inline void delegate<_Rtn, _arg...>::clear()
{
	delete[] _fp;
	_func_num = 0;
	_capacity = 1;
	_fp = new FUNPTR[1];
}

template <typename _Rtn, typename..._arg>
inline void delegate<_Rtn, _arg...>::clear(FUNPTR _newfunc)
{
	delete[] _fp; 
	_fp = new FUNPTR[1]; 
	_fp[0] = _newfunc; 
	_func_num = _capacity = 1; 
}

template <typename _Rtn, typename..._arg>
void delegate<_Rtn, _arg...>::clear(unsigned int _num, ...)
{
	delete[] _fp;
	_func_num = _num;
	if (!_num)
	{
		_fp = new FUNPTR[_capacity = 1];
		return;
	}
	_fp = new FUNPTR[_capacity = _num];
	va_list ap;
	va_start(ap, _num);
	for (unsigned int i = 0; i < _num; ++i)
		_fp[i] = va_arg(ap, FUNPTR);
	va_end(ap);
}

template <typename _Rtn, typename..._arg>
void delegate<_Rtn, _arg...>::append(unsigned int _num, ...)
{
	if (!_num) return;
	if (_func_num + _num > _capacity)
	{
		while ((_capacity *= 2) < _func_num + _num);
		FUNPTR* newAlloc = new FUNPTR[_capacity];
		for (unsigned int i = 0; i < _func_num; ++i)
			newAlloc[i] = _fp[i];
		delete[] _fp;
		_fp = newAlloc;
	}
	va_list ap;
	va_start(ap, _num);
	for (unsigned int i = _func_num; i < _func_num + _num; ++i)
		_fp[i] = va_arg(ap, FUNPTR);
	va_end(ap);
	_func_num += _num;
}

template <typename _Rtn, typename..._arg>
inline void delegate<_Rtn, _arg...>::allocate(unsigned int _num)
{
	delete[] _fp;
	if (!_num) ++_num;
	_capacity = _num;
	_func_num = 0;
	_fp = new FUNPTR[_num];
} 

template <typename _Rtn, typename..._arg>
void delegate<_Rtn, _arg...>::reallocate()
{
	if (_capacity == _func_num || _capacity == 1) return; 
	FUNPTR* newfp; 
	if (_func_num)
	{
		newfp = new FUNPTR[_func_num]; 
		for (unsigned int i = 0; i < _func_num; ++i)
			newfp[i] = _fp[i]; 
	}
	else newfp = new FUNPTR[1]; 
	delete[] _fp; 
	_fp = newfp; 
}

template <typename _Rtn, typename..._arg>
_Rtn delegate<_Rtn, _arg...>::operator()(_arg... argu) const
{
	if (!_func_num) throw empty_delegate();
	for (unsigned int i = 0; i < _func_num - 1; ++i)
		_fp[i](argu...);
	return _fp[_func_num - 1](argu...);
}

template <typename _Rtn, typename..._arg>
delegate<_Rtn, _arg...>& delegate<_Rtn, _arg...>::operator= (const delegate& _newdelg)
{
	if (&_newdelg == this) return *this;
	_func_num = _newdelg._func_num;
	if (_capacity < _newdelg._func_num)
	{
		delete[] _fp;
		_fp = new FUNPTR[_capacity = _func_num];
	}
	for (unsigned int i = 0; i < _func_num; ++i)
		_fp[i] = _newdelg._fp[i];
	return *this;
}

template <typename _Rtn, typename..._arg>
delegate<_Rtn, _arg...>& delegate<_Rtn, _arg...>::operator= (delegate&& _newdelg) noexcept
{
	delete[] _fp;
	_func_num = _newdelg._func_num;
	_capacity = _newdelg._capacity;
	_newdelg._func_num = _newdelg._capacity = 0;
	_fp = _newdelg._fp;
	_newdelg._fp = nullptr;
	return *this;
}

template <typename _Rtn, typename..._arg>
inline delegate<_Rtn, _arg...>& delegate<_Rtn, _arg...>::operator= (FUNPTR _newfunc)
{
	_func_num = 1;
	_fp[0] = _newfunc;
	return *this;
}

template <typename _Rtn, typename..._arg>
delegate<_Rtn, _arg...>& delegate<_Rtn, _arg...>::operator+= (const delegate& _adddelg)
{
	if (_adddelg._func_num == 0) return *this;
	if (_capacity >= _func_num + _adddelg._func_num)
	{
		for (unsigned int i = 0; i < _adddelg._func_num; ++i)
			_fp[_func_num + i] = _adddelg._fp[i];
		_func_num += _adddelg._func_num;
		return *this;
	}
	while ((_capacity *= 2) < _func_num + _adddelg._func_num);
	FUNPTR* tmp = new FUNPTR[_capacity];
	for (unsigned int i = 0; i < _func_num; ++i)
		tmp[i] = _fp[i];
	for (unsigned int j = 0; j < _adddelg._func_num; ++j)
		tmp[_func_num + j] = _adddelg._fp[j];
	_func_num += _adddelg._func_num;
	delete[] _fp;
	_fp = tmp;
	return *this;
}

template <typename _Rtn, typename..._arg>
delegate<_Rtn, _arg...>& delegate<_Rtn, _arg...>::operator+= (FUNPTR _addfunc)
{
	if (_capacity < _func_num + 1)
	{
		_capacity *= 2;
		FUNPTR* tmp = new FUNPTR[_capacity];
		for (unsigned int i = 0; i < _func_num; ++i)
			tmp[i] = _fp[i];
		delete[] _fp;
		_fp = tmp;
	}
	_fp[_func_num++] = _addfunc;
	return *this;
}

template <typename _Rtn, typename..._arg>
delegate<_Rtn, _arg...>& delegate<_Rtn, _arg...>::operator-= (const delegate& _subdelg)
{
	if (_func_num == 0) return *this; 
	if (&_subdelg == this)
	{
		_func_num = 0; 
		return *this; 
	}
	std::set<unsigned int> delPos; 
	for (unsigned int i = 0; i < _subdelg._func_num; ++i)
		for (unsigned int j = _func_num - 1; ; --j)
		{
			if (_fp[j] == _subdelg._fp[i] && delPos.find(j) == delPos.end())
			{
				delPos.insert(j);
				break;
			}
			if (j == 0) break; 
		}
	unsigned int delNum = 0, i = 0, dest; 
	auto calDest = [&]() {return *delPos.begin() < delNum ? 0 : *delPos.begin() - delNum; }; 
	while (!delPos.empty())
	{
		dest = calDest(); 
		delPos.erase(delPos.begin()); 
		for (; i < dest; ++i)
		{
			if (delNum) _fp[i] = _fp[i + delNum]; 
		} 
		++delNum; 
	}
	if (delNum)
	{
		_func_num -= delNum; 
		dest = _func_num - delNum; 
		for (; i < _func_num; ++i) _fp[i] = _fp[i + delNum];
	} 
	return *this; 
}

template <typename _Rtn, typename..._arg>
delegate<_Rtn, _arg...>& delegate<_Rtn, _arg...>::operator-= (FUNPTR _subfunc)
{
	if (_func_num == 0) return *this; 
	for (unsigned int i = _func_num - 1; ; --i)
	{
		if (_fp[i] == _subfunc)
		{
			--_func_num; 
			for (; i < _func_num; ++i) _fp[i] = _fp[i + 1];
			break;
		}
		if (i == 0) break; 
	}
	return *this; 
}

template <typename _Rtn, typename..._arg>
delegate<_Rtn, _arg...>& delegate<_Rtn, _arg...>::operator*= (unsigned int times)
{
	if (_func_num == 0u) return *this; 
	if (_capacity < _func_num * times)
	{
		do { _capacity *= 2; } while (_capacity < _func_num * times);
		FUNPTR* tmp = new FUNPTR[_capacity]; 
		for (unsigned int i = 0; i < _func_num; ++i)
			tmp[i] = _fp[i]; 
		delete[] _fp; 
		_fp = tmp; 
	}
	unsigned int num = _func_num; 
	times -= 1; 
	for (unsigned int i = 0; i < times; ++i)
		for (unsigned int j = 0; j < num; ++j)
			_fp[_func_num++] = _fp[j]; 
	return *this; 
}



__TIMOTHY_NAMESPACE_END

#endif
