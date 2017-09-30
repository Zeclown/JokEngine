#include "LeaderBoard.h"
#include <algorithm>
#include "GameObject.h"
#include "Game.h"
LeaderBoard::LeaderBoard(GameObject * go)
	:ComponentCloneable(go)
{
	entryColors[0] = glm::vec3(255, 0, 255);
	entryColors[1] = glm::vec3(255, 255, 0);
	entryColors[2] = glm::vec3(255, 0, 0);
	entryColors[3] = glm::vec3(0, 0, 255);
	entryColors[4] = glm::vec3(0, 255, 10);
	entryColors[5] = glm::vec3(66, 137, 244);
	entryColors[6] = glm::vec3(244, 66, 161);
	entryColors[7] = glm::vec3(66, 209, 244);
	entryColors[8] = glm::vec3(244, 167, 66);
	entryColors[9] = glm::vec3(66, 244, 149);
}
void LeaderBoard::Init()
{

}


void LeaderBoard::FetchSavedEntries()
{

	std::string line;
	std::fstream scoreFile;
	scoreFile.open("scores.txt");
	if (scoreFile.is_open())
	{
		while (std::getline(scoreFile, line))
		{
			s_LeaderBoardEntry saveEntry = ReadSavedEntry(line);
			RegisterSavedEntry(saveEntry);
		}
	}
	OrderEntries();
	scoreFile.close();
}

void LeaderBoard::GenerateTextEntries(GameObject& TextPrototype)
{
	OrderEntries();
	int newScoreIndex=-1;
	for (size_t i=0;i<entries.size();i++)
	{
		GameObject* NewEntryName=Game::GetInstance().Instantiate(TextPrototype);
		GameObject* NewEntryScore = Game::GetInstance().Instantiate(TextPrototype);
		GameObject* NewEntryRank = Game::GetInstance().Instantiate(TextPrototype);
		glm::vec3 textColor = glm::normalize(entryColors[i]);
		NewEntryScore->GetComponent<TextUI>()->text= std::to_string(entries[i].score);
		NewEntryScore->GetComponent<TextUI>()->color = textColor;
		NewEntryRank->GetComponent<TextUI>()->text = "#" + std::to_string(i + 1);
		NewEntryRank->GetComponent<TextUI>()->color = textColor;
		NewEntryName->GetComponent<TextUI>()->text = entries[i].name;
		NewEntryName->GetComponent<TextUI>()->color = textColor;
		NewEntryScore->GetComponent<TextUI>()->position += glm::vec2(0, 30 + 30 * i);
		NewEntryRank->GetComponent<TextUI>()->position += glm::vec2(-130, 30 + 30 * i);
		NewEntryName->GetComponent<TextUI>()->position += glm::vec2(+130, 30 + 30 * i);
		if (entries[i].name == "HIGHSCORE")
		{
			newScoreIndex = i;
			NewEntryName->GetComponent<TextUI>()->text = "";
		}

		entriesText.push_back(NewEntryScore->GetComponent<TextUI>());
		entriesText.push_back(NewEntryRank->GetComponent<TextUI>());
		entriesText.push_back(NewEntryName->GetComponent<TextUI>());
	}
	if (newScoreIndex != -1)
	{
		input->position = entriesText[newScoreIndex * 3 + 2]->position;
		input->color = entriesText[newScoreIndex * 3 + 2]->color;
	}
}

bool LeaderBoard::CheckScore(int score)
{
	return entries.size()<(size_t)10 || (size_t)score > entries.back().score;
}

void LeaderBoard::RegisterNewEntry(int score,InputBox* box)
{
	input = box;
	isWaitingName = true;
	s_LeaderBoardEntry newEntry;
	newEntry.score = score;
	newEntry.name = "HIGHSCORE";
	RegisterSavedEntry(newEntry);
	OrderEntries();
	
}

s_LeaderBoardEntry* LeaderBoard::RegisterSavedEntry(s_LeaderBoardEntry Entry)
{
	if (entries.size() >= 10)//if we already have 10 score saved, we destroy the last one
		entries.resize(9);
	entries.push_back(s_LeaderBoardEntry(Entry));
	return &entries.back();
}

s_LeaderBoardEntry LeaderBoard::ReadSavedEntry(std::string line)
{
	std::stringstream ss;
	ss.str(line);
	//Items are saved in the following order name;score
	std::string item;
	s_LeaderBoardEntry entry;
	if (std::getline(ss, item, ';'))
	{
		entry.name = &item[0];
		std::string scoreItem;
		if (std::getline(ss, scoreItem, ';'))
		{
			entry.score = stoi(scoreItem);
		}
	}
	return entry;
}

void LeaderBoard::OrderEntries()
{
	//Order the scores from best to last
	for (int i = 0; i < (int)entries.size() - 1; i++)
	{
		if (entries[i].score<entries[i + 1].score)
		{
			iter_swap(entries.begin() + i, entries.begin() + i + 1);
			i = 0;
		}
	}
}

void LeaderBoard::SaveScores()
{
	std::fstream scoreFile;
	scoreFile.open("scores.txt");
	s_LeaderBoardEntry* newHighscore=nullptr;
	for (size_t i = 0; i<entries.size(); i++)
	{
		if (entries[i].name == "HIGHSCORE")
		{
			newHighscore = &entries[i];
		}
	}
	if (isWaitingName && input && newHighscore)
	{	
		newHighscore->name = input->text;
	}


	for (auto entry : entries)
	{
		scoreFile << entry.name << ";"<< entry.score<<"\n";
	}
	scoreFile.close();
}



