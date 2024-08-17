#include <array>
#include <cassert>
#include <iostream>
#include <limits>
#include "Random.h"


// Increase amount of new lines if your isn't
// at the very bootom of the console
constexpr int g_consoleLines{ 25 };

class Direction
{
public:
	enum Type
	{
		up,
		down,
		left,
		right,
		maxDirections,
	};

	Direction(Type type)
		: m_type(type)
	{}

	Type getType() const
	{
		return m_type;
	}

	Direction operator-() const
	{
		switch (m_type)
		{
		case up: return Direction{ down };
		case down: return Direction{ up };
		case left: return Direction{ right };
		case right: return Direction{ left };
		default: break;
		}

		assert(0 && "Unsupported direction was passed!");
		return Direction{ up };
	}

	static Direction getRandomDirection()
	{
		Type random{ static_cast<Type>(Random::get(0, Type::maxDirections - 1)) };
		return Direction{ random };
	}

private:
	Type m_type{};
};

std::ostream& operator<<(std::ostream& stream, Direction dir)
{
	switch (dir.getType())
	{
	case Direction::up: return (stream << "up");
	case Direction::down: return (stream << "down");
	case Direction::left: return (stream << "left");
	case Direction::right: return (stream << "right");
	default: break;
	}

	assert(0 && "Unsupported direction was passed!");
	return (stream << "unknown direction");
}


struct Point
{
	int x{};
	int y{};

	friend bool operator==(Point p1, Point p2)
	{
		return p1.x == p2.x && p1.y == p2.y;
	}

	friend bool operator!=(Point p1, Point p2)
	{
		return !(p1 == p2);
	}

	Point getAdjacentPoint(Direction dir) const
	{
		switch (dir.getType())
		{
		case Direction::up: return Point{ x, y - 1 };
		case Direction::down: return Point{ x, y + 1 };
		case Direction::left: return Point{ x - 1, y };
		case Direction::right: return Point{ x + 1, y };
		default: break;
		}

		assert(0 && "Unsupported direction was passed!");
		return *this;
	}
};




namespace UserInput
{
	bool isValidCommand(char ch)
	{
		return ch == 'w'
			|| ch == 'a'
			|| ch == 's'
			|| ch == 'd'
			|| ch == 'q';
	}

	void ignoreLine()
	{
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	char getCharacter()
	{
		char operation{};
		std::cin >> operation;
		ignoreLine(); // remove any extraneous input
		return operation;
	}

	char getCommandFromUser()
	{
		char ch{};
		while (!isValidCommand(ch))
			ch = getCharacter();

		return ch;
	}

	Direction charToDirection(char ch)
	{
		switch (ch)
		{
		case 'w': return Direction{ Direction::up };
		case 's': return Direction{ Direction::down };
		case 'a': return Direction{ Direction::left };
		case 'd': return Direction{ Direction::right };
		}

		assert(0 && "Unsupported direction was passed!");
		return Direction{ Direction::up };
	}
};

class Tile
{
public:
	Tile() = default;
	explicit Tile(int number)
		: m_num(number)
	{}

	bool isEmpty() const
	{
		return m_num == 0;
	}

	int getNum() const { return m_num; }

private:
	int m_num{ 0 };
};

std::ostream& operator<<(std::ostream& stream, Tile tile)
{
	if (tile.getNum() > 9)
		stream << " " << tile.getNum() << " ";
	else if (tile.getNum() > 0)
		stream << "  " << tile.getNum() << " ";
	else if (tile.getNum() == 0)
		stream << "    ";
	return stream;
}

class Board
{
public:
	Board() = default;

	static void printEmptyLines(int count)
	{
		for (int i = 0; i < count; ++i)
			std::cout << '\n';
	}

	friend std::ostream& operator<<(std::ostream& stream, const Board& board)
	{
		for (int i = 0; i < g_consoleLines; ++i)
			std::cout << '\n';

		for (int y = 0; y < s_size; ++y)
		{
			for (int x = 0; x < s_size; ++x)
				stream << board.m_tiles[y][x];
			stream << '\n';
		}

		return stream;
	}

	Point getEmptyTilePos() const
	{
		for (int y = 0; y < s_size; ++y)
			for (int x = 0; x < s_size; ++x)
				if (m_tiles[y][x].isEmpty())
					return { x, y };

		assert(0 && "There in no empty tile in the board!!!");
		return { -1, -1 };
	}

	static bool isValidPos(Point pt)
	{
		return (pt.x >= 0 && pt.x < s_size)
			&& (pt.y >= 0 && pt.y < s_size);
	}

	void swapTiles(Point pt1, Point pt2)
	{
		std::swap(m_tiles[pt1.y][pt1.x], m_tiles[pt2.y][pt2.x]);
	}

	// Compare two board to see if they are equal
	friend bool operator==(const Board& f1, const Board& f2) {
		for (int y = 0; y < s_size; ++y)
			for (int x = 0; x < s_size; ++x)
				if (f1.m_tiles[y][x].getNum() != f2.m_tiles[y][x].getNum())
					return false;

		return true;
	}

	bool moveTile(Direction dir)
	{
		Point emptyTile{ getEmptyTilePos() };
		Point adj{ emptyTile.getAdjacentPoint(-dir) };

		if (!isValidPos(adj))
			return false;

		swapTiles(adj, emptyTile);
		return true;
	}

	bool playerWon() const
	{
		static Board s_solved{};
		return s_solved == *this;
	}

	void randomize()
	{
		for (int i = 0; i < 1000;)
		{
			if (moveTile(Direction::getRandomDirection()))
				++i;
		}
	}

private:
	static const int s_size{ 4 };
	Tile m_tiles[s_size][s_size]{
		Tile{1}, Tile{2}, Tile{3}, Tile{4},
		Tile{5}, Tile{6}, Tile{7}, Tile{8},
		Tile{9}, Tile{10}, Tile{11}, Tile{12},
		Tile{13}, Tile{14}, Tile{15}, Tile{0}
	};
};


int main()
{
	Board board{};
	board.randomize();
	std::cout << board;

	while (!board.playerWon())
	{
		char ch{ UserInput::getCommandFromUser() };

		// Handle non-direction commands
		if (ch == 'q')
		{
			std::cout << "\n\nBye!\n\n";
			return 0;
		}

		// Handle direction commands
		Direction dir{ UserInput::charToDirection(ch) };

		bool userMoved{ board.moveTile(dir) };
		if (userMoved)
			std::cout << board;
	}
}