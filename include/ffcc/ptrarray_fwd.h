#if !defined(_FFCC_PTRARRAY_FWD_H_) && !defined(_FFCC_PTRARRAY_H_) && !defined(_FFCC_PTRARRAY_DECL_H_)
#define _FFCC_PTRARRAY_FWD_H_

template <class T>
class CPtrArray
{
public:
    int GetSize();
    T operator[](unsigned long index);
};

#endif // _FFCC_PTRARRAY_FWD_H_
