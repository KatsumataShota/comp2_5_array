﻿#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する
#include "Windows.h"                    // Windows API の機能定義

#include <stdlib.h>		// malloc, free
#include <stdbool.h>	// bool

#include "../include/lib_func.h"

// safe_array を要素数nで初期化する
void initialize(safe_array* ar, int n)
{
	if (n <= 0) n = 1;// 非正の値が来たら、とりあえず1にする

	ar->num = n;
	ar->addr = (int*)malloc(sizeof(int) * n);

	if (ar->addr == NULL) ar->num = 0;// 確保できなかったら要素数は0とする
}

// safe_array を解放する
void release(safe_array* ar)
{
	free(ar->addr);
	ar->addr = NULL;// 多重解放の防止
}

// safe_array の要素数を変更する(以前の値は要素が同じ範囲で残す)
void resize(safe_array* ar, int n)
{
	ar->num = n;
	ar->addr = (int*)malloc(sizeof(int) * n);
	if (ar->addr == NULL) ar->num = 0;
}

// safe_array のindex番目の要素にvalを設定する
// index が確保されていない場所を指していたら返り値をfalseにする（設定出来たらtrue）
bool set(const safe_array* ar, int index, int val)
{
	// ToOo:配列の要素を変更しよう！
	if (index<0 || ar->num <= index) {
		return false;
	}
	ar->addr[index] = val;
	return true;
}

// safe_array のindex番目の要素を取得する
// index が確保されていない場所を指していたら0を返す
int get(const safe_array* ar, int index)
{
	int i=0;
	// ToOo:要素を所得して、indexがおかしかったら0を返そう
	if (index < 0 || ar->num <= index) {
		return 0;
	}
	i = ar->addr[index];
	return i;
}

// int_array の要素数を取得する
int size(const safe_array* ar)
{
	return ar->num;
}