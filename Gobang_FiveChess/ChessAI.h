#pragma once
#include "ChessCommon.h"

//  ChessAI.h
//  Build   on  2011.11.26  
//  Copyright(C) by Alberl
//  Email: 316293804@qq.com
//
//  License
//  This article, along with any associated source code and files, is licensed under The Code Project Open License (CPOL)
//  ����Ŀ����Դ�������CPOL��ԴЭ�飬��ϸ��������Code Project ����


// ����AI�����ٶ��𽥼�����CPUռ�������ߣ�����Ҳ������
// AIFoolish         ��Ȼ������ͣ�����ռ�õ��ڴ��CPU����͵ģ�
// AIPrimary         ռ���ڴ�ͣ�ռ��CPUҲ��
// AIMiddle          �ڴ��CPUռ�þ���
// AIHigh            ռ���ڴ�ͣ�ռ��CPU��

// ����Ĭ�ϻ���Ϊ�׷�
BOOL    AIPrimary (POINT &pt ,   enumChessColor emChess[][ROWS]);                // ����AI      
BOOL    AIHigh    (POINT &pt ,   enumChessColor emChess[][ROWS]);                // �߼�AI      ����������Сalpha-beta��֦
