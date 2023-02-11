#pragma once
//  ChessDraw.h
//  Build   on  2011.11.26  
//  Copyright(C) by Alberl
//  Email: 316293804@qq.com
//
//  License
//  This article, along with any associated source code and files, is licensed under The Code Project Open License (CPOL)
//  本项目所有源码均采用CPOL开源协议，详细内容请于Code Project 查阅


class CChessDraw
{
public:
	CChessDraw(void);
	~CChessDraw(void);

	void    InitBoard(CRect	rect, UINT	uiRows, UINT	uiCols, UINT	uiBoardWidth, UINT	uiPieceRadius);

	void	SetDC(CDC*	pDC);
	void	DrawBackground();							            // 画背景
	void	DrawBoard();										    // 画棋盘
	BOOL	DrawPiece(UINT	uiX,	UINT	uiY,	BOOL	bBlack);// 画棋子		
	void	DrawPieceCur(UINT	uiX,	UINT	uiY);				// 给当前的棋子加上标记

	CRect	GetRectBoard();	// 获取棋盘区域	
	BOOL	GetCoordinateWithPoint(CPoint&	pt,	UINT*	puiX = NULL,	UINT*	puiY = NULL);	// 已知pt，获取棋盘坐标点(puiX,	puiY)	
	BOOL	GetPointWithCoordinate(CPoint&	pt,	UINT	uiX ,	UINT	uiY);                   // 已知棋盘坐标点(puiX,	puiY)，获取pt

private:
	CDC*		m_pDC;					// 绘图DC
	CRect		m_rcBK;					// 背景区域	
	CRect		m_rcBoard;				// 棋盘区域	

	UINT		m_uiBoardCols;			// 棋盘的列数		// 五子棋行、列一样多，其他棋(如象棋)可能不一样
	UINT		m_uiBoardRows;		    // 棋盘的行数
	UINT		m_uiPieceRadius;		// 棋子半径
	UINT		m_uiBoardWidth;		    // 每一格棋盘的边长(正方形格子)

	COLORREF	m_crBKBegin;			// 渐变色起始端
	COLORREF	m_crBKEnd;				// 结尾端
	COLORREF	m_crBoard;				// 棋盘线条的颜色

	void		DrawSpecialPoints();	// 画指定的点，如五子棋中的天元等5个点	这里每种棋的规则都不一样，因此需单独修改
};

