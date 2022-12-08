#pragma once
#include "UsefulType.h"

template <typename T>
inline T Min(const T&, const T&);

template <typename T>
inline T Max(const T& a, const T& b);

template <typename T>
inline void Swap(T& a, T& b);

template <typename T>
inline void Swap(T* a, T* b);

template <typename T>
inline T MakeRandByRange(const T& a, const T& b);

void Shuffle(uint* arr, const uint& arr_length, const uint& n_shuffle);

void GetRandomsNoOverlap(int* arr, const uint& arr_length, const uint& num);