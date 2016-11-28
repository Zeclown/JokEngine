#pragma once
#include "Component.h"
#include "TextUI.h"
#include <iostream>
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
	virtual void Update();
	virtual void FetchSavedEntries();
	virtual void GenerateTextEntries(GameObject& TextPrototype);
	//returns whether the score is a new high score
	virtual bool CheckScore(int score);
	void SaveScores();
	virtual void RegisterNewEntry(int score);
	std::vector<TextUI*> entriesText;
	std::vector<s_LeaderBoardEntry> entries;
	std::array<glm::vec3, 10> entryColors;
	s_LeaderBoardEntry newHighscore;

private:
	void RegisterSavedEntry(s_LeaderBoardEntry Entry);
	s_LeaderBoardEntry ReadSavedEntry(std::string line);
	void OrderEntries();
	bool isWaitingName;

};