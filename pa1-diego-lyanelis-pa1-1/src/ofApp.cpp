#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	//Let's create our buttons
	RedButton = new Button(ofGetWindowWidth()/2-20,ofGetWindowHeight()/2-260,302,239,"images/RedButton.png","sounds/RedButton.mp3");
	BlueButton = new Button(ofGetWindowWidth()/2+35,ofGetWindowHeight()/2-10,236,290,"images/BlueButton.png","sounds/BlueButton.mp3");
	YellowButton = new Button(ofGetWindowWidth()/2-260,ofGetWindowHeight()/2+40,287,239,"images/YellowButton.png","sounds/YellowButton.mp3");
	GreenButton = new Button(ofGetWindowWidth()/2-260,ofGetWindowHeight()/2-260,234,294,"images/GreenButton.png","sounds/GreenButton.mp3");
	MultiplayerButton = new Button(ofGetWindowWidth()/2-500, ofGetWindowHeight()/2-365, 100, 125, "images/multiplayer.png","sounds/GreenButton.mp3");
	FreeTapGameModeButton = new Button(ofGetWindowWidth()/2+400,ofGetWindowHeight()/2-365,125,125,"images/FreeTap.png","sounds/RedButton.mp3");

	//Load the glowing images for the buttons
	redLight.load("images/RedLight.png");
    blueLight.load("images/BlueLight.png");
    yellowLight.load("images/YellowLight.png");
    greenLight.load("images/GreenLight.png");

	//Load other images
	logo.load("images/Logo.png");
	logoLight.load("images/LogoLight.png");
	startUpScreen.load("images/StartScreen.png");
	gameOverScreen.load("images/GameOverScreen.png");

    //Load Music
	backgroundMusic.load("sounds/BackgroundMusic.mp3");
	backgroundMusic.setLoop(true);
	backgroundMusic.play();

	//Initial State
	gameState = StartUp;
}
//--------------------------------------------------------------
void ofApp::update(){

	//We will tick the buttons, aka constantly update them
	//while expecting input from the user to see if anything changed
	if(gameState == PlayerInput){
		RedButton->tick();
		BlueButton->tick();
		YellowButton->tick();
		GreenButton->tick();

		//If the amount of user input equals the sequence limit
		//that means the user has successfully completed the whole
		//sequence and we can proceed with the next level
		if(userIndex == sequenceLimit){
			generateSequence();
			userIndex = 0;
			showingSequenceDuration = 0;
			gameState = PlayingSequence;
		}
	}

	if(gameState == FreeTapGameMode){
		//I need to see how to write this code
	}

	//This will take care of turning on the lights after a few
	//ticks so that they dont stay turned on forever or too long
	if(lightDisplayDuration > 0){
		lightDisplayDuration--;
		if(lightDisplayDuration <= 0){
			lightOff(RED);
			lightOff(BLUE);
			lightOff(YELLOW);
			lightOff(GREEN);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	//Create the background
    ofBackgroundGradient(ofColor(60,60,60), ofColor(10,10,10));

	//Draw the buttons
	ofSetColor(255,0,0);
	RedButton->render();
	BlueButton->render();
	YellowButton->render();
	GreenButton->render();
	FreeTapGameModeButton->render();
	
	
	//This whole if statement will take care of showing
	//the sequence to the user before accepting any input
	if(gameState == StartUp){
		MultiplayerButton->render();
	}

	if(gameState == FreeTapGameMode){
		FreeTapGameModeButton->render();
	}



	// if(gameState == PlayingSequence){
	// 	showingSequenceDuration++;
	// 	ofDrawBitmapString("hello kitten", 60,80);


	// 	if(showingSequenceDuration == 120){
	// 		color = Sequence[userIndex];
	// 	}
	
	// 	if(showingSequenceDuration == 140){
	// 		lightOff(color);
	// 		showingSequenceDuration = 60;
	// 		userIndex++;
	// 	}
	// 	if(userIndex == sequenceLimit){
	// 		lightOff(color);
	// 		userIndex = 0;
	// 		gameState = PlayerInput;
	// 	}
	// }

	else if(gameState == PlayingSequence and player1 == true){
		showingSequenceDuration++;
		ofDrawBitmapString("lol",60,80);


		if(showingSequenceDuration == 120){
			color = SequencePlayer1[UserIndexPlayer1];
		}
	
		if(showingSequenceDuration == 140){
			lightOff(color);
			showingSequenceDuration = 60;
			UserIndexPlayer1++;
		}
		if(UserIndexPlayer1 == sequenceLimit){
			lightOff(color);
			UserIndexPlayer1 = 0;
			gameState = PlayerInput;
		}
	}

	

	//StartUP (You dont need to pay much attention to this)
	//(This is only to create a animation effect at the start of the game)
	if(gameState == StartUp){
		showingSequenceDuration++;
		startUpSequence(showingSequenceDuration);
	}

	//If the statements to see see if the buttons should be lit up
	//If they are then we will draw the glowing images on top of them
	if (RedButton->GetIsLightUp()) {
		redLight.draw(ofGetWindowWidth()/2-60, ofGetWindowHeight()/2-305, 376, 329);
	}
	if (BlueButton->GetIsLightUp()) {
		blueLight.draw(ofGetWindowWidth()/2+5, ofGetWindowHeight()/2-60, 309, 376);
	} 
	if (YellowButton->GetIsLightUp()) {
		yellowLight.draw(ofGetWindowWidth()/2-300, ofGetWindowHeight()/2+5, 374, 318);
	} 
	if (GreenButton->GetIsLightUp()) {
		greenLight.draw(ofGetWindowWidth()/2-307, ofGetWindowHeight()/2-295, 315, 356);
	}

	//Part of the Start Up
	if(logoIsReady){
		logo.draw(ofGetWindowWidth()/2-160,ofGetWindowHeight()/2-150,330,330);
	}

	//Draw the game over screen
	if(gameState == GameOver){
		gameOverScreen.draw(0,0,1024,768);
	}

	//This will draw the "Press to Start" screen at the beginning
	else if(!idle && gameState == StartUp){
		startUpScreen.draw(20,0,1024,768);
	}
}


void ofApp::MultiplayerGameMode(){
	if(player1 == true){
		generateSequencePlayer1();
		UserIndexPlayer1 = 0;
		gameState = PlayingSequence;
		showingSequenceDuration = 0;
		if(checkUserInputPlayer1(color)){
			player1 = false;
			// if the checkuser input is right then player 1 would turn false (making it player2s turn) 
			// and adding it to player1 score with something like player1score++;
			//im just confused on how id be able to see if the user inputed the right color
			
		}
	if(player1 == false){
		gameState = GameOver;
	}
	}
	
};



//This function will reset the game to its initial state
//--------------------------------------------------------------
void ofApp::GameReset(){
	//This function will reset the game to its initial state
	lightOff(RED);
	lightOff(BLUE);
	lightOff(YELLOW);
	lightOff(GREEN);
	Sequence.clear();
	generateSequence();
	userIndex = 0;
	gameState = PlayingSequence;
	showingSequenceDuration = 0;
}

//--------------------------------------------------------------
void ofApp::generateSequence(){

	//This function will generate a random number between 0 and 3
	int random = ofRandom(4);
	
	//Depending on the random number, we will add a button to the sequence
	if(random == 0){
		Sequence.push_back(RED);
	}
	else if(random == 2){
		Sequence.push_back(BLUE);
	}
	else if(random == 3){
		Sequence.push_back(GREEN);
	}
	else if(random = 4){
		Sequence.push_back(YELLOW);
	}

	//We will adjust the sequence limit to the new size of the Sequence list
	sequenceLimit = Sequence.size();
}

//playing sequence para player 1
void ofApp::generateSequencePlayer1(){

	//This function will generate a random number between 0 and 3
	int random = ofRandom(4);
	
	//Depending on the random number, we will add a button to the sequence
	if(random == 0){
		SequencePlayer1.push_back(RED);
	}
	else if(random == 2){
		SequencePlayer1.push_back(BLUE);
	}
	else if(random == 3){
		SequencePlayer1.push_back(GREEN);
	}
	else if(random = 4){
		SequencePlayer1.push_back(YELLOW);
	}

	//We will adjust the sequence limit to the new size of the Sequence list
	sequenceLimit = SequencePlayer1.size();
}

// playingsquence para player2
void ofApp::generateSequencePlayer2(){

	//This function will generate a random number between 0 and 3
	int random = ofRandom(4);
	
	//Depending on the random number, we will add a button to the sequence
	if(random == 0){
		SequencePlayer2.push_back(RED);
	}
	else if(random == 2){
		SequencePlayer2.push_back(BLUE);
	}
	else if(random == 3){
		SequencePlayer2.push_back(GREEN);
	}
	else if(random = 4){
		SequencePlayer2.push_back(YELLOW);
	}

	//We will adjust the sequence limit to the new size of the Sequence list
	sequenceLimit = SequencePlayer2.size();
}


//--------------------------------------------------------------
bool ofApp::checkUserInput(Buttons input){
	//This function will varify if the user input matches the color
	//of the sequence at the current index
	
	// if(Sequence[userIndex] == input){
	// 	return true;
	// }
	// else{
	// 	return false;
	// }
}

bool ofApp::checkUserInputPlayer1(Buttons input){
	//This function will varify if the user input matches the color
	//of the sequence at the current index
	
	if(SequencePlayer1[UserIndexPlayer1] == input){
		return true;
	}
	else{
		return false;
	}
}


bool ofApp::checkUserInputPlayer2(Buttons input){
	//This function will varify if the user input matches the color
	//of the sequence at the current index
	
	if(SequencePlayer2[userIndexPlayer2] == input){
		return true;
	}
	else{
		return false;
	}
}


//--------------------------------------------------------------
void ofApp::lightOn(Buttons color){
	//This function will take care of toggling the "isLightUp" variable to
	//true for the button that matches the color, and also play the button sound
	if(color == RED){
		RedButton->toggleLightOn();
		RedButton->playSound();
	}
	else if(color == BLUE){
		BlueButton->toggleLightOn();
		BlueButton->playSound();
	}
	else if(color == YELLOW){
		YellowButton->toggleLightOn();
        YellowButton->playSound();
	}
	else if(color == GREEN){
		GreenButton->toggleLightOn();
		GreenButton->playSound();
	}
}

//--------------------------------------------------------------
void ofApp::lightOff(Buttons color){
	//This function will take care of toggling the "isLightUp" variable to false
	if(color == RED){
		RedButton->toggleLightOff();
	}
	else if(color == BLUE){
		BlueButton->toggleLightOff();
	}
	else if(color == YELLOW){
		YellowButton->toggleLightOff();
	}
	else if(color == GREEN){
		GreenButton->toggleLightOff();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	//As long as we're not in Idle OR the gameState is GameOver;
	//AND we press the SPACEBAR, we will reset the game
	if((!idle || gameState == GameOver) && tolower(key) == ' '){
		GameReset();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int mouseX, int mouseY ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	//If we're not in Idle and the gameState equals PlayerInput,
	//We will pay attention to the mousePresses from the user
	if(!idle && gameState == StartUp){
		MultiplayerButton->setPressed(x,y);
		if(MultiplayerButton->wasPressed()){
			MultiplayerGameMode();
		}
	}


	if(!idle && gameState == PlayerInput){
		//We mark the pressed button as "pressed"
		RedButton->setPressed(x,y);
		BlueButton->setPressed(x,y);
		YellowButton->setPressed(x,y);
		GreenButton->setPressed(x,y);

		//We check which button got pressed
		if(RedButton->wasPressed()){
			color = RED;
		}
		else if(BlueButton->wasPressed()){
			color = BLUE;
		}
		else if(YellowButton->wasPressed()){
			color = YELLOW;
		}
		else if(GreenButton->wasPressed()){
			color = GREEN;
		}
		//Light up the pressed button for a few ticks
		lightOn(color);
		lightDisplayDuration = 15;
			//If the user input is correct, we can continue checking
			if(checkUserInput(color)){
				userIndex++;
			}
			//If not, then we will terminate the game by 
			//putting it in the GameOver state.
			else{
				gameState = GameOver;
			}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
//--------------------------------------------------------------

//You may honestly ignore this function, shouldnt be something you need
//to change or anything. It's only for the start up animation. But ofc,
//If you wish to make something out of it or make it better, be my guest.
void ofApp::startUpSequence(int count){
	
	if(count < 200){
		GreenButton->toggleLightOn();
	}
	else if(count >= 200 && count < 260){
		GreenButton->toggleLightOff();
		RedButton->toggleLightOn();
	}
	else if(count >= 260 && count < 320){
		RedButton->toggleLightOff();
		BlueButton->toggleLightOn();
	}
	else if(count >= 320 && count < 380){
		BlueButton->toggleLightOff();
		YellowButton->toggleLightOn();
	}
	else if(count >= 380 && count < 440){
		YellowButton->toggleLightOff();
	}
	else if(count >= 440 && count < 500){
		GreenButton->toggleLightOn();
		RedButton->toggleLightOn();
		YellowButton->toggleLightOn();
		BlueButton->toggleLightOn();
	}
	else if(count >= 500 && count < 560){
		GreenButton->toggleLightOff();
		RedButton->toggleLightOff();
		YellowButton->toggleLightOff();
		BlueButton->toggleLightOff();
	}
	else if(count >= 560){
		showingSequenceDuration = 400;
	}

	//Logo Drawing
	if(logoIsReady && logoCounter > 0){
		logoCounter--;
		ofSetColor(256,256,256,logoCounter);
		logoLight.draw(ofGetWindowWidth()/2-160,ofGetWindowHeight()/2-150,330,330);
		ofSetColor(256,256,256);
	}
	if((count > 375) && !logoIsReady){
		logoCounter++;

		ofSetColor(256,256,256,logoCounter);
		logoLight.draw(ofGetWindowWidth()/2-160,ofGetWindowHeight()/2-150,330,330);

		ofSetColor(256,256,256,logoCounter);
		logo.draw(ofGetWindowWidth()/2-160,ofGetWindowHeight()/2-150,330,330);

		ofSetColor(256,256,256);
	}
	if(logoCounter >=255){
		logoIsReady = true;
		idle = false;
	}
}
