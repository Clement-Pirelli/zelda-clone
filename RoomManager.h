#pragma once
#include <array>
class Room;

class RoomManager{
public:
	RoomManager();
	~RoomManager();
	Room* getCurrentRoom();
	bool getRoomChange();
	void update();
	void addRoom(Room* givenRoom, int givenRow, int givenColumn);
	int getCurrentRow();
	int getCurrentColumn();
	void changeRoom(int givenRow, int givenColumn);
	void changeRoomFromCave();
private:
	bool roomChange = false;
	int currentRow = 0;
	int currentColumn = 0;
	static const int maxRow = 3;
	static const int maxColumn = 3;
	std::array<std::array<Room*, maxColumn>, maxRow> roomArray;
};
