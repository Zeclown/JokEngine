#pragma once
#include "Component.h"
#include "InputBox.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <array>
struct s_LeaderBoardEntry
{
	std::string name;
	unsigned int score;
};
class LeaderBoard :public ComponentCloneable<Component, LeaderBoard>
{

public:
	LeaderBoard(GameObject *go);
	virtual void Init();
	virtual void FetchSavedEntries();
	virtual void GenerateTextEntries(GameObject& TextPrototype);
	//returns whether the score is a new high score
	virtual bool CheckScore(int score);
	void SaveScores();
	virtual void RegisterNewEntry(int score,InputBox* input);
	std::vector<TextUI*> entriesText;
	std::vector<s_LeaderBoardEntry> entries;
	std::array<glm::vec3, 10> entryColors;

private:
	s_LeaderBoardEntry* RegisterSavedEntry(s_LeaderBoardEntry Entry);
	s_LeaderBoardEntry ReadSavedEntry(std::string line);
	void OrderEntries();
	bool isWaitingName;
	InputBox* input;


};