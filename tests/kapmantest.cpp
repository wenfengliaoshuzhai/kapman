/* This file is part of Kapman.
   Created by Pierre-Benoit Besse <besse.pb@gmail.com>

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
#include "kapmantest.h"
#include "kapman.h"

/**
 * 		KAPMAN CLASS TESTS
 */
 
void KapmanTest::testKapman() {

	Maze * maze = new Maze();

	Kapman kap (0.0, 0.0, maze);
	
	QCOMPARE(kap.getX(), 0.0);
	QCOMPARE(kap.getY(), 0.0);
	QCOMPARE(kap.getAskedXSpeed(), -Kapman::SPEED);		// The kapman goes left at the begining
}

void KapmanTest::testGoUp() {

	Maze * maze = new Maze();

	Kapman kap (0.0, 0.0, maze);

	kap.goUp();

	QCOMPARE(kap.getAskedXSpeed(), 0.0);	
	QCOMPARE(kap.getAskedYSpeed(), -Kapman::SPEED);
}

void KapmanTest::testGoDown() {

	Maze * maze = new Maze();
	
	Kapman kap (0.0, 0.0, maze);

	kap.goDown();

	QCOMPARE(kap.getAskedXSpeed(), 0.0);	
	QCOMPARE(kap.getAskedYSpeed(), Kapman::SPEED);
}

void KapmanTest::testGoRight() {

	Maze * maze = new Maze();

	Kapman kap (0.0, 0.0, maze);

	kap.goRight();

	QCOMPARE(kap.getAskedXSpeed(), Kapman::SPEED);	
	QCOMPARE(kap.getAskedYSpeed(), 0.0);
}

void KapmanTest::testGoLeft() {

	Maze * maze = new Maze();

	Kapman kap (0.0, 0.0, maze);
	
	kap.goLeft();

	QCOMPARE(kap.getAskedXSpeed(), -Kapman::SPEED);	
	QCOMPARE(kap.getAskedYSpeed(), 0.0);
}

// void KapmanTest::testUpdateDirection() {
// 	Kapman kap (0.0, 0.0);
// 	
// 	kap.goLeft();
// 	QCOMPARE(kap.getXSpeed(), 0.0);	
// 	QCOMPARE(kap.getYSpeed(), 0.0);
// 	QCOMPARE(kap.getAskedXSpeed(), -Kapman::SPEED);	
// 	QCOMPARE(kap.getAskedYSpeed(), 0.0);
// 	
// 	kap.updateDirection();
// 	
// 	QCOMPARE(kap.getXSpeed(), -Kapman::SPEED);	
// 	QCOMPARE(kap.getYSpeed(), 0.0);
// 	QCOMPARE(kap.getAskedXSpeed(), 0.0);	
// 	QCOMPARE(kap.getAskedYSpeed(), 0.0);
// }

// void KapmanTest::testStopMoving() {
// 	Kapman kap (0.0, 0.0);
// 	
// 	kap.goDown();
// 	kap.updateDirection();
// 	kap.goRight();
// 	
// 	QCOMPARE(kap.getYSpeed(), Kapman::SPEED);
// 	QCOMPARE(kap.getAskedXSpeed(), Kapman::SPEED);
// 	
// 	kap.stopMoving();
// 	
// 	QCOMPARE(kap.getYSpeed(), 0.0);
// 	QCOMPARE(kap.getXSpeed(), 0.0);
// 	QCOMPARE(kap.getAskedXSpeed(), 0.0);
// 	QCOMPARE(kap.getAskedYSpeed(), 0.0);
// }

void KapmanTest::testUpdateMove() {

}

QTEST_KDEMAIN_CORE(KapmanTest)