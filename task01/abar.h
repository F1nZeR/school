#define _CRT_SECURE_NO_WARNINGS 1

//#include "stdafx.h"

#include <stdio.h>
#include <vector>
#include <time.h>
#include <cassert>
#include <random>


typedef          long long  llong;
typedef unsigned long long ullong;


//#pragma endregion asd  


template<typename T>
class myvector
{

private:

    /// <summary>       �җ��� ��ܙ���ȳ� (�Ƴȣ ܘ������ �����ܙ�)  </summary>
    T*	    m_Data;
    /// <summary>       ��ߘ�Қ ������� ��ܙ���ȳ� (�Ӟ�� Ԗ�������� ��ؚ�� � ����ȳқ ������ �����ܙ�)  </summary>
    int		m_Capacity;
    /// <summary>       ��ߘ��� ���ۗȣ��� �����ܙ�� � ��ܙ���ȳ� (�Ӟ�� ����ݣ��������� Ԗ�������� ��ؚ�� � ����ȳқ ������ �����ܙ�)  </summary>
    int		m_Size;
    /// <summary>       �����۟��ܙ ���ۙ��� �����  </summary>
    int		m_Policy;

    /// <summary>       �җ�ٿ�Қ ������� ��ܙ���ȳ�  </summary>
    static const int    INITIAL_CAPACITY    = 16;


public:

    myvector()
    {
        m_Capacity      = INITIAL_CAPACITY;
        m_Data          = (T*)malloc( (INITIAL_CAPACITY * sizeof(T)) );
        m_Size          = 0;
        m_Policy        = 1.2;
    }
    myvector( float policy )
    {
        m_Capacity      = INITIAL_CAPACITY;
        m_Data          = (T*)malloc( (INITIAL_CAPACITY * sizeof(T)) );
        m_Size          = 0;
        m_Policy        = policy;
    }
    ~myvector()
    {
        if( !__is_pod(T) )
            for( int i = 0;  i < m_Size;  i++ )
                m_Data[i].~T();

        free( m_Data );
    }

    /// <summary> ��٘�ۙ� ��ߘ��� ������� ��ܙ���ȳ� </summary>
    /// <returns>          ��ߘ�Қ ������� ��ܙ���ȳ� </returns>
    int capacity() { return m_Capacity; }
    /// <summary> ��٘�ۙ� ��ߘ��� ���ۗȣ��� �����ܙ�� � ��ܙ���ȳ� </summary>
    /// <returns>          ��ߘ��� ���ۗȣ��� �����ܙ�� � ��ܙ���ȳ� </returns>
    int size() { return m_Size; }

    // because we can

    /// <summary> �����ۙ� �����ܙ � ���ȟ ��ܙ���ȳ� </summary>
    /// <param name="value">    �����ܙ </param>
    void add( const T& value )
    {
        if( m_Size >= m_Capacity )
            reserve( (m_Capacity * m_Policy) );

        memcpy( (m_Data + m_Size), &value, sizeof(T) );
        m_Size++;
    }
    /// <summary> �����ۙ� �����ܙ � ���ȟ ��ܙ���ȳ� </summary>
    /// <param name="value">    �����ܙ </param>
    void push_back( const T& value ) { add( value ); }

    // easy handmade emplace_back()

    /// <summary> �����ۙ� �����ܙ � ���ȟ ��ܙ���ȳ� </summary>
    /// <returns>       ������ �� ��������ܖ� �����ܙ </returns>
    T& add()
    {
        if( m_Size >= m_Capacity )
            reserve( (m_Capacity * m_Policy) + 1 );

        int pos     = m_Size++;

        memset( (m_Data + pos), 0x00, sizeof(T) );

        return *(m_Data + pos);
    }

    // easy handmade erase()

    /// <summary> ����ۙ� �����ܙ� ��ܙ���ȳ�, �җ��Қ � ���������� </summary>
    /// <param name="index">    ����ߣ �����ܙ� </param>
    void erase( int index )
    {
        // !!! ��� ���, �������-��! (ܘ ��� ��������)
        assert( index >= 0  &&  index < m_Size  &&  "Index out of range" );

        if( !__is_pod(T) )
            m_Data[index].~T();

        for( int i = index;  i < (m_Size - 1);  i++ )
            memcpy( (m_Data + i), (m_Data + i + 1), sizeof(T) );

        m_Size--;
    }

    /// <summary> ����ۙ� �����ܙ� ��ܙ���ȳ�, �җ��Қ � ���������� </summary>
    /// <param name="item">     �����ܙ </param>
    void erase( const T* item ) { erase( item - m_Data ); }


    /// <summary> ��٘�ۙ� �����ܙ ��ܙ���ȳ� </summary>
    /// <param name="index">    ����ߣ �����ܙ� ��ܙ���ȳ� </param>
    /// <returns>               ������ �� �����ܙ ��ܙ���ȳ� </returns>
    T& operator[]( int index )
    {
        // !!! ��� ���, �������-��! (ܘ ��� ��������)
        assert( index >= 0  &&  index < m_Size  &&  "Index out of range" );

        T retVal;

        memcpy( &retVal, (m_Data + index), sizeof(T) );

        return retVal;
    }
    /// <summary> ��٘�ۙ� �����ܙ ��ܙ���ȳ� </summary>
    /// <param name="index">    ����ߣ �����ܙ� ��ܙ���ȳ� </param>
    /// <returns>               ��ܣ��ܙ�Қ ������ �� �����ܙ ��ܙ���ȳ� </returns>
    const T& operator[]( int index ) const
    {
        // !!! ��� ���, �������-��! (ܘ ��� ��������)
        assert( index >= 0  &&  index < m_Size  &&  "Index out of range" );

        T retVal;

        memcpy( &retVal, (m_Data + index), sizeof(T) );

        return retVal;
    }

    /// <summary> ��٘�ۙ� ����ҙ�ٿ �� �җ��� ��ܙ���ȳ� </summary>
    /// <returns>       �Ƴȣ ܘ������ �����ܙ� ��ܙ���ȳ� </returns>
    T* begin() { return m_Data; }
    /// <summary> ��٘�ۙ� ����ҙ�ٿ �� ���ȟ ��ܙ���ȳ� </summary>
    /// <returns>       �Ƴȣ ���������� �����ܙ� ��ܙ���ȳ� </returns>
    T* end() { return m_Data + m_Size; }

    /// <summary> ��ۣ�ۙ� ��ܙ���ȳ, �������ۙ� ��ؚ�� (ȣ�� �� POD) </summary>
    void clear()
    {
        if( !__is_pod(T) )
            for( int i = m_Size - 1;  i >= 0;  i-- )
                m_Data[i].~T();

        m_Capacity  = INITIAL_CAPACITY;
        m_Data      = (T*)realloc( m_Data, (INITIAL_CAPACITY * sizeof(T)) );
        m_Size      = 0;
    }

    /// <summary> �������ۙ� ���ۗȣ��� �����ܙ�� ��ܙ���ȳ� </summary>
    /// <param name="index">    ���ۗȣ��� �����ܙ�� ��ܙ���ȳ� </param>
    void resize( int new_size )
    {
        // !!! ��� ���, �������-��! (ܘ ��� ��������)
        assert( new_size >= 0  &&  "Index out of range" );

        if( new_size < m_Capacity )
        {
            if( !__is_pod(T) )
                for( int i = new_size;  i < m_Capacity;  i++ )
                    m_Data[i].~T();
        }
        else
            reserve( new_size );

        m_Size      = m_Size < new_size?  m_Size:  new_size;
    }
        
    /// <summary> ��ȣ�ȗۙ� ������� ��ܙ���ȳ� </summary>
    /// <param name="index">    ������� ��ܙ���ȳ� </param>
    void reserve( int min_capacity )
    {
        if( min_capacity <= m_Capacity )
            return;


        m_Data          = (T*)realloc( m_Data, (min_capacity * sizeof(T)) );

        m_Capacity      = min_capacity;
    }
};
