#include "MenuState.h"
#include "SceneNode.hpp"
#include "Player.h"
#include "Game.hpp"

MenuState::MenuState(StateStack& stack, State::Context context)
	: State(stack, context)
{
	mOptionIndex = 0;
}

void MenuState::buildScene()
{
	std::unique_ptr<SceneNode> backgroundSprite(new SceneNode(mContext.window, SceneNode::Type::MainMenuBackground));
	mMenuBackground = backgroundSprite.get();
	mMenuBackground->setPosition(0.0f, -0.2f, 0.0f);
	mMenuBackground->setScale(6.0, 1.0, 4.5);

	/*std::unique_ptr<SceneNode> MenuSelectSprite(new SceneNode(mContext.window, SceneNode::Type::MenuSelection));
	mMenuSelect = MenuSelectSprite.get();
	mMenuSelect->setPosition(0.0f, 1.0f, 0.0f);
	mMenuSelect->setScale(1.0, 1.0, 0.2);
	mMenuBackground->attachChild(mMenuSelect);*/

	std::unique_ptr<SceneNode> PlayPromptSprite(new SceneNode(mContext.window, SceneNode::Type::PlayPrompt));
	mPlayPrompt = PlayPromptSprite.get();
	mPlayPrompt->setPosition(0.0f, 0.2f, 0.0f);
	mPlayPrompt->setScale(1.0, 1.0, 0.2);
	mMenuBackground->attachChild(mPlayPrompt);

	std::unique_ptr<SceneNode> QuitPromptSprite(new SceneNode(mContext.window, SceneNode::Type::QuitPrompt));
	mQuitPrompt = QuitPromptSprite.get();
	mQuitPrompt->setPosition(0.0f, 0.2f, -0.5f);
	mQuitPrompt->setScale(1.0, 1.0, 0.2);
	mMenuBackground->attachChild(mQuitPrompt);

	LPCWSTR msgbuf = L"Building Menu Scene\n";
	OutputDebugString(msgbuf);

	mMenuBackground->build(stateID);
}

void MenuState::draw(Game* game)
{
}

void MenuState::update(const GameTimer& gt)
{
	timeSinceLastKeyPressed += gt.DeltaTime();
}

void MenuState::handleEvent()
{
	LPCWSTR msgbuf;
	if ((GetAsyncKeyState(VK_DOWN) & 0x8000 || GetAsyncKeyState(VK_UP) & 0x8000) && timeSinceLastKeyPressed > menuSelectionDelay)
	{
		mOptionIndex = (mOptionIndex + 1) % 2;
		timeSinceLastKeyPressed = 0.0f;
		switch (mOptionIndex) {
			case 0: 
				//mMenuSelect->setPosition(0.0f, -0.1f, 0.0f);
				msgbuf = L"Play Selected\n";
				OutputDebugString(msgbuf);
			break;
			case 1:
				//mMenuSelect->setPosition(0.0f, -0.1f, -0.5f);
				msgbuf = L"Quit Selected\n";
				OutputDebugString(msgbuf);
			break;
			default:
			break;
		}
	}
	if (GetAsyncKeyState(' ') & 0x8000)
	{
		switch (mOptionIndex) {
		case 0:
			msgbuf = L"Switching to Play Scene\n";
			mContext.window->SetRenderedState(States::ID::Game);
			OutputDebugString(msgbuf);
			break;
		case 1:
			msgbuf = L"Returning To Title\n";
			mContext.window->SetRenderedState(States::ID::Title);
			OutputDebugString(msgbuf);
			break;
		default:
			break;
		}
	}
}

void MenuState::updateOptionText()
{
}
