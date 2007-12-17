/* This file is part of Kapman.
   Created by Alexandre GALINIER <alex.galinier@hotmail.com>

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

#include <KStandardDirs>
#include "game.h"

Game::Game() {
	m_maze = new Maze();
	m_kapman = new Kapman(Cell::SIZE * 14, Cell::SIZE * 17.5);
	m_ghostList.append(new Ghost(260.0, 215.0, "redGhost_test.svg"));
	m_ghostList.append(new Ghost(260.0, 275.0, "greenGhost_test.svg"));
	m_ghostList.append(new Ghost(222.0, 275.0, "blueGhost_test.svg"));
	m_ghostList.append(new Ghost(298.0, 275.0, "pinkGhost_test.svg"));

	// Start the timer to move the characters regulary
	m_timer = new QTimer(this);
	m_timer->setInterval(15); // 60 FPS
	connect(m_timer, SIGNAL(timeout()), this, SLOT(update()));
	m_timer->start();
}

Game::~Game() {
	delete m_maze;
	delete m_kapman;
	for (int i = 0; i < m_ghostList.size(); i++) {
		delete m_ghostList[i];
	}
}

void Game::start() {
	m_timer->start();
}

void Game::pause() {
	m_timer->stop();
}

Kapman * Game::getKapman() const {
	return m_kapman;
}
		
QList<Ghost*> Game::getGhostList () const {
	return m_ghostList;
}

bool Game::onCenter(Kapman* p_character) {
	// Get the current cell center coordinates
	qreal centerX = (m_maze->getColFromX(p_character->getX()) + 0.5) *
					Cell::SIZE;
	qreal centerY = (m_maze->getRowFromY(p_character->getY()) + 0.5) *
					Cell::SIZE;
	bool willGoPast = false;

	// Will the character go past the center of the cell it's on ?
	// If goes right
	if (p_character->getXSpeed() > 0) {
		willGoPast = (p_character->getX() <= centerX &&
					  p_character->getX() + p_character->getXSpeed() >=
					  centerX);
	}
	// If goes down
	else if (p_character->getXSpeed() < 0) {
		willGoPast = (p_character->getX() >= centerX &&
					  p_character->getX() + p_character->getXSpeed() <=
					  centerX);
	}
	// If goes down
	else if (p_character->getYSpeed() > 0) {
		willGoPast = (p_character->getY() <= centerY &&
					  p_character->getY() + p_character->getYSpeed() >=
					  centerY);
	}
	// If goes up
	else if (p_character->getYSpeed() < 0) {
		willGoPast = (p_character->getY() >= centerY &&
					  p_character->getY() + p_character->getYSpeed() <=
					  centerY);
	}
	// If does not move
	else {
		willGoPast = (p_character->getX() == centerX &&
					  p_character->getY() == centerY);
	}

	return willGoPast;
}

void Game::moveOnCenter(Kapman* p_character) {
	p_character->setX((m_maze->getColFromX(p_character->getX()) + 0.5) *
					Cell::SIZE);
	p_character->setY((m_maze->getRowFromY(p_character->getY()) + 0.5) *
					Cell::SIZE);
	
}

Cell Game::getNextCell(Kapman* p_character) {
	Cell nextCell;
	// Get the current cell coordinates from the character coordinates
	int curCellRow = m_maze->getRowFromY(p_character->getY());
	int curCellCol = m_maze->getColFromX(p_character->getX());

	// Get the next cell function of the character direction
	if (p_character->getXSpeed() > 0) {
		nextCell = m_maze->getCell(curCellRow, curCellCol + 1);
	}
	else if (p_character->getXSpeed() < 0) {
		nextCell = m_maze->getCell(curCellRow, curCellCol - 1);
	}
	else if (p_character->getYSpeed() > 0) {
		nextCell = m_maze->getCell(curCellRow + 1, curCellCol);
	}
	else if (p_character->getYSpeed() < 0) {
		nextCell = m_maze->getCell(curCellRow - 1, curCellCol);
	}

	return nextCell;
}

Cell Game::getAskedNextCell(Kapman* p_character) {
	// Get the current cell coordinates from the character coordinates
	int curCellRow = m_maze->getRowFromY(p_character->getY());
	int curCellCol = m_maze->getColFromX(p_character->getX());
	Cell nextCell;

	// Get the next cell function of the character asked direction
	if (p_character->getAskedXSpeed() > 0) {
		nextCell = m_maze->getCell(curCellRow, curCellCol + 1);
	}
	else if (p_character->getAskedXSpeed() < 0) {
		nextCell = m_maze->getCell(curCellRow, curCellCol - 1);
	}
	else if (p_character->getAskedYSpeed() > 0) {
		nextCell = m_maze->getCell(curCellRow + 1, curCellCol);
	}
	else if (p_character->getAskedYSpeed() < 0) {
		nextCell = m_maze->getCell(curCellRow - 1, curCellCol);
	}

	return nextCell;
}

void Game::keyPressEvent(QKeyEvent* p_event) {
	switch (p_event->key()) {
		case Qt::Key_Up:
			m_kapman->goUp();
			break;
		case Qt::Key_Down:
			m_kapman->goDown();
			break;
		case Qt::Key_Right:
			m_kapman->goRight();
			break;
		case Qt::Key_Left:
			m_kapman->goLeft();
			break;
		default:
			break;
	}
}

void Game::update() {
	// If the kapman does not move
	if (m_kapman->getXSpeed() == 0 && m_kapman->getYSpeed() == 0) {
		// If the user asks for moving
		if (m_kapman->getAskedXSpeed() != 0 ||
			m_kapman->getAskedYSpeed() != 0) {
			// Check the next cell with the asked direction
			if (getAskedNextCell(m_kapman).getType() == Cell::CORRIDOR) {
					// Update the direction
					m_kapman->updateDirection();
					// Move the kapman
					m_kapman->move();
			}
		}
	}
	// If the kapman is already moving
	else {
		// If the kapman wants to go back it does not wait to be on a center
		if (m_kapman->getXSpeed() != 0 &&
			m_kapman->getAskedXSpeed() == -m_kapman->getXSpeed() ||
			m_kapman->getYSpeed() != 0 &&
			m_kapman->getAskedYSpeed() == -m_kapman->getYSpeed()) {
			// Go back
			m_kapman->updateDirection();
			// Move the kapman
			m_kapman->move();
		}
		else {
			// If the kapman gets on a cell center
			if (onCenter(m_kapman)) {
				// If there is an asked direction (but not a half-turn)
				if ((m_kapman->getAskedXSpeed() != 0 ||
					 m_kapman->getAskedYSpeed() != 0) &&
					(m_kapman->getAskedXSpeed() != m_kapman->getXSpeed() ||
					 m_kapman->getAskedYSpeed() != m_kapman->getYSpeed())) {
					// Check the next cell with the kapman asked direction
					if (getAskedNextCell(m_kapman).getType() ==
							Cell::CORRIDOR) {
						// Move the kapman on the cell center
						moveOnCenter(m_kapman);
						// Update the direction
						m_kapman->updateDirection();
					}
					else {
						// Check the next cell with the kapman current direction
						if (getNextCell(m_kapman).getType() != Cell::CORRIDOR) {
							// Move the kapman on the cell center
							moveOnCenter(m_kapman);
							// Stop moving
							m_kapman->stopMoving();
						}
						else {
							// Move the kapman
							m_kapman->move();
						}
					}
				}
				else {
					// Check the next cell with the kapman current direction
					if (getNextCell(m_kapman).getType() != Cell::CORRIDOR) {
						// Move the kapman on the cell center
						moveOnCenter(m_kapman);
						// Stop moving
						m_kapman->stopMoving();
					}
					else {
						// Move the kapman
						m_kapman->move();
					}
				}
			}
			else {
				// Move the kapman
				m_kapman->move();
			}
		}
	}
}
