#include "StdAfx.h"
#include "ChessAI.h"


// SCORE_BLACK[i][j] 
// ��ʾ����j+1������(�����߹�i����λ)������
// i = 0��ʾ���߶�����ס    i = 1��ʾ��һ��û����ס  i = 2 ��ʾ���߶��п�λ
//const   double SCORE_WHITE[][5]   =   {   {0,  0, 0,	0,	1e10}  ,      {1e0,     1e2,	 1e4,	    1e6,   1e10},            {1e1,    1e3,	    1e5	,   1e7,   	1e10}       };
//const   double SCORE_BLACK[][5]   =   {   {0,  0, 0,	0,	-1e9}  ,       {-1e1,   -1e3,	-1e5,   -1e7,	-1e9 },             {-1e2,    -1e4,	-1e6	,	-1e8,	-1e9}       };
const   double SCORE_WHITE[][5]   =   {   {0,  0, 0,	0,	10000000},   {1,     25,	 500,	 2500,   10000000},  {5,    100,	 2500,   50000,   	10000000} };
const   double SCORE_BLACK[][5]   =   {   {0,  0, 0,	0,	-1000000},   {-5,   -100,	-500,   -10000,	-1000000 },  {-25,  -500,	-10000,	-250000,	-1000000} };

// �������i=0�ķ�����ͣ�i>0ʱ����Խ��Խ�ã�
// �磺[1][3]>[2][2]  ������>����  ����Ϊ����һ�壬���ļ�������
// ����>���  ����Ϊ��������һ�壬����ʹ����������,���߻���ɻ������ͱ��������>���� ���з�����һ�壬����ʹ���ı������(���߶�����)�����߻����������
// Ϊ�˲�ʹ�����ص���[i+1][j]    >= 4*[i][j] +1  ��[i][j+1]    >= 4*[i+1][j] +1   �����ȡ�����λȡ������9ȡ��Ϊ10,     81ȡ��Ϊ100
// �ڷ��ĸ���Ҫ����������һ���ڷ����������ܷ֣���ʹ����ȥ�º���     �������ĸ���Ϊ�����10��,    ��Ȼ����������ʱ�׷�����Ҫ�󣬲�Ȼ����ȥ�ºڷ����Լ���Ӯ

/*
�׷�����>�ڷ�����
���Ե��׷��л�����ڷ�������ʱ��Ӧ�������λ�ã�
������ʹ�ڷ���������ģ���ôҲֻ��Ҫһ��������ס
*/

long double    GetScore(UINT uiCol,    UINT  uiRow,  const  enumChessColor emChess[][ROWS],  BOOL   bIgnoreBlank   = FALSE)   
{    
    int iSameColor[MAXCREASE];
    int iBlankFlag[MAXCREASE]   = {0};                         

    GetSameColor(uiCol, uiRow,  emChess[uiCol][uiRow],   iSameColor,    emChess, NULL,    bIgnoreBlank,   iBlankFlag);
     
    long double dbScore    = 0;
    for(int m = 0;  m < MAXCREASE;	m++)
    {
        int i   = iBlankFlag[m];
        int j   = iSameColor[m] - 1;
        
        if(WHITE  == emChess[uiCol][uiRow])
        {
            dbScore  += SCORE_WHITE[i][j];     
        }
        else
        {
            dbScore  += SCORE_BLACK[i][j];     
        }
    }
    
    return  dbScore;
}

long double ScoreEvaluate(const  enumChessColor emChess[][ROWS],  BOOL   bIgnoreBlank   = FALSE)
{
    // Ŀǰ��ֵ�����  �׷�Ϊ����  �����԰׷�����Ϊ�����ڷ�Ϊ��
    // ���������Ӽ������ķ�
    long double dbScoreSum   = 0;
    for(int i=0;  i<ROWS;  i++)
    {
        for(int j=0;  j<ROWS;  j++)
        {
            if(NONE !=  emChess[i][j])   
            {                   
                dbScoreSum   += GetScore(i,j, emChess,    bIgnoreBlank);
            }
        }
    }

    return  dbScoreSum;
}

// Ϊ����ٶȣ���¼ÿһ�������Ĺ�ֵ�����������Ӽ�¼�����������ޣ�����ӵ���¼��  // ���û���
// AlphaBeta(3, -INFINITE,  INFINITE,   pt)     ��pt������3��

// ����Ƿ�Ϊ��������Ϊ��
// �����ֵ�����ʱ�����ܷ����ĵ�
// �ֵ�����ʱ�����ܷ���С�ĵ�

// alphaBetaMax�������������ģ������ʺϰ׷�  ����5������ʱ������ɫӮ����Ϊ10000������ɫӮ��-10000
// ��ôalphaBetaMax(-10000,   10000,  3); ���صı���10000      ���������������򷵻ؾ����ܴ��ֵ
// alphaBetaMin�򷵻ؾ�����С��ֵ
//

// Alpha-beta efficiency depends on move ordering. In the worst case ordering, it's exactly the same as regular minimax.
// It's not better than Beta or better than Alpha
// С����С�Ļ��ߴ�������
// Move ordering, move ordering, move ordering!  Start taking advantage of your iterative deepening. Usually this is implemented with a transposition table, but you can do it without one as well. 

long double AlphaBetaMin( long double dbAlphaMin, long double dbBetaMax, int iDepthleft ,  enumChessColor emChess[][ROWS],   POINT& ptBest) ;
long double AlphaBetaMax( long double dbAlphaMin, long double dbBetaMax, int iDepthleft ,  enumChessColor emChess[][ROWS],   POINT& ptBest) 
{
    ptBest  = CPoint(-1, -1);       // ��������������ptBest����CPoint(-1, -1)��˵������������
    if ( iDepthleft == 0 ) 
    {
        return ScoreEvaluate(emChess); 
    }
    CPoint  ptTmp;      // ��Ϊһ���������ݣ���Ҫ����

    for(int i=0;  i<ROWS;  i++)
    {
        for(int j=0;  j<ROWS;  j++)
        {
            if(NONE ==  emChess[i][j])
            {
                if(ptBest.x  == -1)   
                {
                    ptBest  = CPoint(i, j); // ����ǵ�һ�ν���
                }

                emChess[i][j] = WHITE ;     // ��һ����

                long double   dbScore = AlphaBetaMin( dbAlphaMin, dbBetaMax, iDepthleft - 1,   emChess,   ptTmp);   // �ҳ�Min��������ҵ���������
                             
                emChess[i][j] = NONE;       // ���������ߵ���һ����

                if( dbScore >= dbBetaMax )      
                {
                    ptBest  = CPoint(i, j);
                    return dbBetaMax;       // dbBetaMax-cutoff
//                    return dbScore;  
                }
                if( dbScore > dbAlphaMin )
                {
                    ptBest  = CPoint(i, j);
                    dbAlphaMin = dbScore;   // dbAlphaMin acts like max in MiniMax
                }
            }
        }
    }
    return dbAlphaMin;    //Max
}

long double AlphaBetaMin( long double dbAlphaMin, long double dbBetaMax, int iDepthleft ,  enumChessColor emChess[][ROWS],   POINT& ptBest) 
{
    ptBest  = CPoint(-1, -1);
    if ( iDepthleft == 0 ) 
    {
        //  ��AlphaBetaMax()��    iDepthleftΪ2ʱ���Ӳ��Ӹ��Ŷ����
        // ��iDepthleftΪ3ʱ���Ӹ����ܺܿ��֦�ó�����������������ȷ���������ﲻ�Ӹ���
//     return -ScoreEvaluate(emChess);       
        return ScoreEvaluate(emChess);         
    }

    for(int i=0;  i<ROWS;  i++)
    {
        for(int j=0;  j<ROWS;  j++)
        {
            if(NONE ==  emChess[i][j])
            {
                emChess[i][j] = BLACK ;     // ��һ����

                long double   dbScore = AlphaBetaMax( dbAlphaMin, dbBetaMax, iDepthleft - 1,   emChess,   ptBest); // �ҳ�Max��������ҵ�����С����

                emChess[i][j] = NONE;       // ���������ߵ���һ����
               
                if( dbScore <= dbAlphaMin )  
                {   
                    ptBest  = CPoint(i, j);
                    return dbAlphaMin;      // dbAlphaMin-cutoff
   //                 return dbScore;          
                }
                if( dbScore < dbBetaMax )
                {
                    ptBest  = CPoint(i, j);
                    dbBetaMax = dbScore;    // dbBetaMax acts like min in MiniMax
                }
            }
        }
    }
    return dbBetaMax; // Min
}




// ------------------------------------------------------------ AI  Function ------------------------------------------------------------

// ��Ԥ��
// ����ֽ������֣��ҵ���ֵ����λ��    
BOOL    AIPrimary (POINT &pt ,  enumChessColor emChess[][ROWS])
{
    AlphaBetaMax(-1e10, 1e11, 1, emChess, pt);

    if(pt.x  == -1)   
    {
        return  FALSE;  // ����������
    }
    return  TRUE;
}
    
// Ԥ��2������
BOOL    AIHigh    (POINT &pt ,  enumChessColor emChess[][ROWS])
{
    AlphaBetaMax(-1e7, 1e8, 2, emChess, pt);
    
    if(pt.x  == -1)   
    {
        return  FALSE;  // ����������
    }
    return  TRUE;
}
