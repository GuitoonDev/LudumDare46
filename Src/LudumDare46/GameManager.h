#pragma once

#include <core/Godot.hpp>
#include <Node.hpp>
#include <Control.hpp>
#include <core/NodePath.hpp>
#include <core/String.hpp>
#include <InputEvent.hpp>
#include <Input.hpp>
#include <SceneTree.hpp>
#include <Curve.hpp>
#include <Label.hpp>
#include <string>
#include <iostream>
#include <Timer.hpp>
#include <AudioStreamPlayer.hpp>
#include <iomanip>
#include <sstream>
#include <AnimationPlayer.hpp>

namespace godot {

	enum class GameState {
		Idle,
		Playing,
		Over
	};

	class GameManager : public Node {
		GODOT_CLASS(GameManager, Node)
	public:
		GameManager();
		~GameManager();

		//Properties
		static GameManager* GetGameManager();

		//Godot methods
		static void _register_methods();
		void _input(InputEvent* p_input);
		void _ready();
		void _init();
		void _process(float delta);

		//Game management method
		void AddPoints(const int p_points);
		void DamageFlash();
		void ReflectFlash();
		void Lose();

	private:
		const String ANIM_SCORE = "Score";
		const String ANIM_DAMAGE_FLASH = "DamageFlash";
		const String ANIM_REFLECT_FLASH = "ReflectFlash";

		int m_score;
		float m_time;
		static GameManager* m_manager;
		AnimationPlayer* m_scoreAnimation;
		AnimationPlayer* m_flashAnimation;
		GameState m_gameState;
		Label* m_scoreText;
		Label* m_timeText;
		Control* m_titleScreen;
		Control* m_defeatScreen;
		Label* m_finalScoreText;
		Label* m_finalTimeText;
		Control* m_pauseScreen;

		AudioStreamPlayer* m_startGameAudio;
		AudioStreamPlayer* m_scoreIncrementAudio;

		AudioStreamPlayer* m_musicLoopAudio;

		void StartGame();
		void SetPauseMode();
		void ReloadGame();
		void LeaveGame();
		void DisplayGameOverScreen(const bool p_display);
		void DisplayTitleScreen(const bool p_display);
	};
}
