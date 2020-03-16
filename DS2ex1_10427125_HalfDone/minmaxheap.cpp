#include<stdio.h>
#define NOT_EXIST 0 // �YGetParent���V0�h�N��L�S��(��)���`�I 
/************************
* Push( heap, i )
* heap:= ��n���}�C 
* i:= �s���J���̧��ݪ����� 
* bottom-up
* 
************************/
void Push( Heap heap, int i ) {
	if( GetParent( i ) != NOT_EXIST ) { // �����T�w���J���������O��� , �p�G�O��ڴN�|�������X, Heap[i]�N�O��ڤ]�O�̧��� 
		if( IsMinLevel( GetLevel( i ) ) ) { // �Y�̧��ݪ���m�bmin heap�h �h��ۤv�P���`�I�i��̤j��n�� 
			if( heap[i] > heap[ GetParent(i) ] ) { // �Y���J�����j����`�I , �P���`�I�洫�û��j 
				Swap( heap[i], heap[GetParent( i )] );
				PushMax( heap, GetParent( i ) );
			}
			else PushMin( heap, i ); // �Y�w�P���`�I�����̤j��n , �h�P�l�`�I�i��̤p��n�� 
		}
		else {  // �o�̥N��s�������max heap�h 
			if( Heap[i] < Heap[ GetParent(i)] ) { // �bmax heap�h�h�|�P���`�I�i��̤p��n�� 
				Swap( heap[i], heap[GetParent( i )] ); // ���J�����p����`�I , �P���`�I�洫�û��j 
				PushMin( heap, GetParent( i ) );
			}
			else PushMax( heap, i ); // �Y�w�P���`�I�����̤p��n , �h�P�l�`�I�i��̤j��n�� 
		}
	}
}

void PushMin( Heap heap, int i ) { // �����̤p��n , �ѤU���W�P�����`�I�i��̤p��n�� 
	if( GetParent( GetParent( i ) ) != NOT_EXIST && Heap[i] < Heap[GetParent( GetParent( i ) )] ) { // �Y�`�I�֦������`�I�åB�p�󯪤��`�I , �P���洫�û��j 
		Swap( heap[i], Heap[GetParent( GetParent( i ) )] );
		PushMin( heap, GetParent( GetParent( i ) ) );
	}
}

void PushMax( Heap heap, int i ) { // �����̤j��n , �ѤU���W�P�����`�I�i��̤j��n�� 
	if( GetParent( GetParent( i ) ) != NOT_EXIST && Heap[i] > Heap[GetParent( GetParent( i ) )] ) { // �Y�`�I�֦������`�I�åB�j�󯪤��`�I , �P���洫�û��j  
		Swap( heap[i], Heap[GetParent( GetParent( i ) )] );
		PushMax( heap, GetParent( GetParent( i ) ) );
	}
}

int GetParent( int i ) {
	if( i <= 1 ) return 0;
	else return i / 2;
}

int GetLevel( int i ) { // �ھګe�ɹs�p�� i ���줸�ƶq  , �줸�ƶq�h���h��. ** �Ъ`�N, root�h�����q 1 �}�l ** 
	return 32 - __builtin_clz( i );
}

bool IsMinLevel( int level ) { // �_�Ƽh��min 
	return level & 1;
}

int GetLeftMostIndex( int total ) { // �ھګe�ɹs�p��Ӽh�ƪ��̥���, �ӸӼƦr��w��2^n 
	return 1 << ( 31 - __builtin_clz( total ) ) ;
}
