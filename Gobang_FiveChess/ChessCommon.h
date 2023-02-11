#pragma once
//  ChessCommon.h
//  Build   on  2011.11.26  
//  Copyright(C) by Alberl
//  Email: 316293804@qq.com
//
//  License
//  This article, along with any associated source code and files, is licensed under The Code Project Open License (CPOL)
//  本项目所有源码均采用CPOL开源协议，详细内容请于Code Project 查阅



//  公用头文件   目前只被ChessAI.h   和   Chess.h 共用
//	此项目默认为15*15的五子棋,   如需应用到象棋和其他棋类，则需自行修改，因空闲时间不多，只打算专注一下五子棋		
//
//  注意: 
//  人机对战时，默认人为黑方，机器为白方，     而五子棋规定黑棋先行，即人先走棋


const	int	    MAXCREASE	= 4;    // 此项目为五子棋，所以最大数目为5-1
const	UINT	COLUMNS	    = 15;   // 棋盘的列数
const	UINT	ROWS		= 15;   // 棋盘的行数
enum	enumChessColor  {NONE,	WHITE,	BLACK};		// NONE	无棋子		WHITE 白方棋子	    BLACK 黑方棋子


// 相同颜色计数的加法器
void    SameColorAdder  (UINT	uiCol,	UINT	uiRow,	enumChessColor   emChessColor,    BOOL    bResetCount, int& iColorCount,   BOOL&    bOver,   
                          const enumChessColor iChess[][ROWS],     int* piBlankCount    = NULL );
  
// 在某点处各方向相同颜色的棋子数
void    GetSameColor    (UINT	uiCol,	UINT	uiRow,	enumChessColor   emChessColor,    int*  iSameColor,   
                          const enumChessColor iChess[][ROWS],    int*  piCreaseDirect = NULL,    BOOL   bIgnoreBlank   = FALSE,  int*    piBlankFlag = NULL);

// 某点是否在棋盘中
BOOL    PtInBroad(UINT	uiCol,	UINT	uiRow);