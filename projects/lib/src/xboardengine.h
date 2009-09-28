/*
    This file is part of Cute Chess.

    Cute Chess is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Cute Chess is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Cute Chess.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef XBOARDENGINE_H
#define XBOARDENGINE_H

#include "chessengine.h"

/*!
 * \brief A chess engine which uses the Xboard chess engine communication protocol.
 *
 * Xboard's specifications: http://www.tim-mann.org/xboard/engine-intf.html
 */
class LIB_EXPORT XboardEngine : public ChessEngine
{
	Q_OBJECT

	public:
		/*! Creates a new XboardEngine. */
		XboardEngine(QIODevice* ioDevice, QObject* parent = 0);

		// Inherited from ChessEngine
		void endGame(Chess::Result result);
		void makeMove(const Chess::Move& move);
		Protocol protocol() const;

	protected:
		// Inherited from ChessEngine
		bool sendPing();
		void sendQuit();
		void startProtocol();
		void startGame();
		void startThinking();
		void parseLine(const QString& line);
		void stopThinking();
		void sendOption(const QString& name, const QString& value);

	private slots:
		/*! Initializes the engine, and emits the 'ready' signal. */
		void initialize();

	private:
		void setFeature(const QString& name, const QString& val);
		void setForceMode(bool enable);
		void sendTimeLeft();
		void finishGame();
		
		bool m_forceMode;
		bool m_drawOnNextMove;
		
		// Engine features
		bool m_ftName;
		bool m_ftPing;
		bool m_ftSetboard;
		bool m_ftTime;
		bool m_ftUsermove;
		
		bool m_gotResult;
		int m_lastPing;
		Chess::Move m_nextMove;
		QString m_nextMoveString;
		Chess::MoveNotation m_notation;
		QTimer* m_initTimer;
};

#endif // XBOARDENGINE_H
