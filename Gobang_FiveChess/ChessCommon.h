#pragma once
//  ChessCommon.h
//  Build   on  2011.11.26  
//  Copyright(C) by Alberl
//  Email: 316293804@qq.com
//
//  License
//  This article, along with any associated source code and files, is licensed under The Code Project Open License (CPOL)
//  ����Ŀ����Դ�������CPOL��ԴЭ�飬��ϸ��������Code Project ����



//  ����ͷ�ļ�   Ŀǰֻ��ChessAI.h   ��   Chess.h ����
//	����ĿĬ��Ϊ15*15��������,   ����Ӧ�õ�������������࣬���������޸ģ������ʱ�䲻�ֻ࣬����רעһ��������		
//
//  ע��: 
//  �˻���սʱ��Ĭ����Ϊ�ڷ�������Ϊ�׷���     ��������涨�������У�����������


const	int	    MAXCREASE	= 4;    // ����ĿΪ�����壬���������ĿΪ5-1
const	UINT	COLUMNS	    = 15;   // ���̵�����
const	UINT	ROWS		= 15;   // ���̵�����
enum	enumChessColor  {NONE,	WHITE,	BLACK};		// NONE	������		WHITE �׷�����	    BLACK �ڷ�����


// ��ͬ��ɫ�����ļӷ���
void    SameColorAdder  (UINT	uiCol,	UINT	uiRow,	enumChessColor   emChessColor,    BOOL    bResetCount, int& iColorCount,   BOOL&    bOver,   
                          const enumChessColor iChess[][ROWS],     int* piBlankCount    = NULL );
  
// ��ĳ�㴦��������ͬ��ɫ��������
void    GetSameColor    (UINT	uiCol,	UINT	uiRow,	enumChessColor   emChessColor,    int*  iSameColor,   
                          const enumChessColor iChess[][ROWS],    int*  piCreaseDirect = NULL,    BOOL   bIgnoreBlank   = FALSE,  int*    piBlankFlag = NULL);

// ĳ���Ƿ���������
BOOL    PtInBroad(UINT	uiCol,	UINT	uiRow);