#include<stdio.h>
#define NOT_EXIST 0 // 若GetParent指向0則代表他沒有(祖)父節點 
/************************
* Push( heap, i )
* heap:= 堆積的陣列 
* i:= 新插入的最尾端的元素 
* bottom-up
* 
************************/
void Push( Heap heap, int i ) {
	if( GetParent( i ) != NOT_EXIST ) { // 首先確定插入的元素不是樹根 , 如果是樹根就會直接跳出, Heap[i]就是樹根也是最尾端 
		if( IsMinLevel( GetLevel( i ) ) ) { // 若最尾端的位置在min heap層 則對自己與父節點進行最大堆積化 
			if( heap[i] > heap[ GetParent(i) ] ) { // 若插入元素大於父節點 , 與父節點交換並遞迴 
				Swap( heap[i], heap[GetParent( i )] );
				PushMax( heap, GetParent( i ) );
			}
			else PushMin( heap, i ); // 若已與父節點維持最大堆積 , 則與子節點進行最小堆積化 
		}
		else {  // 這裡代表新元素位於max heap層 
			if( Heap[i] < Heap[ GetParent(i)] ) { // 在max heap層則會與父節點進行最小堆積化 
				Swap( heap[i], heap[GetParent( i )] ); // 插入元素小於父節點 , 與父節點交換並遞迴 
				PushMin( heap, GetParent( i ) );
			}
			else PushMax( heap, i ); // 若已與父節點維持最小堆積 , 則與子節點進行最大堆積化 
		}
	}
}

void PushMin( Heap heap, int i ) { // 維持最小堆積 , 由下往上與祖父節點進行最小堆積化 
	if( GetParent( GetParent( i ) ) != NOT_EXIST && Heap[i] < Heap[GetParent( GetParent( i ) )] ) { // 若節點擁有祖父節點並且小於祖父節點 , 與之交換並遞迴 
		Swap( heap[i], Heap[GetParent( GetParent( i ) )] );
		PushMin( heap, GetParent( GetParent( i ) ) );
	}
}

void PushMax( Heap heap, int i ) { // 維持最大堆積 , 由下往上與祖父節點進行最大堆積化 
	if( GetParent( GetParent( i ) ) != NOT_EXIST && Heap[i] > Heap[GetParent( GetParent( i ) )] ) { // 若節點擁有祖父節點並且大於祖父節點 , 與之交換並遞迴  
		Swap( heap[i], Heap[GetParent( GetParent( i ) )] );
		PushMax( heap, GetParent( GetParent( i ) ) );
	}
}

int GetParent( int i ) {
	if( i <= 1 ) return 0;
	else return i / 2;
}

int GetLevel( int i ) { // 根據前導零計算 i 的位元數量  , 位元數量則為層數. ** 請注意, root層必須從 1 開始 ** 
	return 32 - __builtin_clz( i );
}

bool IsMinLevel( int level ) { // 奇數層為min 
	return level & 1;
}

int GetLeftMostIndex( int total ) { // 根據前導零計算該層數的最左邊, 而該數字恆定為2^n 
	return 1 << ( 31 - __builtin_clz( total ) ) ;
}
