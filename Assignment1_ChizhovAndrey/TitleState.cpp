#include "TitleState.hpp"
#include "SceneNode.hpp"
#include "Player.h"
#include "Game.hpp"


TitleState::TitleState(StateStack& stack, Context context)
	: State(stack, context)
{
	promptEffectTime = 0.0f;
	showPrompt = true;
}

TitleState::~TitleState()
{
}

void TitleState::buildScene()
{		
	std::unique_ptr<SceneNode> backgroundSprite(new SceneNode(mContext.window, SceneNode::Type::MenuBackground));
	mBackgroundSprite = backgroundSprite.get();
	mBackgroundSprite->setPosition(0.0f, 0.0f, 0.0f);
	mBackgroundSprite->setScale(6.0, 1.0, 4.5);

	std::unique_ptr<SceneNode> textPromptSprite(new SceneNode(mContext.window, SceneNode::Type::TitleScreenPrompt));
	mPromptText = textPromptSprite.get();
	mPromptText->setPosition(0, 1.2f, 0.0f);
	mPromptText->setScale(2.0, 1.0, 0.2);
	mBackgroundSprite->attachChild(std::move(mPromptText));

	LPCWSTR msgbuf = L"Building Title Scene\n";
	OutputDebugString(msgbuf);

	mBackgroundSprite->build(stateID);
}

void TitleState::draw(Game* game)
{
	/*
	LPCWSTR msgbuf = L"Drawing Title Scene\n";
	OutputDebugString(msgbuf);
	mBackgroundSprite->drawCurrent(game);
	if (showPrompt) mPromptText->drawCurrent(game);
	*/
}

void TitleState::update(const GameTimer& gt)
{
	promptEffectTime += gt.DeltaTime();

	if (promptEffectTime >= 0.5f)
	{
		showPrompt = !showPrompt;
		promptEffectTime = 0.0f;
	}
}

void TitleState::handleEvent()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		mContext.window->SetRenderedState(States::ID::Menu);
		LPCWSTR msgbuf =L"Switching to menu scene\n";
		OutputDebugString(msgbuf);
	}
}
