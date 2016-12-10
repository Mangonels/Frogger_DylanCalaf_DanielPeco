#include "GUI.hh"
#include "System.hh"
#include "Logger.hh"
#include "MenuScene.hh"
#include "GameScene.hh"
using namespace Logger;

#define CELL_WIDTH 80
#define CELL_HEIGHT 80

MenuScene::MenuScene(void) {
	m_background = { { 0, 0, W.GetWidth(), W.GetHeight() }, ObjectID::BG_01 };
}

MenuScene::~MenuScene(void) {
}

void MenuScene::OnEntry(void) {
}

void MenuScene::OnExit(void) {
}

void MenuScene::Update(void) {
	static MouseCoords mouseCoords(0, 0);
	if (IM.IsMouseDown<MOUSE_BUTTON_LEFT>()) {
		Println("===============");
		Println("mxp: ", mouseCoords);
		mouseCoords = IM.GetMouseCoords();

	}
	else if (IM.IsMouseUp<MOUSE_BUTTON_LEFT>()) {
		Println("mxn: ", IM.GetMouseCoords());
		if (mouseCoords.x > 452 && mouseCoords.x < 662 && mouseCoords.y > 662 && mouseCoords.y < 715) {
			SM.SetCurScene<GameScene>();
		}
	}

	// Test InputManager key methods
	if (IM.IsKeyHold<'a'>()) Println("a hold");
	if (IM.IsKeyDown<'0'>()) Println("0 down");

	if (IM.IsKeyUp<KEY_BUTTON_DOWN>()) Println("down arrow up");
}

void MenuScene::Draw(void) {
	m_background.Draw(); // Render background
	GUI::DrawTextShaded<FontID::FACTORY>("FROGGER",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.1f), 1, 1 },
	{ 190, 0, 160 }, { 50, 200, 230 }); // Render score that will be different when updated
	GUI::DrawTextShaded<FontID::FACTORY>("with enti crush typography lol",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.2f), 1, 1 },
	{ 190, 0, 160 }, { 50, 200, 230 });

	GUI::DrawTextBlended<FontID::CANDY>("Play",
	{ W.GetWidth() >> 1, int(W.GetHeight()*.9f), 1, 1 },
	{ 115, 0, 180 }); // Render score that will be different when updated
}