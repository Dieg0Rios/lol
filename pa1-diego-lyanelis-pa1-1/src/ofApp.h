#pragma once

#include "ofMain.h"
#include "Button.h"


class ofApp : public ofBaseApp{

	//enums to represent game states
	enum GameState{
		StartUp,
		PlayingSequence,
		PlayerInput,
		GameOver,
		Multiplayer,
		FreeTapGameMode
	};

	public:
		//Some OpenFrameworks must-have functions
		void setup();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		//Functions for our game
		void lightOn(Buttons color);
		void lightOff(Buttons color);
		void generateSequence();
		void generateSequencePlayer1();
		void generateSequencePlayer2();
		bool checkUserInput(Buttons c);
		bool checkUserInputPlayer1(Buttons c);
		bool checkUserInputPlayer2(Buttons c);
		void GameReset();
		void startUpSequence(int count);
		void MultiplayerGameMode();
		void FreeTap();
		
	private:
		//This vector will basically act as list of button enums
		//for us to be able to store the sequences
		vector<Buttons> Sequence;
		vector<Buttons> SequencePlayer1;
		vector<Buttons> SequencePlayer2;
	

		//Let's declare the buttons we will use
		Button *RedButton;
		Button *BlueButton;
		Button *YellowButton;
		Button *GreenButton;
		Button *MultiplayerButton;
		Button *FreeTapGameModeButton;

		//These will be mere images which we will draw on top
		//of the actual buttons to give the mere illusion
		//that the original buttons are lighting up
		ofImage redLight;
		ofImage blueLight;
		ofImage yellowLight;
		ofImage greenLight;
		ofImage logo;
		ofImage logoLight;
		ofImage startUpScreen;
		ofImage gameOverScreen;
		ofImage dummy;





		//Few variables we'll need
        ofSoundPlayer backgroundMusic;
		int sequenceLimit = 1;
		int userIndex = 1;
		int UserIndexPlayer1 = 1;
		int userIndexPlayer2 = 1;
		int showingSequenceDuration = 0;
		int lightDisplayDuration = -1;
		Buttons color;
		GameState gameState;
		bool logoIsReady = false;
		int logoCounter = 0;
		bool idle = true;
		bool player1 = true;
		int player1score = 0;
		int player2score = 0;

		
};