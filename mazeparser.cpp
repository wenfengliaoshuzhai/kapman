/* This file is part of Kapman.
   Created by Nathalie Liesse <nathalie.liesse@gmail.com>

   Kapman is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public
   License as published by the Free Software Foundation, version 2.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
   02110-1301, USA
*/

#include "mazeparser.h"
#include "element.h"
#include "pill.h"
#include "energizer.h"

MazeParser::MazeParser(Maze* p_maze) {
	m_maze = p_maze;
}

MazeParser::~MazeParser() {
}

bool MazeParser::startElement(const QString&, const QString&, const QString& p_qName, const QXmlAttributes& p_atts) {
	if(p_qName == "Maze") {
		int nbRows = 0;
		int nbColumns = 0;
		
		for(int i = 0 ; i < p_atts.count() ; i++) {
			if(p_atts.qName(i) == "nbRows") {
				nbRows = p_atts.value(i).toInt();
			}
			
			if(p_atts.qName(i) == "nbColumns") {
				nbColumns = p_atts.value(i).toInt();
			}
		}
		
		m_maze->init(nbRows, nbColumns);
	}
	
	if(p_qName == "Cell") {
		int rowIndex = 0;
		int columnIndex = 0;
		int cellType = 0;
		int itemType = 0;
		
		for(int i = 0 ; i < p_atts.count() ; i++) {
			if(p_atts.qName(i) == "rowIndex") {
				rowIndex = p_atts.value(i).toInt();
			}
			
			if(p_atts.qName(i) == "columnIndex") {
				columnIndex = p_atts.value(i).toInt();
			}
			
			if(p_atts.qName(i) == "allowedMove") {
				cellType = p_atts.value(i).toInt();
			}

			if(p_atts.qName(i) == "item") {
				itemType = p_atts.value(i).toInt();
			}
		}

		switch(itemType)
		{
			case 0:
				m_maze->setCellType(rowIndex, columnIndex, (Cell::CellType)cellType, NULL);
				break;
			case 1:
				m_maze->setCellType(rowIndex, columnIndex, (Cell::CellType)cellType, new Pill(rowIndex, columnIndex, m_maze, "pill_test.svg"));
				break;
			case 2:
				m_maze->setCellType(rowIndex, columnIndex, (Cell::CellType)cellType, new Energizer(rowIndex, columnIndex, m_maze, "energizer_test.svg"));
				break;
		}

	}
	
	return true;
}
