#include <iostream>
#include <concepts>
using namespace std;


template<size_t i, size_t p, size_t s=1>
struct _S_pow:_S_pow<i, p-1, s*i>
{

};

template<size_t i, size_t s>
struct _S_pow<i,0,s>
{
    static const size_t value = s;
};

template<size_t i, size_t p>
struct S_pow
{
    static const size_t value = _S_pow<i, p>::value;
};


template<size_t i, size_t...is>
struct _D_num;

template<size_t i, size_t j, size_t...is>
struct _D_num<i, j, is...>: _D_num< i+S_pow<10,sizeof...(is)>::value*j, is...>
{
};

template<size_t i>
struct _D_num<i>
{
    static const size_t value = i;
};

template<size_t...is>
struct D_num
{
    static const size_t value = _D_num<0,is...>::value;
};





template<size_t n, size_t v = 0>
struct nn: nn<n/10, v+1 >
{};

template< size_t v>
struct nn<0, v>
{
    static const size_t value = v;
};



template<size_t oi ,bool b = true, size_t c = 2>
struct is_prime: is_prime<oi, b&&(oi%c!=0), c+1 >
{
};

template<size_t oi, bool b>
struct is_prime<oi, b, oi >
{
    static const bool value = b;
};

template<bool b, size_t x>
struct is_prime<1, b, x >
{
    static const bool value = false;
};



template<size_t i>
struct shift
{
    static const size_t org_val = i;
    static const size_t shf_val = (i/10)+((i%10)*(S_pow<10,nn<i>::value-1>::value));
};



template<size_t oi, bool b = true, size_t i = nn<oi>::value>
struct iter:iter<shift<oi>::shf_val, b&&is_prime<oi>::value, i-1>
{
};

template<size_t oi, bool b>
struct iter<oi, b, 0>
{
    static const bool value = b;
};


template<size_t i, size_t n = 0>
struct count_circular_primes:count_circular_primes<i-1, n+(iter<i>::value)>
{

};

template< size_t n >
struct count_circular_primes<0, n>
{
    static const size_t value = n;
};

int main()
{
    cout<<count_circular_primes<100>::value<<endl;
    //cout<<iter<74>::value<<endl;

    return 0;
}
